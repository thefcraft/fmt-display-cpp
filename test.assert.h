// test::assert.h
#ifndef TEST_ASSERT_H
#define TEST_ASSERT_H
    #include <iostream>
    #include "fmt.display.h" 
    namespace test {
        static int test_idx = 1;
        static int test_failed = 0;
        void testsFn();
        static std::string test_name = "";
        static int test_name_count_old = 0;
        static int test_name_count = 0;
        template <typename T, typename U>
        void assert_eq(T &x, U &y, std::string x_name, std::string y_name){
            int i = test::test_idx++;
            if (test_name_count == test_name_count_old){
                test_name = fmt::sprint("test case ", i);
            }
            else{
                test_name_count_old++;
            }
            if(x == y) fmt::println(ansi::green, "test ", i, " passed...\t", ansi::white,"[", x_name, ":`", x, "` == ", y_name,":`", y,"`]",
                                 ansi::bg_black, ansi::blue, "\t\tIt(", test::test_name, ")" , ansi::reset);
            else { 
                test::test_failed++; 
                fmt::println(ansi::red, "test ", i, " failed!!!", 
                        "\t[", x_name, ":`", x, "` != ", y_name,":`", y,"`]", ansi::blue, 
                        ansi::bg_black, "\t\tIt(", test::test_name, ")" , ansi::reset); 
                } 
        }
        void assert_true(bool b, std::string b_name){
            int i = test::test_idx++;
            if (test_name_count == test_name_count_old) test_name = fmt::sprint("test case ", i);
            else test_name_count_old++;
            
            if(b) fmt::println(ansi::green, "test ", i, " passed...\t", ansi::white,"[", b_name, ":`", b, "` == ", "True]",
                                 ansi::bg_black, ansi::blue, "\t\tIt(", test::test_name, ")" , ansi::reset);
            else {
                test::test_failed++;
                fmt::println(ansi::red, "test ", i, " failed!!!",
                        "\t[", b_name, ":`", b, "` != True]", ansi::blue,
                        ansi::bg_black, "\t\tIt(", test::test_name, ")" , ansi::reset);
                } 
        }
        void run_tests(){
            test::testsFn();
            fmt::println(ansi::underline, ansi::cyan, "Result", ansi::reset, " :\n\t",  ansi::green, test::test_idx-test::test_failed-1, " tests passed\n\t", ansi::red, test::test_failed, " tests failed", ansi::reset);
        }
    }
    #define assert(b) test::assert_true((bool)b, #b)
    #define asserteq(x, y) test::assert_eq(x, y, #x, #y)
    #define debug(x) std::cerr << "Debugging information: " << #x << " = " << (x) << std::endl
    #define MAKE_TESTS void test::testsFn()
    #define RUN_TESTS test::run_tests()
    #define It(...) test::test_name_count++; test::test_name = #__VA_ARGS__; if(true)
#endif
