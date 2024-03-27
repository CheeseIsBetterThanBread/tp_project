#pragma once

#include "Battlefield.h"
#include <string>
#include <vector>

Battlefield::Battlefield()
    : counter_(0), players_field_(size_, std::vector<int>(size_, 0)),
      enemies_field_(size_, std::vector<int>(size_, INF)) {}

Battlefield* Battlefield::get_pointer() {
  return this;
}