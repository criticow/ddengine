#pragma once

#include <ddenginepch.hpp>

class Temporizer
{
  public:
  float deltaTime;
  float lastTime;
  bool justUpdated;
  float ms;
  float fps;

  Temporizer();
  void update();
  float getTime();
  bool hasPassed(const std::string &name, float milliseconds);
  void createTimePoint(const std::string &name);
  void clearTimepoint(const std::string &name);
  void setCooldown(const std::string &name, float milliseconds);
  float getCooldown(const std::string &name);
  bool isOnCooldown(const std::string &name);

  private:
  std::unordered_map<std::string, float> timeStorage;
  std::unordered_map<std::string, float> cooldownStorage;
  float deltaTimeSum;
  int deltaTimeCount;
  float lastUpdateTime;
  int updateDelay;
  std::chrono::high_resolution_clock::time_point timePoint;
};