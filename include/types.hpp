#pragma once
#include <cstdint>
#include <limits>

using OrderId = uint64_t;
using Price = int64_t; // fixed-point
using Quantity = uint64_t;

constexpr Price INVALID_PRICE = std::numeric_limits<Price>::min();
constexpr OrderId INVALID_ORDER_ID = 0;
constexpr Quantity INVALID_QTY = 0;

enum class Side: uint8_t {Buy,Sell};

enum class OrderType : uint8_t {
    Limit,
    Market,
    IOC,
    FOK,
};

enum class OrderStatus : uint8_t {
    New,
    PartiallyFilled,
    Filled,
    Cancelled,
    Rejected,
};
