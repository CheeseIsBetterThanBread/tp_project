#include "Interactor.h"
#include "Command.h"
#include "RemoteServer.h"

#include <cstring>

Interactor::Interactor(const std::shared_ptr<Battlefield>& local_copy)
    : command_(std::make_shared<Command>(local_copy)), active_(false) {}

void Interactor::handle_event(std::string& response) {
  active_ = response[0] == 'g';
  if (response.size() >= 4 * 10) {
    response.erase(0, 1);
    get_instance()->get_layout(response);
    return;
  }
  if (response.size() > 1) {
    int row = response[1] - '0';
    int column = response[2] - '0';
    command_->process({row, column});
    return;
  }
  command_.reset();
  active_ = response[0] == 'v';
}

std::string Interactor::process_request(std::initializer_list<int> data) {
  std::string response = command_->process(data);
  update(data, response);
  return response;
}

void Interactor::update(std::initializer_list<int> data, const std::string& response) {
  if (data.size() != 2) {
    return;
  }
  if (get_instance()->alive_ == 0) {
    char message[64];
    strcat(message, "done");
    object_.lock()->send_data(message);
    return;
  }
  bool missed = response == "Missed\n";
  char message[64];
  message[0] = missed ? 'm' : 'h';
  auto iterator = data.begin();
  message[1] = '0' + *iterator;
  message[2] = '0' + *(++iterator);
  object_.lock()->send_data(message);
}

std::shared_ptr<Battlefield> Interactor::get_instance() {
  return command_->get_instance();
}

bool Interactor::is_active() const {
  return active_;
}

bool Interactor::is_valid() const {
  return command_ != nullptr;
}