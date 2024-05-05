#include "Battlefield.h"

Battlefield::Battlefield()
    : size_(10), INF(1'000'000'000), counter_(0),
      players_field_(size_, std::vector<int>(size_, 0)),
      enemies_field_(size_, std::vector<int>(size_, INF)) {}

std::shared_ptr<Battlefield> Battlefield::get_pointer() {
  return shared_from_this();
}