#include <ddengine/util/color.hpp>

Color::Color(unsigned int r, unsigned int g, unsigned int b) : Color(r, g, b, 255) {};

Color::Color(unsigned int r, unsigned int g, unsigned int b, unsigned int a)
{
  // Normalize the values into [0.0, 1.0]
  this->r = r / 255.0f;
  this->g = g / 255.0f;
  this->b = b / 255.0f;
  this->a = a / 255.0f;
};

Color::Color(std::string hexColor)
{
  // Check if the string matches the hex colors format
  bool formatChecks = hexColor[0] == '#' && (hexColor.length() == 7 || hexColor.length() == 9);
  ASSERT(formatChecks, "Invalid HEX Color format, use #RRGGBB or #RRGGBBAA");

  // Add default alpha value if not provided
  if(hexColor.length() == 7)
  {
    hexColor += "FF";
  }

  unsigned int hexR;
  unsigned int hexG;
  unsigned int hexB;
  unsigned int hexA;

  // Extract the int values from the hex string into the rgba variables
  sscanf_s(hexColor.c_str(), "#%02x%02x%02x%02x", &hexR, &hexG, &hexB, &hexA);

  // Normalize values into [0.0, 1.0]
  this->r = hexR / 255.0f;
  this->g = hexG / 255.0f;
  this->b = hexB / 255.0f;
  this->a = hexA / 255.0f;
};