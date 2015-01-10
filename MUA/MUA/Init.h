//
//  Init.h
//  MUA
//
//  Created by SmilENow on 1/10/15.
//  Copyright (c) 2015 Jiaquan Yin. All rights reserved.
//

#ifndef __MUA__Init__
#define __MUA__Init__

#include "Value.h"
#include "Operation.h"
#include "GetValue.h"

extern map<string,value*> _namespace;
extern map<string,value*> _namespace_stack[maxn];
extern int _namespace_stack_parent[maxn];
extern value* _namespace_stack_ret[maxn];
extern map<string,op*> _exec_void;
extern map<string,op*> _exec_value;
extern bool _test_ret;
extern int totstack,curstack;

void init();

#endif /* defined(__MUA__Init__) */
