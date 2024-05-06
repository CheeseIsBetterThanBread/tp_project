#pragma once

#include "../connection/Interactor.h"

#include <memory>
#include <vector>

class Adapter {
 public:
  Adapter();
  virtual void add_ship();
  virtual void fire_at();
  virtual void update_field();
  virtual void update_enemy();

  void set_interactor(const std::shared_ptr<Interactor>& interactor);
  static std::shared_ptr<Adapter> get_adapter(const std::string& type);

  virtual ~Adapter() = default;

 protected:
  std::shared_ptr<Interactor> interactor_;
  std::vector<int> ships_left;
};
