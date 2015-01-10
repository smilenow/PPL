//
//  Operation.cpp
//  MUA
//
//  Created by SmilENow on 1/9/15.
//  Copyright (c) 2015 Jiaquan Yin. All rights reserved.
//

#include "Operation.h"

void execlist(string str){
    stringstream ss;
    ss << str;
    int tmpstack = curstack;
    while (1){
        string s;
        ss >> s;
        if (s=="") break;
        bool flag = false;
        for (auto& i:_exec_void)
            if (i.first==s){
                i.second->fun(ss);
                flag = true;
                break;
            }
        if (tmpstack != curstack) break;
        if (flag && s=="stop") break;
        if (flag) continue;
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
        if (flag) continue;
        cout << "Undefine function " << s << endl;
        exit(1);
    }
}


// --- --- --- cin --- --- --- //

void _fun_comment::fun(){
    string str;
    getline(cin,str);
}

void _fun_make::fun(){
    string ss = get_word();
    value* v = get_value();
    if (curstack != 0){
        if (_namespace_stack[curstack].count(ss) != 0 ) _namespace_stack[curstack][ss] = v;
        else _namespace_stack[curstack].insert(make_pair(ss,v));
    }
    if (_namespace.count(ss) != 0 ) _namespace[ss] = v;
    else _namespace.insert(make_pair(ss,v));
}

value* _fun_thing::_fun(){
    string ss = get_word();
    if (curstack != 0){
        if (_namespace_stack[curstack].count(ss) != 0 ) return _namespace_stack[curstack][ss];
    }
    if (_namespace.count(ss) == 0){
        cout << "The parameter of thing, " << ss << " doesn't exist in namespace" << endl;
        exit(1);
    }
    return _namespace[ss];
}

value* _fun_colon::_fun(){
    string ss = get_word();
    if (curstack != 0){
        if (_namespace_stack[curstack].count(ss) != 0 ) return _namespace_stack[curstack][ss];
    }
    if (_namespace.count(ss) == 0){
        cout << "The parameter of colon, " << ss << " doesn't exist in namespace" << endl;
        exit(1);
    }
    return _namespace[ss];
}

void _fun_erase::fun(){
    string ss = get_word();
    if (curstack != 0){
        if (_namespace_stack[curstack].count(ss) != 0 ) _namespace_stack[curstack][ss] = NULL;
        return;
    }
    if (_namespace.count(ss) == 0){
        cout << "The parameter of erase, " << ss << " doesn't exist in namespace" << endl;
        exit(1);
    }
    _namespace[ss] = NULL;
}

value* _fun_isname::_fun(){
    string ss = get_word();
    if (curstack != 0){
        if (_namespace_stack[curstack].count(ss) != 0 ) return new value(true);
    }
    if (_namespace.count(ss) == 0) return new value(false);
    return new value(true);
}

void _fun_print::fun(){
    value* v = get_value();
    if (v==NULL){
        cout << "No value!" << endl;
        return;
    }
    v->print();
}

value* _fun_read::_fun(){
    string s;
    cin >> s;
    if (s[0]=='"'){
        s.erase(s.begin());
        return new value(s);
    }
    return new value(number(s));
}

value* _fun_readlinst::_fun(){
    string line;
    getline(cin,line);
    getline(cin,line);
    
    if (line[0]!='['){
        cout << "The first part of the list is not \"[\" , error" << endl;
    }
    line.erase(line.begin());
    
    list* ll = new list();
    line = get_value(line,&ll->key);
    if (ll->key->check_string() && ll->key->key_string == "End of list") return new value(ll);
    list* cur = ll;
    while (1){
        list* tmp = new list();
        line = get_value(line,&tmp->key);
        cur->next = tmp;
        cur = cur->next;
        if (cur->key->check_string() && cur->key->key_string == "End of list") break;
    }
    return new value(ll);
}

value* _fun_add::_fun(){
    value* v1 = get_value();
    if (!v1->check_number()){
        cout << "The first key of add is not a number, error." << endl;
        exit(1);
    }
    value* v2 = get_value();
    if (!v2->check_number()){
        cout << "The second key of add is not a number, error." << endl;
        exit(1);
    }
    if (v1->key_number._CheckDouble() && v2->key_number._CheckDouble())
        return new value(number(v1->key_number.key_double + v2->key_number.key_double));
    
    if (!v1->key_number._CheckDouble() && v2->key_number._CheckDouble())
        return new value(number(v1->key_number.key_int + v2->key_number.key_double));
    
    if (v1->key_number._CheckDouble() && !v2->key_number._CheckDouble())
        return new value(number(v1->key_number.key_double + v2->key_number.key_int));
    
    return new value(number(v1->key_number.key_int + v2->key_number.key_int));
}

value* _fun_sub::_fun(){
    value* v1 = get_value();
    if (!v1->check_number()){
        cout << "The first key of sub is not a number, error." << endl;
        exit(1);
    }
    value* v2 = get_value();
    if (!v2->check_number()){
        cout << "The second key of sub is not a number, error." << endl;
        exit(1);
    }
    if (v1->key_number._CheckDouble() && v2->key_number._CheckDouble())
        return new value(number(v1->key_number.key_double - v2->key_number.key_double));
    
    if (!v1->key_number._CheckDouble() && v2->key_number._CheckDouble())
        return new value(number(v1->key_number.key_int - v2->key_number.key_double));
    
    if (v1->key_number._CheckDouble() && !v2->key_number._CheckDouble())
        return new value(number(v1->key_number.key_double - v2->key_number.key_int));
    
    return new value(number(v1->key_number.key_int - v2->key_number.key_int));
}

value* _fun_mul::_fun(){
    value* v1 = get_value();
    if (!v1->check_number()){
        cout << "The first key of mul is not a number, error." << endl;
        exit(1);
    }
    value* v2 = get_value();
    if (!v2->check_number()){
        cout << "The second key of mul is not a number, error." << endl;
        exit(1);
    }
    if (v1->key_number._CheckDouble() && v2->key_number._CheckDouble())
        return new value(number(v1->key_number.key_double * v2->key_number.key_double));
    
    if (!v1->key_number._CheckDouble() && v2->key_number._CheckDouble())
        return new value(number(v1->key_number.key_int * v2->key_number.key_double));
    
    if (v1->key_number._CheckDouble() && !v2->key_number._CheckDouble())
        return new value(number(v1->key_number.key_double * v2->key_number.key_int));
    
    return new value(number(v1->key_number.key_int * v2->key_number.key_int));
}

