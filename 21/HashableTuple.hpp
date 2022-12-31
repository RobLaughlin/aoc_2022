#include <boost/functional/hash.hpp>
#include <tuple>

template<class... T>
struct HTuple : std::tuple<T...> {
    HTuple() : std::tuple<T...>() {}
    HTuple(T... args) : std::tuple<T...>(args...) {};
};

namespace std
{
    template<typename... T>
    struct hash<HTuple<T...>>
    {
        size_t operator()(HTuple<T...> const& arg) const noexcept
        {
            return boost::hash_value(arg);
        }
    };
};