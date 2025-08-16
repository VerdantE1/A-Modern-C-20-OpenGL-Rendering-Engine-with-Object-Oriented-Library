#pragma once
#include <stack>
#include "Transform.h"

class TransformStack {
public:
    TransformStack() { stack_.push(Transform()); }

    void Push(const Transform& transform) {
        if (stack_.empty()) {
            stack_.push(Transform());
        }
        stack_.push(stack_.top());
        stack_.top() = stack_.top() * transform;
    }

    void Pop() {
        if (!stack_.empty()) {
            stack_.pop();
        }
    }

    void Clear() {
        while (!stack_.empty()) {
            stack_.pop();
        }
        stack_.push(Transform());
    }

    const Transform& Top() const {
        return stack_.top();
    }

    bool Empty() const {
        return stack_.empty();
    }

private:
    std::stack<Transform> stack_;
};