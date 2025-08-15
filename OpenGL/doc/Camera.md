## Camera类使用文档（精髓版）

** 作用**
Camera类用于管理视图矩阵（View）和投影矩阵（Projection），决定你在3D场景中的观察位置、方向和视野范围。

** 核心用法**
1. * *创建Camera对象 * *
传入位置、目标、上方向、视野角度、宽高比、近平面、远平面：
```cpp
Camera camera(
    glm::vec3(0, 0, 10), // 相机位置
    glm::vec3(0, 0, 0),  // 观察目标
    glm::vec3(0, 1, 0),  // 上方向
    70.0f, aspect, 0.1f, 100.0f // 视野、宽高比、近平面、远平面
);
```

2. * *获取视图和投影矩阵 * *
渲染时传递给着色器：
```cpp
shader.SetUniformMat4fv("view", camera.GetViewMatrix());
shader.SetUniformMat4fv("projection", camera.GetProjectionMatrix());
```

3. * *与场景结合示例 * *
```cpp
Camera camera(
    glm::vec3(0, 0, 10),
    glm::vec3(0, 0, 0),
    glm::vec3(0, 1, 0),
    70.0f, aspect, 0.1f, 100.0f
);

glm::mat4 view = camera.GetViewMatrix();
glm::mat4 projection = camera.GetProjectionMatrix();

shader.SetUniformMat4fv("view", view);
shader.SetUniformMat4fv("projection", projection);
```

**辅助类**
- Frustum类：用于计算视锥体，提供更高级的投影功能。暂时用于DEBUG，防止因为坐标错误导致渲染异常。

** 精髓总结**
Camera类就是“虚拟相机”，让你像现实摄影机一样控制视角和投影。只需设置参数，渲染时用它的矩阵即可实现自由观察和场景变换。