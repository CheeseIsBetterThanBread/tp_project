#include "Interactor.h"
#include "Command.h"

Interactor::Interactor(const std::shared_ptr<Battlefield>& local_copy)
    : command_(std::make_shared<Command>(local_copy)) {}

void Interactor::handle_event(const std::string& response) {
  if (response.size() >= 4 * 10) {
    get_instance()->get_layout(response);
    return;
  }
  // todo
}

std::string Interactor::process_request(std::initializer_list<int> data) {
  std::string response = command_->process(data);
  update();
  return response;
}

void Interactor::update() {
  // todo
}

std::shared_ptr<Battlefield> Interactor::get_instance() {
  return command_->get_instance();
}