#include <iostream>
#include <thread>
//#include "Observer.hpp"
#include "Animation.cpp"
#include "Selection.cpp"
#include "Read.cpp"

int main () {
    vector <int> colorList;
    vector <float> absolutePointsList;
    float angle;
    int frames;

    //Read XML
    file<> file("sample.svg"); 
    xml_document<> myDoc; 
    myDoc.parse<0>(file.data());

    Observer* firstObserver = new Animation();
    Subject* selectionSubject = new Selection(colorList, absolutePointsList, &myDoc);

    return 0;
}