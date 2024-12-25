// fmt::display.h
#ifndef FMT_DISPLAY_H
#define FMT_DISPLAY_H
    
// Uncomment the following line if you want to use runtime type checking (not recommended due to harder error location).
// #define FMT_DISPLAY_COMPILE_TIME_ERROR 

#include <sstream>  // For std::ostringstream
#include <type_traits> // For type trait utilities
#include <typeinfo> // For typeid
#include <memory> // For std::unique_ptr
#include <stdexcept> // For std::runtime_error
#include <iostream> // For std::cout

#include <algorithm>
#include <bitset>
#include <iomanip>

namespace ansi {
    // ANSI escape codes for text formatting
    constexpr auto reset = "\033[0m";             // Reset style
    constexpr auto bold = "\033[1m";              // Bold
    constexpr auto italic = "\033[3m";            // Italic
    constexpr auto underline = "\033[4m";         // Underline
    constexpr auto blink = "\033[5m";             // Blink
    constexpr auto reverse = "\033[7m";           // Reverse colors
    constexpr auto hidden = "\033[8m";            // Hidden text
    constexpr auto strikethrough = "\033[9m";     // Strikethrough

    // ANSI escape codes for text colors
    constexpr auto black = "\033[30m";            // Black
    constexpr auto red = "\033[31m";              // Red
    constexpr auto green = "\033[32m";            // Green
    constexpr auto yellow = "\033[33m";           // Yellow
    constexpr auto blue = "\033[34m";             // Blue
    constexpr auto magenta = "\033[35m";          // Magenta
    constexpr auto cyan = "\033[36m";             // Cyan
    constexpr auto white = "\033[37m";            // White

    // ANSI escape codes for background colors
    constexpr auto bg_black = "\033[40m";         // Black background
    constexpr auto bg_red = "\033[41m";           // Red background
    constexpr auto bg_green = "\033[42m";         // Green background
    constexpr auto bg_yellow = "\033[43m";        // Yellow background
    constexpr auto bg_blue = "\033[44m";          // Blue background
    constexpr auto bg_magenta = "\033[45m";       // Magenta background
    constexpr auto bg_cyan = "\033[46m";          // Cyan background
    constexpr auto bg_white = "\033[47m";         // White background
}

namespace fmt {

    // Helper function for safe string formatting
    template<typename ... Args>
    std::string format_string(const std::string& format, Args ... args) {
        int size_s = std::snprintf(nullptr, 0, format.c_str(), args ...) + 1; // +1 for null terminator
        if (size_s <= 0) {
            throw std::runtime_error("\033[31mError during formatting.\033[0m");
        }
        size_t size = static_cast<size_t>(size_s);
        std::unique_ptr<char[]> buffer(new char[size]);
        std::snprintf(buffer.get(), size, format.c_str(), args ...);
        return std::string(buffer.get(), buffer.get() + size - 1); // Exclude the null terminator
    }
    
    // Base Display template class (not implemented yet)
    template<typename T>
    struct Display {
        void print(const T &data){
            std::cout<<"Not implemented yet"<<std::endl;
        }
    };

    namespace detail {
        // Helper type to check if T has operator<< for std::ostream i.e., for std::cout
        template<typename T>
        struct is_printable{
            private:
                template<typename U>
                static auto test(int) -> decltype(std::declval<std::ostream&>()<<(std::declval<U>()), std::true_type{});
                template<typename>
                static std::false_type test(...);
            public:
                static constexpr bool value = decltype(test<T>(0))::value;
        };

        // Helper trait to detect if a type has a custom Display specialization i.e., struct fmt::Display<XXX>
        template<typename T>
        struct ShouldPrint {
            private:
                template<typename U>
                static auto test(int) -> decltype(Display<U>::print(std::declval<U>()), std::true_type{});
                template<typename>
                static std::false_type test(...);
            public:
                static constexpr bool value = decltype(test<T>(0))::value;
        };        

        // Common implementation for printing types to a given stream
        template<typename T, typename Stream>
        inline void _print_impl_to_stream(const T& arg, Stream& stream) {
            #ifdef FMT_DISPLAY_COMPILE_TIME_ERROR
                static_assert(ShouldPrint<T>::value || is_printable<T>::value, 
                    "\033[34m\n\n \
                    \n********************************************************************** \033[0m\033[31m \
                    \nError: fmt::Display is not implemented for some type. \
                    \nPlease implement the appropriate traits for this type. \
                    \nIf you are using a custom type, consider adding fmt::Display<T> specialization. \
                    \n\033[34m********************************************************************** \
                    \n\n\033[0m");
            #endif

            if constexpr (ShouldPrint<T>::value) {
                stream << Display<T>::print(arg);  // Custom printing via Display trait
            } else {
                #ifdef FMT_DISPLAY_COMPILE_TIME_ERROR
                    stream << arg;
                #else
                    if constexpr (is_printable<T>::value) {
                        stream << arg;  // Standard stream printing
                    } else {
                        stream << std::endl << std::endl 
                               << ansi::red << "Error : fmt::Display is not implemented for type : " 
                               << typeid(T).name() << ansi::reset << std::endl << std::endl;
                        throw std::runtime_error("fmt::Display is not implemented yet");
                    }
                #endif
            }
        }

