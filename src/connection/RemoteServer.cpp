#include <arpa/inet.h>
#include <iostream>
#include <sys/socket.h>

#include "RemoteServer.h"

RemoteServer::RemoteServer() {
  int PORT = 8080;
  const char* IP = "192.168.1.100";

  // create a socket
  sockfd_ = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd_ < 0) {
    std::cerr << "Error creating socket" << std::endl;
    return;
  }

  // set address and port number for the server
  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  inet_pton(AF_INET, IP, &server_addr.sin_addr);

  // connect to the server
  if (connect(sockfd_, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
    std::cerr << "Error connecting to server" << std::endl;
    return;
  }
}

RemoteServer* RemoteServer::get_pointer() {
  return this;
}

RemoteServer::~RemoteServer() {
  close(sockfd_);
}
