#pragma once

#include "ObserverSystem.h"
#include "RemoteServer.h"
#include "../command/Command.h"
#include <initializer_list>
#include <string>

class Interactor : public Observer {
 public:
  Interactor();
  void handle_event() override;
  std::string process_request(std::initializer_list<int>); // need strong guarantee todo

 private:
  RemoteServer* connection_;
  Command* command_;
};