// test::assert.h
#ifndef TEST_ASSERT_H
#define TEST_ASSERT_H
    #include <iostream>
    #include <stdexcept> // For std::runtime_error
    #include <algorithm>  // For std::replace
    #include "fmt\full.h" 
    namespace test {
        static int test_idx = 1;
        static int test_failed = 0;
        void testsFn();
        static std::string test_name = "";
        static int test_name_count_old = 0;
        static int test_name_count = 0;

        
        std::string replace_new_line(const std::string& str) {
            std::string result = str;  // Copy the original string to a modifiable variable
            size_t pos = 0;
            while ((pos = result.find('\n', pos)) != std::string::npos) {
                result.replace(pos, 1, "\\n");
                pos += 2;  // Skip over the newly inserted "\\n"
            }
            return result;
        }
        
        class Tin {
            std::stringstream buffer;
            std::streambuf* old_cin;
            public:
                Tin(): old_cin(nullptr) {}
                // ~Tin() { 
                //     if(old_cin) std::cin.rdbuf(old_cin); 
                // }
                void init(){ // overwrite std::cin
                    if(!old_cin) {
                        old_cin = std::cin.rdbuf();
                        std::cin.rdbuf(buffer.rdbuf());
                    }
                }
                void destroy(){ // reset std::cin
                    if(old_cin) std::cin.rdbuf(old_cin);
                    old_cin = nullptr;
                }
                template<typename... Args>
                void set(const Args&... args) {
                    ((buffer << args << '\n'), ...);
                    // init();
                }
                void clear() {
                    buffer.str("");
                    buffer.clear();
                    // destroy();
                }
        };

        class Tout {
            std::stringstream buffer;
            std::streambuf* old_cout;
            public:
                Tout(): old_cout(nullptr) {}
                // ~Tout() { 
                //     if(old_cout) std::cout.rdbuf(old_cout); 
                // }
                void init(){ // overwrite std::cout
                    if(!old_cout) {
                        old_cout = std::cout.rdbuf();
                        std::cout.rdbuf(buffer.rdbuf());
                    }
                }
                void destroy(){ // reset std::cout
                    if(old_cout) std::cout.rdbuf(old_cout);
                    old_cout = nullptr;
                }
                std::string get() const {
                    return buffer.str();
                }

                void clear() {
                    buffer.str("");
                    buffer.clear();
                    // destroy();
                }

                void assert_eq(const std::string _x, const std::string x_name){
                    this->destroy();

                    std::string x = replace_new_line(_x);
                    std::string y = replace_new_line(this->get());

                    int i = test::test_idx++;
            
                    if (test_name_count == test_name_count_old) test_name = fmt::print.sprint("test case ", i);
                    else test_name_count_old++;

                    bool pass = x.length() == y.length();
                    for (int i = 0; i < x.size(); i++){
                        if(!pass) break;
                        pass = x == y;
                    }
                    
                    if(pass) fmt::println(ansi::green, "test ", i, " passed...\t", ansi::white,"[", x_name, ":`", x, "` == ", "tout",":`", y,"`]",
                                         ansi::bg_black, ansi::blue, "\t\tIt(", test::test_name, ")" , ansi::reset);
                    else { 
                        test::test_failed++; 
                        fmt::println(ansi::red, "test ", i, " failed!!!", 
                                "\t[", x_name, ":`", x, "` != ", "tout",":`", y,"`]", ansi::blue, 
                                ansi::bg_black, "\t\tIt(", test::test_name, ")" , ansi::reset); 
                    } 
                    
                    this->init();
                }
        };

        Tin _tin;
        Tout _tout;

        void print_tests(){
            fmt::println(
                ansi::underline, ansi::cyan, "Result", ansi::reset, " :\n\t",  
                ansi::green, test::test_idx-test::test_failed-1, " tests passed\n\t", 
                ansi::red, test::test_failed, " tests failed", ansi::reset
            );
        }

        template <typename T, typename U>
        void assert_eq(const T &x, const U &y, std::string x_name, std::string y_name){
            test::_tout.destroy();
            int i = test::test_idx++;
            
            if (test_name_count == test_name_count_old) test_name = fmt::print.sprint("test case ", i);
            else test_name_count_old++;

            std::string _x = replace_new_line(fmt::print.sprint(x));
            std::string _y = replace_new_line(fmt::print.sprint(y));

            if(x == y) fmt::println(ansi::green, "test ", i, " passed...\t", ansi::white,"[", x_name, ":`", _x, "` == ", y_name,":`", _y,"`]",
                                 ansi::bg_black, ansi::blue, "\t\tIt(", test::test_name, ")" , ansi::reset);
            else { 
                test::test_failed++; 
                fmt::println(ansi::red, "test ", i, " failed!!!", 
                        "\t[", x_name, ":`", _x, "` != ", y_name,":`", _y,"`]", ansi::blue, 
                        ansi::bg_black, "\t\tIt(", test::test_name, ")" , ansi::reset); 
            } 
            test::_tout.init();
        }
        void assert_true(const bool &b, std::string b_name){
            test::_tout.destroy();
            int i = test::test_idx++;
            if (test_name_count == test_name_count_old) test_name = fmt::print.sprint("test case ", i);
            else test_name_count_old++;
            
            if(b) fmt::println(ansi::green, "test ", i, " passed...\t", ansi::white,"[", b_name, ":`", b, "` == ", "True]",
                                 ansi::bg_black, ansi::blue, "\t\tIt(", test::test_name, ")" , ansi::reset);
            else {
                test::test_failed++;
                fmt::println(ansi::red, "test ", i, " failed!!!",
                        "\t[", b_name, ":`", b, "` != True]", ansi::blue,
                        ansi::bg_black, "\t\tIt(", test::test_name, ")" , ansi::reset);
            } 
            test::_tout.init();
        }
    }
    #define assert(b) test::assert_true((bool)b, #b)
    #define asserteq(x, y) test::assert_eq(x, y, #x, #y)
    #define asserttout(b) test::_tout.assert_eq(b, #b)
    #define debug(x) std::cerr << "Debugging information: " << #x << " = " << fmt::print.sprint(x) << std::endl
    #define MAKE_TESTS void test::testsFn()
    #define RUN_TESTS test::_tin.init(); test::_tout.init(); test::testsFn(); test::_tin.clear(); test::_tout.clear(); test::_tin.destroy(); test::_tout.destroy(); test::print_tests();
    #define It(...) test::test_name_count++; test::test_name = #__VA_ARGS__; test::_tout.clear(); if(true)
    #define tout test::_tout
    #define tin test::_tin
#endif