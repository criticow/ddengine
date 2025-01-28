#pragma once

#include <iostream>

namespace ddengine
{
  class Logger
  {
    public:
    void log(const std::string &fmt)
    {
      std::cout << fmt << std::endl;
    }
  };

  inline Logger logger;
};