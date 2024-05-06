#pragma once

#include "Adapter.h"

class CommandLine : public Adapter {
 public:
  void add_ship() override;
  void fire_at() override;
  void update_field() override;
  void update_enemy() override;
};