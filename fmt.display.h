#ifndef FMT_DISPLAY_H
#define FMT_DISPLAY_H
    #include <sstream>  // For std::ostringstream
    #include <vector> // for vector printing

    namespace ansi {
        constexpr auto reset = "\033[0m";
        constexpr auto bold = "\033[1m";
        constexpr auto underline = "\033[4m";

        constexpr auto black = "\033[30m";
        constexpr auto red = "\033[31m";
        constexpr auto green = "\033[32m";
        constexpr auto yellow = "\033[33m";
        constexpr auto blue = "\033[34m";
        constexpr auto magenta = "\033[35m";
        constexpr auto cyan = "\033[36m";
        constexpr auto white = "\033[37m";

        constexpr auto bg_black = "\033[40m";
        constexpr auto bg_red = "\033[41m";
        constexpr auto bg_green = "\033[42m";
        constexpr auto bg_yellow = "\033[43m";
        constexpr auto bg_blue = "\033[44m";
        constexpr auto bg_magenta = "\033[45m";
        constexpr auto bg_cyan = "\033[46m";
        constexpr auto bg_white = "\033[47m";
    }   
    namespace fmt {
        template<typename T>
        struct Display {
            void print(const T &data){
                std::cout<<"Not implemented yet"<<std::endl;
            }
        };
        template<typename T>
        class HasDisplay {
            private:
                // Helper type for SFINAE to detect the presence of Display<T>::print
                template<typename U>
                static auto test(int) -> decltype(Display<U>::print(std::declval<U>()), std::true_type{});
                template<typename>
                static std::false_type test(...);
            public:
                static constexpr bool value = decltype(test<T>(0))::value;
        };
        // Helper trait to check if a type has an operator<< for std::ostream
        template<typename T, typename = void>
        struct is_printable : std::false_type {};
        template<typename T>
        struct is_printable<T, std::void_t<decltype(std::cout << std::declval<T>())>> : std::true_type {};

        // Helper trait to check if a type should be printed
        template<typename T>
        struct ShouldPrint {
            static constexpr bool value = fmt::HasDisplay<T>::value;
        };
        // Implementation for types that should be printed
        template<typename T>
        inline void print_impl(const T& arg) {
            if constexpr (ShouldPrint<T>::value) {
                std::cout << Display<T>::print(arg);
            }else if constexpr (!ShouldPrint<T>::value){
                if constexpr (is_printable<T>::value) {
                    std::cout << arg;
                } else {
                    std::cout << ansi::red << "fmt::Display is not implemented yet" << ansi::reset; // Yellow warning message
                }
            }
        }
        template<typename... Args>
        inline void print(const Args&... args) {
            (print_impl(args), ...);
        }
        template<typename... Args>
        inline void println(const Args&... args) {
            (print_impl(args), ...);
            std::cout << std::endl;
        }
        
        // Implementation for types that should be printed
        template<typename T>
        inline void print_impl_oss(const T& arg, std::ostringstream &oss) {
            if constexpr (ShouldPrint<T>::value) {
                oss << Display<T>::print(arg);
            }else if constexpr (!ShouldPrint<T>::value){
                if constexpr (is_printable<T>::value) {
                    oss << arg;
                } else {
                    oss << ansi::red << "fmt::Display is not implemented yet" << ansi::reset; // Yellow warning message
                }
            }
        }
        class fmtout{
            std::ostringstream oss;
            public:
                fmtout(){}
                template<typename T>
                fmtout(const T &str){oss<<str;}
                template<typename... Args>
                inline void print(const Args&... args) {
                    (print_impl_oss(args, oss), ...);
                }
                template<typename... Args>
                inline void println(const Args&... args) {
                    (print_impl_oss(args, oss), ...);
                    oss << std::endl;
                }
                std::string str() const {
                    return oss.str();
                }
        };
        template<typename... Args>
        inline std::string sprint(const Args&... args) {
            std::ostringstream oss;
            (print_impl_oss(args, oss), ...);
            return oss.str();
        }
        template<typename... Args>
        inline std::string sprintln(const Args&... args) {
            std::ostringstream oss;
            (print_impl_oss(args, oss), ...);
            oss << std::endl;
            return oss.str();
        }
    }


    // generic functions for printing vectors
    template<typename T>
    struct fmt::Display<std::vector<T>> {
        static std::string print(const std::vector<T> &data) {
            fmt::fmtout result;
            result.print('[');
            bool first = true;
            for (const auto& item : data) {
                if (!first) result.print(", ");
                result.print(item);
                first = false;
            }
            result.print(']');
            return result.str();
        }
    };
    template<>
    struct fmt::Display<fmt::fmtout> {
        static std::string print(const fmt::fmtout &data) {
            return data.str();
        }
    };
#endif 
