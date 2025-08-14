# Shader开发规范（C++项目适配）

## 1. 基本概念

- Shader（着色器）是运行在 GPU 上的程序，用于实现顶点处理、片元处理等图形渲染流程。
- 在本项目中，Shader 资源类负责加载、解析和管理 Shader 文件，并在构造时自动解析 Shader 源码，编译并链接为 OpenGL 程序对象。同时在创建的同时还会绑定其到上下文中。
```cpp
	std::shared_ptr<Shader> shader = std::make_shared<Shader>("res/shaders/Basic.shader");
	//调用时解析,编译链接同时还会绑定到当前上下文
```

## 2. 全局变量命名约定

- 所有 Shader 的全局变量（Uniform）必须采用统一前缀 `u_`，后接描述性名称和序号（如有多个同类变量）。
- 示例：`u_Texture1`, `u_Texture2`, `u_Color`, `u_ModelMatrix`。
- 这样便于 C++ 端通过 `SetUniform*` 接口进行变量绑定和赋值，保证资源与 Shader 变量一一对应。

## 3. C++与Shader变量绑定

- C++ 端通过 `Shader::SetUniform*` 方法设置 Shader 变量值，变量名需与 Shader 文件中的 Uniform 名称完全一致。
- 例如，Square 图形类会调用 `shader->SetUniform1i("u_Texture1", texture->GetAssignedSlot());`，对应 Shader 文件中的 `uniform sampler2D u_Texture1;`。


| C++类型         | Shader类型         | 命名示例           |
|-----------------|-------------------|--------------------|
| int             | uniform int       | u_Index            |
| float           | uniform float     | u_Alpha            |
| glm::vec3       | uniform vec3      | u_LightPos         |
| glm::mat4       | uniform mat4      | u_ModelMatrix      |
| Texture对象      | uniform sampler2D | u_Texture1, u_Texture2 |

## 4. 多资源适配

- 当有多个同类资源（如多张纹理），变量名需带序号：`u_Texture1`, `u_Texture2`，C++端通过循环依次绑定。
- 示例：
```cpp
 for (size_t i = 0; i < textures.size(); ++i) { shader->SetUniform1i("u_Texture" + std::to_string(i + 1), textures[i]->GetAssignedSlot()); }
```

对应 Shader 文件：
```glsl
uniform sampler2D u_Texture1;
uniform sampler2D u_Texture2;
```

## 5. 变换与矩阵变量

- 变换相关变量建议统一命名为 `u_ModelMatrix`, `u_ViewMatrix`, `u_ProjectionMatrix`，便于 C++ 端传递变换矩阵。

## 6. 其他建议

- 所有 Shader Uniform 变量应有明确用途和注释，便于 C++ 端开发者理解和维护。
- 禁止在 Shader 中使用未在 C++ 端绑定的 Uniform，避免运行时警告或错误。
- 推荐将 Shader 变量命名规范写入团队开发文档，保持一致性。
- 建议顶点的pos属性是以3维向量的形式传入(for c++)。
---