value* _fun_div::_fun(){
    value* v1 = get_value();
    if (!v1->check_number()){
        cout << "The first key of div is not a number, error." << endl;
        exit(1);
    }
    value* v2 = get_value();
    if (!v2->check_number()){
        cout << "The second key of div is not a number, error." << endl;
        exit(1);
    }
    if (!v2->key_number._CheckDouble() && v2->key_number.key_int==0){
        cout << "Divide zero!!" << endl;
        exit(1);
    }
    
    if (v1->key_number._CheckDouble() && v2->key_number._CheckDouble())
        return new value(number(v1->key_number.key_double / v2->key_number.key_double));
    
    if (!v1->key_number._CheckDouble() && v2->key_number._CheckDouble())
        return new value(number(v1->key_number.key_int / v2->key_number.key_double));
    
    if (v1->key_number._CheckDouble() && !v2->key_number._CheckDouble())
        return new value(number(v1->key_number.key_double / v2->key_number.key_int));
    
    return new value(number(v1->key_number.key_int / v2->key_number.key_int));
}


value* _fun_mod::_fun(){
    value* v1 = get_value();
    if (!v1->check_number()){
        cout << "The first key of mod is not a number, error." << endl;
        exit(1);
    }
    value* v2 = get_value();
    if (!v2->check_number()){
        cout << "The second key of mod is not a number, error." << endl;
        exit(1);
    }
    if (!v2->key_number._CheckDouble() && v2->key_number.key_int==0){
        cout << "Divide zero!!" << endl;
        exit(1);
    }

    if (v1->key_number._CheckDouble()){
        cout << "The first key of mod is a double, error." << endl;
        exit(1);
    }
    
    if (v2->key_number._CheckDouble()){
        cout << "The second key of mod is a double, error." << endl;
        exit(1);
    }
    
    return new value(number(v1->key_number.key_int % v2->key_number.key_int));
}

value* _fun_eq::_fun(){
    value* v1 = get_value();
    value* v2 = get_value();
    if (v1->type != v2->type){
        cout << "The type between eq is not same, error" << endl;
        exit(1);
    }
    if (v1->type == value::type_number) return new value(v1->key_number==v2->key_number);
    if (v1->type == value::type_string) return new value(v1->key_string==v2->key_string);
    cout << "The parameters of eq is not number | word, error" << endl;
    exit(1);
}

value* _fun_gt::_fun(){
    value* v1 = get_value();
    value* v2 = get_value();
    if (v1->type != v2->type){
        cout << "The type between eq is not same, error" << endl;
        exit(1);
    }
    if (v1->type == value::type_number) return new value(v1->key_number>v2->key_number);
    if (v1->type == value::type_string) return new value(v1->key_string>v2->key_string);
    cout << "The parameters of eq is not number | word, error" << endl;
    exit(1);
}

value* _fun_lt::_fun(){
    value* v1 = get_value();
    value* v2 = get_value();
    if (v1->type != v2->type){
        cout << "The type between eq is not same, error" << endl;
        exit(1);
    }
    if (v1->type == value::type_number) return new value(v1->key_number<v2->key_number);
    if (v1->type == value::type_string) return new value(v1->key_string<v2->key_string);
    cout << "The parameters of eq is not number | word, error" << endl;
    exit(1);
}

value* _fun_and::_fun(){
    value* v1 = get_value();
    if (v1->type != value::type_bool){
        cout << "The first parameter' type of and is not bool, error " << endl;
        exit(1);
    }
    value* v2 = get_value();
    if (v2->type != value::type_bool){
        cout << "The second parameter' type of and is not bool, error " << endl;
        exit(1);
    }
    return new value((v1->key_bool && v2->key_bool));
}

value* _fun_or::_fun(){
    value* v1 = get_value();
    if (v1->type != value::type_bool){
        cout << "The first parameter' type of or is not bool, error " << endl;
        exit(1);
    }
    value* v2 = get_value();
    if (v2->type != value::type_bool){
        cout << "The second parameter' type of or is not bool, error " << endl;
        exit(1);
    }
    return new value((v1->key_bool || v2->key_bool));
}


value* _fun_not::_fun(){
    value* v1 = get_value();
    if (v1->type != value::type_bool){
        cout << "The parameter' type of not is not bool, error " << endl;
        exit(1);
    }
    return new value((not v1->key_bool));
}

value* _fun_random::_fun(){
    value* v1 = get_value();
    if (v1->type!=value::type_number){
        cout << "The parameter of random is not number, error" << endl;
    }
    int x;
    if (v1->key_number._CheckDouble()) x=(int)v1->key_number.key_double;
    else x = v1->key_number.key_int;
    srand((unsigned)time(NULL));
    return new value(number((rand()%x)));
}

value* _fun_sqrt::_fun(){
    value* v1 = get_value();
    if (v1->type!=value::type_number){
        cout << "The parameter of random is not number, error" << endl;
    }
    if (v1->key_number._CheckDouble())
        return new value(number(sqrt(v1->key_number.key_double)));
    else return new value(number(sqrt(v1->key_number.key_int)));
}

value* _fun_isnumber::_fun(){
    value* v1 = get_value();
    return new value(v1->check_number());
}

value* _fun_isword::_fun(){
    value* v1 = get_value();
    return new value(v1->check_string());
}

value* _fun_islist::_fun(){
    value* v1 = get_value();
    return new value(v1->check_list());
}

value* _fun_isbool::_fun(){
    value* v1 = get_value();
    return new value(v1->check_bool());
}

