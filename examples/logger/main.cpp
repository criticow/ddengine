#include <ddengine/util/logger.hpp>

int main()
{
  // Debug logging (Blue)
  LOGGER_DEBUG("Hello Debug!");
  // Warn logging (Yellow)
  LOGGER_WARN("Hello Warn!");
  // Error logging (Red with file and line)
  LOGGER_ERROR("Hello Error!");
  // Critical logging (Red and white with file and line)
  LOGGER_CRITICAL("Hello Critical!");
  // Sequential replacement
  LOGGER_DEBUG("{}, {}, {}", 0, 1, 2);
  // Indexed replacement
  LOGGER_DEBUG("{0}, {1}, {2}", 0, 1, 2);
  // Scrambled indexed replacement
  LOGGER_DEBUG("{2}, {0}, {1}", 0, 1, 2);
  // Mixed replacement
  LOGGER_DEBUG("{}, {2}, {}", 0, 1, 2);
  // Assert logging (breaks the program if condition fails)
  bool condition = true;
  ASSERT(condition, "Assert true test {}, {}, {}", 1, 2, 3);
  ASSERT(!condition, "Assert false test {}, {}, {}", 1, 2, 3);
}