#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <vector>
#include "player.h"
#include "sandWorm.h"
#include "helper.h"

class Controller {
 public:
  void HandleInput(bool &running, Player &player, std::vector<std::vector<State>> &grid) const;
  void HandleInput(bool &running, SandWorm &sandWorm, Player &player, std::vector<std::vector<State>> &grid) const; 

 private:
  void ChangeDirection(Player &player, Player::Direction input,
                       Player::Direction opposite) const;
  void ChangeDirection(SandWorm &sandWorm, SandWorm::Direction input) const;
};

#endif
