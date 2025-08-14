# VertexArray 使用说明

## 1. 基本概念

`VertexArray`（顶点数组对象，VAO）是 OpenGL 中用于管理顶点属性状态的对象。它记录了顶点缓冲（VBO）、索引缓冲（IBO）以及顶点属性布局的绑定关系，使得渲染时只需一次性绑定 VAO 即可恢复所有顶点状态。
 

 ```cpp
 /*
This is VertexArrayObject,which is used to manage Vertex Buffer Objects (VBOs) and Index Buffer Objects (IBOs).
VBOs is just a buffer which has no semantic meaning, it just stores data.Also does IBOs.
VAOs is used to control how the data in VBOs and IBOs interpreted by the GPU.

Also,Bind and Unbind are used to set the the VAO state as current in OpenGL or not.

*/
class VertexArray :public Resource {
public:
	VertexArray();
	~VertexArray();
	void Bind() const;
	void Unbind() const;
	void LinkBufferAndLayout(const VertexBuffer& vb,const VertexBufferLayout& layout);

private:
	// Add this line to define m_id, inherited from Resource
	// unsigned int m_id; // Already inherited from Resource, no need to redefine
};    
    // No changes needed here, m_id is inherited from Resource
```
---

## 2. 支持的主要函数及语义

### 构造与析构
- `VertexArray()`  
  构造函数，创建一个新的 VAO 并分配 OpenGL 资源句柄。
```cpp
VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &m_id)); // Generate a Vertex Array Object (VAO) to store the vertex attribute state
	GLCall(glBindVertexArray(m_id)); // Bind the VAO to the current context
}

```
- `~VertexArray()`  
  析构函数，自动释放 VAO 资源。调用 `glDeleteVertexArrays` 删除 VAO，确保资源被正确释放。

### 绑定与解绑
- `void Bind() const`  
  绑定当前 VAO，使其成为当前 OpenGL 上下文的活动 VAO。后续的顶点属性设置、绘制等操作都作用于该 VAO。
- `void Unbind() const`  
  解绑 VAO，将当前活动 VAO设置为 0（无效），防止后续操作影响该 VAO。

### 绑定缓冲与布局
- `void LinkBufferAndLayout(const VertexBuffer& vb, const VertexBufferLayout& layout)`  
- 将指定的顶点缓冲（VBO）和顶点属性布局（Layout）绑定到当前 VAO，并设置顶点属性指针。此函数会遍历布局，依次设置每个顶点属性的类型、数量、是否归一化等信息。
- 函数会遍历VertexBufferLayout里面的所有元素，对每个元素调用 `glVertexAttribPointer` 设置顶点属性指针，并启用`glEnableVertexAttribArray(i)`相应的顶点属性。
```cpp

### 资源管理
- `unsigned int GetID() const`  
  获取 VAO 的 OpenGL 资源句柄（ID），用于底层调试或高级操作。

---

## 3. 使用流程示例
```cpp
void DrawPoint(GLFWwindow* window)
{
    VertexArray vao;

    Shader shader("res/shaders/OnePoint.shader");
    Renderer renderer;

    while(!glfwWindowShouldClose(window))
    {
        renderer.Clear();
        BindAll(vao, shader);
		GLCall(glPointSize(100.0f)); 
        GLCall(glDrawArrays(GL_POINTS, 0, 1));
        GLCall(glfwSwapBuffers(window));
        GLCall(glfwPollEvents());
	}

}
```

## 4. 注意事项
- 无论Shader是否需要数据,VertexArray都需要绑定。OpenGL不会自动生成顶点数据，哪怕你在shader里写死gl_Position=vec4(...)，也只是说“如果我有数据输入时，你这样处理”。
- 