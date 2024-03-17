#pragma once

#include "Command.h"

class AddShipCommand : public Command {
 public:
  std::string execute(const query&) override;
};
