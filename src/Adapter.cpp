#pragma once

#include "../include/Adapter.h"
#include <iostream>

Adapter::Adapter() : interactor_(nullptr) {
  ships_left.resize(5);
  for (int i = 1; i < 5; ++i) {
    ships_left[i] = 5 - i;
  }
}

void Adapter::set_interactor(Interactor* interactor) {
  interactor_ = interactor;
}

void Adapter::add_ship() {
  std::cout << "Enter coordinates(4) of your ship, separated by comma\n";
  std::cout
      << "First two should represent coordinates of one corner and are separated by whitespace\n";
  std::cout << "Last two - coordinates of opposing corner and are also separated by whitespace\n";
  std::cout << "When entering coordinates be sure that you type symbol before number\n";
  bool correct = false;
  while (!correct) {
    char first_;
    int second;
    char comma;
    char third_;
    int fourth;
    try {
      std::cin >> first_ >> second >> comma >> third_ >> fourth;
    } catch (...) {
      std::cout << "You have to use symbols from A to J and numbers from 1 to 10\n";
      continue;
    }
    int first = first_ - 'A';
    --second;
    int third = third_ - 'A';
    --fourth;
    if (std::min({first, second, third, fourth}) < 0 ||
        std::max({first, second, third, fourth}) > 9) {
      std::cout << "You have to place your ship inside of the playing field\n";
      continue;
    }
    int size = std::abs(first - third) + std::abs(second - fourth);
    if ((first != third && second != fourth) || size > 4) {
      std::cout << "You can't use this ship in game\n";
      continue;
    }
    if (ships_left[size] == 0) {
      std::cout << "You've placed enough of these already\n";
      continue;
    }
    --ships_left[size];
    std::string output = "plug";
    try {
      //output = interactor_->process_request({first, second, third, fourth});
    } catch (...) {
      std::cout << "Your ship intersects other ships\n";
      continue;
    }
    std::cout << output;
    correct = true;
  }
}

void Adapter::fire_at() {
  std::cout << "Enter coordinates of the square which is going to be shot\n";
  std::cout
      << "Symbol should be first, followed by whitespace after which there should be a number\n";
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
    std::string output = "plug";
    try {
      // output = interactor_->process_request({first, second});
    } catch (...) {
      std::cout << "You've already tried there\n";
      continue;
    }
    correct = true;
    std::cout << output;
  }
}