        // Overload for printing to std::cout
        template<typename T>
        inline void print_impl(const T& arg) {
            _print_impl_to_stream(arg, std::cout);
        }
        
        // Overload for printing to std::ostringstream
        template<typename T>
        inline void print_impl_oss(const T& arg, std::ostringstream &oss) {
            _print_impl_to_stream(arg, oss);
        }
    }   // End of namespace detail

    // fmtout class for formatted output with depth tracking
    class fmtout {
        private:
            std::ostringstream oss;

        public:
            void *data;
            size_t data_size;

            fmtout(void *data = nullptr, size_t data_size = 0): data(data), data_size(data_size) {}
            
            // Overloaded operator<< to handle output
            template<typename T>
            fmtout& operator<<(const T& value) {
                detail::print_impl_oss(value, oss);
                return *this;
            }

            // Print multiple arguments
            template<typename... Args>
            inline void print(const Args&... args) {
                (detail::print_impl_oss(args, oss), ...);
            }

            // Print with a newline
            template<typename... Args>
            inline void println(const Args&... args) {
                (detail::print_impl_oss(args, oss), ...);
                oss << std::endl;
            }

            // Convert the output to a string
            std::string str() const { return oss.str(); }

            // Clear the string and return it
            std::string clear_str() { 
                std::string result = oss.str(); 
                clear(); 
                return result; 
            }

            // Clear the output buffer
            void clear() { oss.str(""); oss.clear(); }
    };
    
    // TODO: BETA NAMESPACE
    namespace __format_namespace{
        // template <typename T>
        // inline void f_octal(fmt::fmtout &oss, const T& value){
        //     oss << std::oct << value;
        // }
        // template <typename T>
        // inline void f_bin(fmt::fmtout &oss, const T& value){
        //     oss << std::bitset<16>(value);
        // }
        // template <typename T>
        // inline void f_hex(fmt::fmtout &oss, const T& value){
        //     oss << std::hex << value;
        // }
        // template <typename T>
        // inline void f_scientific(fmt::fmtout &oss, const T& value){
        //     oss << std::scientific << value;
        // }
        // template <typename T>
        // inline void f_fixed(fmt::fmtout &oss, const T& value){
        //     oss << std::fixed << value;
        // }
        // Helper function to format individual values
        template <typename T>
        std::string formatValue(const T& value, const std::string& format) {
            fmt::fmtout oss;
            if (format.empty() || format.length() == 1) {
                oss << value;
                return oss.clear_str();
            }
            if (format.length() == 2 && format[0] == '!' && format[1] == 'r') { // {!r} => 'value'
                oss << '\'' << value << '\'';
                return oss.clear_str();
            }
            
            if (format[0] != ':') {
                oss << value;
                // std::cout<<"\033[31mError: Unknown format {"<<format<<"}\033[0m";
                // throw std::runtime_error("\033[31mError during formatting.\033[0m"); // In case unknown specific format 
            }
            // // if (format.length() == 2 && format[1] == '_') {
            // //     oss << "1_000_000";
            // // }else if (format.length() == 2 && format[1] == ',') {
            // //     oss << "1,000,000";
            // // }else 
            // if (format.length() == 2 && format[1] == 'o') {
            //     f_octal(oss, value);
            // }else if (format.length() == 2 && format[1] == 'b') {
            //     f_bin(oss, value);
            // }else if (format.length() == 2 && format[1] == 'x') {
            //     f_hex(oss, value);
            // }else if (format.length() == 2 && format[1] == 'e') {
            //     f_scientific(oss, value);
            // }else if (format.length() == 2 && format[1] == 'f') {
            //     f_fixed(oss, value);
            // }else 
            else if (format.length() == 3 && format[1] == '!' && format[2] == 'r') { // {:!r} => 'value'
                oss << '\'' << value << '\'';
            }
            // else if (format.length() >= 3 && format[2] == '<') {
            //     int width = std::stoi(format.substr(3));
            //     oss << std::left << std::setfill(format[1]) << std::setw(width) << value;
            // }else if (format.length() >= 3 && format[2] == '>') {
            //     int width = std::stoi(format.substr(3));
            //     oss << std::right << std::setfill(format[1]) << std::setw(width) << value;
            // }else if (format.length() >= 3 && format[2] == '^') {
            //     int width = std::stoi(format.substr(3));
            //     oss << std::internal << std::setfill(format[1]) << std::setw(width) << value;
            // }else if (format[1] == '<') {
            //     int width = std::stoi(format.substr(2));
            //     oss << std::left << std::setw(width) << value;
            // }else if (format[1] == '>') {
            //     int width = std::stoi(format.substr(2));
            //     oss << std::right << std::setw(width) << value;
            // }else if (format[1] == '^') {
            //     int width = std::stoi(format.substr(2));
            //     oss << std::internal << std::setw(width) << value;
            // }else if (format[1] == '.' && format[format.length()-1] == 'f') {
            //     int precision = std::stoi(format.substr(2, format.length()-2));
            //     oss << std::fixed << std::setprecision(precision) << value;
            // }
            else{
                oss << value;
                // std::cout<<"\033[31mError: Unknown format {"<<format<<"}\033[0m";
                // throw std::runtime_error("\033[31mError during formatting.\033[0m"); // In case unknown specific format 
            }
            return oss.clear_str();
        }


