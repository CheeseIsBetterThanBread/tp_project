#pragma once

#include "FireAtCommand.h"

std::string FireAtCommand::execute(const query& request) {
  int& flag = local_copy_->enemies_field_[request.aim.first][request.aim.second];
  if (flag == 0) {
    // can't shoot same square twice
    throw;
  }
  if (flag == local_copy_->INF) {
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
