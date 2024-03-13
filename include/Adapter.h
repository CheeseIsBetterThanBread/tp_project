#pragma once

#include "connection/Interactor.h"
#include <vector>

class Adapter {
 public:
  Adapter();
  void add_ship();
  void fire_at();
  void set_interactor(Interactor* interactor);

 private:
  Interactor* interactor_;
  std::vector<int> ships_left;
};