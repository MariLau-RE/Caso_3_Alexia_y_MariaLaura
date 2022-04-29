#include <iostream>
#include <thread>
//#include "Observer.hpp"
#include "Animation.cpp"
#include "Selection.cpp"
#include "Read.cpp"

int main () {
    Observer* firstObserver = new Animation();
    Subject* selectionSubject = new Selection();

    int colorList []={};
    int puntosAbsolutosList []={};
    float angle;
    int frames;

      //Leer XML
        file<> file("sample.svg"); // Lee y carga el archivo en memoria
        xml_document<> myDoc; //Raíz del árbol DOM
        myDoc.parse<0>(file.data()); //Parsea el XML en un DOM
    
    return 0;
}