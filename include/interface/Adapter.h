#pragma once

#include "../connection/Interactor.h"
#include <vector>

class Adapter {
 public:
  Adapter();
  virtual void add_ship() = 0;
  virtual void fire_at() = 0;
  void set_interactor(Interactor* interactor);
  static Adapter* get_adapter(const std::string& type);

 protected:
  Interactor* interactor_;
  std::vector<int> ships_left;
};
