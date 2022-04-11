#include <vector>

class Observer {
public:
  virtual ~Observer(){};
  virtual void updateObserver() = 0;
};

class Subject {
public:
  virtual ~Subject(){};
  virtual void attachObserver(Observer *observer) = 0;
  virtual void detachObserver(Observer *observer) = 0;
  virtual void notifyObserver(){}
};