+++
title = "Templates: From Basics to SFINAE"
date = 2025-02-10
draft = false
series = ["Modern C++ Deep Dive"]
tags = ["cpp", "templates", "generics"]
description = "Function and class templates, template specialisation, and intro to SFINAE."
+++

## Function Templates

Templates let you write code that works for multiple types:

```cpp
template <typename T>
T max(T a, T b) {
    return a > b ? a : b;
}

// Usage — compiler deduces T = int, then T = double
int    i = max(3, 7);        // T = int
double d = max(3.14, 2.71);  // T = double
```

The compiler **instantiates** a concrete version for each unique `T` it sees.

## Class Templates

```cpp
template <typename T, std::size_t N>
class FixedArray {
    T data_[N];
public:
    T& operator[](std::size_t i) { return data_[i]; }
    constexpr std::size_t size() const { return N; }
};

FixedArray<int, 8> arr;
arr[0] = 42;
```

Non-type template parameters (like `N` above) must be compile-time constants.

## Template Specialisation

You can provide a different implementation for specific types:

```cpp
// Primary template
template <typename T>
struct is_pointer { static constexpr bool value = false; };

// Full specialisation for pointer types
template <typename T>
struct is_pointer<T*> { static constexpr bool value = true; };

static_assert(is_pointer<int*>::value  == true);
static_assert(is_pointer<int>::value   == false);
```

## SFINAE — Substitution Failure Is Not An Error

When template argument substitution fails, the compiler doesn't error — it just removes that overload from consideration. This enables compile-time dispatch:

```cpp
#include <type_traits>

// Only enabled for integral types
template <typename T>
std::enable_if_t<std::is_integral_v<T>, void>
print_type(T val) {
    std::cout << "integral: " << val << "\n";
}

// Only enabled for floating-point types
template <typename T>
std::enable_if_t<std::is_floating_point_v<T>, void>
print_type(T val) {
    std::cout << "float: " << val << "\n";
}

print_type(42);     // "integral: 42"
print_type(3.14);   // "float: 3.14"
```

{{< callout type="tip" title="Prefer Concepts in C++20" >}}
SFINAE is powerful but notoriously hard to read. C++20 **Concepts** achieve the same effect far more cleanly:

```cpp
template <std::integral T>
void print_type(T val) { /* ... */ }
```
{{< /callout >}}
