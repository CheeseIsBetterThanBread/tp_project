#pragma once

#include "Adapter.h"

class Bot : public Adapter {
 public:
  Bot();
  void add_ship() override;
  void fire_at() override;
  void update_field() override;
  void update_enemy() override;
  void finish_victory() override;
  void finish_defeat() override;

 private:
  int layout_;
  int layout_index_;
  int strategy_;
  int strategy_index_;
};