#include "Interactor.h"
#include "Command.h"

Interactor::Interactor(std::shared_ptr<Command>&& command)
    : command_(std::move(command)) {}

void Interactor::handle_event() {
    // todo
}

std::string Interactor::process_request(std::initializer_list<int> data) {
  std::string response = command_->process(data);
  // todo process response
  return response;
}