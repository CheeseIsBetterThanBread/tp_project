#include "CommandLine.h"

#include <iostream>

std::string convert(int number) {
  std::string answer;
  while (number > 0) {
    answer += '0' + number % 10;
    number /= 10;
  }
  std::reverse(answer.begin(), answer.end());
  return answer;
}

void print(const std::vector<std::vector<std::string>>& display) {
  const int size = 10;
  std::string separator = "|";
  std::string answer;
  std::string head = " ";
  std::string filler = "--";
  for (int i = 1; i <= 10; ++i) {
    head += separator + convert(i);
    filler += "--";
  }
  head += '\n';
  filler += '\n';
  answer += head;
  for (int row = 0; row < size; ++row) {
    answer += filler;
    answer += 'A' + row;
    answer += separator;
    for (int column = 0; column < size; ++column) {
      answer += display[row][column] + separator;
    }
    answer += '\n';
  }
  std::cout << answer;
}

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
      second = std::stoi(second_) - 1;
      third = toupper(third_) - 'A';
      fourth = std::stoi(fourth_) - 1;
    } catch (...) {
      std::cout
          << "You have to use symbols from A(a) to J(j) and numbers from 1 to 10\n";
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
    try {
      interactor_->process_request({first, second, third, fourth});
    } catch (...) {
      std::cout << "Your ship intersects other ships\n";
      continue;
    }
    update_field();
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

void CommandLine::update_field() {
  std::string square = "\u25FC";
  std::string cross = "\u00D7";
  std::string blank = " ";
  auto pointer = interactor_->get_instance();
  std::vector<std::vector<std::string>>
      display(pointer->size_, std::vector<std::string>(pointer->size_, blank));
  for (int x = 0; x < pointer->size_; ++x) {
    for (int y = 0; y < pointer->size_; ++y) {
      if (pointer->players_field_[x][y] == 0) {
        continue;
      }
      if (pointer->players_field_[x][y] > 0) {
        display[x][y] = square;
      } else {
        display[x][y] = cross;
      }
    }
  }
  print(display);
}