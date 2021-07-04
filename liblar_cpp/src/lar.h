//
//  lar.h
//  liblar
//
//  Created by wry on 28/06/21.
//
//

#ifndef LIBLAR_LAR_H
#define LIBLAR_LAR_H

#include <memory>
#include <string>

struct Release
{
    std::string _title;
    std::string _link;
    std::string _description;
    std::string _pub_date;
};

struct Lar
{
    /**
     * Fetch first item from releases rss
     * @param path filepath to releases.rss
     * @return Release instance parsed from xml
     */
    std::shared_ptr<Release> first_release_item(const std::string& path, std::string& error);
};

#endif /* LIBLAR_LAR_H */

