+++
title = "Move Semantics and Rvalue References"
date = 2025-01-20
draft = false
series = ["Modern C++ Deep Dive"]
tags = ["cpp", "performance", "memory"]
description = "Understanding rvalue references, move constructors, and when moves actually happen."
+++

## The Problem With Copies

Before C++11, returning a large object from a function meant copying it — even if the original was a temporary that would immediately be destroyed.

```cpp
std::vector<int> make_vec() {
    std::vector<int> v(1000000, 42);
    return v;   // Pre-C++11: copy! (or RVO, which was not guaranteed)
}
```

**Move semantics** let us *transfer* ownership of resources instead of copying them.

## Lvalues and Rvalues

An **lvalue** is an expression that refers to a memory location you can take the address of. An **rvalue** is everything else — temporaries, literals, the result of expressions.

```cpp
int x = 5;
int* p = &x;     // ok — x is an lvalue
int* q = &42;    // error — 42 is an rvalue, no address
```

**Rvalue references** (type `T&&`) bind to rvalues. They signal "I can steal from this":

```cpp
void process(std::string&& s) {
    // s is a named variable inside here (so it's an lvalue!),
    // but it was bound from an rvalue — safe to move.
    internal_store = std::move(s);
}
```

## Move Constructor and Move Assignment

A class should provide these alongside the copy versions:

```cpp
class Buffer {
    std::size_t size_;
    int* data_;

public:
    // Move constructor
    Buffer(Buffer&& other) noexcept
        : size_(other.size_), data_(other.data_)
    {
        other.size_ = 0;
        other.data_ = nullptr;  // leave the "donor" in a valid but empty state
    }

    // Move assignment
    Buffer& operator=(Buffer&& other) noexcept {
        if (this != &other) {
            delete[] data_;
            size_ = other.size_;
            data_ = other.data_;
            other.size_ = 0;
            other.data_ = nullptr;
        }
        return *this;
    }

    ~Buffer() { delete[] data_; }
};
```

{{< callout type="note" title="Mark moves noexcept" >}}
Marking move constructors `noexcept` is critical. STL containers like `std::vector` will only use your move constructor during reallocation if it's `noexcept`. Otherwise they fall back to copying for exception safety.
{{< /callout >}}

## `std::move` is Just a Cast

`std::move` does *not* move anything. It's an unconditional cast to an rvalue reference, signalling intent:

```cpp
std::vector<int> a = {1, 2, 3};
std::vector<int> b = std::move(a);  // cast + then move ctor takes over
// a is now in a valid but unspecified state (likely empty)
```

After `std::move(a)`, don't use `a` except to assign to it or destroy it.

## The Rule of Five

If you define any of: destructor, copy constructor, copy assignment, move constructor, move assignment — you should explicitly define (or `= default` / `= delete`) all five.

```cpp
class MyClass {
public:
    MyClass() = default;
    ~MyClass();                                  // 1
    MyClass(const MyClass&);                     // 2
    MyClass& operator=(const MyClass&);          // 3
    MyClass(MyClass&&) noexcept;                 // 4
    MyClass& operator=(MyClass&&) noexcept;      // 5
};
```

{{< callout type="tip" title="Prefer the Rule of Zero" >}}
The best move semantics are the ones you don't write. Use smart pointers (`unique_ptr`, `shared_ptr`) and standard containers as members, and the compiler generates correct move operations automatically. Only drop to the rule of five when you're managing raw resources directly.
{{< /callout >}}
