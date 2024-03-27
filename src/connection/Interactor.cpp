#pragma once

#include "Interactor.h"

Interactor::Interactor() : command_(nullptr) {}

void Interactor::handle_event() {
    /* not ready */
}

std::string Interactor::process_request(std::initializer_list<int> data) {
  return "";
}