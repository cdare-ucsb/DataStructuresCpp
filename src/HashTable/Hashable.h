#ifndef HASHABLE_H
#define HASHABLE_H


#include <concepts>
#include <functional> // for std::hash

template<typename T>
concept Hashable = requires(T a) {
    { std::hash<T>{}(a) } -> std::convertible_to<std::size_t>;
};

#endif // HASHABLE_H