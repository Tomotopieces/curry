#include <functional>
#include <iostream>
using std::function;

template<typename T, typename U, typename R>
function<T(U, R)> square = [](U a, R b) -> T { return a * a + b * b; };

template<typename T, typename U, typename R>
function<function<T(U)>(R)> squareC = [](R a) -> function<T(U)> { return [a](U b) -> T { return a * a + b * b; }; };

template<typename T, typename U, typename R>
function<function<function<T(U)>(R)>(function<T(U, R)>)> curry =
[](function<T(U, R)> func) -> function<function<T(U)>(R)> { return [func](R a) -> function<T(U)> { return [func, a](U b) -> T { return func(a, b); }; }; };

template<typename T, typename U, typename R>
function<function<T(U, R)>(function<function<T(U)>(R)>)> uncurry =
[](function<function<T(U)>(R)> func) -> function<T(U, R)> { return [func](U b, R a) -> T { return func(b)(a); }; };

int main() {
    std::cout << square<int, int, int>(3, 4) << std::endl;
    std::cout << squareC<int, int, int>(3)(4) << std::endl;
    std::cout << curry<int, int, int>(square<int, int, int>)(3)(4) << std::endl;
    std::cout << uncurry<int, int, int>(squareC<int, int, int>)(3, 4) << std::endl;

    getchar();
    return 0;
}