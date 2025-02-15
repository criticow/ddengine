#pragma once

#include <ddenginepch.hpp>

/*
  - Logs the first argument normally if only one argument is provided
  - Replaces {} sequentially like in std::format: LOGGER_TYPE("{}, {}, {}", 0, 1, 2);
  - Replaces {0}, {1}, {2}... for the appropriate arguments: LOGGER_TYPE("{0}, {1}, {2}", 0, 1, 2);
*/

namespace ddengine
{
  class Logger
  {
    public:
    template <typename... Args>
    void debug(Args&&... args)
    {
      log(std::forward<Args>(args)...);
      std::cout << "[\033[36mDBG\033[0m]: " << buffer << std::endl;
    }

    template <typename... Args>
    void warn(Args&&... args)
    {
      log(std::forward<Args>(args)...);
      std::cout << "[\033[33mWRN\033[0m]: " << buffer << std::endl;
    }

    template <typename... Args>
    void error(const char *file, int line, Args&&... args)
    {
      log(std::forward<Args>(args)...);
      std::string cppFile = std::string(file);
      cppFile = cppFile.substr(cppFile.find_last_of("\\") + 1);
      std::cout << "[\033[31mERR\033[0m][\033[34m" << cppFile << ":" << line << "\033[0m]: " << buffer << std::endl;
    }

    template <typename... Args>
    void critical(const char *file, int line, Args&&... args)
    {
      log(std::forward<Args>(args)...);
      std::string cppFile = std::string(file);
      cppFile = cppFile.substr(cppFile.find_last_of("\\") + 1);
      std::cout << "[\033[41m\033[37mCRT\033[0m][\033[34m"<< cppFile << ":" << line << "\033[0m]: " << buffer << std::endl;
    }

    private:
    std::string buffer = "";

    void log(const auto &fmt)
    {
      std::ostringstream sstream;
      sstream << fmt;
      buffer = sstream.str();
    }

    template<typename... Args>
    void log(const std::string &fmt, Args... args)
    {
      buffer = fmt;
      size_t index = 0;
      // Replace recursively
      ((replace(index++, args)), ...);
    }

    template <typename T>
    void replace(size_t index, T value)
    {
      std::ostringstream sstream;
      if(std::is_same<T, bool>::value)
      {
        sstream << std::boolalpha << value;
      }
      else
      {
        sstream << value;
      }

      // Not indexed replacements
      size_t pos = buffer.find("{}");
      if(pos != std::string::npos)
      {
        buffer.replace(pos, 2, sstream.str());
      }

      // Indexed replacement
      pos = buffer.find("{" + std::to_string(index) + "}");
      while(pos != std::string::npos)
      {
        buffer.replace(pos, 3, sstream.str());
        pos = buffer.find("{" + std::to_string(index) + "}");
      }
    }
  };

  inline Logger logger;
};

#ifdef NDEBUG

#define LOGGER_DEBUG(...) do { } while(0)
#define LOGGER_WARN(...) do { } while(0)
#define LOGGER_ERROR(...) do { } while(0)
#define LOGGER_CRITICAL(...) do { } while(0)
#define ASSERT(condition, ...) if(condition) { do { } while(0); }

#else

#if defined(_MSC_VER)
  // For Visual Studio
  #define DEBUG_BREAK __debugbreak()
#elif defined(__GNUC__) || defined(__clang__)
  // For GCC and Clang
  #define DEBUG_BREAK __builtin_trap()
#else
  // For other compilers/platforms, you may need to adapt
  #error "Unsupported compiler/platform for DEBUG_BREAK"
#endif

#define LOGGER_DEBUG(...) ddengine::logger.debug(__VA_ARGS__)
#define LOGGER_WARN(...) ddengine::logger.warn(__VA_ARGS__)
#define LOGGER_ERROR(...) ddengine::logger.error(__FILE__, __LINE__, __VA_ARGS__)
#define LOGGER_CRITICAL(...) ddengine::logger.critical(__FILE__, __LINE__, __VA_ARGS__)
#define ASSERT(condition, ...) \
  if (!(condition)) { \
    ddengine::logger.critical(__FILE__, __LINE__, __VA_ARGS__); \
    DEBUG_BREAK; \
  }

#endif