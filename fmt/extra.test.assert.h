// test::assert.h
#ifndef TEST_ASSERT_H
#define TEST_ASSERT_H
    #include <iostream>
    #include <stdexcept> // For std::runtime_error
    #include <algorithm>  // For std::replace
    #include "full.h" 
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
        
        std::string join_new_line(const std::string& str) {
            return str;  // Base case for a single string
        }
        template<typename... Args>
        std::string join_new_line(const std::string& str, const Args&... args) {
            return str + "\n" + join_new_line(args...);  // Recursively join strings with newlines
        }
        // Function to show git-like diff with color and formatted output
        void show_git_diff(const std::string& expected, const std::string& actual) {
            size_t len_expected = expected.length();
            size_t len_actual = actual.length();
            size_t max_len = std::max(len_expected, len_actual);

            // Start constructing the output
            std::string expected_diff = "";
            std::string actual_diff = "";

            bool is_different = false;

            // Compare the expected and actual strings
            for (size_t i = 0; i < max_len; ++i) {
                if (i < len_expected && i < len_actual) {
                    // If the characters are the same, print them in white
                    if (expected[i] == actual[i]) {
                        expected_diff += expected[i];
                        actual_diff += actual[i];
                    } else {
                        // Characters are different, highlight differences
                        expected_diff += fmt::print.sprint(ansi::green, expected[i], ansi::reset);
                        actual_diff += fmt::print.sprint(ansi::red, actual[i], ansi::reset);
                        is_different = true;
                    }
                } else if (i < len_expected) {
                    // If actual is shorter than expected, print expected as green
                    expected_diff += fmt::print.sprint(ansi::green, expected[i], ansi::reset);
                    is_different = true;
                } else if (i < len_actual) {
                    actual_diff += fmt::print.sprint(ansi::red, actual[i], ansi::reset);
                    is_different = true;
                }
            }

            // Show the diff if there's a difference
            if (is_different) {
                fmt::println(ansi::green, "+", ansi::yellow, " '", ansi::reset, expected_diff, ansi::yellow, "'");  // Expected (green for difference)
                fmt::println(ansi::red, "-", ansi::yellow, " '", ansi::reset, actual_diff, ansi::yellow, "'");  // Actual (red for difference)
            }
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
                        
                        // Show line-by-line or character-by-character comparison:
                        show_git_diff(x, y);
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
        void assert_eq(const T &_x, const U &_y, std::string x_name, std::string y_name){
            test::_tout.destroy();
            int i = test::test_idx++;

            std::string x = replace_new_line(fmt::print.sprint(_x));
            std::string y = replace_new_line(fmt::print.sprint(_y));
            
            if (test_name_count == test_name_count_old) test_name = fmt::print.sprint("test case ", i);
            else test_name_count_old++;

            if(x == y) fmt::println(ansi::green, "test ", i, " passed...\t", ansi::white,"[", x_name, ":`", x, "` == ", y_name,":`", y,"`]",
                                 ansi::bg_black, ansi::blue, "\t\tIt(", test::test_name, ")" , ansi::reset);
            else { 
                test::test_failed++; 
                fmt::println(ansi::red, "test ", i, " failed!!!", 
                        "\t[", x_name, ":`", x, "` != ", y_name,":`", y,"`]", ansi::blue, 
                        ansi::bg_black, "\t\tIt(", test::test_name, ")" , ansi::reset); 
                // Show line-by-line or character-by-character comparison:
                show_git_diff(x, y);
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
    #define asserttout(...) test::_tout.assert_eq(test::join_new_line(__VA_ARGS__), #__VA_ARGS__)
    #define debug(x) std::cerr << "Debugging information: " << #x << " = " << fmt::print.sprint(x) << std::endl
    #define MAKE_TESTS void test::testsFn()
    #define RUN_TESTS test::_tin.init(); test::_tout.init(); test::testsFn(); test::_tin.clear(); test::_tout.clear(); test::_tin.destroy(); test::_tout.destroy(); test::print_tests();
    #define It(...) test::test_name_count++; test::test_name = #__VA_ARGS__; test::_tout.clear(); if(true)
    #define tout test::_tout
    #define tin test::_tin
#endif