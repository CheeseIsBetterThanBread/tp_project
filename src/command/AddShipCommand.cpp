#pragma once

#include "AddShipCommand.h"

std::string AddShipCommand::execute(const query& request) {
  int left = std::max(0, std::min(request.front.first, request.back.first) - 1);
  int right = std::min(9, std::max(request.front.first, request.back.first) + 1);
  int down = std::max(0, std::min(request.front.second, request.back.second) - 1);
  int up = std::min(9, std::max(request.front.second, request.back.second) + 1);
  for (int x = left; x <= right; ++x) {
    for (int y = down; y <= up; ++y) {
      if (local_copy_->players_field_[x][y] != 0) {
        // ships intersect
        throw;
      }
    }
  }
  ++local_copy_->counter_;
  for (int x = std::min(request.front.first, request.back.first);
       x <= std::max(request.front.first, request.back.first); ++x) {
    for (int y = std::min(request.front.second, request.back.second);
         y <= std::max(request.front.second, request.back.second);
         ++y) {
      local_copy_->players_field_[x][y] = local_copy_->counter_;
    }
  }
  return "Ship is placed";
}