#include "ObserverSystem.h"

Observable::Observable() : observer_() {};

void Observable::notify(std::string& response) {
  observer_.lock()->handle_event(response);
}

Observer::Observer() : object_() {}

void Observable::set_observer(const std::shared_ptr<Observer>& observer) {
  observer_ = observer;
  observer_.lock()->set_object(shared_from_this());
}

void Observer::set_object(const std::shared_ptr<Observable>& object) {
  object_ = object;
}