value* _fun_isempty::_fun(){
    value* v1 = get_value();
    if (v1->check_string()) return new value(v1->key_string == "" || v1->key_string.length() == 0);
    if (v1->check_list()){
        if (v1->key_list==NULL) return new value(true);
        if ((v1->key_list->key->type == -1) && (v1->key_list->next == NULL)) return new value(true);
        if (v1->key_list->key->check_string() && v1->key_list->key->key_string == "End of list") return new value(true);
        return new value(false);
    }
    cout << "The parameter of isempty is not word | list , error " << endl;
    exit(1);
}

void _fun_test::fun(){
    value* v1 = get_value();
    if (!v1->check_bool()){
        cout << "The parameter of test is not bool, error " << endl;
        exit(1);
    }
    _test_ret = v1->key_bool;
}

void _fun_iftrue::fun(){
    value* v1 = get_value();
    if (!_test_ret) return;
    if (!v1->check_list()){
        cout << "The parameter of iftrue is not list, error " << endl;
        exit(1);
    }
    
    string s = v1->key_list->Convert_To_String();
    execlist(s);
}

void _fun_iffalse::fun(){
    value* v1 = get_value();
    if (_test_ret) return;
    if (!v1->check_list()){
        cout << "The parameter of iffalse is not list, error " << endl;
        exit(1);
    }

    string s = v1->key_list->Convert_To_String();
    execlist(s);
}

value* _fun_word::_fun(){
    value* v1 = get_value();
    if (!v1->check_string()){
        cout << "The first parameter of word is not word, error " << endl;
        exit(1);
    }
    value* v2 = get_value();
    if (v2->check_list()){
        cout << "The second parameter of word is list, error " << endl;
        exit(1);
    }
    string s = v1->key_string;
    stringstream ss;
    if (v2->check_bool()){
        if (v2->key_bool) s = s + "True";
        else s = s + "False";
    }
    if (v2->check_number()){
        if (v2->key_number._CheckDouble()) ss << v2->key_number.key_double;
        else ss << v2->key_number.key_int;
        string s2;
        ss >> s2;
        s = s + s2;
    }
    if (v2->check_string()) s = s + v2->key_string;
    return new value(s);
}

value* _fun_list::_fun(){
    value* v1 = get_value();
    if (!v1->check_list()){
        cout << "The first parameter of list is not list, error " << endl;
        exit(1);
    }
    value* v2 = get_value();
    if (!v2->check_list()){
        cout << "The second parameter of list is not list, error " << endl;
        exit(1);
    }
    list* l = v1->key_list;
    list* l2 = v2->key_list;
    list* cur = l;
    if (cur->key->check_string() && cur->key->key_string == "End of list") return new value(l2);
    list* pre = cur;
    cur = cur->next;
    while (cur!=NULL){
        if (cur->key->check_string() && cur->key->key_string == "End of list") break;
        cur = cur->next;
        pre = pre->next;
    }
    pre->next = l2;
    return new value(l);
}

void _fun_join::fun(){
    value* v1 = get_value();
    if (!v1->check_list()){
        cout << "The first parameter of join is not list, error " << endl;
        exit(1);
    }
    value* v2 = get_value();
    list* cur = v1->key_list;
    while (cur!=NULL){
        if (cur->key->check_string() && cur->key->key_string == "End of list") break;
        cur = cur->next;
    }
    cur->key = v2;
    cur->next = new list(new value((string)"End of list"));
}

value* _fun_first::_fun(){
    value *v1 = get_value();
    if (v1->check_string()){
        if (v1->key_string.length() == 0){
            cout << "The word is empty, cannot find the first character" << endl;
            exit(1);
        }
        string str = "";
        str = str + v1->key_string[0];
        return new value(str);
    }
    if (v1->check_list()) {
        if (v1->key_list->key->check_string() && v1->key_list->key->key_string == "End of list") {
            cout << "The list is empty, cannot find the first item" << endl;
            exit(1);
        }
        return v1->key_list->key;
    }
    cout << "The parameter of first is not word | list , error " << endl;
    exit(1);
}

value* _fun_last::_fun(){
    value *v1 = get_value();
    if (v1->check_string()){
        if (v1->key_string.length() == 0){
            cout << "The word is empty, cannot find the last character" << endl;
            exit(1);
        }
        string str = "";
        str = str + v1->key_string[v1->key_string.length()-1];
        return new value(str);
    }
    if (v1->check_list()){
        list* cur = v1->key_list;
        if (cur->key->check_string() && cur->key->key_string == "End of list") {
            cout << "The list is empty, cannot find the last item" << endl;
            exit(1);
        }
        list* pre = v1->key_list;
        cur = cur->next;
        while (cur!=NULL){
            if (cur->key->check_string() && cur->key->key_string == "End of list")
                return pre->key;
            pre = pre->next;
            cur = cur->next;
        }
    }
    cout << "The parameter of last is not word | list , error " << endl;
    exit(1);
}

value* _fun_butfirst::_fun(){
    value *v1 = get_value();
    if (v1->check_string()){
        string s = v1->key_string;
        if (s.length() == 0){
            cout << "The word is empty, cannot find the butfirst character" << endl;
            exit(1);
        }
        s.erase(s.begin());
        return new value(s);
    }
    if (v1->check_list()){
        list* cur = v1->key_list;
        if (cur->key->check_string() && cur->key->key_string == "End of list") {
            cout << "The list is empty, cannot find the butfirst item" << endl;
            exit(1);
        }
        cur=cur->next;
        list* ret_head = NULL,* ret = NULL;
        while (cur!=NULL){
            if (cur->key->check_string() && cur->key->key_string == "End of list"){
                if (ret_head==NULL) return new value(new list(new value((string)"End of list")));
                ret->next = new list(new value((string)"End of list"));
                return new value(ret_head);
            }
            if (ret==NULL){
                ret = new list(new value(cur->key));
                ret_head = ret;
            } else {
                ret->next = new list(new value(cur->key));
                ret = ret->next;
            }
            cur = cur->next;
        }
    }
    cout << "The parameter of butfirst is not word | list , error " << endl;
    exit(1);
}

