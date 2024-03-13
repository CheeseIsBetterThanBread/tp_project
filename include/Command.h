#pragma once

#include "connection/RemoteServer.h"
#include "connection/Battlefield.h"
#include <initializer_list>
#include <string>
#include <utility>

class Command {
 protected:
  struct query {
    std::pair<int, int> front;
    std::pair<int, int> back;
    std::pair<int, int> aim;

    query(std::initializer_list<int>);
  };

 public:
  Command(Battlefield*);
  virtual std::string execute(const query&) = 0;

 protected:
  Battlefield* local_copy_;
};
