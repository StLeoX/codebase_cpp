//
// Created by StLeoX on 2022/10/15.
//


#pragma once

#include <cassert>
#include <stdexcept>

#define ASSERT(expr, msg) assert((expr) && (msg))

#define UNREACHABLE(msg) throw std::logic_error(msg)

// Macros to disable copying and moving
#define DISALLOW_COPY(cname)          \
  cname(const cname &) = delete;      \
  cname &operator=(const cname &) = delete;

#define DISALLOW_MOVE(cname)          \
  cname(cname &&) = delete;           \
  cname &operator=(cname &&) = delete;

#define DISALLOW_COPY_AND_MOVE(cname) \
  DISALLOW_COPY(cname);               \
  DISALLOW_MOVE(cname);

