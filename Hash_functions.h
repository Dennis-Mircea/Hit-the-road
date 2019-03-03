/*
 *  Copyright [2018] <CIUPITU DENNIS-MIRCEA 313CA>
 */

#ifndef HASH_FUNCTIONS_H_
#define HASH_FUNCTIONS_H_

#define INT_HASH	1000
#define	STRING_HASH	8497

#include <string>

unsigned int hashingFunction(int nr) {
    return nr;
}

unsigned int charHashingFunction(std::string str) {
    return str.length() + STRING_HASH;
}

unsigned int hash_fct(std::string str) {
    unsigned int hash = 5381;
    int c;

    const char *cstr = str.c_str();

    while ((c = *cstr++) != 0) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

#endif  // HASH_FUNCTIONS_H_
