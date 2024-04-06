#pragma once

#include "Command.h"

class AddShipCommand : public Command {
 public:
  AddShipCommand(Battlefield* local_copy);
  std::string execute(std::initializer_list<int>) override;
};
