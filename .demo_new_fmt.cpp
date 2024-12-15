#include "fmt/display.h"
#include "fmt/vector_large.h"
#include <iostream>
#include <vector>

#include <random>
#include <ctime>

template<> 
struct fmt::Display<float>{ 
    static std::string print(const float &data) { 
        return fmt::format_string("%.4f", data);
    }
};

int main() {
    const int dim1 = 3, dim2 = 4, dim3 = 2, dim4 = 9;
    
    std::vector<std::vector<std::vector<std::vector<float>>>> data(dim1, 
                std::vector<std::vector<std::vector<float>>>(dim2, 
                            std::vector<std::vector<float>>(dim3, 
                                        std::vector<float>(dim4))));

    std::random_device rd;
    std::mt19937 gen(rd()); // Mersenne Twister engine
    std::uniform_real_distribution<> dis(0.0, 1.0); // Generate random floats between 0.0 and 1.0

    // Populate the 4D vector with random floats
    for (int i = 0; i < dim1; ++i) {
        for (int j = 0; j < dim2; ++j) {
            for (int k = 0; k < dim3; ++k) {
                for (int l = 0; l < dim4; ++l) {
                    data[i][j][k][l] = dis(gen);
                }
            }
        }
    }

    fmt::println(data);

    fmt::println.printf("name: {}, age: {}", "laksh", 16);
    fmt::println.printf("36 in hex: {:x}", 36);
    fmt::println.printf("123.123: {:.2f}", 123.123);

    return 0;
}

// WOoo! My library is good enough to print such complex data types...

// [[[[0.1136, 0.5419, 0.6146, ..., 0.8676, 0.8374, 0.2832],
//    [0.6736, 0.7414, 0.7165, ..., 0.0780, 0.5147, 0.6606]],

//   [[0.9251, 0.7543, 0.1122, ..., 0.9922, 0.8164, 0.1025],
//    [0.6204, 0.7355, 0.6697, ..., 0.6644, 0.1097, 0.4142]],

//   [[0.7766, 0.0936, 0.6605, ..., 0.1724, 0.1668, 0.0654],
//    [0.4869, 0.1534, 0.7883, ..., 0.3910, 0.5088, 0.9367]],

//   [[0.6562, 0.7938, 0.5210, ..., 0.1712, 0.7341, 0.0932],
//    [0.4377, 0.5150, 0.0853, ..., 0.2892, 0.2956, 0.0549]]],


//  [[[0.6142, 0.1394, 0.3504, ..., 0.3466, 0.1323, 0.9954],
//    [0.0572, 0.1608, 0.9169, ..., 0.7056, 0.8058, 0.9135]],

//   [[0.6925, 0.2727, 0.5862, ..., 0.3541, 0.0258, 0.2660],
//    [0.5719, 0.6119, 0.7257, ..., 0.6159, 0.2237, 0.0903]],

//   [[0.2978, 0.2528, 0.2788, ..., 0.6682, 0.3957, 0.6564],
//    [0.8338, 0.6298, 0.8080, ..., 0.8154, 0.6620, 0.3998]],

//   [[0.8890, 0.2264, 0.6800, ..., 0.0894, 0.2206, 0.5793],
//    [0.4307, 0.1304, 0.2914, ..., 0.7028, 0.5419, 0.2948]]],


//  [[[0.5782, 0.0931, 0.0292, ..., 0.9472, 0.0619, 0.8507],
//    [0.9713, 0.4420, 0.9469, ..., 0.8423, 0.4256, 0.2517]],

//   [[0.9140, 0.0965, 0.1997, ..., 0.7112, 0.6901, 0.2793],
//    [0.2566, 0.0105, 0.3480, ..., 0.9331, 0.5373, 0.3682]],

//   [[0.0199, 0.4962, 0.4813, ..., 0.2415, 0.4349, 0.5323],
//    [0.2165, 0.6648, 0.9838, ..., 0.5700, 0.4818, 0.5977]],

//   [[0.8588, 0.9529, 0.5630, ..., 0.9118, 0.2560, 0.1053],
//    [0.1198, 0.0544, 0.7275, ..., 0.5693, 0.6271, 0.2282]]]]