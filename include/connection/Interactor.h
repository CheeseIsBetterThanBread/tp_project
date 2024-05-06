#pragma once

#include "ObserverSystem.h"
#include "command/Command.h"

#include <initializer_list>
#include <memory>
#include <string>

class Interactor : public Observer {
 public:
  explicit Interactor(const std::shared_ptr<Battlefield>& local_copy);
  void handle_event(std::string& response) override;
  void update(std::initializer_list<int> data, const std::string& response) override;
  std::string process_request(std::initializer_list<int>);

  std::shared_ptr<Battlefield> get_instance() override;
  bool is_active() const;

 private:
  std::shared_ptr<Command> command_;
  bool active_;
};