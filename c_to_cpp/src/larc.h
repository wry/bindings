//
//  larc.h
//  liblarc
//
//  Created by wry on 04/07/21.
//
//

#ifndef LIBLARC_LARC_H
#define LIBLARC_LARC_H

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

struct Lar;
typedef struct Lar Lar;

struct Release;
typedef struct Release Release;

typedef struct
{
    const char * title;
    const char * link;
    const char * description;
    const char * pub_date;
} CRelease;

/**
 * Create new Lar instance
 * @return the new instance
 */
Lar * Lar_new();
/**
 * Delete a Lar instance
 * @param lar the instance to delete
 */
void Lar_delete(Lar * lar);

/**
 * Fetch topmost item from releases rss
 * @param lar lar instance
 * @param path the path to releases.rss
 * @param error the ptr to which error should be written (owner must free it)
 * @return a Release instance (caller must call deleting function)
 */
Release * Lar_first_release_item(Lar * lar, const char * path, char ** error);

/**
 * Copy release instance to a C friendly struct
 * @param release a Release instance
 * @param crelease a CRelease instance (all fields will point to fields in Release)
 */
void Release_copy_into(Release * release, CRelease * crelease);

/**
 * Delete a release instance
 * @param release the instance to delete
 */
void Release_delete(Release * release);

#ifdef __cplusplus
}
#endif

#endif /* LIBLARC_LARC_H */

