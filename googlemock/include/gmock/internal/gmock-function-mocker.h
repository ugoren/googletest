#ifndef GOOGLETEST_GOOGLEMOCK_INCLUDE_GMOCK_INTERNAL_GMOCK_FUNCTION_MOCKER_H_
#define GOOGLETEST_GOOGLEMOCK_INCLUDE_GMOCK_INTERNAL_GMOCK_FUNCTION_MOCKER_H_

#include "googletest/googlemock/include/gmock/gmock-generated-function-mockers.h"

#define MOCK_METHOD(_Ret, _MethodName, _Args, _Spec)                       \
  GMOCK_INTERNAL_MOCK_METHOD_IMPL(GMOCK_INTERNAL_NARG0 _Args, _MethodName, \
                                  GMOCK_INTERNAL_HAS_CONST(_Spec),         \
                                  GMOCK_INTERNAL_HAS_OVERRIDE(_Spec),      \
                                  GMOCK_INTERNAL_GET_CALLTYPE(_Spec),      \
                                  (GMOCK_INTERNAL_SIGNATURE(_Ret, _Args)))

#define GMOCK_INTERNAL_MOCK_METHOD_IMPL(_N, _MethodName, _Constness,           \
                                        _Override, _CallType, _Signature)      \
  typename ::testing::internal::Function<GMOCK_INTERNAL_REMOVE_PARENS(         \
      _Signature)>::Result _CallType                                           \
  _MethodName(GMOCK_INTERNAL_REPEAT(_N, GMOCK_INTERNAL_PARAMETER, _Signature)) \
      GMOCK_INTERNAL_IF(_Constness, const, ) GMOCK_INTERNAL_EMPTY(_)           \
          GMOCK_INTERNAL_IF(_Override, override, ) {                           \
    static_assert(                                                             \
        ::testing::tuple_size<typename ::testing::internal::Function<          \
                GMOCK_INTERNAL_REMOVE_PARENS(_Signature)>::ArgumentTuple>::    \
                value == _N,                                                   \
        "This method does not take " GMOCK_INTERNAL_STRINGIZE(                 \
            _N) " arguments");                                                 \
    GMOCK_MOCKER_(_N, _Constness, _MethodName)                                 \
        .SetOwnerAndName(this, #_MethodName);                                  \
    return GMOCK_MOCKER_(_N, _Constness, _MethodName)                          \
        .Invoke(GMOCK_INTERNAL_REPEAT(_N, GMOCK_INTERNAL_FORWARD_ARG,          \
                                      _Signature));                            \
  }                                                                            \
  ::testing::MockSpec<GMOCK_INTERNAL_REMOVE_PARENS(_Signature)>                \
      gmock_##_MethodName(GMOCK_INTERNAL_REPEAT(                               \
          _N, GMOCK_INTERNAL_MATCHER_PARAMETER, _Signature))                   \
          GMOCK_INTERNAL_IF(_Constness, const, ) {                             \
    GMOCK_MOCKER_(_N, _Constness, _MethodName).RegisterOwner(this);            \
    return GMOCK_MOCKER_(_N, _Constness, _MethodName)                          \
        .With(GMOCK_INTERNAL_REPEAT(_N, GMOCK_INTERNAL_MATCHER_ARGUMENT, ~));  \
  }                                                                            \
  ::testing::MockSpec<GMOCK_INTERNAL_REMOVE_PARENS(_Signature)>                \
      gmock_##_MethodName(                                                     \
          const ::testing::internal::WithoutMatchers&,                         \
          GMOCK_INTERNAL_IF(_Constness, const, )                               \
              GMOCK_INTERNAL_EMPTY(_)::testing::internal::Function<            \
                  GMOCK_INTERNAL_REMOVE_PARENS(_Signature)>*) const {          \
    return GMOCK_INTERNAL_VCAT(::testing::internal::AdjustConstness_,          \
                               GMOCK_INTERNAL_IF(_Constness, const, ))(this)   \
        ->gmock_##_MethodName(GMOCK_INTERNAL_REPEAT(                           \
            _N, GMOCK_INTERNAL_A_MATCHER_ARGUMENT, _Signature));               \
  }                                                                            \
  mutable ::testing::FunctionMocker<GMOCK_INTERNAL_REMOVE_PARENS(_Signature)>  \
      GMOCK_MOCKER_(_N, _Constness, _MethodName)

