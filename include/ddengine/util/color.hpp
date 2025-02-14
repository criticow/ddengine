#pragma once

#include <ddenginepch.hpp>

class Color : public glm::vec4
{
  public:
  Color(){};
  Color(unsigned int r, unsigned int g, unsigned int b);
  Color(unsigned int r, unsigned int g, unsigned int b, unsigned int a);
  Color(std::string hexColor);
};