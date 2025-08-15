markdown
## Transform类使用文档（精髓版）

**作用**  
Transform类用于管理物体的空间变换，包括位置（position）、旋转（rotation，欧拉角，单位为弧度）和缩放（scale），并自动生成变换矩阵，方便模型在场景中移动、旋转和缩放。
语义：Transform关注于基础变换,即由一次平移、一次旋转和一次缩放组成的变换。它不处理复杂的变换组合。


**核心用法**
1. **创建和设置属性**
```cpp
Transform t;
t.position = glm::vec3(1.0f, 2.0f, 3.0f); // 设置位置
t.rotation = glm::vec3(0.0f, glm::radians(45.0f), 0.0f); // Y轴旋转45度
t.scale = glm::vec3(2.0f, 2.0f, 2.0f); // 设置缩放
```

2. **获取变换矩阵**
```cpp
glm::mat4 modelMatrix = t.GetMatrix();
```

**精髓总结**  
Transform类将平移、旋转、缩放整合为一个变换矩阵，渲染时直接用于模型变换，让物体在三维空间中灵活变换。只包含基础变换，不处理复杂的变换组合。复杂的变换组合请用多个Transform对象或其他变换类。
Transform类设有缓存机制。若属性未改变，则返回缓存的变换矩阵，避免重复计算，提高性能。若调用改变参数的方法（如`SetPosition`、`SetRotation`等），则会清除缓存，确保下次获取矩阵时重新计算。
Transform只能由set方法更改内部属性，其他方法（如`GetMatrix`）不会修改属性。这样可以确保变换矩阵的正确性和一致性。

setMatrix方法用于直接设置变换矩阵，适用于需要手动控制变换的场景。

**对于操作符\* **
Transform类重载了乘法操作符`*`，允许直接将Transform与glm::mat4矩阵相乘，方便在变换链中使用。
数学乘法中，遵循GLM风格。A * B * v 表示：v 先被 B 变换，再被 A 变换。
对于Transform类的乘法操作符，左侧是Transform对象，右侧是glm::mat4矩阵，表示先应用Transform的变换再应用矩阵的变换。可以交换相乘但语义不同。
对于glm::mat4类似。但返回mat4对象而不是Transform对象。


**亮点**
- 左乘/右乘都支持，并且按照 GLM/线性代数标准顺序（先写的先用）。
- 变换矩阵懒更新（dirty 标记），性能好。
- Transform 复合也合理。
- 私有成员安全性+友元运算符灵活性兼顾。