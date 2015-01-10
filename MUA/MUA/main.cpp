//
//  main.cpp
//  MUA
//
//  Created by SmilENow on 1/9/15.
//  Copyright (c) 2015 Jiaquan Yin. All rights reserved.
//

#include <iostream>
#include "Value.h"
#include "GetValue.h"
#include "Operation.h"
#include "Init.h"
#include "Execute.h"

map<string,value*> _namespace;
map<string,value*> _namespace_stack[maxn];
int _namespace_stack_parent[maxn];
value* _namespace_stack_ret[maxn];
map<string,op*> _exec_void;
map<string,op*> _exec_value;
bool _test_ret;
int totstack = 0,curstack = 0;

int main(int argc, const char * argv[]) {
    init();
    while (true) execute();
    return 0;
}



// list [ item ]
// butfirst && butlast list ret its copy!
