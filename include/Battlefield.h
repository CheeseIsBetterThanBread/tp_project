#pragma once

#include <string>
#include <vector>

class Battlefield {
 public:
  Battlefield();
  Battlefield* get_pointer();

  static const int size_ = 10;
  static const int INF = 1'000'000'000;
  int counter_;

  std::vector<std::vector<int>> players_field_;
  std::vector<std::vector<int>> enemies_field_;
};