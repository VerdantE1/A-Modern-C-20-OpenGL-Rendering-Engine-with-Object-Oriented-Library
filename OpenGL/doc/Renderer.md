# Renderer 使用文档

## 概述
`Renderer` 封装了常用的 OpenGL 渲染流程，提供清屏、绘制、线框模式和深度测试等功能，帮助将底层状态调用标准化，提升代码可读性与复用性。适用于 C++20 与现代 OpenGL 使用场景。

## 公有接口
- ``void Clear()``;
  - 清除颜色与深度缓冲（确保下一帧从干净的缓冲开始渲染）。
- ``void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const``;
  - 使用给定 VA/IB/Shader进行索引绘制。	通用的以VertexArray, IndexBuffer和Shader的渲染并以三角形为图元的渲染函数。该函数会调用BindAll自动绑定VAO, IBO和Shader.
- ``void ClearColor();``
  - 设置清屏颜色（内部通常调用 glClearColor）。
- ``const Renderer& SetPolygonMode(bool mode) const;``
  - 切换线框/填充模式（true=线框，false=填充）。
- ``const Renderer& SetDepthTest(bool enable) const;``
  - 开启/关闭深度测试。

公有成员（状态开关，便于外部查询/标记）：
- mutable bool UsePolygonMode = false;
- mutable bool UseDepthTest = false;

## 使用示例
- 基础渲染循环（与顶点/索引/着色器配合）：
 ```cpp
 Renderer renderer;
 renderer.SetPolygonMode(true).SetDepthTest(true); //链式调用
 ```