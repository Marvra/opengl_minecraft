#include <tuple>
#include <unordered_map>

struct TupleHash {
    template <typename... T>
    std::size_t operator()(const std::tuple<T...>& tup) const {
        return std::apply([](const auto&... args) {
            std::size_t seed = 0;
            ((seed ^= std::hash<std::decay_t<decltype(args)>>{}(args) + 0x9e3779b9 + (seed << 6) + (seed >> 2)), ...);
            return seed;
        }, tup);
    }
};
