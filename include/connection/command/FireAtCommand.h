#pragma once

#include "Command.h"

class FireAtCommand : public Command {
 public:
  explicit FireAtCommand(const std::shared_ptr<Battlefield>& local_copy);
  std::string execute(std::initializer_list<int>) override;
  std::string process_shot(std::initializer_list<int>) override;
};
