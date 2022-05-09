/** 
 * Caso #3 Análisis de Algoritmos
 * Maria Laura Retana Elizondo 2019390522
 * Alexia Cerdas Aguilar 2019026961
**/

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
    vector<vector<float>> absolutePoints;
    vector <xml_node<>*> vectorPaths;
    vector <string> matchColorList;
    vector <double> matchAbsolutePoints;

  public:
    Selection(vector <string> pColorList, vector<vector<float>> pAbsolutePoints){
      colorList = pColorList;
      absolutePoints = pAbsolutePoints;
      
    }
    void extractXMLData(xml_document<>* pDocument);
    void extractNodeData(xml_node<>* pDocumentNode);
    void goThroughVector();
    void analyzeColor(xml_node<>* pPathFound);
    void analyzeAbsolutePoints(xml_node<>* pPathFound);
    void printColorList();
};

//Loop through the root element of the document
void Selection::extractXMLData(xml_document<>* pDocument){
  xml_node<>* documentNode = pDocument->first_node();
  extractNodeData(documentNode);
}

//Goes through the rest of the elements of the document
void Selection::extractNodeData(xml_node<>* pDocumentNode){
  for (pDocumentNode = pDocumentNode->first_node(); pDocumentNode != NULL; pDocumentNode = pDocumentNode->next_sibling()){
    if (pDocumentNode->type() == node_element){
      string nodeName = pDocumentNode->name();
      
      if(nodeName == "path"){
        vectorPaths.push_back(pDocumentNode);
      }
      extractNodeData(pDocumentNode);
    }
  }
}

//Sends each path to analyzeColor method
void Selection::goThroughVector(){
  for(int vectorCounter = 0; vectorCounter < vectorPaths.size(); vectorCounter++){
    xml_node<>* pathFound = vectorPaths[vectorCounter];
    analyzeColor(pathFound);
    analyzeAbsolutePoints(pathFound);
  }
}

//Analizes each path one by one
void Selection::analyzeColor(xml_node<>* pPathFound){
  xml_attribute<>* pathAttribute = pPathFound->first_attribute();

  for (xml_attribute<>* pathAttribute = pPathFound->first_attribute(); pathAttribute != NULL; pathAttribute = pathAttribute->next_attribute()){
    string nameAttribute = pathAttribute->name();
    string valueAttribute = pathAttribute->value();

    for(int eachColorIndex = 0; eachColorIndex < colorList.size(); eachColorIndex++){
      string hexColor = colorList[eachColorIndex];

      if (nameAttribute == "opacity"){ matchColorList.push_back("#000000"); }
      if (nameAttribute == "fill" && hexColor == valueAttribute){ matchColorList.push_back(valueAttribute); }
      
    }
  }
}

//Analizes each path one by one
void Selection::analyzeAbsolutePoints(xml_node<>* pPathFound){
  xml_attribute<>* pathAttribute = pPathFound->first_attribute();
  string nameAttribute = pathAttribute->name();
  
    for (pathAttribute; pathAttribute != NULL; pathAttribute = pathAttribute->next_attribute()){
      if(nameAttribute == "d"){
        string valueAttribute = pathAttribute->value();
        cout << valueAttribute << endl;
    }
  }
}

void Selection::printColorList(){
  cout << "[";
  for(int colorListCounter = 0; colorListCounter < matchColorList.size(); colorListCounter++){
    if(colorListCounter == matchColorList.size()-1){
      cout << matchColorList[colorListCounter];
    }
    else{
      cout << matchColorList[colorListCounter] << ",";
    }
  }
  cout << "]";
}

int main (){
  vector <string> colorList;
  vector<vector<float>> absolutePoints;
  colorList= {"#000000","#222223"};
  absolutePoints = { {34,29} , {16.7,95.3} , {3,7} };
  
  file<> file("tesla.svg"); // read and load file into memory
  xml_document<> imageSVG; 
  imageSVG.parse<0>(file.data()); 

  Selection selection = Selection(colorList, absolutePoints);
  selection.extractXMLData(&imageSVG);
  selection.goThroughVector();
  //selection.printColorList();
}
