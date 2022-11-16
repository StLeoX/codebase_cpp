//
// Created by leo on 2022/11/15.
// Lisp List Implement. Using data_ptr and ref_count
//

#pragma once

#include <cinttypes>
#include <typeinfo>
#include <string>
#include <sstream>

template<typename T>
class Seq;

/**
 * 序列节点
 * @tparam T
 */
template<typename T>
class SeqItem
{
    friend class Seq<T>;

public:
    SeqItem(const T &data, SeqItem<T> *next) :
            rc_(1),
            data_(data),
            next_(next)
    {
        if (next_ != nullptr) ++rc_;
    }

    SeqItem(const T &data) :
            rc_(1),
            data_(data),
            next_(nullptr) {}

private:
    uint32_t rc_;  // refcount
    const T data_;  // data
    SeqItem<T> next_;  // next
};

// 是否允许递归计算
// #define enable_rec

/**
 * 序列
 * @tparam T
 */
template<typename T>
class Seq
{
public:
    /// 创建序列：空序列
    explicit Seq() : item_(nullptr) {}

    /// 创建序列：头元素为t，尾序列为s
    explicit Seq(const T &t, Seq<T> s) :
            item_(new SeqItem<T>(t, s.item_)) {}

    /// 创建序列：尾序列为s
    explicit Seq(SeqItem<T> *s) :
            item_(s) { if (s != nullptr) ++s->rc_; }

            // todo(enhance) list_init support
/*
    /// 创建序列：变长元素
    template<typename... Args>
    explicit Seq(Args... args)
    {
        insert_head(args...);
    }
*/

    /// 创建序列：复制
    Seq(const Seq &other) :
            item_(other.item_)
    {
        if (item_ != nullptr) ++item_->rc_;
    }

    /// 创建序列：复制赋值
    Seq &operator=(const Seq &other)
    {
        if (other.item_ != nullptr) --other.item_->rc_;
        destroy(item_);
        item_ = other.item_;
        return *this;
    }

    /// 销毁序列
    ~Seq() { destroy(item_); }

    /// 销毁序列：级联销毁
    void destroy(SeqItem<T> *item)
    {
        while (item != nullptr && --item->rc_ == 0)
        {
            SeqItem<T> *next = item->next_;
            delete item;
            item = next;
        }
    }

    /// 获取元素：头元素
    T head() const { return empty() ? T{} : item_->data_; }

    /// 获取元素:尾序列
    Seq<T> tail() const { return empty() ? Seq() : Seq(item_->next_); }

    /// 获取长度
    int length() const
    {
#ifndef enable_rec
        int ret = 0;
        while (!empty())
        {
            *this = this->tail();
            ++ret;
        }
        return ret;
#endif
        // 递归版本
        return empty() ? 0 : 1 + tail().length();
    }

    /// 获取元素：转为字符串
    std::string to_string() const
    {
        return "";
    }

    /// 判断为空
    bool empty() const { return item_ == nullptr; }

    /// 判断相等
    bool operator==(const Seq &other) const
    {
        return false;
    }

    /// 插入元素：在头部插入
    Seq<T> insert_head(const T &t)
    {
        item_ = new SeqItem(t, item_);
        return *this;
    }

    /// 插入元素：在头部插入
    Seq<T> insert_tail(const T &t) { return Seq(); }


private:
    SeqItem<T> *item_;  // data_ptr
};
