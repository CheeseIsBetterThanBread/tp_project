#include "Battlefield.h"
#include "interface/Adapter.h"
#include "connection/Interactor.h"
#include "connection/RemoteServer.h"

#include <iostream>
#include <memory>
#include <string>
#include <unistd.h>

void set_up(const std::shared_ptr<Interactor>& interactor,
            std::shared_ptr<RemoteServer>& server,
            std::shared_ptr<Adapter>& adapter) {
  server->set_observer(interactor);
  adapter->set_interactor(interactor);
}

void initiate_game(const std::shared_ptr<Adapter>& adapter) {
  int ships = 10;
  for (int index = 0; index < ships; ++index) {
    adapter->add_ship();
  }
}

int main(int, char** argv) {
  // create all necessary objects and connect them
  auto local_copy = std::make_shared<Battlefield>();
  auto interactor = std::make_shared<Interactor>(local_copy);
  auto server = std::make_shared<RemoteServer>();
  auto adapter = Adapter::get_adapter(static_cast<std::string>(argv[1]));
  set_up(interactor, server, adapter);

  // set up playing fields
  uint delay = 2;
  initiate_game(adapter);
  server->send_layout();
  bool flag;
  do {
    sleep(delay);
    flag = server->receive_data();
  } while (!flag);
  std::cerr << "Fields are set up" << std::endl;

  // gameplay
  while (interactor->is_valid()) {
    while (interactor->is_active()) {
      adapter->fire_at();
      sleep(delay);
      server->receive_data();
    }
    while (!interactor->is_active()) {
      sleep(delay);
      server->receive_data();
    }
  }

  // end of the game
  if (interactor->is_active()) { // player won
    adapter->finish_victory();
  } else { // player lost
    adapter->finish_defeat();
  }
}