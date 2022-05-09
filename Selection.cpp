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
};

//Loop through the root element of the document
void Selection::extractXMLData(xml_document<>* pDocument){
  xml_node<>* documentNode = pDocument->first_node();
  extractNodeData(documentNode);
}

//goes through the rest of the elements of the document
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

//Get each path ??????????
void Selection::goThroughVector(){
  for(int vectorCounter = 0; vectorCounter < vectorPaths.size(); vectorCounter++){
    xml_node<>* pathFound = vectorPaths[vectorCounter];
    analyzeColor(pathFound);
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

      if (hexColor == "#000000" && nameAttribute == "opacity"){ matchColorList.push_back(valueAttribute); }
      if (nameAttribute == "fill" && hexColor == valueAttribute){ matchColorList.push_back(valueAttribute);}
      
    }
  }
}

int main (){
  vector <string> colorList;
  vector<vector<float>> absolutePoints;
  colorList= {"#FFFFFF" , "#D76F16", "#79271B"};
  absolutePoints = { {34,29} , {16.7,95.3} , {3,7} };
  
  file<> file("Forest.svg"); // read and load file into memory
  xml_document<> imageSVG; 
  imageSVG.parse<0>(file.data()); 

  Selection selection = Selection(colorList, absolutePoints);
  selection.extractXMLData(&imageSVG);

}
