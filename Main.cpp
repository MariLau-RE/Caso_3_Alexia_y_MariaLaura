#include <iostream>
#include <thread>

//#include "Observer.hpp"
#include "Animation.cpp"
#include "Selection.cpp"

int main () {
    Observer* firstObserver = new Animation();
    Subject* selectionSubject = new Selection();

    return 0;
}