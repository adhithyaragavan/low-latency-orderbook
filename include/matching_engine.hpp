#pragma once
#include "order_book.hpp"
#include <vector>

class MatchingEngine {
public:
    void submit(Order* o,std::vector<Trade>& trades);
private:
    OrderBook book_;

    void match_limit(Order* o,std::vector<Trade>& trades);
    void match_market(Order* o,std::vector<Trade>& trades);
    void fill_against_book(Order* o,std::vector<Trade>& trades);
};