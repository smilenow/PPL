#用BNF描述MUA语言

*	姓名：尹嘉权
*	学号：3120000419
*	班级：计科1205

===
##	lexeme 语素
*	0,1,2,3,4,5,6,7,8,9,.
*	a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z
*	[,],-,"
*	true,false
*	//,:,make,thing,erase,isname,print,read,readlinst,add,sub,mul,div,mod,
eq,gt,lt,and,or,not,random,sqrt,isnumber,isword,islist,isbool,isempty,
test,iftrue,iffalse,word,list,join,first,last,butfirst,butlast,item,
repeat,stop,wait,save,load,erall,poall,output,local,if,run


===

##	token 标记

*	由0,1,2,3,4,5,6,7,8,9 构成的集合：digit
*	由a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z 构成的集合：letter
*	由所有合法的 _number 构成的集合：数字 number
*	由所有合法的 _word ,并且不包含所有lexeme所构成的集合：单词 word
*	由所有合法的 _list 构成的集合：列表 list
*	由lexeme中 true,false 构成的集合：布尔 bool，即{true,false}

===

##	terminals 终结符

*	所有的lexeme 和 token 均为终结符

===

##	non-terminals 非终结符

*	`<_number0>` `<_number1>` `<_number>`
*	`<_word0>` `<_word>`
*	`<_list_element>` `<_list>`
*	`<program>`
*	`<set_of_stmts>` `<stmts>` `<stmt>` `<//>` `<charset>`
*	`<word>` `<number>` `<bool>` `<list>` `<value>`
*	`<op1_word>` `<op1_number>` `<op1_value>` `<one_word_operator>` `<one_number_operator>` `<one_value_operator>` `<number_operator>` `<numword_operator>` `<andor_operator>`
*	`<op_number>` `<op_numword>` `<op_and_or>` `<op_not>`
*	`<make>` `<iftrue>` `<iffalse>` `<word_link>` `<list_link>` `<first_wl>` `<last_wl>` `<butfirst_wl>` `<butlast_wl>` `<item_n_wl>` `<check_empty>`
*	`<functionName>` `<arglist>` `<funciton_define>` `<function_use>`
*	`<pi>`

===

##	start 起始符号

*	`<program>`

===

##	production rules 生成规则

*	`<_number0>` -> `digit` | `<_number0>digit`
*	`<_number1>` -> `<_number0>` | `<_number0>.<_number0>`
*	`<_number>` -> `-<_number1>` | `<_number1>`

---

*	`<_word0>` -> `letter` | `<_word0>letter`
*	`<_word>` -> `"<_word0>`

---

*	`<_list_element>` -> `<_list_element> (<_word>|<_number>)` | `(<_word>|<_number>)`
*	`<_list>` -> `[<_list_element>]`

---

*	`<program>`  -> `<set_of_stmts>`
*	`<set_of_stmts>` -> `<stmts>` | `<stmts>'\n'<stmts>`
*	`<stmts>` -> `<stmt>` | `<stmt> <//>` | `<stmt><//>`
*	`<//>` -> `//<charset>` | `// <charset>`
*	`<charset>` -> `word` | `number` | `<charset> <charset>`
*	`<stmt>` -> `print <value>` | `erase <word>` | `<make>` | `<iftrue>` | `<iffalse>` | `join <list> <value>` | `repeat <number> <list>` | `stop` | `wait <number>` | `save <word>` | `load <word>` | `erall` | `poall` | `<function_define>` | `<function_use>` | `output <value>` | `local <value>` | `run <list>` | `if <bool> <list> <list>`

---

*	`<word>` -> `word`
*	`<number>` -> `number` | `<pi>`
*	`<bool>` -> `bool`
*	`<list>` -> `list`
*	`<value>` -> `read` | `readlinst` | `<op1_word>` | `<op1_number>` | `<op1_value>` | `<op_number>` | `<op_numword>` | `<op_and_or>` | `<op_not>` | `<word_link>` | `<list_link>` | `<first_wl>` | `<last_wl>` | `<butfirst_wl>` | `<buflast_wl>` | `<item_n_wl>` | `<check_empty>`

---

*	`<op1_word>` -> `<one_word_operator> <word>`
*	`<op1_number>` -> `<one_number_operator> <number>`
*	`<op1_value>` -> `<one_value_operator> <value>`
*	`<one_word_operator>` -> `thing` | `:` | `isname`
*	`<one_number_operator>` -> `random` | `sqrt`
*	`<one_value_operator>` -> `isnumber` | `isword` | `islist` | `isbool` | `test` | `isempty`
*	`<number_operator>` -> `add` | `sub` | `mul` | `div` | `mod`
*	`<numword_operator>` -> `eq` | `gt` | `lt`
*	`<andor_operator>` -> `and` | `or`

*	`<op_number>` -> `<number_operator> <number> <number>`
*	`<op_numword>` -> `<numword_operator> <number> <number>` | `<numword_operator> <word> <word>`
*	`<op_and_or>` -> `<andor_operator> <bool> <bool>`
*	`<op_not>` -> `not <bool>`

---

*	`<make>` -> `make <word> <value>`
*	`<iftrue>` -> `iftrue <list>`
*	`<iffalse>` -> `iffalse <list>`
*	`<word_link>` -> `word <word> <word>` | `word <word> <number>` | `word <word> <bool>`
*	`<list_link>` -> `list <list> <list>`
*	`<first_wl>` -> `first <word>` | `first <list>`
*	`<last_wl>` -> `last <word>` | `last <list>`
*	`<butfirst_wl>` -> `butfirst <word>` | `butfirst <list>`
*	`<butlast_wl>` -> `butlast <word>` | `butlast <list>`
*	`<item_n_wl>` -> `item <number> <word>` | `item <number> <list>`
*	`<check_empty>` -> `isempty <list>`

---

*	`<functionName>` -> `letter<functionName>` | `letter`
*	`<arglist>` -> `<list>`
*	`<funciton_define>` -> `make <functionName> [<arglist> <list>]`
*	`<function_use>` -> `<functionName> <arglist>`

---

*	`<pi>` -> 3.14159