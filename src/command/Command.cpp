#pragma once

#include "../../include/command/Command.h"

Command::Command(Battlefield* local_copy) : local_copy_(local_copy) {}

Command::query::query(std::initializer_list<int> data) {
  int size = static_cast<int>(data.size());
  auto iterator = data.begin();
  if (size == 2) {
    front = {0, 0};
    back = {0, 0};
    aim = {*iterator, *(++iterator)};
    return;
  }
  aim = {0, 0};
  front = {*iterator, *(++iterator)};
  ++iterator;
  back = {*iterator, *(++iterator)};
}