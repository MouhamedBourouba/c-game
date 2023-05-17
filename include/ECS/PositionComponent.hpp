#pragma once

#include "ECS.hpp"
#include <cstdio>
#include <iostream>

class PositionComponent : public Component {
private:
  int xpos, ypos;

public:
  void init() override {
    xpos = 100;
    ypos = 0;
  };
  void setPos(int x, int y) {
    xpos = x;
    ypos = y;
  };
  void update() override { xpos++; }
  int getXPos() { return xpos; };
  int getYPos() { return ypos; };
};
