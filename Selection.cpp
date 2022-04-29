#include <iostream>
#include <vector>

#include "Observer.hpp"
using namespace std;

class Selection : public Subject {
private:
    vector <int> colorList;
    vector <float> absolutePointsList;
    vector <string> pathsList;
    xml_document<> myDoc;

public:
    Selection(vector <int> _colorList, vector <float> _absolutePointsList, &_myDoc) {
        colorList = _colorList;
        absolutePointsList = _absolutePointsList;
        myDoc = _myDoc;
    }
    ~Selection() {}

    void attachObserver(Observer* color) {
        //colorList.emplace_back(color);
    }

    void detachObserver(Observer* color) {
        //colorList.remove(color);
    }

    void notifyObserver() {
        /*for (Observer* actual : colorList) {
            actual->updateObserver();
        }*/
    }

    vector <string> findPaths(){
        extractXMLData(&myDoc);
        return ;
    }

};


