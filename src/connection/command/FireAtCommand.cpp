#pragma once

#include "FireAtCommand.h"

FireAtCommand::FireAtCommand(Battlefield* local_copy) : Command(local_copy) {}

std::string FireAtCommand::execute(std::initializer_list<int> data) {
  Command::Query request(data);
  int& flag = local_copy_->enemies_field_[request.aim.first][request.aim.second];
  if (flag == 0) {
    // can't shoot same square twice
    throw;
  }
  const int INF = local_copy_->INF;
  if (flag == INF) {
    flag = 0;
    return "Missed!";
  }
  flag *= -1;
  for (std::vector<int>& row : local_copy_->enemies_field_) {
    for (int& item : row) {
      if (item == -flag) {
        return "Got a hit!";
      }
    }
  }
  return "One more down!";
}
