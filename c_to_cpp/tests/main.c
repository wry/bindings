//
//  main.c
//  liblarc
//
//  Created by wry on 28/06/21.
//
//

#include <larc.h>

#include <stdio.h>

int main()
{
    Lar * lar = Lar_new();

    char * error = NULL;
    Release * release = Lar_first_release_item(lar, "/tmp/releases.rss", &error);

    if (release == NULL)
    {
        printf("Error : %s", error);
        free(error);
        return 1;
    }

    CRelease crelease = {};
    Release_copy_into(release, &crelease);

    printf("%s, %s, %s, %s\n", crelease.title, crelease.link, crelease.description, crelease.pub_date);

    Release_delete(release);
    
    Lar_delete(lar);

    return 0;
}