//
//  Operation.h
//  MUA
//
//  Created by SmilENow on 1/9/15.
//  Copyright (c) 2015 Jiaquan Yin. All rights reserved.
//

#ifndef __MUA__Operation__
#define __MUA__Operation__

#include "Value.h"
#include "GetValue.h"
#include "StringStreamGetValue.h"
#include <ctime>
#include <iostream>
#include <chrono>
#include <thread>
#include <fstream>

class op{
public:
    op(){};
    virtual ~op(){};
    virtual void fun(){};
    virtual void fun(stringstream&){};
    virtual value* _fun(){ return NULL; };
    virtual value* _fun(stringstream&){ return NULL; };
};

class _fun_comment: public op{
public:
    virtual void fun();
    virtual void fun(stringstream&);
};

class _fun_make: public op{
public:
    virtual void fun();
    virtual void fun(stringstream&);
};

class _fun_thing: public op{
public:
    virtual value* _fun();
    virtual value* _fun(stringstream&);
};

class _fun_colon: public op{
public:
    virtual value* _fun();
    virtual value* _fun(stringstream&);
};

class _fun_erase: public op{
public:
    virtual void fun();
    virtual void fun(stringstream&);
};

class _fun_isname: public op{
public:
    virtual value* _fun();
    virtual value* _fun(stringstream&);
};

class _fun_print: public op{
public:
    virtual void fun();
    virtual void fun(stringstream&);
};

class _fun_read: public op{
public:
    virtual value* _fun();
    virtual value* _fun(stringstream&);
};

class _fun_readlinst: public op{
public:
    virtual value* _fun();
    virtual value* _fun(stringstream&);
};

class _fun_add: public op{
public:
    virtual value* _fun();
    virtual value* _fun(stringstream&);
};

class _fun_sub: public op{
public:
    virtual value* _fun();
    virtual value* _fun(stringstream&);
};

class _fun_mul: public op{
public:
    virtual value* _fun();
    virtual value* _fun(stringstream&);
};

class _fun_div: public op{
public:
    virtual value* _fun();
    virtual value* _fun(stringstream&);
};

class _fun_mod: public op{
public:
    virtual value* _fun();
    virtual value* _fun(stringstream&);
};

class _fun_eq: public op{
public:
    virtual value* _fun();
    virtual value* _fun(stringstream&);
};

class _fun_gt: public op{
public:
    virtual value* _fun();
    virtual value* _fun(stringstream&);
};

class _fun_lt: public op{
public:
    virtual value* _fun();
    virtual value* _fun(stringstream&);
};

class _fun_and: public op{
public:
    virtual value* _fun();
    virtual value* _fun(stringstream&);
};

class _fun_or: public op{
public:
    virtual value* _fun();
    virtual value* _fun(stringstream&);
};

class _fun_not: public op{
public:
    virtual value* _fun();
    virtual value* _fun(stringstream&);
};

class _fun_random: public op{
public:
    virtual value* _fun();
    virtual value* _fun(stringstream&);
};

class _fun_sqrt: public op{
public:
    virtual value* _fun();
    virtual value* _fun(stringstream&);
};

class _fun_isnumber: public op{
public:
    virtual value* _fun();
    virtual value* _fun(stringstream&);
};

class _fun_isword: public op{
public:
    virtual value* _fun();
    virtual value* _fun(stringstream&);
};

class _fun_islist: public op{
public:
    virtual value* _fun();
    virtual value* _fun(stringstream&);
};

class _fun_isbool: public op{
public:
    virtual value* _fun();
    virtual value* _fun(stringstream&);
};

class _fun_isempty: public op{
public:
    virtual value* _fun();
    virtual value* _fun(stringstream&);
};

class _fun_test: public op{
public:
    virtual void fun();
    virtual void fun(stringstream&);
};

class _fun_iftrue: public op{
public:
    virtual void fun();
    virtual void fun(stringstream&);
};

class _fun_iffalse: public op{
public:
    virtual void fun();
    virtual void fun(stringstream&);
};

class _fun_word: public op{
public:
    virtual value* _fun();
    virtual value* _fun(stringstream&);
};

class _fun_list: public op{
public:
    virtual value* _fun();
    virtual value* _fun(stringstream&);
};

class _fun_join: public op{
public:
    virtual void fun();
    virtual void fun(stringstream&);
};

class _fun_first: public op{
public:
    virtual value* _fun();
    virtual value* _fun(stringstream&);
};

class _fun_last: public op{
public:
    virtual value* _fun();
    virtual value* _fun(stringstream&);
};

class _fun_butfirst: public op{
public:
    virtual value* _fun();
    virtual value* _fun(stringstream&);
};

class _fun_butlast: public op{
public:
    virtual value* _fun();
    virtual value* _fun(stringstream&);
};

class _fun_item: public op{
public:
    virtual value* _fun();
    virtual value* _fun(stringstream&);
};

class _fun_repeat: public op{
public:
    virtual void fun();
    virtual void fun(stringstream&);
};

class _fun_stop: public op{
public:
    virtual void fun();
    virtual void fun(stringstream&);
};

class _fun_wait: public op{
public:
    virtual void fun();
    virtual void fun(stringstream&);
};

class _fun_save: public op{
public:
    virtual void fun();
    virtual void fun(stringstream&);
};

class _fun_load: public op{
public:
    virtual void fun();
    virtual void fun(stringstream&);
};

class _fun_erall: public op{
public:
    virtual void fun();
    virtual void fun(stringstream&);
};

class _fun_poall: public op{
public:
    virtual void fun();
    virtual void fun(stringstream&);
};

class _fun_if: public op{
public:
    virtual void fun();
    virtual void fun(stringstream&);
};

class _fun_run: public op{
public:
    virtual void fun();
    virtual void fun(stringstream&);
};

class _fun_output: public op{
public:
    virtual void fun();
    virtual void fun(stringstream&);
};

class _fun_local: public op{
public:
    virtual void fun();
    virtual void fun(stringstream&);
};

void execlist(string);

extern map<string,value*> _namespace;
extern map<string,value*> _namespace_stack[maxn];
extern int _namespace_stack_parent[maxn];
extern value* _namespace_stack_ret[maxn];
extern map<string,op*> _exec_void;
extern map<string,op*> _exec_value;
extern bool _test_ret;
extern int totstack,curstack;

#endif /* defined(__MUA__Operation__) */
