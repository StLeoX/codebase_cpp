//
// Created by StLeoX on 2022/10/15.
// From: BusTub/rwlatch.h
//

#pragma once

#include <climits>
#include <condition_variable>
#include <mutex>

#include "common_cb/macros.h"

/**
 * Reader-Writer lock backed by std::mutex.
 */
class ReaderWriterLock
{
    using mutex_t = std::mutex;
    using cond_t = std::condition_variable;
    static const uint32_t MAX_READERS = UINT_MAX;

public:
    ReaderWriterLock() = default;

    ~ReaderWriterLock() { std::lock_guard<mutex_t> guard(mutex_); }

    DISALLOW_COPY(ReaderWriterLock);

    /**
     * Acquire a write lock.
     */
    void WLock()
    {
        std::unique_lock<mutex_t> lock(mutex_);
        while (writer_entered_)
        {
            reader_.wait(lock);
        }
        writer_entered_ = true;
        while (reader_count_ > 0)
        {
            writer_.wait(lock);
        }
    }

    /**
     * Release a write lock.
     */
    void WUnlock()
    {
        std::lock_guard<mutex_t> guard(mutex_);
        writer_entered_ = false;
        reader_.notify_all();
    }

    /**
     * Acquire a read lock.
     */
    void RLock()
    {
        std::unique_lock<mutex_t> lock(mutex_);
        while (writer_entered_ || reader_count_ == MAX_READERS)
        {
            reader_.wait(lock);
        }
        reader_count_++;
    }

    /**
     * Release a read lock.
     */
    void RUnlock()
    {
        std::lock_guard<mutex_t> guard(mutex_);
        reader_count_--;
        if (writer_entered_)
        {
            if (reader_count_ == 0)
            {
                writer_.notify_one();
            }
        } else
        {
            if (reader_count_ == MAX_READERS - 1)
            {
                // Note: this implementation will lead to deadlock after reader count reaches the maximum.
                reader_.notify_one();
            }
        }
    }

private:
    mutex_t mutex_;
    cond_t writer_;
    cond_t reader_;
    uint32_t reader_count_{0};
    bool writer_entered_{false};
};

