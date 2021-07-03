//
//  ktcpp.cpp
//  ktcpp
//
//  Created by wry on 28/06/21.
//
//

#include "ktcpp.h"

#include <iostream>
#include <pugixml.hpp>

struct Ktcpp
{
  Ktcpp();
  ~Ktcpp();

  pugi::xml_document * doc;
};

Ktcpp::Ktcpp() :
  doc(new pugi::xml_document)
{
}

Ktcpp::~Ktcpp()
{
  delete doc;
}

Ktcpp * Ktcpp_new()
{
  return new Ktcpp;
}

void Ktcpp_delete(Ktcpp * diz)
{
  if (diz == nullptr) return;
  delete diz;
}

void Ktcpp_load(Ktcpp * diz, const char * path)
{
  pugi::xml_parse_result result = diz->doc->load_file(path);
  std::cout << "Load result: " << result.description() << std::endl;
}

void Ktcpp_select_nodes(Ktcpp * diz, const char * sel)
{
  pugi::xpath_node_set nodes = diz->doc->select_nodes(sel);
  for (pugi::xpath_node_set::const_iterator it = nodes.begin(); it != nodes.end(); ++it)
  {
    pugi::xpath_node node = *it;
    for (pugi::xml_node child = node.node().first_child(); child; child = child.next_sibling())
    {
      std::cout << child.name() << "," << child.text().as_string() << "\n";
    }
  }
}

