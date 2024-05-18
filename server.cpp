#include <cstring>
#include <fstream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <vector>

std::ofstream out("../logging/log_server.txt");

int main() {
  int PORT = 8888;

  out << "Creating a server socket" << std::endl;
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    out << "Error creating server socket" << std::endl;
    return 1;
  }
  out << "Creating a server socket -- Done" << std::endl;

  // set address and port number for the server
  sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  server_addr.sin_addr.s_addr = INADDR_ANY;

  out << "Binding server socket" << std::endl;
  if (bind(sockfd, (struct sockaddr*) &server_addr, sizeof(server_addr)) < 0) {
    out << "Error binding server socket" << std::endl;
    return 1;
  }
  out << "Binding server socket -- Done" << std::endl;

  // listen for connections
  if (listen(sockfd, 2) < 0) {
    out << "Error listening on socket" << std::endl;
    return 1;
  }

  out << "Accepting client sockets" << std::endl;
  std::vector<int> client_sockets;
  while (true) {
    sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    int client_sockfd = accept(sockfd, (struct sockaddr*) &client_addr, &client_len);
    if (client_sockfd < 0) {
      out << "Error accepting connection" << std::endl;
      continue;
    }
    client_sockets.push_back(client_sockfd);
    if (client_sockets.size() == 2) {
      break;
    }
  }
  out << "Accepting client sockets -- Done" << std::endl;

  out << "Starting the game" << std::endl;

  // statuses after shots
  auto wait = "w";
  auto go = "g";
  char miss = 'm';
  char hit = 'h';
  auto victory = "v";
  auto loss = "l";

  out << "Exchanging layouts" << std::endl;
  int active = 0;
  uint delay = 5;
  ssize_t received;
  char active_buffer[128]{};
  char passive_buffer[128]{};
  do {
    sleep(delay);
    received = recv(client_sockets[active], active_buffer, 128, 0);
  } while (received == 0);
  do {
    sleep(delay);
    received = recv(client_sockets[active ^ 1], passive_buffer, 128, 0);
  } while (received == 0);

  char active_response[256]{};
  char passive_response[256]{};
  strcat(active_response, go);
  strcat(active_response, passive_buffer);
  strcat(passive_response, wait);
  strcat(passive_response, active_buffer);

  send(client_sockets[active], active_response, strlen(active_response), 0);
  send(client_sockets[active ^ 1], passive_response, strlen(passive_response), 0);
  out << "Exchanging layouts -- Done" << std::endl;

  // communicate with clients
  char buffer[64]{};
  while (true) {
    memset(buffer, 0, sizeof(buffer));
    int active_client = client_sockets[active];
    int passive_client = client_sockets[active ^ 1];
    do {
      sleep(delay);
      received = recv(active_client, buffer, 64, 0);
    } while (received == 0);

    char response[256]{};
    if (buffer[0] == hit) {
      strcat(response, wait);
      strcat(response, buffer + 1);
      send(passive_client, response, strlen(response), 0);
      send(active_client, go, strlen(go), 0);
      continue;
    } else if (buffer[0] == miss) {
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
  out << "Game ended" << std::endl;

  out << "Closing sockets" << std::endl;
  for (int client_sockfd : client_sockets) {
    close(client_sockfd);
  }
  close(sockfd);
  out << "Closing sockets -- Done" << std::endl;
}
