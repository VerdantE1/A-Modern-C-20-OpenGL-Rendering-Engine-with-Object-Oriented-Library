# OpenGL现代化渲染引擎
## Updating (2025.8.1~Now)
## 1. 项目简介

一个基于现代OpenGL（Core Profile）的C++渲染引擎，提供了完整的3D图形渲染能力。该项目采用面向对象设计，封装了OpenGL底层API，提供简洁易用的渲染接口。支持基础几何体渲染、纹理映射、变换矩阵操作、太阳系动画演示等功能。

**主要特性：**
- 现代OpenGL Core Profile (3.3+)
- 面向对象的渲染架构
- 完整的3D几何体支持
- 灵活的着色器系统
- 高效的资源管理
- 动态场景渲染

## 2. 项目核心类

| 类名           | 作用                               | 使用的C++语言特性                               |
| -------------- | ---------------------------------- | ----------------------------------------------- |
| `Shaper`       | 抽象基类，定义所有几何体的通用接口 | 纯虚函数、多态、RAII资源管理                    |
| `Sphere`       | 球体几何体，支持程序化生成顶点     | 继承、inline函数、constexpr、数学计算算法       |
| `Cube`         | 立方体几何体，预定义顶点数据       | 继承、constexpr静态数组、成员初始化列表         |
| `Pyramid`      | 金字塔几何体，支持纹理映射         | 继承、静态constexpr数据成员                     |
| `Renderer`     | 渲染器，封装OpenGL渲染调用         | mutable关键字、方法链式调用、const正确性        |
| `Transform`    | 3D变换矩阵封装，支持位移/旋转/缩放 | 运算符重载、友元函数、lazy evaluation（脏标记） |
| `VertexArray`  | 顶点数组对象(VAO)管理              | RAII资源管理、构造函数/析构函数                 |
| `VertexBuffer` | 顶点缓冲对象(VBO)管理              | RAII、模板特化                                  |
| `IndexBuffer`  | 索引缓冲对象(EBO)管理              | RAII、类型安全                                  |
| `Shader`       | 着色器程序管理，支持uniform变量    | 字符串处理、文件I/O、OpenGL状态管理             |
| `Texture`      | 纹理对象管理和加载                 | RAII、图像处理                                  |
| `SolarSystem`  | 太阳系动画演示系统                 | 函数式接口、时间驱动动画                        |

**C++20特性应用：**
- `requires`表达式用于概念约束（Utility.h中的成员探测）
- 可变参数模板（BindAll/UnbindAll函数）
- constexpr计算和编译期优化
- 智能指针和现代内存管理
- 范围for循环和auto类型推导

## 3. 项目亮点

### 🎯 **现代化设计模式**
- **RAII资源管理**：所有OpenGL资源自动管理生命周期，防止内存泄漏
- **多态渲染系统**：通过Shaper基类实现统一的渲染接口
- **链式API调用**：Renderer支持方法链式调用，提升代码可读性

### 🚀 **性能优化特性**
- **批量绑定/解绑**：BindAll/UnbindAll函数支持一次性处理多个OpenGL对象
- **实例化渲染**：支持DrawInstanced高效渲染大量相同几何体
- **Lazy Evaluation**：Transform矩阵采用脏标记延迟计算

### 🎨 **强大的渲染能力**
- **程序化几何体生成**：Sphere类动态生成球体顶点和索引
- **灵活的着色器系统**：支持顶点/片段着色器热加载和uniform变量
- **完整的3D变换**：支持模型/视图/投影矩阵变换

### 🛠️ **开发友好特性**
- **智能错误检测**：GLCall宏提供详细的OpenGL错误定位
- **类型安全的概念约束**：使用C++20 requires检查类型是否支持特定操作
- **丰富的调试信息**：完整的构建日志和错误追踪

### ⭐ **实用演示系统**
- **太阳系动画**：展示复杂的3D场景渲染和动画系统
- **多种几何体演示**：点、三角形、立方体、金字塔、球体等
- **交互式控制**：支持实时参数调整和场景切换

## 4. 文件目录结构

```
OpenGL/
├── src/
│   ├── Application.cpp          # 主程序入口和渲染循环
│   ├── DrawDemo.cpp/.h          # 各种几何体渲染演示
│   ├── SolarSystem.cpp/.h       # 太阳系动画系统
│   └── include/                 # 核心类库
│       ├── Renderer.cpp/.h      # 渲染器核心
│       ├── Shader.cpp/.h        # 着色器管理
│       ├── Texture.cpp/.h       # 纹理管理
│       ├── VertexArray.cpp/.h   # VAO管理
│       ├── VertexBuffer.cpp/.h  # VBO管理
│       ├── IndexBuffer.cpp/.h   # EBO管理
│       ├── VertexBufferLayout.h # 顶点布局定义
│       ├── Utility.cpp/.h       # 通用工具函数
│       ├── Transform.h          # 3D变换矩阵
│       ├── Shaper.h             # 几何体抽象基类
│       ├── AllShaperTypes.h     # 所有几何体类型汇总
│       ├── 2D/
│       │   └── IsoscelesTriangle.h  # 2D等腰三角形
│       ├── 3D/
│       │   ├── Cube.h           # 立方体
│       │   ├── Pyramid.h        # 金字塔
│       │   └── Sphere.h         # 球体
│       ├── ViewUtils/
│       │   └── Camera.h         # 相机系统
│       └── Ds/
│           └── TransformStack.h # 变换矩阵栈
├── res/
│   ├── shaders/                 # 着色器源码
│   │   ├── Basic.shader         # 基础着色器
│   │   ├── SoloarSystem.shader  # 太阳系着色器
│   │   ├── 3DShaderWithTexture.shader # 3D纹理着色器
│   │   └── ...                  # 其他专用着色器
│   └── textures/                # 纹理资源
│       ├── Texture1.jpg
│       ├── Texture2.jpg
│       └── textures1.jpg
├── vendor/                      # 第三方库
│   ├── glm/                     # GLM数学库
│   └── stb_image/               # 图像加载库
└── doc/                         # 项目文档
    ├── Utility.md               # 工具类使用说明
    ├── VertexArray使用说明.md   # VAO使用指南
    ├── Renderer.md              # 渲染器文档
    ├── Shaper.md                # 几何体系统文档
    └── Transform.md             # 变换系统文档
```

## 5. 快速开始

```cpp
// 创建窗口和基础设置
GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Demo", NULL, NULL);

// 创建几何体和渲染器
Cube cube;
Renderer renderer;
Shader shader("res/shaders/Basic.shader");

// 渲染循环
while (!glfwWindowShouldClose(window)) {
    renderer.Clear();
    
    BindAll(cube.GetVertexArray(), shader);
    cube.Draw(shader, renderer);
    
    glfwSwapBuffers(window);
    glfwPollEvents();
}
```

## 6. 系统要求

- **编译器：** 支持C++20的编译器（MSVC 2019+, GCC 10+, Clang 12+）
- **图形API：** OpenGL 3.3 Core Profile或更高版本
- **依赖库：** GLFW, GLEW, GLM, STB Image
- **操作系统：** Windows 10/11, Linux, macOS

---

*该项目展示了现代C++在图形编程中的最佳实践，适合学习OpenGL渲染管线和3D图形编程。*
