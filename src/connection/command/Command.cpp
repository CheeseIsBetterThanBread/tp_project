#include "Command.h"
#include "FireAtCommand.h"
#include "AddShipCommand.h"

Command::Command(const std::shared_ptr<Battlefield>& local_copy)
    : local_copy_(local_copy) {}

Command::Query::Query(std::initializer_list<int> data) {
  int size = static_cast<int>(data.size());
  auto iterator = data.begin();
  if (size == 2) {
    front = {0, 0};
    back = {0, 0};
    aim = {*iterator, *(++iterator)};
    return;
  }
  aim = {0, 0};
  front = {*iterator, *(++iterator)};
  ++iterator;
  back = {*iterator, *(++iterator)};
}

std::string Command::execute(std::initializer_list<int>) {
  return "something went wrong";
}

std::string Command::process(std::initializer_list<int> data) {
  std::shared_ptr<Command> real_command;
  if (data.size() == 2) {
    real_command = std::make_shared<FireAtCommand>(local_copy_);
  } else {
    real_command = std::make_shared<AddShipCommand>(local_copy_);
  }
  std::string answer = real_command->execute(data);
  return answer;
}

std::shared_ptr<Battlefield> Command::get_instance() {
  return local_copy_;
}