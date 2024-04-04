#pragma once

#include "Command.h"
#include "FireAtCommand.h"
#include "AddShipCommand.h"

Command::Command(Battlefield* local_copy) : local_copy_(local_copy) {}

Command::Query::Query(std::initializer_list<int> data) {
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

Command* Command::get_command(std::initializer_list<int> data) {
  if (data.size() == 2) {
    return new FireAtCommand(local_copy_);
  }
  return new AddShipCommand(local_copy_);
}