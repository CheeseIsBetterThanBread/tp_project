#include "Adapter.h"
#include "CommandLine.h"

Adapter::Adapter() : interactor_(nullptr) {
  ships_left.resize(5);
  for (int i = 1; i < 5; ++i) {
    ships_left[i] = 5 - i;
  }
}

void Adapter::set_interactor(const std::shared_ptr<Interactor>& interactor) {
  interactor_ = interactor;
}

std::shared_ptr<Adapter> Adapter::get_adapter(const std::string& type) {
  if (type == "terminal") {
    return std::make_shared<CommandLine>();
  }
  return nullptr;
}

void Adapter::fire_at() {}

void Adapter::add_ship() {}

void Adapter::update_field() {}

void Adapter::update_enemy() {}