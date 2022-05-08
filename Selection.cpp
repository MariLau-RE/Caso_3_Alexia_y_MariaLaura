#include <vector>
#include <iostream>
#include "rapidxml/rapidxml_ext.hpp" //classes for managing the DOM
#include "rapidxml/rapidxml_utils.hpp" //file class
#include <sstream>
#include <fstream>
#include "Observer.hpp"

using namespace rapidxml; //library namespace
using namespace std;

class Selection{
  private: 
    vector <string> colorList;
    vector <double> absolutePoints;
    vector <xml_node<>*> vectorPaths;

  public:
    Selection(vector <string> _colorList, vector <double> _absolutePoints){
      colorList = _colorList;
      absolutePoints = _absolutePoints;
      
    }
    void printXMLData(xml_document<>* doc);
    void printNodeData(xml_node<>* node);
};

//goes through the rest of the elements of the document
void Selection::printNodeData(xml_node<>* node){
  for (node = node->first_node(); node != NULL; node = node->next_sibling()){
    if (node->type() == node_element){
      string nodeName = node->name();

      xml_attribute<>* attrib = node->first_attribute();
      
      if(nodeName == "path"){
        vectorPaths.push_back(node);
      }

      printNodeData(node);
    }
  }
}

//Loop through the root element of the document
void Selection:: printXMLData(xml_document<>* doc){
  xml_node<>* node = doc->first_node();

  cout << "Etiqueta: " << node->name() << endl;
  for (xml_attribute<>* attrib = node->first_attribute(); attrib != NULL; attrib = attrib->next_attribute()){
    cout << " Atributo: " << attrib->name() << endl;
    cout << "\tValor: " << attrib->value() << endl;
  }

  printNodeData(node);
}

int main (){

  vector <string> colorList;
  vector <double> absolutePoints;
  
  file<> file("Forest.svg"); // read and load file into memorya
  xml_document<> myDoc; 
  myDoc.parse<0>(file.data()); 

  Selection selection = Selection(colorList, absolutePoints);

  selection.printXMLData(&myDoc);
  
}