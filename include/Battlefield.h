#pragma once

#include <memory>
#include <vector>

class Battlefield : std::enable_shared_from_this<Battlefield> {
 public:
  Battlefield();
  std::shared_ptr<Battlefield> get_pointer();
  void get_layout(const std::string& layout);

  const int size_;
  const int INF;
  int counter_;
  int alive_;

  std::vector<std::vector<int>> players_field_;
  std::vector<std::vector<int>> enemies_field_;
};