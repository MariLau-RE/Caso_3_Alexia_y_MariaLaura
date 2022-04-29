#include <iostream>
#include <list>
#include <vector>
#include <thread>

#include "Observer.hpp"
#include "Selection.cpp"
using namespace std;

class Animation : public Observer {
public:
    Animation() {}
    ~Animation() {}
    void update() {}
};

int main () {
    Observer* firstObserver = new Animation();
    Subject* selectionSubject = new Selection();

    return 0;
}