//
//  larc.c
//  liblarc
//
//  Created by wry on 04/07/21.
//
//

#include "larc.h"

#include <lar.h>

#include <string.h>

Lar * Lar_new()
{
    return new Lar;
}

void Lar_delete(Lar * lar)
{
    if (lar == nullptr) return;
    delete lar;
}

Release * Lar_first_release_item(Lar * lar, const char * path, char ** error)
{
    std::string error_str;
    const std::shared_ptr<Release> release = lar->first_release_item(path, error_str);

    if (release == nullptr)
    {
        *error = (char *)calloc(1, error_str.size()+1);
        strncpy(*error, error_str.c_str(), error_str.size());
        return nullptr;
    }

    return new Release(*release);
}

void Release_copy_into(Release * release, CRelease * crelease)
{
    crelease->title = release->_title.c_str();
    crelease->link = release->_link.c_str();
    crelease->description = release->_description.c_str();
    crelease->pub_date = release->_pub_date.c_str();
}

void Release_delete(Release * release)
{
    if (release == nullptr) return;
    delete release;
}