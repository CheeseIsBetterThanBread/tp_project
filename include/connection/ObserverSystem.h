#pragma once

#include <memory>

class Observable;

class Observer {
 public:
  Observer();
  virtual void handle_event(const std::string& response) = 0;
  virtual void update() = 0;
  void set_object(const std::shared_ptr<Observable>& object);
  virtual std::shared_ptr<Battlefield> get_instance() = 0;

  virtual ~Observer() = default;

 protected:
  std::weak_ptr<Observable> object_;
};

class Observable : public std::enable_shared_from_this<Observable> {
 public:
  Observable();
  virtual void notify(const std::string& response);
  void set_observer(const std::shared_ptr<Observer>& observer);

 protected:
  std::weak_ptr<Observer> observer_;
};