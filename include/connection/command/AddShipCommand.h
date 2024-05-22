#pragma once

#include "Command.h"

class AddShipCommand : public Command {
 public:
  explicit AddShipCommand(const std::shared_ptr<Battlefield>& local_copy);
  std::string execute(std::initializer_list<int>) override;
};
