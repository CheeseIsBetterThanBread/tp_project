#include "Bot.h"

#include <chrono>
#include <sstream>
#include <random>

std::vector<std::string> basic = {
    "A 1 A 1", "A 3 A 3", "A 5 A 5", "A 7 A 7",
    "D 1 D 2", "D 4 D 5", "D 7 D 8",
    "G 1 G 3", "G 5 G 7",
    "J 1 J 4"
};

std::vector<std::string> outsider = {
    "C 1 C 1", "F 10 F 10", "H 1 H 1", "J 6 J 6",
    "E 1 F 1", "C 10 D 10", "J 8 J 9",
    "A 7 A 9", "J 2 J 4",
    "A 2 A 5"
};

std::vector<std::string> isolate_ones = {
    "B 3 B 3", "E 1 E 1", "F 4 F 4", "H 2 H 2",
    "D 8 E 8", "I 6 J 6", "J 8 J 9",
    "A 6 C 6", "G 8 G 10",
    "B 10 E 10"
};

std::vector<std::string> isolate_diagonals = {
    "A 2 A 2", "C 10 C 10", "G 3 G 3", "H 9 H 9",
    "E 3 E 4", "E 8 E 9", "I 6 J 6",
    "D 1 F 1", "J 2 J 4",
    "B 4 B 7"
};

std::vector<std::vector<std::string>> layouts = {
    basic,
    outsider,
    isolate_ones,
    isolate_diagonals
};

std::vector<std::vector<std::string>> strategies = {}; // todo

Bot::Bot() : layout_index_(0), strategy_index_(0) {
  std::mt19937
      seed(std::chrono::high_resolution_clock::now().time_since_epoch().count());

  std::uniform_int_distribution
      layout_generator(0, static_cast<int>(layouts.size()) - 1);
  layout_ = layout_generator(seed);

  std::uniform_int_distribution
      strategy_generator(0, static_cast<int>(strategies.size()) - 1);
  strategy_ = strategy_generator(seed);
}

void Bot::add_ship() {
  auto coordinates = layouts[layout_][layout_index_++];
  std::istringstream iss(coordinates);
  char first_;
  int second;
  char third_;
  int fourth;
  iss >> first_ >> second >> third_ >> fourth;

  int first = first_ - 'A';
  --second;
  int third = third_ - 'A';
  --fourth;
  int size = std::abs(first - third) + std::abs(second - fourth);
  --ships_left[size];

  interactor_->process_request({first, second, third, fourth});
}

void Bot::fire_at() {} // todo

void Bot::update_field() {}

void Bot::update_enemy() {}

void Bot::finish_victory() {}

void Bot::finish_defeat() {}