        // Base case: no arguments left to process
        void formatImpl(std::string::size_type pos, std::string& result) {}

        // Recursive case: process each argument and format accordingly
        template <typename Arg, typename... Args>
        void formatImpl(std::string::size_type pos, std::string& result, const Arg& arg, const Args&... args) {
            pos = result.find("{", pos);  // Find the next placeholder
            std::string::size_type end = result.find("}", pos+1);
            if (pos == std::string::npos || end == std::string::npos) return;
            while (true){
                std::string::size_type start = result.find("{", pos+1);
                if (start == std::string::npos || start > end) break;
                pos = start;
            }
            std::string specifier = result.substr(pos + 1, end - pos - 1);
            specifier.erase(std::remove(specifier.begin(), specifier.end(), ' '), specifier.end()); // remove all space
            result.replace(pos, end - pos + 1, 
                           formatValue(arg, specifier));
            formatImpl(end, result, args...);  // Recursively process the remaining arguments
        }
    };

    // PrintFormatter class for customized print formatting
    class PrintFormatter{
        private:
            std::string sep;  // Separator between arguments
            std::string end;  // End of line (e.g., newline)
        public:
            // Constructor with optional separator and end-of-line
            PrintFormatter(const std::string& sep = "", const std::string& end = "")
                        : sep(sep), end(end) {}

            // Getter for separator
            std::string separator() const { return sep; }

            // Getter for end of line
            std::string end_of_line() const { return end; }

            // Setter for separator
            void set_separator(const std::string& sep) {
                this->sep = sep;
            }

            // Setter for end of line
            void set_end_of_line(const std::string& end) {
                this->end = end;
            }

            // Print with separator and end of line
            template<typename T, typename... Args>
            inline void print(const T& first, const Args&... args) {
                detail::print_impl(first);
                if (sep != "") ((std::cout << sep, detail::print_impl(args)), ...);
                else (detail::print_impl(args), ...);
                if (end != "") std::cout << end;
            }

            // Return formatted string
            template<typename T, typename... Args>
            inline std::string sprint(const T& first, const Args&... args) {
                std::ostringstream oss;
                detail::print_impl_oss(first, oss);
                if (sep != "") ((oss << sep, detail::print_impl_oss(args, oss)), ...);
                else (detail::print_impl_oss(args, oss), ...);
                if (end != "") oss << end;
                return oss.str();
            }
            
            // TODO: BETA FUNCTION
            template<typename... Args>
            inline void printf(const std::string& str, const Args&... args) {
                std::string result = str;
                std::string::size_type pos = 0;
                __format_namespace::formatImpl(pos, result, args...);  // Start the recursive formatting
                std::cout << result;
                if (end != "") std::cout << end;
            }
            // TODO: BETA FUNCTION
            template<typename... Args>
            inline std::string sprintf(const std::string& str, const Args&... args) {
                std::ostringstream oss;
                std::string result = str;
                std::string::size_type pos = 0;
                __format_namespace::formatImpl(pos, result, args...);  // Start the recursive formatting
                oss << result;
                if (end != "") oss << end;
                return oss.str();
            }
            
            // Operator() to print the formatted output
            template<typename T, typename... Args>
            inline void  operator()(const T& first, const Args&... args) {
                this->print(first, args...);
            }
            
            // Operator() to print just the end of line if no arguments
            inline void operator()() {
                if (end != "") std::cout << end;
            }
        };

    // Global instances of PrintFormatter
    fmtout fout;
    PrintFormatter print = PrintFormatter("", "");
    PrintFormatter println = PrintFormatter("", "\n");
}

// Specialization of Display for fmtout type
template<>
struct fmt::Display<fmt::fmtout> {
    static std::string print(const fmt::fmtout &data) {
        return data.str();
    }
};

#endif // FMT_DISPLAY_H
