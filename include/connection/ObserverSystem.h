#pragma once

#include <memory>

class Observable;

class Observer {
 public:
  Observer();
  virtual void handle_event() = 0;
  void set_object(const std::shared_ptr<Observable>& object);

  virtual ~Observer() = default;

 protected:
  std::weak_ptr<Observable> object_;
};

class Observable : public std::enable_shared_from_this<Observable> {
 public:
  Observable();
  void notify();
  void set_observer(const std::shared_ptr<Observer>& observer);

 protected:
  std::weak_ptr<Observer> observer_;
};