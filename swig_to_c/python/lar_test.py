#!/usr/bin/python

import Lar

lar = Lar.Lar_new()

release = Lar.Lar_first_release_item(lar, "/tmp/releases.rss")

if isinstance(release,str):
    print("Error : {}".format(release))
    exit(1)

crelease = Lar.CRelease()
Lar.Release_copy_into(release, crelease)

print("{}, {}, {}, {}\n".format(crelease.title, crelease.link, crelease.description, crelease.pub_date))

Lar.Release_delete(release)

Lar.Lar_delete(lar)
