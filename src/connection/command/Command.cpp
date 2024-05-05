#include "Command.h"
#include "FireAtCommand.h"
#include "AddShipCommand.h"

Command::Command(Battlefield* local_copy) : local_copy_(local_copy) {}

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
  Command* real_command = nullptr;
  if (data.size() == 2) {
    real_command = new FireAtCommand(local_copy_);
  } else {
    real_command = new AddShipCommand(local_copy_);
  }
  std::string answer;
  try {
    answer = real_command->execute(data);
  } catch (...) {
    delete real_command;
    throw;
  }
  delete real_command;
  return answer;
}