value* _fun_butlast::_fun(){
    value *v1 = get_value();
    if (v1->check_string()){
        string s = v1->key_string;
        if (s.length() == 0){
            cout << "The word is empty, cannot find the butlast character" << endl;
            exit(1);
        }
        s.erase(s.end()-1);
        return new value(s);
    }
    if (v1->check_list()){
        list* cur = v1->key_list;
        if (cur->key->check_string() && cur->key->key_string == "End of list") {
            cout << "The list is empty, cannot find the butlast item" << endl;
            exit(1);
        }
        list* pre = cur;
        cur = cur->next;
        list* ret = NULL;
        list* ret_head = NULL;
        while (cur!=NULL){
            if (cur->key->check_string() && cur->key->key_string == "End of list"){
                if (ret_head==NULL) return new value(new list(new value((string)"End of list")));
                ret->next = new list(new value((string)"End of list"));
                return new value(ret_head);
            }
            if (ret==NULL){
                ret = new list(new value(pre->key));
                ret_head = ret;
            } else {
                ret->next = new list(new value(pre->key));
                ret = ret->next;
            }
            cur = cur->next;
            pre = pre->next;
        }
    }
    cout << "The parameter of butlast is not word | list , error " << endl;
    exit(1);
}

value* _fun_item::_fun(){
    value* v1 = get_value();
    if (!v1->check_number()){
        cout << "The first parameter' type of item is not number , error " << endl;
        exit(1);
    }
    if (v1->key_number._CheckDouble()){
        cout << "The number is double, error" << endl;
        exit(1);
    }
    value* v2 = get_value();
    if (v2->check_string()){
        if (v2->key_string.length()<v1->key_number.key_int){
            cout << "The word is shorter than the required number, error" << endl;
            exit(1);
        }
        return new value(v2->key_string[v1->key_number.key_int-1]);
    }
    if (v2->check_list()){
        list* cur = v2->key_list;
        int tot = 0;
        while (cur!=NULL){
            if (cur->key->check_string() && cur->key->key_string == "End of list"){
                cout << "The list is shorter than the required number, error" << endl;
                exit(1);
            }
            tot++;
            if (tot==v1->key_number.key_int) return cur->key;
            cur = cur->next;
        }
    }
    cout << "The second parameter' type of item is not word | list , error " << endl;
    exit(1);
}

void _fun_repeat::fun(){
    value* v1 = get_value();
    if (!v1->check_number()){
        cout << "The first parameter' type of item is not number , error " << endl;
        exit(1);
    }
    if (v1->key_number._CheckDouble()){
        cout << "The number is double, error" << endl;
        exit(1);
    }
    value *v2 = get_value();
    for (int i=0;i<v1->key_number.key_int;i++){
        string s = v2->key_list->Convert_To_String();
        execlist(s);
    }
}

void _fun_stop::fun(){
    if (curstack == 0) { cout << "Exit successfullly." << endl; exit(0); }
    curstack = _namespace_stack_parent[curstack];
}

void _fun_wait::fun(){
    value *v1 = get_value();
    if (!v1->check_number()){
        cout << "The first parameter' type of item is not number , error " << endl;
        exit(1);
    }
    int time;
    if (v1->key_number._CheckDouble()) time = (int)v1->key_number.key_double;
    else time = v1->key_number.key_int;
    
    std::chrono::milliseconds dura( time );
    std::this_thread::sleep_for( dura );
}

void _fun_save::fun(){
    value* v1 = get_value();
    if (!v1->check_string()){
        cout << "The parameter of save is not word, error" << endl;
        exit(1);
    }
    if (v1->key_string.length()==0){
        cout << "The parameter of save is empty, error" << endl;
        exit(1);
    }
    ofstream fout(v1->key_string);
    for (auto &i:_namespace){
        fout << "make \"" << i.first << " ";
        i.second->print(fout);
        fout << endl;
    }
    fout << "$EOF$" << endl;
    fout.close();
}

void _fun_load::fun(){
    value* v1 = get_value();
    if (!v1->check_string()){
        cout << "The parameter of save is not word, error" << endl;
        exit(1);
    }
    if (v1->key_string.length()==0){
        cout << "The parameter of save is empty, error" << endl;
        exit(1);
    }
    ifstream fin(v1->key_string);
    while (!fin.eof()){
        string s;
        getline(fin,s);
        stringstream ss;
        ss << s;
        string s1,s2;
        ss >> s1;
        if (s1 == "$EOF$") break;
        ss >> s2;
        s2.erase(s2.begin());
        getline(ss,s);
        value* v = get_value(s);
        _namespace.insert(make_pair(s2, v));
    }
    fin.close();
}

void _fun_erall::fun(){
    _namespace.clear();
}

void _fun_poall::fun(){
    for (auto &i:_namespace){
        cout << "The value of " << i.first << endl;
        i.second->print();
    }
}

void _fun_if::fun(){
    value* v1 = get_value();
    if (!v1->check_bool()){
        cout << "The first parameter of if is not bool, error" << endl;
        exit(1);
    }
    value *v2 = get_value();
    if (!v2->check_list()){
        cout << "The second parameter of if is not list, error" << endl;
        exit(1);
    }
    value *v3 = get_value();
    if (!v3->check_list()){
        cout << "The third parameter of if is not list, error" << endl;
        exit(1);
    }
    if (v1->key_bool){
        string s = v2->key_list->Convert_To_String();
        execlist(s);
    }
    else{
        string s = v3->key_list->Convert_To_String();
        execlist(s);
    }
}

void _fun_run::fun(){
    value *v1 = get_value();
    if (!v1->check_list()){
        cout << "The parameter of run is not list, error" << endl;
        exit(1);
    }
    string s = v1->key_list->Convert_To_String();
    execlist(s);
}

void _fun_output::fun(){
    value* v1 = get_value();
    _namespace_stack_ret[curstack] = v1;
}

void _fun_local::fun(){
    value* v1 = get_value();
    if (!v1->check_string()){
        cout << "The local definition is not a word variable, error" << endl;
        exit(1);
    }
    _namespace_stack[curstack][v1->key_string] = NULL;
}

// --- --- --- --- --- --- --- //
// --- --- --- sin --- --- --- //
// --- --- --- --- --- --- --- //

void _fun_comment::fun(stringstream& sin){
    string str;
    getline(sin,str);
}

