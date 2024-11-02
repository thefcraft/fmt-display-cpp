#ifndef DOTENV_H
#define DOTENV_H

#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <optional>
#include <algorithm>

namespace dotenv
{

    class Environment
    {
    private:
        std::map<std::string, std::string> env_vars;

        static std::string trim(const std::string &str)
        {
            const auto start = str.find_first_not_of(" \t\r\n");
            if (start == std::string::npos)
                return "";

            const auto end = str.find_last_not_of(" \t\r\n");
            return str.substr(start, end - start + 1);
        }

        static std::pair<std::string, std::string> parse_line(const std::string &line)
        {
            if (line.empty() || line[0] == '#')
            {
                return {"", ""};
            }

            auto pos = line.find('=');
            if (pos == std::string::npos)
            {
                return {"", ""};
            }

            std::string key = trim(line.substr(0, pos));
            std::string value = trim(line.substr(pos + 1));

            // Remove quotes if present
            if (value.size() >= 2 &&
                ((value.front() == '"' && value.back() == '"') ||
                 (value.front() == '\'' && value.back() == '\'')))
            {
                value = value.substr(1, value.size() - 2);
            }

            return {key, value};
        }

    public:
        Environment() = default;

        bool load_dotenv(const std::string &path = ".env")
        {
            std::ifstream file(path);
            if (!file.is_open())
            {
                return false;
            }

            std::string line;
            while (std::getline(file, line))
            {
                auto [key, value] = parse_line(line);
                if (!key.empty())
                {
                    env_vars[key] = value;
                }
            }

            return true;
        }

        std::string operator[](const std::string &key) const
        {
            auto it = env_vars.find(key);
            if (it == env_vars.end())
            {
                return ""; // Return empty string if key not found
            }
            return it->second;
        }

        std::optional<std::string> get(const std::string &key) const
        {
            auto it = env_vars.find(key);
            if (it == env_vars.end())
            {
                return std::nullopt;
            }
            return it->second;
        }

        bool has(const std::string &key) const
        {
            return env_vars.find(key) != env_vars.end();
        }

        // Get all environment variables
        const std::map<std::string, std::string> &all() const
        {
            return env_vars;
        }

        // Clear all loaded environment variables
        void clear()
        {
            env_vars.clear();
        }
    };

    // Global environment instance
    inline Environment env;

} // namespace dotenv

#endif // DOTENV_H