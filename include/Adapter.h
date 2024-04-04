#pragma once

#include "connection/Interactor.h"
#include <vector>

class Adapter {
 public:
  Adapter();
  virtual void add_ship() = 0;
  virtual void fire_at() = 0;
  void set_interactor(Interactor* interactor);

 protected:
  Interactor* interactor_;
  std::vector<int> ships_left;
};

class CommandLine : public Adapter {
 public:
  void add_ship() override;
  void fire_at() override;
};