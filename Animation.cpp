#include <iostream>
#include <thread>

#include "Observer.hpp"
using namespace std;

class Animation : public Observer {
public:
    Animation() {}
    ~Animation() {}
    void updateObserver() {}
};
