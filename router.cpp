#include<tuple>
#include<iostream>
#include<functional>


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

template<typename... Ts>
std::ostream& operator<<(std::ostream& os, std::tuple<Ts...> const& theTuple)
{
    std::apply
    (
        [&os](Ts const&... tupleArgs)
        {
            os << '[';
            std::size_t n{0};
            ((os << tupleArgs << (++n != sizeof...(Ts) ? ", " : "")), ...);
            os << ']';
        }, theTuple
    );
    return os;
}

template <typename... T>
int sum(T... vals) {
    return (vals + ...);
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

int main()
{
    std::cout << scan<int, int, float>("hello 52 world 34 final 9.0", "hello %d world %d final %f") << std::endl;
    std::cout << std::tuple(3, 43, 5.9) << std::endl;
    std::cout << sum(1, 2, 3, 4, 5) << std::endl;

    Route<int, int, float> route(
        "hello %d world %d final %f",
        [](int a, int b, float c) {
            std::cout << a << " - " << b  << " " << c << std::endl;
    });

    route("hello 52 world 34 final 9.0");

    return 0;
}

