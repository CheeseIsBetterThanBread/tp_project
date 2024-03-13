#pragma once

#include "../../include/connection/ObserverSystem.h"

Observable::Observable() : observer_(nullptr) {};

void Observable::notify() {
  observer_->handle_event();
}

Observer::Observer() : object_(nullptr) {}

void Observable::set_observer(Observer* observer) {
  observer_ = observer;
  observer_->set_object(this);
}

void Observer::set_object(Observable* object) {
  object_ = object;
}