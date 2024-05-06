#pragma once

#include "ObserverSystem.h"
#include "command/Command.h"

#include <initializer_list>
#include <memory>
#include <string>

class Interactor : public Observer {
 public:
  explicit Interactor(const std::shared_ptr<Battlefield>& local_copy);
  void handle_event(const std::string& response) override;
  void update() override;
  std::string process_request(std::initializer_list<int>);

  std::shared_ptr<Battlefield> get_instance() override;

 private:
  std::shared_ptr<Command> command_;
};