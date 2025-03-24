// Comparable.h
#ifndef COMPARABLE_H
#define COMPARABLE_H

#include <concepts>

template<typename T>
concept Comparable = requires(T a, T b) {
    { a < b } -> std::convertible_to<bool>;
    { a > b } -> std::convertible_to<bool>;
    { a <= b } -> std::convertible_to<bool>;
    { a >= b } -> std::convertible_to<bool>;
    { a == b } -> std::convertible_to<bool>;
    { a != b } -> std::convertible_to<bool>;
};

#endif // COMPARABLE_H