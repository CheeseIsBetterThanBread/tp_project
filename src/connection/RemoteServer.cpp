#include <algorithm>
#include <cstring>
#include <fstream>
#include <netinet/in.h>
#include <sys/socket.h>

#include "Battlefield.h"
#include "RemoteServer.h"

std::ofstream out("../logging/log_players.txt");

RemoteServer::RemoteServer() {
  int PORT = 8888;

  out << "Creating a client socket" << std::endl;
  sockfd_ = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd_ < 0) {
    out << "Error creating client socket" << std::endl;
    return;
  }
  out << "Creating a client socket -- Done" << std::endl;

  // set address and port number for the server
  sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  server_addr.sin_addr.s_addr = INADDR_ANY;

  out << "Connecting to the server" << std::endl;
  if (connect(sockfd_, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
    out << "Error connecting to server" << std::endl;
    return;
  }
  out << "Connecting to the server -- Done" << std::endl;
}

RemoteServer::~RemoteServer() {
  out << "Closing socket" << std::endl;
  close(sockfd_);
  out << "Closing socket -- Done" << std::endl;
}

void RemoteServer::send_layout() {
  auto pointer = observer_.lock()->get_instance();
  using pair = std::pair<int, int>;

  out << "Retrieving layout" << std::endl;
  std::vector<std::vector<pair>> ships(10);
  for (int row = 0; row < pointer->size_; ++row) {
    for (int column = 0; column < pointer->size_; ++column) {
      int value = pointer->players_field_[row][column];
      if (value != 0) {
        ships[value - 1].emplace_back(row, column);
      }
    }
  }
  out << "Retrieving layout -- Done" << std::endl;

  out << "Picking borders" << std::endl;
  std::vector<std::pair<pair, pair>> borders(10);
  for (int i = 0; i < 10; ++i) {
    borders[i] = {*min_element(ships[i].begin(), ships[i].end()),
                  *max_element(ships[i].begin(), ships[i].end())};
  }
  out << "Picking borders -- Done" << std::endl;

  out << "Preparing to send" << std::endl;
  char buffer[256]{};
  for (int i = 0; i < 10; ++i) {
    buffer[4 * i] = '0' + borders[i].first.first;
    buffer[4 * i + 1] = '0' + borders[i].first.second;
    buffer[4 * i + 2] = '0' + borders[i].second.first;
    buffer[4 * i + 3] = '0' + borders[i].second.second;
  }
  out << "Preparing to send -- Done" << std::endl;
  send_data(buffer);
}

void RemoteServer::send_data(const char* data) const {
  send(sockfd_, data, strlen(data), 0);
}

bool RemoteServer::receive_data() {
  ssize_t received;
  char buffer[256]{};
  received = recv(sockfd_, buffer, 256, 0);
  if (received != 0) {
    std::string response(buffer);
    notify(response);
  }
  return received != 0;
}