//
//  Execute.cpp
//  MUA
//
//  Created by SmilENow on 1/10/15.
//  Copyright (c) 2015 Jiaquan Yin. All rights reserved.
//

#include "Execute.h"

void execute(){
    string s;
    cin >> s;
    for (auto& i:_exec_void)
        if (i.first==s){
            i.second->fun();
            return;
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
                        curstack = _namespace_stack_parent[retstack];
                    }
            }
        }
    cout << "Undefine function " << s << endl;
    exit(1);
}