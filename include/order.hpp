#pragma once
#include "types.hpp"

struct Order{
    OrderId id;
    Price price;
    Quantity quantity;
    Quantity filled_qty;
    Side side;
    OrderType type;
    OrderStatus status;

    Order* prev;
    Order* next;

    Quantity remaining() const { return quantity - filled_qty;}
    bool is_done() const{
        return status == OrderStatus::Filled||
               status == OrderStatus::Cancelled;

    }  
};

struct Trade {
    OrderId aggressor_id;
    OrderId passive_id;
    Price   price;
    Quantity quantity;
};
