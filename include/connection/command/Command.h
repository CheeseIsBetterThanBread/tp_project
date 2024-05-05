#pragma once

#include <initializer_list>
#include <memory>
#include <string>
#include <utility>

#include "../../Battlefield.h"

class Command {
 protected:
  struct Query {
    std::pair<int, int> front;
    std::pair<int, int> back;
    std::pair<int, int> aim;

    Query(std::initializer_list<int>);
  };

 public:
  explicit Command(const std::shared_ptr<Battlefield>& local_copy);
  virtual std::string execute(std::initializer_list<int> data);
  std::string process(std::initializer_list<int> data);

  virtual ~Command() = default;

  std::shared_ptr<Battlefield> get_instance();

 protected:
  std::shared_ptr<Battlefield> local_copy_;
};
