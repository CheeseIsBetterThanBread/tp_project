#include <arpa/inet.h>
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <unistd.h>
#include <vector>

int main() {
  int PORT = 8080;
  const char* IP = "0.0.0.0";

  // create a socket
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    std::cerr << "Error creating socket" << std::endl;
    return 1;
  }

  // set address and port number for the server
  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  inet_pton(AF_INET, IP, &server_addr.sin_addr);

  // bind the socket to the address and port
  if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
    std::cerr << "Error binding socket" << std::endl;
    return 1;
  }

  // listen for connections
  if (listen(sockfd, 3) < 0) {
    std::cerr << "Error listening on socket" << std::endl;
    return 1;
  }

  // accept incoming connections
  std::vector<int> client_sockets;
  while (true) {
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    int client_sockfd = accept(sockfd, (struct sockaddr *)&client_addr, &client_len);
    if (client_sockfd < 0) {
      std::cerr << "Error accepting connection" << std::endl;
      continue;
    }

    client_sockets.push_back(client_sockfd);
    if (client_sockets.size() == 2) {
      break;
    }
  }

  // statuses after shots
  auto wait = "w";
  auto go = "g";
  char miss = 'm';
  char hit = 'h';
  auto victory = "v";
  auto loss = "l";

  // exchange layouts
  int active = 0;
  {
    char active_buffer[128];
    char passive_buffer[128];
    recv(client_sockets[active], active_buffer, 128, 0);
    recv(client_sockets[active ^ 1], passive_buffer, 128, 0);

    char active_response[256];
    char passive_response[256];
    strcat(active_response, go);
    strcat(active_response, passive_buffer);
    strcat(passive_response, wait);
    strcat(passive_response, active_buffer);

    send(client_sockets[active], active_response, strlen(active_response), 0);
    send(client_sockets[active ^ 1], passive_response, strlen(passive_response), 0);
  }

  // communicate with clients
  char buffer[64];
  while (true) {
    int active_client = client_sockets[active];
    int passive_client = client_sockets[active ^ 1];
    recv(active_client, buffer, 64, 0);

    char response[256];
    if (buffer[0] == hit) {
      strcat(response, wait);
      strcat(response, buffer + 1);
      send(passive_client, response, strlen(response), 0);
      send(active_client, go, strlen(go), 0);
      continue;
    }
    if (buffer[0] == miss) {
      strcat(response, go);
      strcat(response, buffer + 1);
      send(passive_client, response, strlen(response), 0);
      send(active_client, wait, strlen(wait), 0);
      active ^= 1;
      continue;
    }

    // active client shot last ship
    send(active_client, victory, strlen(victory), 0);
    send(passive_client, loss, strlen(loss), 0);
    break;
  }

  // close all sockets
  for (int client_sockfd : client_sockets) {
    close(client_sockfd);
  }
  close(sockfd);
}
