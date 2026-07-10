#include "matching_engine.hpp"

void MatchingEngine::submit(Order* o,std::vector<Trade>& trades) {
    switch(o->type){
        case OrderType::Limit: match_limit(o,trades); break;
        case OrderType::Market: match_market(o,trades); break;
        case OrderType::IOC:    match_limit(o,trades); break;
                                if(!o->is_done()) o->status = OrderStatus::Cancelled;
                                break;
        case OrderType::FOK:
            //only fil if the entire quantity can be matched
            fill_against_book(o,trades);
            if(o->remaining()>0){
                // undo all fills - reject the order
                trades.clear();
                o->status = OrderStatus::Rejected;
            }
            break;

    }
}

void MatchingEngine::match_limit(Order* o,std::vector<Trade>& trades) {
    fill_against_book(o,trades);
    if(!o->is_done()) book_.add_order(o); //rest goes into the book
}
void MatchingEngine::match_market(Order* o,std::vector<Trade>& trades) {
    fill_against_book(o, trades);
    if(!o->is_done()) o->status = OrderStatus::Cancelled; // no resting market orders
}

void MatchingEngine::fill_against_book(Order* o, std::vector<Trade>& trades) {
    auto try_match = [&](auto& levels) {
        while(o->remaining()>0&& !levels.empty()){
            auto& [level_price,level] = *levels.begin();

            // limit order price check
            if (o->type == OrderType::Limit) {
                if(o->side == Side::Buy && o->price<level_price) break;
                if(o->side == Side::Sell && o->price> level_price) break;
            }
            
            Order* passive = level.head;
            while(passive && o->remaining() > 0) {
                Quantity fill_qty = std::min(o->remaining(), passive->remaining());

                trades.push_back({o->id, passive->id, level_price, fill_qty});

                o->filled_qty += fill_qty;
                passive->filled_qty += fill_qty;

                o->status = (o->remaining() == 0)?OrderStatus::Filled : OrderStatus::PartiallyFilled;
                passive->status = (passive->remaining() == 0) ? OrderStatus::Filled : OrderStatus::PartiallyFilled;

                level.total_qty -= fill_qty;

                Order* next = passive->next;
                if (passive->is_done()) level.remove_order(passive);
                passive = next;
            }
            if (level.total_qty == 0) levels.erase(levels.begin());
        }
    };
    if(o->side == Side::Buy) try_match(book_.asks_);
    else                     try_match(book_.bids_);   
}