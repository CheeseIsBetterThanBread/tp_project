#pragma once

#include "../include/AddShipCommand.h"

std::string AddShipCommand::execute(const query& request) {
  local_copy_->add_ship(request.front, request.back);
}