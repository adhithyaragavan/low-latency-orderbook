#pragma once
#include "order.hpp"

struct PriceLevel {
    Price price;
    Quantity total_qty;
    Order* head; //first order(matched first)
    Order* tail; //last order(newest)

    void add_order(Order* o){
        o->prev = tail;
        o->next = nullptr;
        if(tail)tail->next = o;
        else head = o;
        tail = o;
        total_qty+= o->remaining();
    }

    void remove_order(Order* o){
        if (o->prev) o->prev->next = o->next;
        else         head = o->next;
        if(o->next)o->next->prev = o->prev;
        else       tail = o->prev;
        total_qty -= o->remaining();
        o->prev = o->next = nullptr;
    }    
};