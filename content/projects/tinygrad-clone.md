+++
title = "micrograd++: A Tiny Autograd Engine in C++"
date = 2025-01-25
draft = false
tags = ["cpp", "deep-learning", "autograd", "project"]
description = "Building a minimal autograd engine in C++ to understand automatic differentiation from the ground up."
+++

## Motivation

After reading Karpathy's micrograd, I wanted to understand automatic differentiation deeply enough to implement it. And of course, I wanted to do it in C++ with zero dependencies.

## Design

The core is a `Value` class wrapping a scalar `float` and a computation graph:

```cpp
#include <functional>
#include <memory>
#include <set>
#include <vector>

class Value {
public:
    float data;
    float grad = 0.0f;
    std::string label;

    // The backward function — populated during forward pass
    std::function<void()> backward_ = [](){};
    std::vector<std::shared_ptr<Value>> prev_;

    Value(float data, std::string label = "")
        : data(data), label(std::move(label)) {}

    std::shared_ptr<Value> operator+(std::shared_ptr<Value> other);
    std::shared_ptr<Value> operator*(std::shared_ptr<Value> other);
    std::shared_ptr<Value> relu();

    void backward();
};
```

The magic is in the operator overloads — each one builds the backward closure:

```cpp
std::shared_ptr<Value> Value::operator+(std::shared_ptr<Value> other) {
    auto out = std::make_shared<Value>(this->data + other->data, "+");
    out->prev_ = {shared_from_this(), other};

    // Capture by value to keep the nodes alive
    auto self = shared_from_this();
    out->backward_ = [self, other, out]() {
        self->grad  += out->grad;
        other->grad += out->grad;
    };
    return out;
}
```

## Topological Sort for Backprop

Backpropagation requires evaluating gradients in reverse topological order:

```cpp
void Value::backward() {
    std::vector<Value*> topo;
    std::set<Value*> visited;

    std::function<void(Value*)> build_topo = [&](Value* v) {
        if (!visited.count(v)) {
            visited.insert(v);
            for (auto& child : v->prev_)
                build_topo(child.get());
            topo.push_back(v);
        }
    };
    build_topo(this);

    this->grad = 1.0f;
    for (auto it = topo.rbegin(); it != topo.rend(); ++it)
        (*it)->backward_();
}
```

## Results

Trained a 2-layer MLP on XOR — converges in ~500 steps. The gradient values match PyTorch to 5 decimal places.

**Repo:** [github.com/rosxnb/micrograd-cpp](https://github.com/rosxnb)
