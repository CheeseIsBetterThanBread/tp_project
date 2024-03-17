#pragma once

#include "../../include/command/FireAtCommand.h"

std::string FireAtCommand::execute(const query& request) {
  local_copy_->fire_at(request.aim);
}
