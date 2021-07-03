//
//  ktcpp.h
//  ktcpp
//
//  Created by wry on 28/06/21.
//
//

#ifndef KTCPP_KTCPP_H
#define KTCPP_KTCPP_H

#ifdef __cplusplus
extern "C" {
#endif

struct Ktcpp;
typedef struct Ktcpp Ktcpp;

Ktcpp * Ktcpp_new();
void Ktcpp_delete(Ktcpp *);

void Ktcpp_load(Ktcpp *, const char *);
void Ktcpp_select_nodes(Ktcpp *, const char *);

#ifdef __cplusplus
}
#endif

#endif /* KTCPP_KTCPP_H */