void _fun_make::fun(stringstream& sin){
    string ss = get_word(sin);
    value* v = get_value(sin);
    if (curstack != 0){
        if (_namespace_stack[curstack].count(ss) != 0 ) _namespace_stack[curstack][ss] = v;
        else _namespace_stack[curstack].insert(make_pair(ss,v));
    }
    if (_namespace.count(ss) != 0 ) _namespace[ss] = v;
    else _namespace.insert(make_pair(ss,v));
}

value* _fun_thing::_fun(stringstream& sin){
    string ss = get_word(sin);
    if (curstack != 0){
        if (_namespace_stack[curstack].count(ss) != 0 ) return _namespace_stack[curstack][ss];
    }
    if (_namespace.count(ss) == 0){
        cout << "The parameter of thing, " << ss << " doesn't exist in namespace" << endl;
        exit(1);
    }
    return _namespace[ss];
}

value* _fun_colon::_fun(stringstream& sin){
    string ss = get_word(sin);
    if (curstack != 0){
        if (_namespace_stack[curstack].count(ss) != 0 ) return _namespace_stack[curstack][ss];
    }
    if (_namespace.count(ss) == 0){
        cout << "The parameter of colon, " << ss << " doesn't exist in namespace" << endl;
        exit(1);
    }
    return _namespace[ss];
}

void _fun_erase::fun(stringstream& sin){
    string ss = get_word(sin);
    if (curstack != 0){
        if (_namespace_stack[curstack].count(ss) != 0 ) _namespace_stack[curstack][ss] = NULL;
        return;
    }
    if (_namespace.count(ss) == 0){
        cout << "The parameter of erase, " << ss << " doesn't exist in namespace" << endl;
        exit(1);
    }
    _namespace[ss] = NULL;
}

value* _fun_isname::_fun(stringstream& sin){
    string ss = get_word(sin);
    if (curstack != 0){
        if (_namespace_stack[curstack].count(ss) != 0 ) return new value(true);
    }
    if (_namespace.count(ss) == 0) return new value(false);
    return new value(true);
}

void _fun_print::fun(stringstream& sin){
    value* v = get_value(sin);
    if (v==NULL){
        cout << "No value!" << endl;
        return;
    }
    v->print();
}

value* _fun_read::_fun(stringstream& sin){
    string s;
    sin >> s;
    if (s[0]=='"'){
        s.erase(s.begin());
        return new value(s);
    }
    return new value(number(s));
}

value* _fun_readlinst::_fun(stringstream& sin){
    string line;
    getline(cin,line);
    getline(cin,line);
    
    if (line[0]!='['){
        cout << "The first part of the list is not \"[\" , error" << endl;
    }
    line.erase(line.begin());
    
    list* ll = new list();
    line = get_value(line,&ll->key);
    if (ll->key->check_string() && ll->key->key_string == "End of list") return new value(ll);
    list* cur = ll;
    while (1){
        list* tmp = new list();
        line = get_value(line,&tmp->key);
        cur->next = tmp;
        cur = cur->next;
        if (cur->key->check_string() && cur->key->key_string == "End of list") break;
    }
    return new value(ll);
}

value* _fun_add::_fun(stringstream& sin){
    value* v1 = get_value(sin);
    if (!v1->check_number()){
        cout << "The first key of add is not a number, error." << endl;
        exit(1);
    }
    value* v2 = get_value(sin);
    if (!v2->check_number()){
        cout << "The second key of add is not a number, error." << endl;
        exit(1);
    }
    if (v1->key_number._CheckDouble() && v2->key_number._CheckDouble())
        return new value(number(v1->key_number.key_double + v2->key_number.key_double));
    
    if (!v1->key_number._CheckDouble() && v2->key_number._CheckDouble())
        return new value(number(v1->key_number.key_int + v2->key_number.key_double));
    
    if (v1->key_number._CheckDouble() && !v2->key_number._CheckDouble())
        return new value(number(v1->key_number.key_double + v2->key_number.key_int));
    
    return new value(number(v1->key_number.key_int + v2->key_number.key_int));
}

value* _fun_sub::_fun(stringstream& sin){
    value* v1 = get_value(sin);
    if (!v1->check_number()){
        cout << "The first key of sub is not a number, error." << endl;
        exit(1);
    }
    value* v2 = get_value(sin);
    if (!v2->check_number()){
        cout << "The second key of sub is not a number, error." << endl;
        exit(1);
    }
    if (v1->key_number._CheckDouble() && v2->key_number._CheckDouble())
        return new value(number(v1->key_number.key_double - v2->key_number.key_double));
    
    if (!v1->key_number._CheckDouble() && v2->key_number._CheckDouble())
        return new value(number(v1->key_number.key_int - v2->key_number.key_double));
    
    if (v1->key_number._CheckDouble() && !v2->key_number._CheckDouble())
        return new value(number(v1->key_number.key_double - v2->key_number.key_int));
    
    return new value(number(v1->key_number.key_int - v2->key_number.key_int));
}

value* _fun_mul::_fun(stringstream& sin){
    value* v1 = get_value(sin);
    if (!v1->check_number()){
        cout << "The first key of mul is not a number, error." << endl;
        exit(1);
    }
    value* v2 = get_value(sin);
    if (!v2->check_number()){
        cout << "The second key of mul is not a number, error." << endl;
        exit(1);
    }
    if (v1->key_number._CheckDouble() && v2->key_number._CheckDouble())
        return new value(number(v1->key_number.key_double * v2->key_number.key_double));
    
    if (!v1->key_number._CheckDouble() && v2->key_number._CheckDouble())
        return new value(number(v1->key_number.key_int * v2->key_number.key_double));
    
    if (v1->key_number._CheckDouble() && !v2->key_number._CheckDouble())
        return new value(number(v1->key_number.key_double * v2->key_number.key_int));
    
    return new value(number(v1->key_number.key_int * v2->key_number.key_int));
}

