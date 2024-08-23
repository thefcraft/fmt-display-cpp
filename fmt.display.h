#ifndef FMT_DISPLAY_H
#define FMT_DISPLAY_H
    #include <sstream>  // For std::ostringstream
    #include <type_traits> // ?
    #include <typeinfo> // ?
    #include <memory>
    #include <stdexcept>

    namespace ansi {
        // ANSI styles
        constexpr auto reset = "\033[0m";
        constexpr auto bold = "\033[1m";
        constexpr auto italic = "\033[3m";
        constexpr auto underline = "\033[4m";
        constexpr auto blink = "\033[5m";
        constexpr auto reverse = "\033[7m";
        constexpr auto hidden = "\033[8m";
        constexpr auto strikethrough = "\033[9m";

        // ANSI text colors
        constexpr auto black = "\033[30m";
        constexpr auto red = "\033[31m";
        constexpr auto green = "\033[32m";
        constexpr auto yellow = "\033[33m";
        constexpr auto blue = "\033[34m";
        constexpr auto magenta = "\033[35m";
        constexpr auto cyan = "\033[36m";
        constexpr auto white = "\033[37m";

        // ANSI background colors
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
        template<typename ... Args>
        std::string string_format( const std::string& format, Args ... args ){
            int size_s = std::snprintf( nullptr, 0, format.c_str(), args ... ) + 1; // Extra space for '\0'
            if( size_s <= 0 ){ throw std::runtime_error( "Error during formatting." ); }
            auto size = static_cast<size_t>( size_s );
            std::unique_ptr<char[]> buf( new char[ size ] );
            std::snprintf( buf.get(), size, format.c_str(), args ... );
            return std::string( buf.get(), buf.get() + size - 1 ); // We don't want the '\0' inside
        }

        template<typename T>
        struct Display {
            void print(const T &data){
                std::cout<<"Not implemented yet"<<std::endl;
            }
        };
        namespace detail {
            // Helper trait to check if a type has an operator<< for std::ostream
            template<typename T, typename = void>
            struct is_printable : std::false_type {};
            template<typename T>
            struct is_printable<T, std::void_t<decltype(std::declval<std::ostream&>() << std::declval<T>())>> : std::true_type {};
    
            template<typename T>
            struct has_display {
                private:
                    // Helper type for SFINAE to detect the presence of Display<T>::print
                    template<typename U>
                    static auto test(int) -> decltype(Display<U>::print(std::declval<U>()), std::true_type{});
                    template<typename>
                    static std::false_type test(...);
                public:
                    static constexpr bool value = decltype(test<T>(0))::value;
            };        
            // Helper trait to check if a type should be printed
            template<typename T>
            struct ShouldPrint {
                static constexpr bool value = has_display<T>::value;
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
                        std::cout << std::endl << std::endl << ansi::red << "Error : fmt::Display is not implemented for type : " << typeid(T).name() << ansi::reset << std::endl << std::endl ; // Red Error message
                        throw std::runtime_error( "fmt::Display is not implemented yet" ); 
                    }
                }
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
                        // oss << ansi::red << "Error : fmt::Display is not implemented yet" << ansi::reset; // Red Warning message
                        std::cout << std::endl << std::endl << ansi::red << "Error : fmt::Display is not implemented for type : " << typeid(T).name() << ansi::reset << std::endl << std::endl ; // Red Error message
                        throw std::runtime_error( "fmt::Display is not implemented yet" ); 
                    }
                }
            }
        }    
        template<typename... Args>
        inline void print(const Args&... args) {
            (detail::print_impl(args), ...);
        }
        template<typename... Args>
        inline void println(const Args&... args) {
            (detail::print_impl(args), ...);
            std::cout << std::endl;
        }
        template<typename... Args>
        inline std::string sprint(const Args&... args) {
            std::ostringstream oss;
            (detail::print_impl_oss(args, oss), ...);
            return oss.str();
        }
        template<typename... Args>
        inline std::string sprintln(const Args&... args) {
            std::ostringstream oss;
            (detail::print_impl_oss(args, oss), ...);
            oss << std::endl;
            return oss.str();
        }
        
        class fmtout{
            std::ostringstream oss;
            public:
                fmtout(){}
                template<typename T>
                fmtout(const T &str){oss<<str;}

                template<typename T>
                fmtout& operator<<(const T& value) {
                    detail::print_impl_oss(value, oss);
                    return *this;
                }

                template<typename... Args>
                inline void print(const Args&... args) {
                    (detail::print_impl_oss(args, oss), ...);
                }
                template<typename... Args>
                inline void println(const Args&... args) {
                    (detail::print_impl_oss(args, oss), ...);
                    oss << std::endl;
                }
                std::string str() const { return oss.str(); }
                void clear() { oss.str(""); oss.clear(); }
        };
        
    }

    template<>
    struct fmt::Display<fmt::fmtout> {
        static std::string print(const fmt::fmtout &data) {
            return data.str();
        }
    };

    // Display specializations for standard containers
    #include <vector> // for vector printing
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
    #include <map>
    template<typename K, typename V>
    struct fmt::Display<std::map<K, V>> {
        static std::string print(const std::map<K, V>& map) {
            fmt::fmtout out;
            out << "{";
            bool first = true;
            for (const auto& [key, value] : map) {
                if (!first) out << ", ";
                out << key << ": " << value;
                first = false;
            }
            out << "}";
            return out.str();
        }
    };
    #include <set>
    template<typename T>
    struct fmt::Display<std::set<T>> {
        static std::string print(const std::set<T>& set) {
            fmtout out;
            out << "{";
            bool first = true;
            for (const auto& value : set) {
                if (!first) out << ", ";
                out << value;
                first = false;
            }
            out << "}";
            return out.str();
        }
    };
    #if __cplusplus >= 201703L // C++17 or newer
        #include <optional>
        template<typename T>
        struct fmt::Display<std::optional<T>> {
            static std::string print(const std::optional<T>& opt) {
                if (opt) return sprint("Some(", *opt, ")");
                else return "None";
            }
        };
        #include <variant>
        template<typename... Types>
        struct fmt::Display<std::variant<Types...>> {
            static std::string print(const std::variant<Types...>& var) {
                return std::visit([](const auto& value) {
                    return sprint("Variant(", value, ")");
                }, var);
            }
        };
    #endif // __cplusplus >= 201703L
#endif 
