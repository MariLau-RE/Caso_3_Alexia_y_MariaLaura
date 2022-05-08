#include <iostream>
#include <vector>

#include "Observer.hpp"
//#include "Read.hpp"

#include <iostream>
#include "rapidxml/rapidxml_ext.hpp" //Clases para manejo del DOM
#include "rapidxml/rapidxml_utils.hpp" //Clase File
#include <sstream>
#include <fstream>

using namespace std;
using namespace rapidxml; //Namespace de la librería
using namespace std;

//Recorre el elemento raíz del documento
void printXMLData(xml_document<>* doc){
  xml_node<>* node = doc->first_node();

  cout << "Etiqueta: " << node->name() << endl;
  for (xml_attribute<>* attrib = node->first_attribute(); attrib != NULL; attrib = attrib->next_attribute()){
    cout << " Atributo: " << attrib->name() << endl;
    cout << "\tValor: " << attrib->value() << endl;
  }

  printNodeData(node);
}

//Recorre el resto de elementos del documento
void printNodeData(xml_node<>* node){
  for (node = node->first_node(); node != NULL; node = node->next_sibling()){
    if (node->type() == node_element){
      cout << "Etiqueta: " << node->name() << endl;

      for (xml_attribute<>* attrib = node->first_attribute(); attrib != NULL; attrib = attrib->next_attribute()){
        cout << "\tAtributo: " << attrib->name() << endl;
        cout << "\t-Valor: " << attrib->value() << endl;
      }
      printNodeData(node);
    }
  }
}


int main (){

    //Leer el archivo
    file<> file("1801287.svg"); // Lee y carga el archivo en memoria
    xml_document<> myDoc; //Raíz del árbol DOM
    myDoc.parse<0>(file.data()); //Parsea el XML en un DOM

    //Recorrer elementos y atributos
    //printXMLData(&myDoc);

  //Modificar un atributo existente
  //Modifica el atributo indicado del primer elemento <path> que se encuentre
  xml_node<> *modifyNode = myDoc.first_node()->first_node("path");

  string newDirection = "M 10 10 L 50 50 L 10 50 Z";
  modifyNode->first_attribute("d")->value(newDirection.c_str());

  string newColor = "pink";
  modifyNode->first_attribute("stroke")->value(newColor.c_str());

  printXMLData(&myDoc);

}