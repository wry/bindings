//
//  main.cpp
//  liblar_test
//
//  Created by wry on 28/06/21.
//
//

#include <iostream>

#include <lar.h>

int main()
{
    Lar lar {};

    std::string error;
    const std::shared_ptr<Release> release = lar.first_release_item("/tmp/releases.rss", error);

    if (release == nullptr)
    {
        std::cout << "Error : " << error << std::endl;
        return 1;
    }

    std::cout << release->_title << "," << release->_link << "," << release->_description << "," << release->_pub_date << std::endl; 

    return 0;
}
