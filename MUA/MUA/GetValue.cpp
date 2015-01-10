//
//  GetValue.cpp
//  MUA
//
//  Created by SmilENow on 1/10/15.
//  Copyright (c) 2015 Jiaquan Yin. All rights reserved.
//

#include "GetValue.h"

string get_word(){
    string s;
    cin >> s;
    if (s[0]=='"'){
        s.erase(s.begin());
        return s;
    } else {
        for (auto& i:_exec_value)
            if (i.first==s){
                value* v = i.second->_fun();
                if (!v->check_string()){
                    cout << "The function " << s << " doesn't return a word, error " << endl;
                    exit(1);
                }
                return v->key_string;
            }
    }
    return s;
}

value* get_value(){
    string s;
    cin >> s;
    for (auto& i:_exec_value)
        if (i.first==s){
            value* v = i.second->_fun();
            return v;
        }
    for (auto& i:_namespace)
        if (i.first==s){
            value* v = i.second;
            if (v->check_list()){
                if (v->key_list->key->check_list() && v->key_list->next!=NULL && v->key_list->next->key->check_list())
                    if (v->key_list->next->next->key->type == value::type_string && v->key_list->next->next->key->key_string == "End of list"){
                        totstack++;
                        list* cur = v->key_list->key->key_list;
                        while (cur!=NULL){
                            if (cur->key->check_string() && cur->key->key_string == "End of list") break;
                            if (!cur->key->check_string()){
                                cout << "The elements in arglist is not a word, error" << endl;
                                exit(1);
                            }
                            value* now = get_value();
                            _namespace_stack[totstack][cur->key->key_string] = now;
                            cur = cur->next;
                        }
                        _namespace_stack_parent[totstack] = curstack;
                        curstack = totstack;
                        string str = v->key_list->next->key->key_list->Convert_To_String();
                        int retstack = curstack;
                        execlist(str);
                        value* ret = _namespace_stack_ret[retstack];
                        curstack = _namespace_stack_parent[retstack];
                        return ret;
                    }
            }
        }
    if (s=="true" || s=="True") return new value(true);
    if (s=="false" || s=="False") return new value(false);
    if (s[0]=='"'){
        s.erase(s.begin());
        return new value(s);
    }
    if ((s[0]>='A' && s[0]<='Z') || (s[0]>='a' && s[0]<='z'))
        return new value(s);
    if (s[0]==']') return new value((string)"End of list");
    if (s[0]=='['){
        list* ll = new list();
        ll->key = get_value_to_list();
        if (ll->key->type == value::type_string && ll->key->key_string == "End of list") return new value(ll);
        list* cur = ll;
        while (true){
            list* tmp = new list();
            tmp->key = get_value_to_list();
            cur->next = tmp;
            cur = cur->next;
            if (cur->key->type == value::type_string && cur->key->key_string == "End of list") break;
        }
        return new value(ll);
    }
    return new value(number(s));
}

value* get_value_to_list(){
    string s;
    cin >> s;
    if (s=="true" || s=="True") return new value(true);
    if (s=="false" || s=="False") return new value(false);
    if ((s[0]>='A' && s[0]<='Z') || (s[0]>='a' && s[0]<='z'))
        return new value(s);
    if (s[0]==']') return new value((string)"End of list");
    if (s[0]=='['){
        list* ll = new list();
        ll->key = get_value_to_list();
        if (ll->key->type == value::type_string && ll->key->key_string == "End of list") return new value(ll);
        list* cur = ll;
        while (true){
            list* tmp = new list();
            tmp->key = get_value_to_list();
            cur->next = tmp;
            cur = cur->next;
            if (cur->key->type == value::type_string && cur->key->key_string == "End of list") break;
        }
        return new value(ll);
    }
    if (s[0]>='0' && s[0]<='9') return new value(number(s));
    return new value(s);
}

string get_value(string str,value** v){
    stringstream ss;
    string s,s_ret;
    ss << str;
    ss >> s;
    getline(ss,s_ret);
    
    for (auto& i:_exec_value)
        if (i.first==s){
            *v = i.second->_fun();
            return s_ret;
        }
    if (s=="true" || s=="True") { *v = new value(true); return s_ret; }
    if (s=="false" || s=="False") { *v= new value(false); return s_ret; }
    if ((s[0]>='A' && s[0]<='Z') || (s[0]>='a' && s[0]<='z')){
        *v = new value(s);
        return s_ret;
    }
    if (s[0]==']') { *v = new value((string)"End of list"); return s_ret; }
    if (s[0]=='['){
        list* ll = new list();
        s_ret = get_value_to_list(s_ret,&ll->key);
        if (ll->key->type == value::type_string && ll->key->key_string == "End of list")
        { *v = new value(ll); return s_ret; }
        list* cur = ll;
        while (true){
            list* tmp = new list();
            s_ret = get_value_to_list(s_ret,&tmp->key);
            cur->next = tmp;
            cur = cur->next;
            if (cur->key->type == value::type_string && cur->key->key_string == "End of list") break;
        }
        *v = new value(ll);
        return s_ret;
    }
    *v = new value(number(s));
    return s_ret;
}

string get_value_to_list(string str,value** v){
    stringstream ss;
    string s,s_ret;
    ss << str;
    ss >> s;
    getline(ss,s_ret);
    if (s=="true" || s=="True") { *v = new value(true); return s_ret; }
    if (s=="false" || s=="False") { *v= new value(false); return s_ret; }
    if ((s[0]>='A' && s[0]<='Z') || (s[0]>='a' && s[0]<='z')){
        *v = new value(s);
        return s_ret;
    }
    if (s[0]==']') { *v = new value((string)"End of list"); return s_ret; }
    if (s[0]=='['){
        list* ll = new list();
        s_ret = get_value_to_list(s_ret,&ll->key);
        if (ll->key->type == value::type_string && ll->key->key_string == "End of list")
        { *v = new value(ll); return s_ret; }
        list* cur = ll;
        while (true){
            list* tmp = new list();
            s_ret = get_value_to_list(s_ret,&tmp->key);
            cur->next = tmp;
            cur = cur->next;
            if (cur->key->type == value::type_string && cur->key->key_string == "End of list") break;
        }
        *v = new value(ll);
        return s_ret;
    }
    if (s[0]>='0' && s[0]<='9') *v = new value(number(s));
    else *v = new value(s);
    return s_ret;
}

value* get_value(string s){
    
    while (s.length()>0 && s[0]==' ') s.erase(s.begin());

    if (s=="true" || s=="True") return new value(true);
    if (s=="false" || s=="False") return new value(false);
    if (s[0]=='"'){
        s.erase(s.begin());
        return new value(s);
    }
    if (s[0]>='0' && s[0]<='9') return new value(number(s));
    if (s[0]==']') { return new value((string)"End of list"); }
    if (s[0]=='['){
        s.erase(s.begin());
        list* ll = new list();
        s = get_value(s,&ll->key);
        if (ll->key->check_string() && ll->key->key_string == "End of list") return new value(ll);
        list* cur = ll;
        while (1){
            list* tmp = new list();
            s = get_value_to_list(s,&tmp->key);
            cur->next = tmp;
            cur = cur->next;
            if (cur->key->check_string() && cur->key->key_string == "End of list") break;
        }
        return new value(ll);
    }
    return NULL;
}