#define GMOCK_INTERNAL_HAS_CONST(_Tuple) \
  GMOCK_INTERNAL_HAS_COMMA(              \
      GMOCK_INTERNAL_FOR_EACH(GMOCK_INTERNAL_DETECT_CONST, ~, _Tuple))

#define GMOCK_INTERNAL_HAS_OVERRIDE(_Tuple) \
  GMOCK_INTERNAL_HAS_COMMA(                 \
      GMOCK_INTERNAL_FOR_EACH(GMOCK_INTERNAL_DETECT_OVERRIDE, ~, _Tuple))

#define GMOCK_INTERNAL_GET_CALLTYPE(_Tuple) \
  GMOCK_INTERNAL_FOR_EACH(GMOCK_INTERNAL_GET_CALLTYPE_IMPL, ~, _Tuple)

#define GMOCK_INTERNAL_DETECT_CONST(_i, _, _elem) \
  GMOCK_INTERNAL_VCAT(GMOCK_INTERNAL_DETECT_CONST_I_, _elem)

#define GMOCK_INTERNAL_DETECT_CONST_I_const ,

#define GMOCK_INTERNAL_DETECT_OVERRIDE(_i, _, _elem) \
  GMOCK_INTERNAL_VCAT(GMOCK_INTERNAL_DETECT_OVERRIDE_I_, _elem)

#define GMOCK_INTERNAL_DETECT_OVERRIDE_I_override ,

#define GMOCK_INTERNAL_GET_CALLTYPE_IMPL(_i, _, _elem)                       \
  GMOCK_INTERNAL_IF(GMOCK_INTERNAL_IS_CALLTYPE(_elem),                       \
                    GMOCK_INTERNAL_GET_VALUE_CALLTYPE, GMOCK_INTERNAL_EMPTY) \
  (_elem)

#define GMOCK_INTERNAL_IS_CALLTYPE(_arg) \
  GMOCK_INTERNAL_IS_BEGIN_PARENS(        \
      GMOCK_INTERNAL_VCAT(GMOCK_INTERNAL_IS_CALLTYPE_HELPER_, _arg))

#define GMOCK_INTERNAL_GET_VALUE_CALLTYPE(_arg) \
  GMOCK_INTERNAL_IDENTITY GMOCK_INTERNAL_VCAT(  \
      GMOCK_INTERNAL_IS_CALLTYPE_HELPER_, _arg)

#define GMOCK_INTERNAL_IS_CALLTYPE_HELPER_Calltype

#define GMOCK_INTERNAL_SIGNATURE(_Ret, _Args)                              \
  GMOCK_INTERNAL_IF(GMOCK_INTERNAL_IS_BEGIN_PARENS(_Ret),                  \
                    GMOCK_INTERNAL_REMOVE_PARENS, GMOCK_INTERNAL_IDENTITY) \
  (_Ret)(GMOCK_INTERNAL_FOR_EACH(GMOCK_INTERNAL_GET_TYPE, ~, _Args))

#define GMOCK_INTERNAL_GET_TYPE(_i, _, _elem)                              \
  GMOCK_INTERNAL_COMMA_IF(_i)                                              \
  GMOCK_INTERNAL_IF(GMOCK_INTERNAL_IS_BEGIN_PARENS(_elem),                 \
                    GMOCK_INTERNAL_REMOVE_PARENS, GMOCK_INTERNAL_IDENTITY) \
  (_elem)

#define GMOCK_INTERNAL_PARAMETER(_i, _Signature, _)              \
  GMOCK_INTERNAL_COMMA_IF(_i)                                    \
  GMOCK_INTERNAL_ARG_O(typename, GMOCK_INTERNAL_INC(_i),         \
                       GMOCK_INTERNAL_REMOVE_PARENS(_Signature)) \
  gmock_a##_i

