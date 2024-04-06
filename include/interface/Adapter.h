#pragma once

#include "../connection/Interactor.h"
#include <vector>

class Adapter {
 public:
  Adapter();
  virtual void add_ship();
  virtual void fire_at();
  void set_interactor(Interactor* interactor);
  static Adapter* get_adapter(const std::string& type);

  virtual ~Adapter() = default;

 protected:
  Interactor* interactor_;
  std::vector<int> ships_left;
};
