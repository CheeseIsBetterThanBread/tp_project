#pragma once

#include "Battlefield.h"
#include "interface/Adapter.h"
#include "connection/Interactor.h"
#include "connection/RemoteServer.h"
#include "connection/command/Command.h"

#include <string>

void set_up(Interactor& interactor, RemoteServer& server, Adapter* adapter) {
  server.set_observer(&interactor);
  adapter->set_interactor(&interactor);
}

int main(int argc, char** argv) {
  Battlefield local_copy;
  Command main_command(&local_copy);
  Interactor interactor(&main_command);
  RemoteServer server;
  Adapter* adapter = Adapter::get_adapter(static_cast<std::string>(argv[1]));
  set_up(interactor, server, adapter);
  delete adapter;
}