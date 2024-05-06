#pragma once

#include "../connection/Interactor.h"

#include <memory>
#include <vector>

class Adapter {
 public:
  Adapter();
  virtual void add_ship() = 0;
  virtual void fire_at() = 0;
  virtual void update_field() = 0;
  virtual void update_enemy() = 0;

  virtual void finish_victory() = 0;
  virtual void finish_defeat() = 0;

  void set_interactor(const std::shared_ptr<Interactor>& interactor);
  static std::shared_ptr<Adapter> get_adapter(const std::string& type);

  virtual ~Adapter() = default;

 protected:
  std::shared_ptr<Interactor> interactor_;
  std::vector<int> ships_left;
};
