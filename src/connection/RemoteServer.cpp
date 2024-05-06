#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <sys/socket.h>

#include "Battlefield.h"
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

RemoteServer::~RemoteServer() {
  close(sockfd_);
}

void RemoteServer::send_layout() {
  auto pointer = observer_.lock()->get_instance();
  using pair = std::pair<int, int>;

  // get all ships
  std::vector<std::vector<pair>> ships(10);
  for (int row = 0; row < pointer->size_; ++row) {
    for (int column = 0; column < pointer->size_; ++column) {
      int value = pointer->players_field_[row][column];
      if (value != 0) {
        ships[value - 1].emplace_back(row, column);
      }
    }
  }

  // get borders of ships
  std::vector<std::pair<pair, pair>> borders(10);
  for (int i = 0; i < 10; ++i) {
    borders[i] = {*min_element(ships[i].begin(), ships[i].end()),
                  *max_element(ships[i].begin(), ships[i].end())};
  }

  // send info to server
  char buffer[256];
  for (int i = 0; i < 10; ++i) {
    buffer[4 * i] = '0' + borders[i].first.first;
    buffer[4 * i + 1] = '0' + borders[i].first.second;
    buffer[4 * i + 2] = '0' + borders[i].second.first;
    buffer[4 * i + 3] = '0' + borders[i].second.second;
  }
  send(sockfd_, buffer, strlen(buffer), 0);
}

std::string RemoteServer::receive_data() const {
  char buffer[256];
  recv(sockfd_, buffer, strlen(buffer), 0);
  return {buffer};
}