#define GMOCK_INTERNAL_FORWARD_ARG(_i, _Signature, _) \
  GMOCK_INTERNAL_COMMA_IF(_i)                         \
  ::testing::internal::forward<GMOCK_INTERNAL_ARG_O(  \
      typename, GMOCK_INTERNAL_INC(_i),               \
      GMOCK_INTERNAL_REMOVE_PARENS(_Signature))>(gmock_a##_i)

#define GMOCK_INTERNAL_MATCHER_PARAMETER(_i, _Signature, _)          \
  GMOCK_INTERNAL_COMMA_IF(_i)                                        \
  GMOCK_INTERNAL_MATCHER_O(typename, GMOCK_INTERNAL_INC(_i),         \
                           GMOCK_INTERNAL_REMOVE_PARENS(_Signature)) \
  gmock_a##_i

#define GMOCK_INTERNAL_MATCHER_ARGUMENT(_i, _1, _2) \
  GMOCK_INTERNAL_COMMA_IF(_i)                       \
  gmock_a##_i

#define GMOCK_INTERNAL_A_MATCHER_ARGUMENT(_i, _Signature, _) \
  GMOCK_INTERNAL_COMMA_IF(_i)                                \
  ::testing::A<GMOCK_INTERNAL_ARG_O(                         \
      typename, GMOCK_INTERNAL_INC(_i),                      \
      GMOCK_INTERNAL_REMOVE_PARENS(_Signature))>()

#define GMOCK_INTERNAL_ARG_O(_tn, _i, ...) GMOCK_ARG_(_tn, _i, __VA_ARGS__)

#define GMOCK_INTERNAL_MATCHER_O(_tn, _i, ...) \
  GMOCK_MATCHER_(_tn, _i, __VA_ARGS__)

#define GMOCK_INTERNAL_STRINGIZE(...) GMOCK_INTERNAL_STRINGIZE_I(__VA_ARGS__)

// Evaluates to the number of arguments after expansion.
//
//   #define PAIR x, y
//
//   GERROR_INTERNAL_NARG() => 1
//   GERROR_INTERNAL_NARG(x) => 1
//   GERROR_INTERNAL_NARG(x, y) => 2
//   GERROR_INTERNAL_NARG(PAIR) => 2
//
// Requires: the number of arguments after expansion is at most 15.
#define GMOCK_INTERNAL_NARG(...)                                             \
  GMOCK_INTERNAL_16TH(__VA_ARGS__, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, \
                      3, 2, 1, 0)

// If the arguments after expansion have no tokens, evaluates to `1`. Otherwise
// evaluates to `0`.
//
// Requires: * the number of arguments after expansion is at most 15.
//           * If the argument is a macro, it must be able to be called with one
//             argument.
//
// Implementation details:
//
// There is one case when it generates a compile error: if the argument is macro
// that cannot be called with one argument.
//
//   #define M(a, b)  // it doesn't matter what it expands to
//
//   // Expected: expands to `0`.
//   // Actual: compile error.
//   GMOCK_INTERNAL_IS_EMPTY(M)
//
// There are 4 cases tested:
//
// * __VA_ARGS__ possible expansion has no unparen'd commas. Expected 0.
// * __VA_ARGS__ possible expansion is not enclosed in parenthesis. Expected 0.
// * __VA_ARGS__ possible expansion is not a macro that ()-evaluates to a comma.
//   Expected 0
// * __VA_ARGS__ is empty, or has unparen'd commas, or is enclosed in
//   parenthesis, or is a macro that ()-evaluates to comma. Expected 1.
//
// We trigger detection on '0001', i.e. on empty.
#define GMOCK_INTERNAL_IS_EMPTY(...)                              \
  GMOCK_INTERNAL_IS_EMPTY_I(                                      \
      GMOCK_INTERNAL_HAS_COMMA(__VA_ARGS__),                      \
      GMOCK_INTERNAL_HAS_COMMA(GMOCK_INTERNAL_COMMA __VA_ARGS__), \
      GMOCK_INTERNAL_HAS_COMMA(__VA_ARGS__()),                    \
      GMOCK_INTERNAL_HAS_COMMA(GMOCK_INTERNAL_COMMA __VA_ARGS__()))

// Evaluates to the number of arguments after expansion. Identifies 'empty' as
// 0.
//
//   #define PAIR x, y
//
//   GERROR_INTERNAL_NARG0() => 0
//   GERROR_INTERNAL_NARG0(x) => 1
//   GERROR_INTERNAL_NARG0(x, y) => 2
//   GERROR_INTERNAL_NARG0(PAIR) => 2
//
// Requires: * the number of arguments after expansion is at most 15.
//           * If the argument is a macro, it must be able to be called with one
//             argument.
#define GMOCK_INTERNAL_NARG0(...)                            \
  GMOCK_INTERNAL_IF(GMOCK_INTERNAL_IS_EMPTY(__VA_ARGS__), 0, \
                    GMOCK_INTERNAL_NARG(__VA_ARGS__))

// Expands to 1 if the first argument starts with something in parentheses,
// otherwise to 0.
#define GMOCK_INTERNAL_IS_BEGIN_PARENS(...)              \
  GMOCK_INTERNAL_HEAD(                                   \
      GMOCK_INTERNAL_VCAT(GMOCK_INTERNAL_IS_VARIADIC_R_, \
                          GMOCK_INTERNAL_IS_VARIADIC_C __VA_ARGS__))

// Expands to _Macro(0, _Data, e1) _Macro(1, _Data, e2) ... _Macro(K -1, _Data,
// eK) as many of GMOCK_INTERNAL_NARG0 _Tuple.
// Requires: * |_Macro| can be called with 3 arguments.
//           * |_Tuple| expansion has no more than 15 elements.
#define GMOCK_INTERNAL_FOR_EACH(_Macro, _Data, _Tuple) \
  GMOCK_INTERNAL_VCAT(GMOCK_INTERNAL_FOR_EACH_IMPL_,   \
                      GMOCK_INTERNAL_NARG0 _Tuple)     \
  (0, _Macro, _Data, _Tuple)

// Expands to _Macro(0, _Data, ) _Macro(1, _Data, ) ... _Macro(K - 1, _Data)
// Empty if _K = 0.
// Requires: * |_Macro| can be called with 3 arguments.
//           * |_K| literal between 0 and 15
#define GMOCK_INTERNAL_REPEAT(_K, _Macro, _Data)       \
  GMOCK_INTERNAL_VCAT(GMOCK_INTERNAL_REPEAT_IMPL_, _K) \
  (0, _Macro, _Data)

///////////////////////////////////////////////////////////////////////////////
//               HARDCORE IMPLEMENTATION DETAILS FOLLOW                      //
//                    DO NOT USE FROM OTHER FILES                            //
///////////////////////////////////////////////////////////////////////////////
#define GMOCK_INTERNAL_STRINGIZE_I(...) #__VA_ARGS__
//
#define GMOCK_INTERNAL_16TH(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, \
                            _13, _14, _15, X, ...)                             \
  X
