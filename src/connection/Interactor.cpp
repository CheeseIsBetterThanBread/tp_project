#pragma once

#include "Interactor.h"
#include "Command.h"

Interactor::Interactor(Command* command) : command_(command) {}

void Interactor::handle_event() {
    // todo
}

std::string Interactor::process_request(std::initializer_list<int> data) {
  std::string response = command_->process(data);
  // todo process response
  return response;
}