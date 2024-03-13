#pragma once

#include "../include/FireAtCommand.h"

std::string FireAtCommand::execute(const query& request) {
  local_copy_->fire_at(request.aim);
}
