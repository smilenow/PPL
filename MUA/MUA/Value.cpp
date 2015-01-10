//
//  Value.cpp
//  MUA
//
//  Created by SmilENow on 1/9/15.
//  Copyright (c) 2015 Jiaquan Yin. All rights reserved.
//

#include "Value.h"

const int number::type_int = 0;
const int number::type_double = 1;

number::number(string str){
    stringstream ss;
    bool flag = true;
    int dot = 0;
    for (int i=0;i<(int)str.length();i++){
        if (str[i]=='.'){
            dot++;
            continue;
        }
        if (!(str[i]>='0' && str[i]<='9')){
            flag = false;
            break;
        }
    }
    if (dot>1) flag = false;
    if (!flag){
        cout << "The input number " << str << " is invalid" << endl;
        exit(1);
    }
    ss << str;
    if (dot==0){
        ss >> key_int;
        type = number::type_int;
    } else {
        ss >> key_double;
        type = number::type_double;
    }
}

bool number::operator==(const number & rhs) const{
    if (type != rhs.type) return false;
    if (type == number::type_int) return key_int == rhs.key_int;
    return fabs(key_double-rhs.key_double)<1e-6;
}

bool number::operator>(const number& rhs) const{
    if (type != rhs.type) return false;
    if (type == number::type_int) return key_int > rhs.key_int;
    return key_double>rhs.key_double;
}
bool number::operator<(const number& rhs) const{
    if (type != rhs.type) return false;
    if (type == number::type_int) return key_int < rhs.key_int;
    return key_double<rhs.key_double;
}

void number::print() const{
    switch (type) {
        case number::type_int:
            cout << key_int << endl;
            break;
        case number::type_double:
            cout << key_double << endl;
            break;
        default:
            break;
    }
}

void number::print(ofstream &fout) const{
    switch (type) {
        case number::type_int:
            fout << key_int;
            break;
        case number::type_double:
            fout << key_double;
            break;
        default:
            break;
    }
}

string number::Convert_To_String() const{
    stringstream ss;
    string s = "";
    if (type == type_double){
        ss << key_double;
        ss >> s;
        return s;
    }
    ss << key_int;
    ss >> s;
    return s;
}

const int value::type_number=0;
const int value::type_string=1;
const int value::type_list=2;
const int value::type_bool=3;

void value::print(){
    switch (type) {
        case value::type_number:
            key_number.print();
            break;
        case value::type_string:
            cout << key_string << endl;
            break;
        case value::type_list:
            key_list->print();
            break;
        case value::type_bool:
            if (key_bool) cout << "True" << endl;
            else cout << "False" << endl;
            break;
        default:
            break;
    }
}

void value::copy(const value *that){
    type = that->type;
    key_number = that->key_number;
    key_bool = that->key_bool;
    key_string = that->key_string;
    key_list = that->key_list;
}

void value::print(ofstream& fout){
    switch (type) {
        case value::type_number:
            key_number.print(fout);
            break;
        case value::type_string:
            fout << key_string;
            break;
        case value::type_list:
            key_list->print(fout);
            break;
        case value::type_bool:
            if (key_bool) fout << "True";
            else cout << "False";
            break;
        default:
            break;
    }
}

void list::print(){
    cout << "[" << endl;
    if (!((key->type == value::type_string) && (key->key_string == "End of list"))){
        key->print();
        list* cur = next;
        while (cur!=NULL){
            if (!((cur->key->type == value::type_string) && (cur->key->key_string == "End of list")))
                cur->key->print();
            cur = cur->next;
        }
    }
    cout << "]" << endl;
}

void list::print(ofstream &fout){
    fout << " [ ";
    if (!((key->type == value::type_string) && (key->key_string == "End of list"))){
        key->print(fout);
        fout << " ";
        list* cur = next;
        while (cur!=NULL){
            if (!((cur->key->type == value::type_string) && (cur->key->key_string == "End of list"))){
                cur->key->print(fout); fout<< " " ;
            }
            cur = cur->next;
        }
    }
    fout << " ] ";
}

string list::Convert_To_String(){
    if (key->check_string() && key->key_string == "End of list") return "";
    switch (key->type) {
        case value::type_number:
            return key->key_number.Convert_To_String() + " " + next->Convert_To_String();
            break;
        case value::type_string:
            return key->key_string + " " + next->Convert_To_String();
            break;
        case value::type_list:
            return " [ " + key->key_list->Convert_To_String() + " ] " + next->Convert_To_String();
            break;
        case value::type_bool:
            if (key->key_bool) return "True " + next->Convert_To_String();
            else return "False " + next->Convert_To_String();
            break;
        default:
            break;
    }
    return "";
}