//
#define GMOCK_INTERNAL_COMMA(...) ,
#define GMOCK_INTERNAL_HAS_COMMA(...) \
  GMOCK_INTERNAL_16TH(__VA_ARGS__, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0)
#define GMOCK_INTERNAL_CAT5(_0, _1, _2, _3, _4) _0##_1##_2##_3##_4
#define GMOCK_INTERNAL_IS_EMPTY_I(_0, _1, _2, _3) \
  GMOCK_INTERNAL_HAS_COMMA(                       \
      GMOCK_INTERNAL_CAT5(GMOCK_INTERNAL_EMPTY_CASE_, _0, _1, _2, _3))
#define GMOCK_INTERNAL_EMPTY_CASE_0001 ,
//
#define GMOCK_INTERNAL_VCAT(...) GMOCK_INTERNAL_VCAT_I(__VA_ARGS__)
#define GMOCK_INTERNAL_VCAT_I(_0, ...) _0##__VA_ARGS__
// |COND| is 0 or 1. |THEN| must not contain unparenthesized commas.
#define GMOCK_INTERNAL_IF(_Cond, _Then, ...) \
  GMOCK_INTERNAL_VCAT(GMOCK_INTERNAL_IF_, _Cond)(_Then, __VA_ARGS__)
#define GMOCK_INTERNAL_IF_1(_Then, ...) _Then
#define GMOCK_INTERNAL_IF_0(_Then, ...) __VA_ARGS__
//
#define GMOCK_INTERNAL_HEAD(...) GMOCK_INTERNAL_HEAD_I(__VA_ARGS__)
#define GMOCK_INTERNAL_HEAD_I(_0, ...) _0
//
#define GMOCK_INTERNAL_TAIL(...) GMOCK_INTERNAL_TAIL_I(__VA_ARGS__)
#define GMOCK_INTERNAL_TAIL_I(_0, ...) __VA_ARGS__
//
#define GMOCK_INTERNAL_IS_VARIADIC_C(...) 1
#define GMOCK_INTERNAL_IS_VARIADIC_R_1 1,
#define GMOCK_INTERNAL_IS_VARIADIC_R_GMOCK_INTERNAL_IS_VARIADIC_C 0,
//
#define GMOCK_INTERNAL_CALL_MACRO(_i, _Macro, _Data, _Elem) \
  _Macro(_i, _Data, _Elem)
