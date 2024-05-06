#include "Battlefield.h"

Battlefield::Battlefield()
    : size_(10), INF(1'000'000'000), counter_(0),
      players_field_(size_, std::vector<int>(size_, 0)),
      enemies_field_(size_, std::vector<int>(size_, INF)) {}

std::shared_ptr<Battlefield> Battlefield::get_pointer() {
  return shared_from_this();
}

void Battlefield::get_layout(const std::string& layout) {
  for (int counter = 0; counter < 10; ++counter) {
    int row_low = layout[4 * counter] - '0';
    int column_low = layout[4 * counter + 1] - '0';
    int row_high = layout[4 * counter + 2] - '0';
    int column_high = layout[4 * counter + 3] - '0';
    for (int row = row_low; row <= row_high; ++row) {
      for (int column = column_low; column <= column_high; ++column) {
        enemies_field_[row][column] = counter + 1;
      }
    }
  }
}