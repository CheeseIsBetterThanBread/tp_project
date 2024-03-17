#pragma once

#include "../../include/command/AddShipCommand.h"

std::string AddShipCommand::execute(const query& request) {
  local_copy_->add_ship(request.front, request.back);
}