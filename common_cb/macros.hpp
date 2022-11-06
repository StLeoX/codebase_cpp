//
// Created by StLeoX on 2022/10/15.
//
// some useful macro definitions


#pragma once

#include <cassert>
#include <stdexcept>
#include <functional>
#include <type_traits>


/**
 * 断言并消息
 * */
#define ASSERT(expr, msg) assert((expr) && (msg))


/**
 * 不可达代码抛出异常
 * */
#define UNREACHABLE(msg) throw std::logic_error(msg)


/**
 * 禁用类的拷贝构造
 * */
#define DISALLOW_COPY(cname)          \
  cname(const cname &) = delete;      \
  cname &operator=(const cname &) = delete;


/**
 * 禁用类的移动构造
 * */
#define DISALLOW_MOVE(cname)          \
  cname(cname &&) = delete;           \
  cname &operator=(cname &&) = delete;


/**
 * ScopeGuard\n
 *   类似于DEFER的作用域包裹器\n
 * */
#define __SCOPEGUARD_CONCATENATE_IMPL(s1, s2) s1##s2
#define __SCOPEGUARD_CONCATENATE(s1, s2) __SCOPEGUARD_CONCATENATE_IMPL(s1, s2)
namespace clover {
template<typename Fun>
class ScopeGuard
{
public:
    ScopeGuard(Fun &&f) : _fun(std::forward<Fun>(f)), _active(true)
    {
    }

    ~ScopeGuard()
    {
        if (_active)
        {
            _fun();
        }
    }

    void dismiss()
    {
        _active = false;
    }

    ScopeGuard() = delete;

    ScopeGuard(const ScopeGuard &) = delete;

    ScopeGuard &operator=(const ScopeGuard &) = delete;

    ScopeGuard(ScopeGuard &&rhs) : _fun(std::move(rhs._fun)), _active(rhs._active)
    {
        rhs.dismiss();
    }

private:
    Fun _fun;
    bool _active;
};

namespace detail {
enum class ScopeGuardOnExit
{
};

template<typename Fun>
inline ScopeGuard<Fun> operator+(ScopeGuardOnExit, Fun &&fn)
{
    return ScopeGuard<Fun>(std::forward<Fun>(fn));
}
} // namespace detail
} // namespace scope_guard

// macro definition
#define ON_SCOPE_EXIT \
    auto __SCOPEGUARD_CONCATENATE(ext_exitBlock_, __LINE__) = scope_guard::detail::ScopeGuardOnExit() + [&]()


/**
 * DEFER Implement01\n
 *   using template, using `__COUNTER__`\n
 *   from: https://zhuanlan.zhihu.com/p/35191739\n
 * */
#define DEFER_1(x, y) x##y
#define DEFER_2(x, y) DEFER_1(x, y)
#define DEFER_0(x)    DEFER_2(x, __COUNTER__)

template <typename Function>
struct doDefer {
    Function f;
    doDefer(Function f) : f(f) {}
    ~doDefer() { f(); }
};

template <typename Function>
doDefer<Function> deferer(Function f) {
    return doDefer<Function>(f);
}

#define defer(expr)   auto DEFER_0(_defered_option) = deferer([&](){expr;})


/**
 * DEFER Implement02\n
 * using <functional>, using pair-recursive macro\n
 * */
class DeferHelper
{
public:
    DeferHelper(const std::function<void()> defer) : defer_(std::move(defer)) {}

    ~DeferHelper()
    {
        if (defer_) defer_();
    }

private:
    const std::function<void()> defer_;
};

#define AA(B, C) B##C
#define BB(B, C) AA(B,C)
#define DEFER(callback) common::DeferHelper BB(defer_helper_, __LINE__)(callback)

