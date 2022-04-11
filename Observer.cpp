#include <iostream>
#include <list>
#include <vector>
#include <thread>

#include "Observer.hpp"
using namespace std;

class Animation : public Observer {
public:
    Animation() {}
    ~Animation() {}

    void update() {}
};

class Selection : public Subject {
private:
    list<Observer*> colorList;
    list<Observer*> puntosAbsolutosList; // cambiar nombre de esta variable a ingles

public:
    Selection() {}
    ~Selection() {}

    void attach(Observer* color) {
        colorList.emplace_back(color);
    }

    void detach(Observer* color) {
        colorList.remove(color);
    }

    void notify() {
        for (Observer* actual : colorList) {
            actual->updateObserver();
        }
    }
};

main () {
    Observer* firstObserver = new Animation();
    Subject* selectionSubject = new Selection();

    return 0;
}