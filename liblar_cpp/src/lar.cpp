//
//  lar.cpp
//  liblar
//
//  Created by wry on 28/06/21.
//
//

#include "lar.h"

#include <pugixml.hpp>
#include <iostream>

std::shared_ptr<Release> Lar::first_release_item(const std::string& path, std::string& error)
{
    pugi::xml_document doc {};
    pugi::xml_parse_result result = doc.load_file(path.c_str());
    if (result.status != pugi::status_ok)
    {
        error = result.description();
        return nullptr;
    }

    const std::shared_ptr<Release> release = std::make_shared<Release>();

    pugi::xpath_node_set nodes = doc.select_nodes("//channel/item[description[contains(text(),\"iPadOS\")]][1]");
    for (pugi::xpath_node_set::const_iterator it = nodes.begin(); it != nodes.end(); ++it)
    {
        pugi::xpath_node node = *it;
        for (pugi::xml_node child = node.node().first_child(); child; child = child.next_sibling())
        {
            const std::string name = child.name();

            if (name == "title")
            {
                release->_title = child.text().as_string();
            }
            else if (name == "link")
            {
                release->_link = child.text().as_string();
            }
            else if (name == "description")
            {
                release->_description = child.text().as_string();
            }
            else if (name == "pubDate")
            {
                release->_pub_date = child.text().as_string();
            }
        }
    }

    return release;
}

