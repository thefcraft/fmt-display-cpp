#include <iostream>
#include "fmt.display.h"
#include <vector>
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
// using namespace fmt;
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
    fmt::print("Complex : ", c);
}
// Output
// [1, 2.2, 3]
// [[1, 2.2, 3], [1, 2.2, 3], [1, 2.2, 3]]
// [[[1, 2.2, 3], [1, 2.2, 3], [1, 2.2, 3]], [[1, 2.2, 3], [1, 2.2, 3], [1, 2.2, 3]], [[1, 2.2, 3], [1, 2.2, 3], [1, 2.2, 3]]]
// [1, 2.2, 3]
// [[1, 2.2, 3], [1, 2.2, 3], [1, 2.2, 3]]
// [[[1, 2.2, 3], [1, 2.2, 3], [1, 2.2, 3]], [[1, 2.2, 3], [1, 2.2, 3], [1, 2.2, 3]], [[1, 2.2, 3], [1, 2.2, 3], [1, 2.2, 3]]]
// point : (0,0)
// Complex : 3.8+1.2i
