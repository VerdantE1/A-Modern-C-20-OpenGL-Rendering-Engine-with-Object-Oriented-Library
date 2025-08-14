# Shaper 使用说明

## 1. 基本概念

`Shaper` 是所有图形形状类的抽象基类，统一管理渲染资源（如 Shader、Texture）和变换接口。所有具体形状（如 Square、Rectangle、Circle、Cube 等）都应继承自 `Shaper`。

---

## 2. 资源传递与解耦

- 形状类不直接创建 Shader 和 Texture，而是**由外部传入**（通过构造函数或 `SetShader`/`AddTexture` 方法），实现资源解耦和复用。
- 推荐使用智能指针（如 `std::shared_ptr`）管理 Shader 和 Texture，避免内存泄漏和重复释放。

---

## 3. 变换接口

- 所有形状类默认生成单位几何体（如单位正方形、单位矩形等）。
- 如需缩放、平移、旋转等变换，请通过 `SetTransform(const glm::mat4&)` 接口设置变换矩阵。
- 变换矩阵类型为 `glm::mat4`，默认初始化为单位矩阵。

---

## 4. 渲染接口 Draw

- 所有形状类需实现 `Draw(Renderer& renderer)` 方法，统一渲染流程。
- 渲染时会自动绑定 Shader、Texture 资源，并调用 Renderer 的 `Draw` 方法。
- 根据OpenGL的规定,在绑定Texture之前，必须先绑定Shader。
```cpp
	oid Shaper::Draw(Renderer& renderer) {
	if (shader) {
		shader->Bind();
		for (const auto& texture : textures) {
			texture->Bind();
		}
		renderer.Draw(*this);
	}
}
```

---

## 5. 扩展规范

- 新增形状类时，请继承自 `Shaper`，并遵循资源传递和变换接口规范。

---

## 6. 示例代码
