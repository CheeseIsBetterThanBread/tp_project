#pragma once

#include "ObserverSystem.h"

class RemoteServer : public Observable {
 public:
  RemoteServer();
  virtual ~RemoteServer();

  void send_layout();
  void send_data(const char* data) const override;
  bool receive_data();

 private:
  int sockfd_;
};