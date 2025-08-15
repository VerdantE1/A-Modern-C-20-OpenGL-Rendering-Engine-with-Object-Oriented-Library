# Utility 使用文档

本模块为 OpenGL 渲染相关的通用工具集合，提供错误检查宏、批量绑定/解绑工具及相关类型探测能力，帮助你在保持代码简洁的同时提升调试效率与健壮性。适用于 C++20 与现代 OpenGL 环境。

---

## 功能概览

- 宏
  - ASSERT(X)：断言失败时在调试器中中断。
  - GLCall(X)：清空 OpenGL 错误→执行语句→检查并日志所有 GL 错误。
- OpenGL 错误处理
  - void GLClearError()：清空 OpenGL 错误队列。
  - bool GLLogCall(const char* function, const char* file, int line)：记录并打印执行后产生的 OpenGL 错误，返回是否无错。
- 绑定/解绑批处理
  - template<typename... Args> void BindAll(const Args&... args)：对参数包中具备 Bind() 的对象逐一调用 Bind()。
  - template<typename... Args> void UnbindAll(const Args&... args)：对参数包中具备 Unbind() 的对象逐一调用 Unbind()。
- 成员探测（C++20）
  - template <typename T> constexpr bool has_bind_v：类型 T 是否具有 Bind() 成员。
  - template <typename T> constexpr bool has_unbind_v：类型 T 是否具有 Unbind() 成员。

---

## 接口与语义

### 1) 调试与错误检查

- ASSERT(X)
  - 语义：当 X 为 false 时触发调试中断（__debugbreak）。
  - 典型用法：参数校验、状态断言等仅在调试期使用的检查。

- GLCall(X)
  - 语义：对一行 OpenGL 调用进行“清错→执行→验错”包装。
  - 行为：
    1) GLClearError() 清空遗留错误；
    2) 执行 X；
    3) GLLogCall(#X, __FILE__, __LINE__) 打印并返回是否无错；失败将触发 ASSERT。
  - 适用范围：任何可能生成 GL 错误码的调用（gl*），包裹非 gl* 函数不会报错，但只是在执行后检查 OpenGL 错误状态。

- void GLClearError()
  - 语义：循环调用 glGetError() 直到返回 GL_NO_ERROR，清空错误队列。

- bool GLLogCall(const char* function, const char* file, int line)
  - 语义：遍历并输出当前错误队列中所有错误，附带函数名、源文件与行号，返回是否无错误。
  - 典型日志：GL Error [0x0502] at glDrawElements (xxx.cpp:123)

### 2) 批量绑定/解绑

- template<typename... Args> void BindAll(const Args&... args)
  - 语义：对参数包中每个对象，如果存在 Bind() 成员，则调用之；否则打印警告。
  - 典型对象：VertexArray、VertexBuffer、IndexBuffer、Shader、Texture 等。

- template<typename... Args> void UnbindAll(const Args&... args)
  - 语义：对参数包中每个对象，如果存在 Unbind() 成员，则调用之；否则打印警告。

- 成员探测变量
  - has_bind_v<T>：使用 requires 表达式在编译期判断 T 是否可调用 Bind()。
  - has_unbind_v<T>：使用 requires 表达式在编译期判断 T 是否可调用 Unbind()。

---

## 使用示例

- 渲染帧循环中进行绘制并检查错误：
```cpp
Renderer renderer;
renderer.Clear(); BindAll(va, shader, texture1, texture2);
shader.SetUniform4f("u_Color", 1.0f, 0.3f, 0.8f, 1.0f);
// OpenGL 调用建议使用 GLCall 包裹（便于定位错误） GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
UnbindAll(va, ib, shader);
```
- 包裹交换缓冲与事件轮询（可选）：
```cpp
GLCall(glfwSwapBuffers(window)); // 执行后顺带检查是否存在GL错误 GLCall(glfwPollEvents());       
// 同上（GLFW 本身非 GL 调用，检查的是调用前后 GL 错误状态）

```


---

## 最佳实践

- 为所有潜在产生 GL 错误的 gl* 调用加上 GLCall，快速定位问题发生的位置（函数/文件/行）。
- 在每帧渲染的固定流程中，使用 BindAll/UnbindAll 统一资源绑定/解绑，保证代码简洁一致。
- 在进入渲染循环前，完成 Shader、VA/IB、Texture 等对象的初始化，循环中仅进行最小化的状态切换与绘制。
- 错误检查仅建议在 Debug 构建中开启；Release 可选择移除或保留轻量日志。

---

## 亮点（Highlights）

- C++20 requires 检测：通过 requires 表达式在编译期判定类型是否具备 Bind/Unbind 接口，零侵入、零开销（无虚函数、无 RTTI）。
- 参数包与折叠表达式：BindAll/UnbindAll 使用参数包与折叠表达式对任意数量对象批处理，API 简洁优雅。
- 一致性调试体验：GLCall 将“清错→执行→验错”标准化，错误源可追溯至具体语句、文件与行号，大幅提升定位效率。
- 非侵入式使用：你的资源类只需实现 Bind()/Unbind()，无需继承或实现额外接口，即可被 BindAll/UnbindAll 识别并使用。
- 与现有代码无缝集成：已在示例与渲染循环中广泛使用，贴近实际开发流程。

---

## 注意事项

- 上下文与线程
  - OpenGL 错误状态与上下文绑定，请在拥有当前 GL 上下文的线程调用 GLCall/GLClearError/GLLogCall。
- 包裹非 GL 调用
  - GLCall 包裹非 gl* 函数（如 GLFW 调用）本身无害，但其意义仅在于“执行后顺带检查是否有 GL 错误”。若需严格区分，可只对 gl* 调用使用 GLCall。
- 输出下标提示
  - 当前实现中用于输出参数顺序的 idx 为 static 且未自增，日志里会始终打印相同下标，仅作轻量提示之用。如需准确索引，可在折叠中引入计数或结构化绑定。
- 条件判断的小建议
  - BindAll 中应基于 has_bind_v 进行条件编译判断；UnbindAll 基于 has_unbind_v。请确保实现与语义保持一致。

---