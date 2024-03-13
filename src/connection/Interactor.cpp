#pragma once

#include "../../include/connection/Interactor.h"

Interactor::Interactor() : connection_(nullptr), command_(nullptr) {}

void Interactor::handle_event() {
    /* not ready */
}

std::string Interactor::process_request(std::initializer_list<int>) {}