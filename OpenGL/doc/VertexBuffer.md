

---

### 代码构造参数传递注意事项（VertexBufferLayout 用法）

#### VertexBufferLayout 构造函数参数传递规范

- **VertexBufferLayout** 的构造函数接受一个 `std::vector<std::variant<float, unsigned int, unsigned char>>` 类型的参数，用于描述每个顶点属性的分量数和类型。
- **直接用大括号初始化**对象时，可以简写为：
  ```cpp
  VertexBufferLayout layout({3.0f, 3.0f, 2.0f});
  ```
  这时编译器会自动推断为 `std::vector<float>`，并隐式转换成 `std::vector<SupportedTypes>`。

- **在使用 `std::make_shared` 创建智能指针对象时**，不能直接用花括号参数，否则会编译报错。  
  正确的做法是：**显式构造 vector 并传递**。
  ```cpp
  auto layout = std::make_shared<VertexBufferLayout>(
      std::vector<VertexBufferLayout::SupportedTypes>{3.0f, 3.0f, 2.0f}
  );
  ```
  或者：
  ```cpp
  std::vector<VertexBufferLayout::SupportedTypes> elems = {3.0f, 3.0f, 2.0f};
  auto layout = std::make_shared<VertexBufferLayout>(elems);
  ```

#### 详细说明

> 这是因为 C++ 语法在模板函数（如 `std::make_shared`）中，不能自动将 `{}` 花括号参数推断为 `std::vector`，而需要你**手动构造 vector** 以确保类型匹配。

#### 示例对比

```cpp
// 正确：直接变量构造
VertexBufferLayout layout({3.0f, 3.0f, 2.0f});

// 正确：智能指针构造需要显式 vector
auto layout_ptr = std::make_shared<VertexBufferLayout>(
    std::vector<VertexBufferLayout::SupportedTypes>{3.0f, 3.0f, 2.0f}
);

// 错误：不能直接用大括号初始化
// auto layout_ptr = std::make_shared<VertexBufferLayout>({3.0f, 3.0f, 2.0f}); // 编译报错
```

#### 建议

- **凡是在用智能指针（如 `std::make_shared`）创建 VertexBufferLayout 或类似接受 vector 类型参数的对象时，务必显式构造 vector！**

---
