#pragma once

#include "Command.h"

class FireAtCommand : public Command {
 public:
  FireAtCommand(Battlefield* local_copy);
  std::string execute(std::initializer_list<int>) override;
};