value* _fun_div::_fun(stringstream& sin){
    value* v1 = get_value(sin);
    if (!v1->check_number()){
        cout << "The first key of div is not a number, error." << endl;
        exit(1);
    }
    value* v2 = get_value(sin);
    if (!v2->check_number()){
        cout << "The second key of div is not a number, error." << endl;
        exit(1);
    }
    if (!v2->key_number._CheckDouble() && v2->key_number.key_int==0){
        cout << "Divide zero!!" << endl;
        exit(1);
    }
    
    if (v1->key_number._CheckDouble() && v2->key_number._CheckDouble())
        return new value(number(v1->key_number.key_double / v2->key_number.key_double));
    
    if (!v1->key_number._CheckDouble() && v2->key_number._CheckDouble())
        return new value(number(v1->key_number.key_int / v2->key_number.key_double));
    
    if (v1->key_number._CheckDouble() && !v2->key_number._CheckDouble())
        return new value(number(v1->key_number.key_double / v2->key_number.key_int));
    
    return new value(number(v1->key_number.key_int / v2->key_number.key_int));
}


value* _fun_mod::_fun(stringstream& sin){
    value* v1 = get_value(sin);
    if (!v1->check_number()){
        cout << "The first key of mod is not a number, error." << endl;
        exit(1);
    }
    value* v2 = get_value(sin);
    if (!v2->check_number()){
        cout << "The second key of mod is not a number, error." << endl;
        exit(1);
    }
    if (!v2->key_number._CheckDouble() && v2->key_number.key_int==0){
        cout << "Divide zero!!" << endl;
        exit(1);
    }
    
    if (v1->key_number._CheckDouble()){
        cout << "The first key of mod is a double, error." << endl;
        exit(1);
    }
    
    if (v2->key_number._CheckDouble()){
        cout << "The second key of mod is a double, error." << endl;
        exit(1);
    }
    
    return new value(number(v1->key_number.key_int % v2->key_number.key_int));
}

value* _fun_eq::_fun(stringstream& sin){
    value* v1 = get_value(sin);
    value* v2 = get_value(sin);
    if (v1->type != v2->type){
        cout << "The type between eq is not same, error" << endl;
        exit(1);
    }
    if (v1->type == value::type_number) return new value(v1->key_number==v2->key_number);
    if (v1->type == value::type_string) return new value(v1->key_string==v2->key_string);
    cout << "The parameters of eq is not number | word, error" << endl;
    exit(1);
}

value* _fun_gt::_fun(stringstream& sin){
    value* v1 = get_value(sin);
    value* v2 = get_value(sin);
    if (v1->type != v2->type){
        cout << "The type between eq is not same, error" << endl;
        exit(1);
    }
    if (v1->type == value::type_number) return new value(v1->key_number>v2->key_number);
    if (v1->type == value::type_string) return new value(v1->key_string>v2->key_string);
    cout << "The parameters of eq is not number | word, error" << endl;
    exit(1);
}

value* _fun_lt::_fun(stringstream& sin){
    value* v1 = get_value(sin);
    value* v2 = get_value(sin);
    if (v1->type != v2->type){
        cout << "The type between eq is not same, error" << endl;
        exit(1);
    }
    if (v1->type == value::type_number) return new value(v1->key_number<v2->key_number);
    if (v1->type == value::type_string) return new value(v1->key_string<v2->key_string);
    cout << "The parameters of eq is not number | word, error" << endl;
    exit(1);
}

value* _fun_and::_fun(stringstream& sin){
    value* v1 = get_value(sin);
    if (v1->type != value::type_bool){
        cout << "The first parameter' type of and is not bool, error " << endl;
        exit(1);
    }
    value* v2 = get_value(sin);
    if (v2->type != value::type_bool){
        cout << "The second parameter' type of and is not bool, error " << endl;
        exit(1);
    }
    return new value((v1->key_bool && v2->key_bool));
}

value* _fun_or::_fun(stringstream& sin){
    value* v1 = get_value(sin);
    if (v1->type != value::type_bool){
        cout << "The first parameter' type of or is not bool, error " << endl;
        exit(1);
    }
    value* v2 = get_value(sin);
    if (v2->type != value::type_bool){
        cout << "The second parameter' type of or is not bool, error " << endl;
        exit(1);
    }
    return new value((v1->key_bool || v2->key_bool));
}


value* _fun_not::_fun(stringstream& sin){
    value* v1 = get_value(sin);
    if (v1->type != value::type_bool){
        cout << "The parameter' type of not is not bool, error " << endl;
        exit(1);
    }
    return new value((not v1->key_bool));
}

value* _fun_random::_fun(stringstream& sin){
    value* v1 = get_value(sin);
    if (v1->type!=value::type_number){
        cout << "The parameter of random is not number, error" << endl;
    }
    int x;
    if (v1->key_number._CheckDouble()) x=(int)v1->key_number.key_double;
    else x = v1->key_number.key_int;
    srand((unsigned)time(NULL));
    return new value(number((rand()%x)));
}

value* _fun_sqrt::_fun(stringstream& sin){
    value* v1 = get_value(sin);
    if (v1->type!=value::type_number){
        cout << "The parameter of random is not number, error" << endl;
    }
    if (v1->key_number._CheckDouble())
        return new value(number(sqrt(v1->key_number.key_double)));
    else return new value(number(sqrt(v1->key_number.key_int)));
}

value* _fun_isnumber::_fun(stringstream& sin){
    value* v1 = get_value(sin);
    return new value(v1->check_number());
}

value* _fun_isword::_fun(stringstream& sin){
    value* v1 = get_value(sin);
    return new value(v1->check_string());
}

value* _fun_islist::_fun(stringstream& sin){
    value* v1 = get_value(sin);
    return new value(v1->check_list());
}

value* _fun_isbool::_fun(stringstream& sin){
    value* v1 = get_value(sin);
    return new value(v1->check_bool());
}

value* _fun_isempty::_fun(stringstream& sin){
    value* v1 = get_value(sin);
    if (v1->check_string()) return new value(v1->key_string == "" || v1->key_string.length() == 0);
    if (v1->check_list()){
        if (v1->key_list==NULL) return new value(true);
        if ((v1->key_list->key->type == -1) && (v1->key_list->next == NULL)) return new value(true);
        if (v1->key_list->key->check_string() && v1->key_list->key->key_string == "End of list") return new value(true);
        return new value(false);
    }
    cout << "The parameter of isempty is not word | list , error " << endl;
    exit(1);
}

