#include <iostream>
#include "fmt.display.h"
#include <vector>
#include <map>
#include <set>
#include <optional>
#include <variant>


using namespace std;
// using namespace fmt;
class Point{
    public:
        int x, y;
        Point(int x, int y) : x(x), y(y) { }
};
template<>
struct fmt::Display<Point> {
    static std::string print(const Point &data) {
        return fmt::sprint('(', data.x, ',', data.y, ')');
    }
};
class Complex{
    public:
        float r, i;
        Complex(float r, float i) : r(r), i(i) { }
};
template<>
struct fmt::Display<Complex> {
    static std::string print(const Complex &data) {
        fmt::fmtout result;
        result.print(data.r, '+');
        result.print(data.i, 'i');
        return result.str();
    }
};
template<> 
struct fmt::Display<float>{ 
    static std::string print(const float &data) { 
        return fmt::string_format("%.2f", data);
    }
};
// template<> 
// struct fmt::Display<int>{ 
//     static std::string print(const float &data) { 
//         return fmt::sprint("Int(", data, ")");
//     }
// };
int main(){
    vector<float> f = {1.0, 2.2, 3.0};
    vector<vector<float>> p = {f, f, f};
    vector<vector<vector<float>>> pp = {p, p, p};
    fmt::println(f);
    fmt::println(p);
    fmt::println(pp);

    fmt::fmtout result;
    result.println(f, '\n', p);
    result.println(pp);
    // cout<<result.str()<<endl;
    fmt::print(result);

    Point point = Point(0, 0);
    fmt::println("point : ", point);

    Complex c = Complex(3.8, 1.2);
    fmt::println("Complex : ", c);

    map<int, vector<float>> m;
    m[0] = f;
    m[1] = f;
    m[2] = f;
    fmt::println(m);

    set<int> s = {1,2,3, 3, 3};
    fmt::println(s);

    optional<int> o;
    fmt::println(o);

    std::variant<int, float, vector<float>> myVar;
    myVar = 42;                // Holds an int
    fmt::println(myVar);
    myVar = 3.14f;             // Holds a float
    fmt::println(myVar);
    myVar = f; 
    fmt::println(myVar);
}
