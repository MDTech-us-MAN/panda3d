/**
 * PANDA 3D SOFTWARE
 * Copyright (c) Carnegie Mellon University.  All rights reserved.
 *
 * All use of this software is subject to the terms of the revised BSD
 * license.  You should have received a copy of this license along
 * with this source code in a file named "LICENSE."
 *
 * @file pvector.h
 * @author drose
 * @date 2001-06-05
 */

#ifndef PVECTOR_H
#define PVECTOR_H

#include <vector>
#include <initializer_list>

#include "dtoolbase.h"
#include "pallocator.h"
#include "register_type.h"

#ifndef USE_STL_ALLOCATOR
// If we're not using custom allocators, just use the standard class
// definition.
#define pvector vector

#elif defined(CPPPARSER)
// Simplified definition to speed up Interrogate parsing.
template<class Type>
class pvector : public std::vector<Type> {
PUBLISHED:
  const Type &operator[](size_t index) const;
  Type &operator[](size_t index);
  size_t size() const;
};

#else

/**
 * This is our own Panda specialization on the default STL vector.  Its main
 * purpose is to call the hooks for MemoryUsage to properly track STL-
 * allocated memory.
 */
template<class Type>
class pvector : public std::vector<Type, pallocator_array<Type> > {
public:
  typedef pallocator_array<Type> allocator;
  typedef std::vector<Type, allocator> base_class;
  typedef typename base_class::size_type size_type;

  explicit pvector(TypeHandle type_handle = pvector_type_handle) : base_class(allocator(type_handle)) { }
  pvector(const pvector<Type> &copy) : base_class(copy) { }
  pvector(pvector<Type> &&from) noexcept : base_class(std::move(from)) {};
  explicit pvector(size_type n, TypeHandle type_handle = pvector_type_handle) : base_class(n, Type(), allocator(type_handle)) { }
  explicit pvector(size_type n, const Type &value, TypeHandle type_handle = pvector_type_handle) : base_class(n, value, allocator(type_handle)) { }
  pvector(const Type *begin, const Type *end, TypeHandle type_handle = pvector_type_handle) : base_class(begin, end, allocator(type_handle)) { }
  pvector(std::initializer_list<Type> init, TypeHandle type_handle = pvector_type_handle) : base_class(std::move(init), allocator(type_handle)) { }

  pvector<Type> &operator =(const pvector<Type> &copy) {
    base_class::operator =(copy);
    return *this;
  }

  pvector<Type> &operator =(pvector<Type> &&from) noexcept {
    base_class::operator =(std::move(from));
    return *this;
  }

PUBLISHED:
  const Type &operator[](size_t index) const {
    return base_class::at(index);
  };
  Type &operator[](size_t index) {
    return base_class::at(index);
  };

  size_t size() const {
    return base_class::size();
  }
};

#endif  // USE_STL_ALLOCATOR

#endif
