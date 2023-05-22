#pragma once

#include "ECS.hpp"
#include <cstdio>
#include <iostream>
#include <ostream>

class PositionComponent : public Component {
private:
  int xpos, ypos;
  bool grounded = false;
  double volacty;

public:
  void init() override {
    xpos = 100;
    ypos = 0;
  };
  void setPos(int x, int y) {
    xpos = x;
    ypos = y;
  };
  void setXPos(int x) { xpos = x; };
  void setYPos(int y) { ypos = y; };
  void update() override {
    grounded = ypos < 384;
    volacty = volacty + 0.4;
    if (grounded)
      ypos = ypos + volacty;
    else
      volacty = 0;
  }
  int getXPos() { return xpos; };
  int getYPos() { return ypos; };
};
