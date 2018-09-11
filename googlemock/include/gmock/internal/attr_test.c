#define CAT(a, b) CAT2(a, b)
#define CAT2(a, b) a##b
#define STR(x) STR2(x)
#define STR2(x) #x
#define EXPAND(macro, args) macro args

#define IS_CONST_const ,
#define IS_TYPENAME_typename ,
#define IS_CALLTYPE_Calltype(...) ,
#define EXTRACT_CALLTYPE_Calltype(...) __VA_ARGS__


#define TUP_GET_CONST(a, b, c) GET_CONST(a) GET_CONST(b) GET_CONST(c)
#define TUP_GET_TYPENAME(a, b, c) GET_TYPENAME(a) GET_TYPENAME(b) GET_TYPENAME(c)
#define TUP_GET_CALLTYPE(a, b, c) GET_CALLTYPE(a) GET_CALLTYPE(b) GET_CALLTYPE(c)
#define TUP_GET_OTHER(a, b, c) GET_OTHER(a) GET_OTHER(b) GET_OTHER(c)

#define GET_CONST(x) THIRD(CAT(IS_CONST_, x), x,)
#define GET_TYPENAME(x) THIRD(CAT(IS_TYPENAME_, x), x,)
#define GET_CALLTYPE(x) THIRD(CAT(IS_CALLTYPE_, x), CAT(EXTRACT_CALLTYPE_, x),)
#define GET_OTHER(x) THIRD(CAT(IS_CONST_, x) CAT(IS_TYPENAME_, x) CAT(IS_CALLTYPE_, x),, x)

#define THIRD(...) EXPAND(THIRD2, (__VA_ARGS__))
#define THIRD2(a, b, c, ...) c

#define TUP_GET_ALL(a, b, c) STR(a b c) yields C TUP_GET_CONST(a, b, c) T TUP_GET_TYPENAME(a, b, c) CT TUP_GET_CALLTYPE(a, b, c) A TUP_GET_OTHER(a, b, c)

nothing TUP_GET_ALL(typename,Calltype(foo),override)
first: TUP_GET_ALL(const,typename,override)
second: TUP_GET_ALL(override,const,typename)
third: TUP_GET_ALL(typename,override,const)
parens: TUP_GET_ALL(typename,Calltype(foo, 3),noexcept)
parens1: TUP_GET_ALL(typename,Calltype(foo, 3),const)
