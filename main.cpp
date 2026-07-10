
#include "matching_engine.hpp"
#include <iostream>



int main() {
    MatchingEngine engine;

    Order o1{};
    o1.id       = 1;
    o1.side     = Side::Buy;
    o1.type     = OrderType::Limit;
    o1.price    = 5000;   // $50.00 in cents
    o1.quantity = 100;
    o1.status   = OrderStatus::New;

    Order o2{};
    o2.id       = 2;
    o2.side     = Side::Sell;
    o2.type     = OrderType::Limit;
    o2.price    = 5000;
    o2.quantity = 100;
    o2.status   = OrderStatus::New;

    std::vector<Trade> trades;
    engine.submit(&o1, trades);
    engine.submit(&o2, trades);

    std::cout << "Trades executed: " << trades.size() << "\n";
    for (auto& t : trades)
        std::cout << "  Trade: qty=" << t.quantity << " @ " << t.price << "\n";

    return 0;
}