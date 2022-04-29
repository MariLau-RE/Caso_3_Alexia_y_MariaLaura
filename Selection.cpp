#include <iostream>
#include <list>

#include "Observer.hpp"
using namespace std;

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