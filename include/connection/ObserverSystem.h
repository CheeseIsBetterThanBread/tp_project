#pragma once

class Observable;

class Observer {
 public:
  Observer();
  virtual void handle_event() = 0;
  void set_object(Observable* object);

 protected:
  Observable* object_;
};

class Observable {
 public:
  Observable();
  void notify();
  void set_observer(Observer* observer);

 protected:
  Observer* observer_;
};