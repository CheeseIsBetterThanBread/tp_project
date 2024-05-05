#pragma once

#include "ObserverSystem.h"
#include "command/Command.h"

#include <initializer_list>
#include <memory>
#include <string>

class Interactor : public Observer {
 public:
  explicit Interactor(std::shared_ptr<Command>&& command);
  void handle_event() override;
  std::string process_request(std::initializer_list<int>);

  std::shared_ptr<Battlefield> get_instance();

 private:
  std::shared_ptr<Command> command_;
};