//
#define GMOCK_INTERNAL_FOR_EACH_IMPL_0(_i, _Macro, _Data, _Tuple)
#define GMOCK_INTERNAL_FOR_EACH_IMPL_1(_i, _Macro, _Data, _Tuple) \
  GMOCK_INTERNAL_CALL_MACRO(_i, _Macro, _Data, GMOCK_INTERNAL_HEAD _Tuple)
#define GMOCK_INTERNAL_FOR_EACH_IMPL_2(_i, _Macro, _Data, _Tuple)          \
  GMOCK_INTERNAL_CALL_MACRO(_i, _Macro, _Data, GMOCK_INTERNAL_HEAD _Tuple) \
  GMOCK_INTERNAL_FOR_EACH_IMPL_1(GMOCK_INTERNAL_INC(_i), _Macro, _Data,    \
                                 (GMOCK_INTERNAL_TAIL _Tuple))
#define GMOCK_INTERNAL_FOR_EACH_IMPL_3(_i, _Macro, _Data, _Tuple)          \
  GMOCK_INTERNAL_CALL_MACRO(_i, _Macro, _Data, GMOCK_INTERNAL_HEAD _Tuple) \
  GMOCK_INTERNAL_FOR_EACH_IMPL_2(GMOCK_INTERNAL_INC(_i), _Macro, _Data,    \
                                 (GMOCK_INTERNAL_TAIL _Tuple))
#define GMOCK_INTERNAL_FOR_EACH_IMPL_4(_i, _Macro, _Data, _Tuple)          \
  GMOCK_INTERNAL_CALL_MACRO(_i, _Macro, _Data, GMOCK_INTERNAL_HEAD _Tuple) \
  GMOCK_INTERNAL_FOR_EACH_IMPL_3(GMOCK_INTERNAL_INC(_i), _Macro, _Data,    \
                                 (GMOCK_INTERNAL_TAIL _Tuple))
#define GMOCK_INTERNAL_FOR_EACH_IMPL_5(_i, _Macro, _Data, _Tuple)          \
  GMOCK_INTERNAL_CALL_MACRO(_i, _Macro, _Data, GMOCK_INTERNAL_HEAD _Tuple) \
  GMOCK_INTERNAL_FOR_EACH_IMPL_4(GMOCK_INTERNAL_INC(_i), _Macro, _Data,    \
                                 (GMOCK_INTERNAL_TAIL _Tuple))
#define GMOCK_INTERNAL_FOR_EACH_IMPL_6(_i, _Macro, _Data, _Tuple)          \
  GMOCK_INTERNAL_CALL_MACRO(_i, _Macro, _Data, GMOCK_INTERNAL_HEAD _Tuple) \
  GMOCK_INTERNAL_FOR_EACH_IMPL_5(GMOCK_INTERNAL_INC(_i), _Macro, _Data,    \
                                 (GMOCK_INTERNAL_TAIL _Tuple))
#define GMOCK_INTERNAL_FOR_EACH_IMPL_7(_i, _Macro, _Data, _Tuple)          \
  GMOCK_INTERNAL_CALL_MACRO(_i, _Macro, _Data, GMOCK_INTERNAL_HEAD _Tuple) \
  GMOCK_INTERNAL_FOR_EACH_IMPL_6(GMOCK_INTERNAL_INC(_i), _Macro, _Data,    \
                                 (GMOCK_INTERNAL_TAIL _Tuple))
