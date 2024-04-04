#pragma once

#include "../Battlefield.h"
#include <initializer_list>
#include <string>
#include <utility>

class Command {
 protected:
  struct Query {
    std::pair<int, int> front;
    std::pair<int, int> back;
    std::pair<int, int> aim;

    Query(std::initializer_list<int>);
  };

 public:
  Command(Battlefield*);
  virtual std::string execute(std::initializer_list<int> data) = 0;
  Command* get_command(std::initializer_list<int>);

  virtual ~Command() = default;

 protected:
  Battlefield* local_copy_;
};
