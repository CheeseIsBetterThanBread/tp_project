#include "CommandLine.h"
#include <iostream>

void CommandLine::add_ship() {
  std::cout << "Enter coordinates(4) of your ship, separated by comma\n";
  std::cout << "First two should represent coordinates of one corner\n";
  std::cout << "Last two - coordinates of opposing corner\n";
  std::cout
      << "When entering coordinates be sure that you type symbol before number\n";
  bool correct = false;
  while (!correct) {
    char first_;
    std::string second_;
    char third_;
    std::string fourth_;
    try {
      std::cin >> first_ >> second_ >> third_ >> fourth_;
    } catch (...) {
      std::cout
          << "You should enter coordinates using format <symbol><number>, <symbol><number>\n";
      continue;
    }
    int first;
    int second;
    int third;
    int fourth;
    try {
      first = toupper(first_) - 'A';
      second_.pop_back();
      second = std::stoi(second_);
      third = toupper(third_) - 'A';
      fourth = std::stoi(fourth_);
    } catch (...) {
      std::cout << "You have to use symbols from A to J and numbers from 1 to 10\n";
      continue;
    }
    if (std::min({first, second, third, fourth}) < 0 ||
        std::max({first, second, third, fourth}) > 9) {
      std::cout << "You have to place your ship inside of the playing field\n";
      continue;
    }
    int size = std::abs(first - third) + std::abs(second - fourth) + 1;
    if ((first != third && second != fourth) || size > 4) {
      std::cout << "You can't use this ship in a game\n";
      continue;
    }
    if (ships_left[size] == 0) {
      std::cout << "You've placed enough of these already\n";
      continue;
    }
    --ships_left[size];
    std::string output;
    std::cout << size << std::endl;
    try {
      output = interactor_->process_request({first, second, third, fourth});
      std::cout << "i'm here" << std::endl;
    } catch (...) {
      std::cout << "Your ship intersects other ships\n";
      continue;
    }
    std::cout << output << '\n';
    correct = true;
  }
}

void CommandLine::fire_at() {
  std::cout << "Enter coordinates of the square which is going to be shot\n";
  std::cout << "Symbol should go first, followed by a number\n";
  bool correct = false;
  while (!correct) {
    char letter;
    int second;
    try {
      std::cin >> letter >> second;
    } catch (...) {
      std::cout << "Incorrect input\n";
      continue;
    }
    int first = letter - 'A';
    --second;
    if (std::min(first, second) < 0 || std::max(first, second) > 9) {
      std::cout << "You can't shoot squares outside playing field\n";
      continue;
    }
    std::string output;
    try {
      output = interactor_->process_request({first, second});
    } catch (...) {
      std::cout << "You've already tried there\n";
      continue;
    }
    correct = true;
    std::cout << output;
  }
}