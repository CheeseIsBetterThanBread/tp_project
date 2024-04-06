#pragma once

#include <vector>

class Battlefield {
 public:
  Battlefield();
  Battlefield* get_pointer();

  const int size_;
  const int INF;
  int counter_;

  std::vector<std::vector<int>> players_field_;
  std::vector<std::vector<int>> enemies_field_;
};