void _fun_test::fun(stringstream& sin){
    value* v1 = get_value(sin);
    if (!v1->check_bool()){
        cout << "The parameter of test is not bool, error " << endl;
        exit(1);
    }
    _test_ret = v1->key_bool;
}

void _fun_iftrue::fun(stringstream& sin){
    value* v1 = get_value(sin);
    if (!_test_ret) return;
    if (!v1->check_list()){
        cout << "The parameter of iftrue is not list, error " << endl;
        exit(1);
    }
    
    string s = v1->key_list->Convert_To_String();
    execlist(s);
}

void _fun_iffalse::fun(stringstream& sin){
    value* v1 = get_value(sin);
    if (_test_ret) return;
    if (!v1->check_list()){
        cout << "The parameter of iffalse is not list, error " << endl;
        exit(1);
    }
    
    string s = v1->key_list->Convert_To_String();
    execlist(s);
}

value* _fun_word::_fun(stringstream& sin){
    value* v1 = get_value(sin);
    if (!v1->check_string()){
        cout << "The first parameter of word is not word, error " << endl;
        exit(1);
    }
    value* v2 = get_value(sin);
    if (v2->check_list()){
        cout << "The second parameter of word is list, error " << endl;
        exit(1);
    }
    string s = v1->key_string;
    stringstream ss;
    if (v2->check_bool()){
        if (v2->key_bool) s = s + "True";
        else s = s + "False";
    }
    if (v2->check_number()){
        if (v2->key_number._CheckDouble()) ss << v2->key_number.key_double;
        else ss << v2->key_number.key_int;
        string s2;
        ss >> s2;
        s = s + s2;
    }
    if (v2->check_string()) s = s + v2->key_string;
    return new value(s);
}

value* _fun_list::_fun(stringstream& sin){
    value* v1 = get_value(sin);
    if (!v1->check_list()){
        cout << "The first parameter of list is not list, error " << endl;
        exit(1);
    }
    value* v2 = get_value(sin);
    if (!v2->check_list()){
        cout << "The second parameter of list is not list, error " << endl;
        exit(1);
    }
    list* l = v1->key_list;
    list* l2 = v2->key_list;
    list* cur = l;
    if (cur->key->check_string() && cur->key->key_string == "End of list") return new value(l2);
    list* pre = cur;
    cur = cur->next;
    while (cur!=NULL){
        if (cur->key->check_string() && cur->key->key_string == "End of list") break;
        cur = cur->next;
        pre = pre->next;
    }
    pre->next = l2;
    return new value(l);
}

void _fun_join::fun(stringstream& sin){
    value* v1 = get_value(sin);
    if (!v1->check_list()){
        cout << "The first parameter of join is not list, error " << endl;
        exit(1);
    }
    value* v2 = get_value(sin);
    list* cur = v1->key_list;
    while (cur!=NULL){
        if (cur->key->check_string() && cur->key->key_string == "End of list") break;
        cur = cur->next;
    }
    cur->key = v2;
    cur->next = new list(new value((string)"End of list"));
}

value* _fun_first::_fun(stringstream& sin){
    value *v1 = get_value(sin);
    if (v1->check_string()){
        if (v1->key_string.length() == 0){
            cout << "The word is empty, cannot find the first character" << endl;
            exit(1);
        }
        string str = "";
        str = str + v1->key_string[0];
        return new value(str);
    }
    if (v1->check_list()) {
        if (v1->key_list->key->check_string() && v1->key_list->key->key_string == "End of list") {
            cout << "The list is empty, cannot find the first item" << endl;
            exit(1);
        }
        return v1->key_list->key;
    }
    cout << "The parameter of first is not word | list , error " << endl;
    exit(1);
}

value* _fun_last::_fun(stringstream& sin){
    value *v1 = get_value(sin);
    if (v1->check_string()){
        if (v1->key_string.length() == 0){
            cout << "The word is empty, cannot find the last character" << endl;
            exit(1);
        }
        string str = "";
        str = str + v1->key_string[v1->key_string.length()-1];
        return new value(str);
    }
    if (v1->check_list()){
        list* cur = v1->key_list;
        if (cur->key->check_string() && cur->key->key_string == "End of list") {
            cout << "The list is empty, cannot find the last item" << endl;
            exit(1);
        }
        list* pre = v1->key_list;
        cur = cur->next;
        while (cur!=NULL){
            if (cur->key->check_string() && cur->key->key_string == "End of list")
                return pre->key;
            pre = pre->next;
            cur = cur->next;
        }
    }
    cout << "The parameter of last is not word | list , error " << endl;
    exit(1);
}

value* _fun_butfirst::_fun(stringstream& sin){
    value *v1 = get_value(sin);
    if (v1->check_string()){
        string s = v1->key_string;
        if (s.length() == 0){
            cout << "The word is empty, cannot find the butfirst character" << endl;
            exit(1);
        }
        s.erase(s.begin());
        return new value(s);
    }
    if (v1->check_list()){
        list* cur = v1->key_list;
        if (cur->key->check_string() && cur->key->key_string == "End of list") {
            cout << "The list is empty, cannot find the butfirst item" << endl;
            exit(1);
        }
        cur=cur->next;
        list* ret_head = NULL,* ret = NULL;
        while (cur!=NULL){
            if (cur->key->check_string() && cur->key->key_string == "End of list"){
                if (ret_head==NULL) return new value(new list(new value((string)"End of list")));
                ret->next = new list(new value((string)"End of list"));
                return new value(ret_head);
            }
            if (ret==NULL){
                ret = new list(new value(cur->key));
                ret_head = ret;
            } else {
                ret->next = new list(new value(cur->key));
                ret = ret->next;
            }
            cur = cur->next;
        }
    }
    cout << "The parameter of butfirst is not word | list , error " << endl;
    exit(1);
}

