#!/usr/bin/python

import Lar

lar = Lar.Lar_new()

# will crash if path incorrect, should pass a char**
error = None
release = Lar.Lar_first_release_item(lar, "/tmp/releases.rss", error)

if release is None:
    print("Error : $error")
    # free(error);
    exit(1)

crelease = Lar.CRelease()
Lar.Release_copy_into(release, crelease)

print("{}, {}, {}, {}\n".format(crelease.title, crelease.link, crelease.description, crelease.pub_date))

Lar.Release_delete(release)

Lar.Lar_delete(lar)
