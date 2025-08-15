# Shaper 使用文档

## 概述
`Shaper` 是一个抽象基类，用于封装一组与几何体相关的 OpenGL 资源：`VertexArray`、`VertexBuffer`、`IndexBuffer`、`VertexBufferLayout`。  
它在实例化时完成 VAO/VBO/IBO 的创建与布局关联，子类仅需提供顶点与索引数据即可专注于绘制逻辑。

> 重要：根据工程中资源类的实现，这些资源在构造或链接阶段会调用各自的 `Bind()` 绑定当前 OpenGL 上下文。因此，任何 `Shaper` 的实例化都会影响当前上下文状态，且必须在“已有且已设为当前”的 OpenGL 上下文线程中进行。
> Shaper的主要职责是提供顶点和索引数据的封装，并在构造时完成 VAO/VBO/IBO 的创建与布局绑定。Draw方法只是方便后续扩展使用。
所有子类都会在AllShaperTypes.h中注册，便于统一管理和使用。

Shaper的语义应该包含所有资源实体。所以它的内存需要注意，若后续还需使用则保证Shaper对象的生命周期足够长，避免资源被提前释放。
任何扩展Shaper的子类注意IndexSize是数量，而VerticeSize是字节数
---

## 构造与资源生命周期

构造签名：
- `Shaper(float* vertices, unsigned int verticesSize, unsigned int* indices, unsigned int indicesSize, std::vector<VertexBufferLayout::SupportedTypes> acnt_vec)`

参数语义：
- `vertices`/`verticesSize`：顶点数据指针与“字节数”（bytes）。与 `VertexBuffer(const void* data, unsigned int size)` 一致。
- `indices`/`indicesSize`：索引数据指针与“元素个数”（count，非字节数）。与 `IndexBuffer(const unsigned int* data, unsigned int count)` 一致。
- `acnt_vec`：顶点布局每个属性的分量数与类型（例如 `{3.0f, 3.0f, 2.0f}` 表示位置3、法线3、UV2）。类型为 `std::vector<std::variant<float, unsigned int, unsigned char>>`。

内部行为：
- 构造 `VertexBuffer`、`IndexBuffer`、`VertexBufferLayout`，并通过 `VertexArray::LinkBufferAndLayout` 绑定布局。
- 在这些步骤中会对 VAO/VBO/IBO 进行绑定，影响当前 OpenGL 上下文。

资源持有（protected）：
- `VertexArray va;`
- `VertexBuffer vb;`
- `IndexBuffer ib;`
- `VertexBufferLayout layout;`

访问器（const 引用返回）：
- `GetVertexArray()`
- `GetVertexBuffer()`
- `GetIndexBuffer()`
- `GetVertexBufferLayout()`

析构：
- 虚析构，确保子类安全释放；底层资源按各自类的规则释放。

---

## 抽象接口
- `virtual void Draw(Shader& shader, Renderer& renderer) = 0;`
  - 子类实现具体绘制逻辑（设置 uniform/绑定纹理/调用 `renderer.Draw` 等）。

---

## 子类实现规范

子类职责：
1) 提供静态或成员形式的 `vertices` 与 `indices`。
2) 在子类构造函数中将数据与布局传递给 `Shaper` 基类构造函数。
3) 在 `Draw` 中完成绑定和调用 `renderer.Draw(...)`。

布局参数示例：
- 直接构造（推荐）：`std::vector<VertexBufferLayout::SupportedTypes>{3.0f, 3.0f, 2.0f}`
- 若以智能指针包装（参考 VertexBuffer.md），需显式构造 `std::vector`，避免 `{}` 推断失败。

