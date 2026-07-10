#pragma once
#include "price_level.hpp"
#include <map>
#include <unordered_map>
#include <vector>
#include <functional>

class OrderBook{
public:
    //bids: highest price first. asks: lowest price first.
    using BidMap = std::map<Price,PriceLevel,std::greater<Price>>;
    using AskMap = std::map<Price,PriceLevel>;

    void add_order(Order* o);
    bool cancel_order(OrderId id);

    const BidMap& bids() const{ return bids_; }
    const AskMap& asks() const{ return asks_; }

    Price best_bid() const {return bids_.empty()? INVALID_PRICE : bids_.begin()->first; }
    Price best_ask() const {return asks_.empty()? INVALID_PRICE : asks_.begin()->first; }
private:
    BidMap bids_;
    AskMap asks_;
    std::unordered_map<OrderId,Order*> order_map_;
    
    friend class MatchingEngine;
};