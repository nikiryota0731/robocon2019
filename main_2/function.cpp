#include "sub.h"

int getAngleDeg(int nowX, int nowY, int moveX, int moveY) {
  double angle = atan2(moveY - nowY, moveX - nowX);
  if (angle < 0) {
    angle += 2 * PI;
  }
  angle = angle * 180 / PI;
  return (int)angle;
}
