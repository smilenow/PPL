//
//  Value.h
//  MUA
//
//  Created by SmilENow on 1/9/15.
//  Copyright (c) 2015 Jiaquan Yin. All rights reserved.
//

#ifndef __MUA__Value__
#define __MUA__Value__

#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <cmath>
#include <fstream>

#define maxn 100000

using namespace std;

class number{
public:
    static const int type_int;
    static const int type_double;
    int type;
    int key_int;
    double key_double;
    number():type(type_int),key_int(0),key_double(0.0){};
    virtual ~number(){};
    number(int key):type(type_int),key_int(key),key_double(0.0){};
    number(double key):type(type_double),key_int(0),key_double(key){};
    number(string str);
    
    bool _CheckDouble() const { return type==number::type_double; };
    int _GetType() const { return type; };
    int _GetIntKey() const { return key_int; };
    double _GetDoubleKey() const { return key_double; }
    
    void print() const;
    void print(ofstream&) const;
    string Convert_To_String() const;
    
    bool operator==(const number& rhs) const;
    bool operator>(const number& rhs) const;
    bool operator<(const number& rhs) const;
};

class list;

class value{
public:
    static const int type_number,type_string,type_list,type_bool;
    int type;
    number key_number;
    bool key_bool;
    string key_string;
    list* key_list;
    
    value():type(-1),key_number(0.0),key_bool(false),key_string(""),key_list(NULL){};
    virtual ~value(){};
    
    value(const number& thatnumber):type(type_number),key_number(thatnumber),
        key_bool(false),key_string(""),key_list(NULL){};
    value(const string& thatword):type(type_string),key_number(0.0),key_bool(false),
        key_string(thatword),key_list(NULL){};
    value(const bool& thatbool):type(type_bool),key_number(0.0),key_bool(thatbool),
        key_string(""),key_list(NULL){};
    value(list* thatlist):type(type_list),key_number(0.0),key_bool(false),
        key_string(""){ key_list = thatlist; };
    value(value* thatv):type(thatv->type),key_number(thatv->key_number),key_bool(thatv->key_bool),
        key_string(thatv->key_string),key_list(thatv->key_list){};
    void copy(const value* that);
    void print();
    void print(ofstream&);
    bool check_number() const { return (type==value::type_number); };
    bool check_string() const { return (type==value::type_string); };
    bool check_list() const { return (type==value::type_list); };
    bool check_bool() const { return (type==value::type_bool); };
};

class list{
public:
    value* key;
    list* next;
    
    list():key(new value()),next(NULL){};
    virtual ~list(){};
    list(value* kk):key(kk),next(NULL){};
    void print();
    void print(ofstream&);
    string Convert_To_String();
};

extern map<string,value*> _namespace;
extern map<string,value*> _namespace_stack[maxn];
extern int _namespace_stack_parent[maxn];
extern value* _namespace_stack_ret[maxn];
extern bool _test_ret;
extern int totstack,curstack;

#endif /* defined(__MUA__Value__) */
