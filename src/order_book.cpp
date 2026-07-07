#include "order_book.hpp"

void OrderBook::add_order(Order* o){
    order_map_[o->id] = o;

    if(o->side == Side::Buy) {
        auto& level = bids_[o->price];
        level.price = o->price;
        level.add_order(o);
    }else{
        auto& level  = asks_[o->price];
        level.price = o->price;
        level.add_order(o);
    }
}

bool OrderBook::cancel_order(OrderId id) {
    auto it = order_map_.find(id);
    if(it == order_map_.end()) return false;

    Order* o = it->second;
    o->status = OrderStatus::Cancelled;

    if(o->side == Side::Buy){
        auto&level = bids_[o->price];
        level.remove_order(o);
        if(level.total_qty==0) bids_.erase(o->price);
    }else{
        auto& level = asks_[o->price];
        level.remove_order(o);
        if(level.total_qty == 0) asks_.erase(o->price);
    }
    order_map_.erase(it);
    return true;
}