//
//  GetValue.h
//  MUA
//
//  Created by SmilENow on 1/10/15.
//  Copyright (c) 2015 Jiaquan Yin. All rights reserved.
//

#ifndef __MUA__GetValue__
#define __MUA__GetValue__

#include "Value.h"
#include "Operation.h"

string get_word();                  // normal
value* get_value();                 // normal
value* get_value_to_list();         // get value to list , do not implement doCMD
string get_value(string,value**);   // readlinst
string get_value_to_list(string,value**); // get value to list in readlinst, do not implement doCMD
value* get_value(string);           // load


#endif /* defined(__MUA__GetValue__) */
