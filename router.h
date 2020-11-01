#include<tuple>
#include<iostream>
#include<functional>


/*
 * Trying to add support for C++14
 * https://sourceforge.net/p/predef/wiki/Standards/
 * https://en.cppreference.com/w/cpp/experimental/apply
 */
#if !defined(__cplusplus) || __cplusplus < 201703L
#include <experimental/tuple>
namespace std {
    using std::experimental::fundamentals_v1::apply;
}
#endif


template<typename... T>
std::tuple<T...> scan(const std::string& text, const std::string& pattern) {
    std::tuple<T...> values;

    std::apply(
        [&](T&... Args) {
            sscanf(text.c_str(), pattern.c_str(), &Args...);
        },
        values
    );

    return values;
}

template<typename... T>
class Route {
    public:
        using Callable = std::function<void(T...)>;
        Route(const std::string& pattern, const Callable& callable): _pattern(pattern), _callable(callable)
        {}

        void operator() (const std::string& text) {
            std::tuple<T...> values = scan<T...>(text, _pattern);

            std::apply(
                _callable,
                values
            );
        }

    private:
        std::string _pattern;
        Callable _callable;
};

// template<typename... T>
// Route<T...> make_route(const std::string& pattern, std::function<void(T...)> callable) {
//     return Route<T...>(pattern, callable);
// }