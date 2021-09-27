#ifndef HELPER_H
#define HELPER_H

enum class State {kEmpty, kRock, kStart, kFinish};
const int delta[4][2]{{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

bool Collision(float r1x, float r1y, float r2x, float r2y);

#endif