#define GMOCK_INTERNAL_FOR_EACH_IMPL_8(_i, _Macro, _Data, _Tuple)          \
  GMOCK_INTERNAL_CALL_MACRO(_i, _Macro, _Data, GMOCK_INTERNAL_HEAD _Tuple) \
  GMOCK_INTERNAL_FOR_EACH_IMPL_7(GMOCK_INTERNAL_INC(_i), _Macro, _Data,    \
                                 (GMOCK_INTERNAL_TAIL _Tuple))
#define GMOCK_INTERNAL_FOR_EACH_IMPL_9(_i, _Macro, _Data, _Tuple)          \
  GMOCK_INTERNAL_CALL_MACRO(_i, _Macro, _Data, GMOCK_INTERNAL_HEAD _Tuple) \
  GMOCK_INTERNAL_FOR_EACH_IMPL_8(GMOCK_INTERNAL_INC(_i), _Macro, _Data,    \
                                 (GMOCK_INTERNAL_TAIL _Tuple))
#define GMOCK_INTERNAL_FOR_EACH_IMPL_10(_i, _Macro, _Data, _Tuple)         \
  GMOCK_INTERNAL_CALL_MACRO(_i, _Macro, _Data, GMOCK_INTERNAL_HEAD _Tuple) \
  GMOCK_INTERNAL_FOR_EACH_IMPL_9(GMOCK_INTERNAL_INC(_i), _Macro, _Data,    \
                                 (GMOCK_INTERNAL_TAIL _Tuple))
#define GMOCK_INTERNAL_FOR_EACH_IMPL_11(_i, _Macro, _Data, _Tuple)         \
  GMOCK_INTERNAL_CALL_MACRO(_i, _Macro, _Data, GMOCK_INTERNAL_HEAD _Tuple) \
  GMOCK_INTERNAL_FOR_EACH_IMPL_10(GMOCK_INTERNAL_INC(_i), _Macro, _Data,   \
                                  (GMOCK_INTERNAL_TAIL _Tuple))
#define GMOCK_INTERNAL_FOR_EACH_IMPL_12(_i, _Macro, _Data, _Tuple)         \
  GMOCK_INTERNAL_CALL_MACRO(_i, _Macro, _Data, GMOCK_INTERNAL_HEAD _Tuple) \
  GMOCK_INTERNAL_FOR_EACH_IMPL_11(GMOCK_INTERNAL_INC(_i), _Macro, _Data,   \
                                  (GMOCK_INTERNAL_TAIL _Tuple))
#define GMOCK_INTERNAL_FOR_EACH_IMPL_13(_i, _Macro, _Data, _Tuple)         \
  GMOCK_INTERNAL_CALL_MACRO(_i, _Macro, _Data, GMOCK_INTERNAL_HEAD _Tuple) \
  GMOCK_INTERNAL_FOR_EACH_IMPL_12(GMOCK_INTERNAL_INC(_i), _Macro, _Data,   \
                                  (GMOCK_INTERNAL_TAIL _Tuple))
#define GMOCK_INTERNAL_FOR_EACH_IMPL_14(_i, _Macro, _Data, _Tuple)         \
  GMOCK_INTERNAL_CALL_MACRO(_i, _Macro, _Data, GMOCK_INTERNAL_HEAD _Tuple) \
  GMOCK_INTERNAL_FOR_EACH_IMPL_13(GMOCK_INTERNAL_INC(_i), _Macro, _Data,   \
                                  (GMOCK_INTERNAL_TAIL _Tuple))
#define GMOCK_INTERNAL_FOR_EACH_IMPL_15(_i, _Macro, _Data, _Tuple)         \
  GMOCK_INTERNAL_CALL_MACRO(_i, _Macro, _Data, GMOCK_INTERNAL_HEAD _Tuple) \
  GMOCK_INTERNAL_FOR_EACH_IMPL_14(GMOCK_INTERNAL_INC(_i), _Macro, _Data,   \
                                  (GMOCK_INTERNAL_TAIL _Tuple))
