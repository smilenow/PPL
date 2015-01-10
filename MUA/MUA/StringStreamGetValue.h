//
//  StringStreamGetValue.h
//  MUA
//
//  Created by SmilENow on 1/10/15.
//  Copyright (c) 2015 Jiaquan Yin. All rights reserved.
//

#ifndef __MUA__StringStreamGetValue__
#define __MUA__StringStreamGetValue__

#include "Value.h"
#include "Operation.h"

string get_word(stringstream& sin);                  // normal
value* get_value(stringstream& sin);                 // normal
value* get_value_to_list(stringstream& sin);         // get value to list , do not implement doCMD
string get_value(stringstream& sin,string,value**);   // readlinst
string get_value_to_list(stringstream& sin,string,value**); // get value to list in readlinst, do not implement doCMD
value* get_value(stringstream& sin,string);           // load

#endif /* defined(__MUA__StringStreamGetValue__) */
