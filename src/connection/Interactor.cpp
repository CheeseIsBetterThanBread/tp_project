#pragma once

#include "Interactor.h"

Interactor::Interactor() : command_(nullptr) {}

void Interactor::handle_event() {
    // todo
}

std::string Interactor::process_request(std::initializer_list<int> data) {
  Command* real_command = command_->get_command(data);  // allocated with new
  std::string response = real_command->execute(data);
  // todo process response
  delete real_command;
  return response;
}