//
#define GMOCK_INTERNAL_INC(_i) GMOCK_INTERNAL_VCAT(GMOCK_INTERNAL_INC_I_, _i)()
#define GMOCK_INTERNAL_INC_I_0(_) 1
#define GMOCK_INTERNAL_INC_I_1(_) 2
#define GMOCK_INTERNAL_INC_I_2(_) 3
#define GMOCK_INTERNAL_INC_I_3(_) 4
#define GMOCK_INTERNAL_INC_I_4(_) 5
#define GMOCK_INTERNAL_INC_I_5(_) 6
#define GMOCK_INTERNAL_INC_I_6(_) 7
#define GMOCK_INTERNAL_INC_I_7(_) 8
#define GMOCK_INTERNAL_INC_I_8(_) 9
#define GMOCK_INTERNAL_INC_I_9(_) 10
#define GMOCK_INTERNAL_INC_I_10(_) 11
#define GMOCK_INTERNAL_INC_I_11(_) 12
#define GMOCK_INTERNAL_INC_I_12(_) 13
#define GMOCK_INTERNAL_INC_I_13(_) 14
#define GMOCK_INTERNAL_INC_I_14(_) 15
#define GMOCK_INTERNAL_INC_I_15(_) 16
//
#define GMOCK_INTERNAL_COMMA_IF(_i) \
  GMOCK_INTERNAL_VCAT(GMOCK_INTERNAL_COMMA_IF_I_, _i)()
#define GMOCK_INTERNAL_COMMA_IF_I_0(_)
#define GMOCK_INTERNAL_COMMA_IF_I_1(_) ,
#define GMOCK_INTERNAL_COMMA_IF_I_2(_) ,
#define GMOCK_INTERNAL_COMMA_IF_I_3(_) ,
#define GMOCK_INTERNAL_COMMA_IF_I_4(_) ,
#define GMOCK_INTERNAL_COMMA_IF_I_5(_) ,
#define GMOCK_INTERNAL_COMMA_IF_I_6(_) ,
#define GMOCK_INTERNAL_COMMA_IF_I_7(_) ,
#define GMOCK_INTERNAL_COMMA_IF_I_8(_) ,
#define GMOCK_INTERNAL_COMMA_IF_I_9(_) ,
#define GMOCK_INTERNAL_COMMA_IF_I_10(_) ,
#define GMOCK_INTERNAL_COMMA_IF_I_11(_) ,
#define GMOCK_INTERNAL_COMMA_IF_I_12(_) ,
#define GMOCK_INTERNAL_COMMA_IF_I_13(_) ,
#define GMOCK_INTERNAL_COMMA_IF_I_14(_) ,
#define GMOCK_INTERNAL_COMMA_IF_I_15(_) ,
//
#define GMOCK_INTERNAL_REMOVE_PARENS(_0) GMOCK_INTERNAL_REMOVE_PARENS_I _0
#define GMOCK_INTERNAL_REMOVE_PARENS_I(...) __VA_ARGS__ GMOCK_INTERNAL_EMPTY(_)
//
#define GMOCK_INTERNAL_EMPTY(...)
#define GMOCK_INTERNAL_IDENTITY(...) __VA_ARGS__
//
#define GMOCK_INTERNAL_REPEAT_IMPL_0(_i, _Macro, _Data)
#define GMOCK_INTERNAL_REPEAT_IMPL_1(_i, _Macro, _Data) \
  GMOCK_INTERNAL_CALL_MACRO(_i, _Macro, _Data, )
#define GMOCK_INTERNAL_REPEAT_IMPL_2(_i, _Macro, _Data) \
  GMOCK_INTERNAL_CALL_MACRO(_i, _Macro, _Data, )        \
  GMOCK_INTERNAL_REPEAT_IMPL_1(GMOCK_INTERNAL_INC(_i), _Macro, _Data)
#define GMOCK_INTERNAL_REPEAT_IMPL_3(_i, _Macro, _Data) \
  GMOCK_INTERNAL_CALL_MACRO(_i, _Macro, _Data, )        \
  GMOCK_INTERNAL_REPEAT_IMPL_2(GMOCK_INTERNAL_INC(_i), _Macro, _Data)
