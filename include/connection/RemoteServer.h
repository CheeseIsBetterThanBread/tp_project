#pragma once

#include "ObserverSystem.h"

class RemoteServer : public Observable {
  // plug for now, didn't figure out how to work with sockets
 public:
  RemoteServer();
  virtual ~RemoteServer();

  void send_layout();
  void send_data(const char* data) const override;
  void receive_data();

 private:
  int sockfd_;
};