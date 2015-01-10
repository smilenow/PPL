//
//  Init.cpp
//  MUA
//
//  Created by SmilENow on 1/10/15.
//  Copyright (c) 2015 Jiaquan Yin. All rights reserved.
//

#include "Init.h"

void init(){
    _namespace.clear();
    _namespace.insert(make_pair("pi",new value(number(3.14159))));
    _test_ret = false;
    
    _exec_void.insert(make_pair("//", new _fun_comment()));
    _exec_void.insert(make_pair("make", new _fun_make()));
    _exec_void.insert(make_pair("erase", new _fun_erase()));
    _exec_void.insert(make_pair("print", new _fun_print()));
    _exec_void.insert(make_pair("test", new _fun_test()));
    _exec_void.insert(make_pair("iftrue", new _fun_iftrue()));
    _exec_void.insert(make_pair("iffalse", new _fun_iffalse()));
    _exec_void.insert(make_pair("join", new _fun_join()));
    _exec_void.insert(make_pair("repeat", new _fun_repeat()));
    _exec_void.insert(make_pair("stop", new _fun_stop()));
    _exec_void.insert(make_pair("wait", new _fun_wait()));
    _exec_void.insert(make_pair("save", new _fun_save()));
    _exec_void.insert(make_pair("load", new _fun_load()));
    _exec_void.insert(make_pair("erall", new _fun_erall()));
    _exec_void.insert(make_pair("poall", new _fun_poall()));
    _exec_void.insert(make_pair("if", new _fun_if()));
    _exec_void.insert(make_pair("run", new _fun_run()));
    _exec_void.insert(make_pair("output", new _fun_output()));
    _exec_void.insert(make_pair("local", new _fun_local()));
    
    _exec_value.insert(make_pair("thing", new _fun_thing()));
    _exec_value.insert(make_pair(":", new _fun_colon()));
    _exec_value.insert(make_pair("isname", new _fun_isname()));
    _exec_value.insert(make_pair("read", new _fun_read()));
    _exec_value.insert(make_pair("readlinst", new _fun_readlinst()));
    _exec_value.insert(make_pair("add", new _fun_add()));
    _exec_value.insert(make_pair("sub", new _fun_sub()));
    _exec_value.insert(make_pair("mul", new _fun_mul()));
    _exec_value.insert(make_pair("div", new _fun_div()));
    _exec_value.insert(make_pair("mod", new _fun_mod()));
    _exec_value.insert(make_pair("eq", new _fun_eq()));
    _exec_value.insert(make_pair("gt", new _fun_gt()));
    _exec_value.insert(make_pair("lt", new _fun_lt()));
    _exec_value.insert(make_pair("and", new _fun_and()));
    _exec_value.insert(make_pair("or", new _fun_or()));
    _exec_value.insert(make_pair("not", new _fun_not()));
    _exec_value.insert(make_pair("random", new _fun_random()));
    _exec_value.insert(make_pair("sqrt", new _fun_sqrt()));
    _exec_value.insert(make_pair("isnumber", new _fun_isnumber()));
    _exec_value.insert(make_pair("isword", new _fun_isword()));
    _exec_value.insert(make_pair("islist", new _fun_islist()));
    _exec_value.insert(make_pair("isbool", new _fun_isbool()));
    _exec_value.insert(make_pair("isempty", new _fun_isempty()));
    _exec_value.insert(make_pair("word", new _fun_word()));
    _exec_value.insert(make_pair("list", new _fun_list()));
    _exec_value.insert(make_pair("first", new _fun_first()));
    _exec_value.insert(make_pair("last", new _fun_last()));
    _exec_value.insert(make_pair("butfirst", new _fun_butfirst()));
    _exec_value.insert(make_pair("butlast", new _fun_butlast()));
    _exec_value.insert(make_pair("item", new _fun_item()));
}