#define GMOCK_INTERNAL_REPEAT_IMPL_4(_i, _Macro, _Data) \
  GMOCK_INTERNAL_CALL_MACRO(_i, _Macro, _Data, )        \
  GMOCK_INTERNAL_REPEAT_IMPL_3(GMOCK_INTERNAL_INC(_i), _Macro, _Data)
#define GMOCK_INTERNAL_REPEAT_IMPL_5(_i, _Macro, _Data) \
  GMOCK_INTERNAL_CALL_MACRO(_i, _Macro, _Data, )        \
  GMOCK_INTERNAL_REPEAT_IMPL_4(GMOCK_INTERNAL_INC(_i), _Macro, _Data)
#define GMOCK_INTERNAL_REPEAT_IMPL_6(_i, _Macro, _Data) \
  GMOCK_INTERNAL_CALL_MACRO(_i, _Macro, _Data, )        \
  GMOCK_INTERNAL_REPEAT_IMPL_5(GMOCK_INTERNAL_INC(_i), _Macro, _Data)
#define GMOCK_INTERNAL_REPEAT_IMPL_7(_i, _Macro, _Data) \
  GMOCK_INTERNAL_CALL_MACRO(_i, _Macro, _Data, )        \
  GMOCK_INTERNAL_REPEAT_IMPL_6(GMOCK_INTERNAL_INC(_i), _Macro, _Data)
#define GMOCK_INTERNAL_REPEAT_IMPL_8(_i, _Macro, _Data) \
  GMOCK_INTERNAL_CALL_MACRO(_i, _Macro, _Data, )        \
  GMOCK_INTERNAL_REPEAT_IMPL_7(GMOCK_INTERNAL_INC(_i), _Macro, _Data)
#define GMOCK_INTERNAL_REPEAT_IMPL_9(_i, _Macro, _Data) \
  GMOCK_INTERNAL_CALL_MACRO(_i, _Macro, _Data, )        \
  GMOCK_INTERNAL_REPEAT_IMPL_8(GMOCK_INTERNAL_INC(_i), _Macro, _Data)
#define GMOCK_INTERNAL_REPEAT_IMPL_10(_i, _Macro, _Data) \
  GMOCK_INTERNAL_CALL_MACRO(_i, _Macro, _Data, )         \
  GMOCK_INTERNAL_REPEAT_IMPL_9(GMOCK_INTERNAL_INC(_i), _Macro, _Data)
#define GMOCK_INTERNAL_REPEAT_IMPL_11(_i, _Macro, _Data) \
  GMOCK_INTERNAL_CALL_MACRO(_i, _Macro, _Data, )         \
  GMOCK_INTERNAL_REPEAT_IMPL_10(GMOCK_INTERNAL_INC(_i), _Macro, _Data)
#define GMOCK_INTERNAL_REPEAT_IMPL_12(_i, _Macro, _Data) \
  GMOCK_INTERNAL_CALL_MACRO(_i, _Macro, _Data, )         \
  GMOCK_INTERNAL_REPEAT_IMPL_11(GMOCK_INTERNAL_INC(_i), _Macro, _Data)
#define GMOCK_INTERNAL_REPEAT_IMPL_13(_i, _Macro, _Data) \
  GMOCK_INTERNAL_CALL_MACRO(_i, _Macro, _Data, )         \
  GMOCK_INTERNAL_REPEAT_IMPL_12(GMOCK_INTERNAL_INC(_i), _Macro, _Data)
#define GMOCK_INTERNAL_REPEAT_IMPL_14(_i, _Macro, _Data) \
  GMOCK_INTERNAL_CALL_MACRO(_i, _Macro, _Data, )         \
  GMOCK_INTERNAL_REPEAT_IMPL_13(GMOCK_INTERNAL_INC(_i), _Macro, _Data)
#define GMOCK_INTERNAL_REPEAT_IMPL_15(_i, _Macro, _Data) \
  GMOCK_INTERNAL_CALL_MACRO(_i, _Macro, _Data, )         \
  GMOCK_INTERNAL_REPEAT_IMPL_14(GMOCK_INTERNAL_INC(_i), _Macro, _Data)

#endif  // GOOGLETEST_GOOGLEMOCK_INCLUDE_GMOCK_INTERNAL_GMOCK_FUNCTION_MOCKER_H_
