#pragma once

#include "Command.h"

class FireAtCommand : public Command {
 public:
  std::string execute(const query&) override;
};
