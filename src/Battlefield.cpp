#pragma once

#include "../include/Battlefield.h"
#include <string>
#include <vector>

Battlefield::Battlefield()
    : counter_(0), players_field_(size_, std::vector<int>(size_, 0)),
      enemies_field_(size_, std::vector<int>(size_, INF)) {}

Battlefield* Battlefield::get_pointer() {
  return this;
}

void Battlefield::add_ship(const std::pair<int, int>& front, const std::pair<int, int>& back) {
  int left = std::max(0, std::min(front.first, back.first) - 1);
  int right = std::min(9, std::max(front.first, back.first) + 1);
  int down = std::max(0, std::min(front.second, back.second) - 1);
  int up = std::min(9, std::max(front.second, back.second) + 1);
  for (int x = left; x <= right; ++x) {
    for (int y = down; y <= up; ++y) {
      if (players_field_[x][y] != 0) {
        // ships intersect
        throw;
      }
    }
  }
  ++counter_;
  for (int x = std::min(front.first, back.first); x <= std::max(front.first, back.first); ++x) {
    for (int y = std::min(front.second, back.second); y <= std::max(front.second, back.second);
         ++y) {
      players_field_[x][y] = counter_;
    }
  }
}

std::string Battlefield::fire_at(const std::pair<int, int>& aim) {
  int& flag = enemies_field_[aim.first][aim.second];
  if (flag == 0) {
    // can't shoot same square twice
    throw;
  }
  if (flag == INF) {
    flag = 0;
    return "Missed!";
  }
  flag *= -1;
  for (std::vector<int>& row : enemies_field_) {
    for (int& item : row) {
      if (item == -flag) {
        return "Got a hit!";
      }
    }
  }
  return "One more down!";
}