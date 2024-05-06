#include <arpa/inet.h>
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <unistd.h>
#include <vector>

int main() {
  int PORT = 8080;
  const char* IP = "192.168.1.100";

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

  // communicate with clients
  char buffer[256];
  while (true) {
    for (int client_sockfd : client_sockets) {
      recv(client_sockfd, buffer, 256, 0);
      std::cout << "Received from client: " << buffer << std::endl;

      // Send response back to the client
      const char* message = "Hello from server!";
      send(client_sockfd, message, strlen(message), 0);
    }
    break;
  }

  // close all sockets
  for (int client_sockfd : client_sockets) {
    close(client_sockfd);
  }
  close(sockfd);
}
