#pragma once

#include "ObserverSystem.h"

class RemoteServer : public Observable {
  // plug for now, didn't figure out how to work with sockets
 public:
  RemoteServer();
  ~RemoteServer();

  void send_layout();
  void receive_data();

 private:
  int sockfd_;
};