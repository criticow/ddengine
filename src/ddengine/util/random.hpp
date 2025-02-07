#pragma once

#include <ddenginepch.hpp>

class Random
{
  public:
  static std::string UUID();
  static int choose(int min, int max);
};