value* _fun_butlast::_fun(stringstream& sin){
    value *v1 = get_value(sin);
    if (v1->check_string()){
        string s = v1->key_string;
        if (s.length() == 0){
            cout << "The word is empty, cannot find the butlast character" << endl;
            exit(1);
        }
        s.erase(s.end()-1);
        return new value(s);
    }
    if (v1->check_list()){
        list* cur = v1->key_list;
        if (cur->key->check_string() && cur->key->key_string == "End of list") {
            cout << "The list is empty, cannot find the butlast item" << endl;
            exit(1);
        }
        list* pre = cur;
        cur = cur->next;
        list* ret = NULL;
        list* ret_head = NULL;
        while (cur!=NULL){
            if (cur->key->check_string() && cur->key->key_string == "End of list"){
                if (ret_head==NULL) return new value(new list(new value((string)"End of list")));
                ret->next = new list(new value((string)"End of list"));
                return new value(ret_head);
            }
            if (ret==NULL){
                ret = new list(new value(pre->key));
                ret_head = ret;
            } else {
                ret->next = new list(new value(pre->key));
                ret = ret->next;
            }
            cur = cur->next;
            pre = pre->next;
        }
    }
    cout << "The parameter of butlast is not word | list , error " << endl;
    exit(1);
}

value* _fun_item::_fun(stringstream& sin){
    value* v1 = get_value(sin);
    if (!v1->check_number()){
        cout << "The first parameter' type of item is not number , error " << endl;
        exit(1);
    }
    if (v1->key_number._CheckDouble()){
        cout << "The number is double, error" << endl;
        exit(1);
    }
    value* v2 = get_value(sin);
    if (v2->check_string()){
        if (v2->key_string.length()<v1->key_number.key_int){
            cout << "The word is shorter than the required number, error" << endl;
            exit(1);
        }
        return new value(v2->key_string[v1->key_number.key_int-1]);
    }
    if (v2->check_list()){
        list* cur = v2->key_list;
        int tot = 0;
        while (cur!=NULL){
            if (cur->key->check_string() && cur->key->key_string == "End of list"){
                cout << "The list is shorter than the required number, error" << endl;
                exit(1);
            }
            tot++;
            if (tot==v1->key_number.key_int) return cur->key;
            cur = cur->next;
        }
    }
    cout << "The second parameter' type of item is not word | list , error " << endl;
    exit(1);
}

void _fun_repeat::fun(stringstream& sin){
    value* v1 = get_value(sin);
    if (!v1->check_number()){
        cout << "The first parameter' type of item is not number , error " << endl;
        exit(1);
    }
    if (v1->key_number._CheckDouble()){
        cout << "The number is double, error" << endl;
        exit(1);
    }
    value *v2 = get_value(sin);
    for (int i=0;i<v1->key_number.key_int;i++){
        string s = v2->key_list->Convert_To_String();
        execlist(s);
    }
}

void _fun_stop::fun(stringstream& sin){
    if (curstack == 0) { cout << "Exit successfullly." << endl; exit(0); }
    curstack = _namespace_stack_parent[curstack];
}

void _fun_wait::fun(stringstream& sin){
    value *v1 = get_value(sin);
    if (!v1->check_number()){
        cout << "The first parameter' type of item is not number , error " << endl;
        exit(1);
    }
    int time;
    if (v1->key_number._CheckDouble()) time = (int)v1->key_number.key_double;
    else time = v1->key_number.key_int;
    
    std::chrono::milliseconds dura( time );
    std::this_thread::sleep_for( dura );
}

void _fun_save::fun(stringstream& sin){
    value* v1 = get_value(sin);
    if (!v1->check_string()){
        cout << "The parameter of save is not word, error" << endl;
        exit(1);
    }
    if (v1->key_string.length()==0){
        cout << "The parameter of save is empty, error" << endl;
        exit(1);
    }
    ofstream fout(v1->key_string);
    for (auto &i:_namespace){
        fout << "make \"" << i.first;
        i.second->print(fout);
        fout << endl;
    }
    fout.close();
}

void _fun_load::fun(stringstream& sin){
    value* v1 = get_value(sin);
    if (!v1->check_string()){
        cout << "The parameter of save is not word, error" << endl;
        exit(1);
    }
    if (v1->key_string.length()==0){
        cout << "The parameter of save is empty, error" << endl;
        exit(1);
    }
    ifstream fin(v1->key_string);
    while (!fin.eof()){
        string s;
        getline(fin,s);
        stringstream ss;
        ss << s;
        string s1,s2;
        ss >> s1;
        ss >> s2;
        s2.erase(s2.begin());
        getline(ss,s);
        value* v = get_value(s);
        _namespace.insert(make_pair(s2, v));
    }
    fin.close();
}

void _fun_erall::fun(stringstream& sin){
    _namespace.clear();
}

void _fun_poall::fun(stringstream& sin){
    for (auto &i:_namespace){
        cout << "The value of " << i.first << endl;
        i.second->print();
    }
}

void _fun_if::fun(stringstream& sin){
    value* v1 = get_value(sin);
    if (!v1->check_bool()){
        cout << "The first parameter of if is not bool, error" << endl;
        exit(1);
    }
    value *v2 = get_value(sin);
    if (!v2->check_list()){
        cout << "The second parameter of if is not list, error" << endl;
        exit(1);
    }
    value *v3 = get_value(sin);
    if (!v3->check_list()){
        cout << "The third parameter of if is not list, error" << endl;
        exit(1);
    }
    if (v1->key_bool){
        string s = v2->key_list->Convert_To_String();
        execlist(s);
    }
    else{
        string s = v3->key_list->Convert_To_String();
        execlist(s);
    }
}

void _fun_run::fun(stringstream& sin){
    value *v1 = get_value(sin);
    if (!v1->check_list()){
        cout << "The parameter of run is not list, error" << endl;
        exit(1);
    }
    string s = v1->key_list->Convert_To_String();
    execlist(s);
}

void _fun_output::fun(stringstream& sin){
    value* v1 = get_value(sin);
    _namespace_stack_ret[curstack] = v1;
}

void _fun_local::fun(stringstream& sin){
    value* v1 = get_value(sin);
    if (!v1->check_string()){
        cout << "The local definition is not a word variable, error" << endl;
        exit(1);
    }
    _namespace_stack[curstack][v1->key_string] = NULL;
}