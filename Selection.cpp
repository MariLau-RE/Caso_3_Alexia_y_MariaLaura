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
    Selection(vector <string> _colorList, vector<vector<float>> _absolutePoints){
      colorList = _colorList;
      absolutePoints = _absolutePoints;
      
    }
    void extractXMLData(xml_document<>* doc);
    void extractNodeData(xml_node<>* node);
    void nose();
    void analyzeColor(xml_node<>* pathFound);
};

//Loop through the root element of the document
void Selection::extractXMLData(xml_document<>* doc){
  xml_node<>* node = doc->first_node();
  extractNodeData(node);
}

//goes through the rest of the elements of the document
void Selection::extractNodeData(xml_node<>* node){
  for (node = node->first_node(); node != NULL; node = node->next_sibling()){
    if (node->type() == node_element){
      string nodeName = node->name();
      xml_attribute<>* attrib = node->first_attribute();
      
      if(nodeName == "path"){
        vectorPaths.push_back(node);
      }
      extractNodeData(node);
    }
  }
}

//Get each path ??????????
void Selection::nose(){
  for(int i = 0; i < vectorPaths.size(); i++){
    xml_node<>* pathFound = vectorPaths[i];
    analyzeColor(pathFound);
  }
}

//Analizes each path one by one
void Selection::analyzeColor(xml_node<>* pathFound){
  xml_attribute<>* attrib = pathFound->first_attribute();

  for (xml_attribute<>* attrib = pathFound->first_attribute(); attrib != NULL; attrib = attrib->next_attribute()){
    string attributeName = attrib->name();
    string attributeValue = attrib->value();

    for(int eachColorIndex = 0; eachColorIndex < colorList.size(); eachColorIndex++){
      string hexColor = colorList[eachColorIndex];

      if (hexColor == "#000000" && attributeName == "opacity"){ matchColorList.push_back(attributeValue); }
      if (attributeName == "fill" && hexColor == attributeValue){ matchColorList.push_back(attributeValue);}
      if (attributeName == "stroke"){
        
      }
    }
  }
}

int main (){
  vector <string> colorList;
  vector<vector<float>> absolutePoints;
  colorList= {"#FFFFFF" , "#D76F16", "#79271B"};
  absolutePoints = { {34,29} , {16.7,95.3} , {3,7} };
  
  file<> file("Forest.svg"); // read and load file into memory
  xml_document<> myDoc; 
  myDoc.parse<0>(file.data()); 

  Selection selection = Selection(colorList, absolutePoints);
  selection.extractXMLData(&myDoc);

}
