// -*- C++ -*-
//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef _LIBCPP___MEMORY_CONSTRUCT_AT_H
#define _LIBCPP___MEMORY_CONSTRUCT_AT_H

#include <__config>
#include <__debug>
#include <__iterator/access.h>
#include <__memory/addressof.h>
#include <__utility/forward.h>
#include <type_traits>
#include <utility>

#if !defined(_LIBCPP_HAS_NO_PRAGMA_SYSTEM_HEADER)
#pragma GCC system_header
#endif

_LIBCPP_BEGIN_NAMESPACE_STD

// construct_at

#if _LIBCPP_STD_VER > 17

template<class _Tp, class ..._Args, class = decltype(
    ::new (declval<void*>()) _Tp(declval<_Args>()...)
)>
_LIBCPP_INLINE_VISIBILITY
constexpr _Tp* construct_at(_Tp* __location, _Args&& ...__args) {
    _LIBCPP_ASSERT(__location, "null pointer given to construct_at");
    return ::new ((void*)__location) _Tp(_VSTD::forward<_Args>(__args)...);
}

#endif

// destroy_at

#if _LIBCPP_STD_VER > 14

template <class _ForwardIterator>
_LIBCPP_HIDE_FROM_ABI _LIBCPP_CONSTEXPR_AFTER_CXX17
void destroy(_ForwardIterator, _ForwardIterator);

template <class _Tp, _EnableIf<!is_array_v<_Tp>, int> = 0>
_LIBCPP_HIDE_FROM_ABI _LIBCPP_CONSTEXPR_AFTER_CXX17
void destroy_at(_Tp* __loc) {
    _LIBCPP_ASSERT(__loc, "null pointer given to destroy_at");
    __loc->~_Tp();
}

#if _LIBCPP_STD_VER > 17
template <class _Tp, _EnableIf<is_array_v<_Tp>, int> = 0>
_LIBCPP_HIDE_FROM_ABI _LIBCPP_CONSTEXPR_AFTER_CXX17
void destroy_at(_Tp* __loc) {
    _LIBCPP_ASSERT(__loc, "null pointer given to destroy_at");
    _VSTD::destroy(_VSTD::begin(*__loc), _VSTD::end(*__loc));
}
#endif

template <class _ForwardIterator>
_LIBCPP_HIDE_FROM_ABI _LIBCPP_CONSTEXPR_AFTER_CXX17
void destroy(_ForwardIterator __first, _ForwardIterator __last) {
    for (; __first != __last; ++__first)
        _VSTD::destroy_at(_VSTD::addressof(*__first));
}

template <class _ForwardIterator, class _Size>
_LIBCPP_HIDE_FROM_ABI _LIBCPP_CONSTEXPR_AFTER_CXX17
_ForwardIterator destroy_n(_ForwardIterator __first, _Size __n) {
    for (; __n > 0; (void)++__first, --__n)
        _VSTD::destroy_at(_VSTD::addressof(*__first));
    return __first;
}

#endif

_LIBCPP_END_NAMESPACE_STD

#endif // _LIBCPP___MEMORY_CONSTRUCT_AT_H
