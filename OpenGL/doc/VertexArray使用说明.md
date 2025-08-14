# VertexArray ʹ��˵��

## 1. ��������

`VertexArray`�������������VAO���� OpenGL �����ڹ���������״̬�Ķ�������¼�˶��㻺�壨VBO�����������壨IBO���Լ��������Բ��ֵİ󶨹�ϵ��ʹ����Ⱦʱֻ��һ���԰� VAO ���ɻָ����ж���״̬��
 

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

## 2. ֧�ֵ���Ҫ����������

### ����������
- `VertexArray()`  
  ���캯��������һ���µ� VAO ������ OpenGL ��Դ�����
```cpp
VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &m_id)); // Generate a Vertex Array Object (VAO) to store the vertex attribute state
	GLCall(glBindVertexArray(m_id)); // Bind the VAO to the current context
}

```
- `~VertexArray()`  
  �����������Զ��ͷ� VAO ��Դ������ `glDeleteVertexArrays` ɾ�� VAO��ȷ����Դ����ȷ�ͷš�

### ������
- `void Bind() const`  
  �󶨵�ǰ VAO��ʹ���Ϊ��ǰ OpenGL �����ĵĻ VAO�������Ķ����������á����ƵȲ����������ڸ� VAO��
- `void Unbind() const`  
  ��� VAO������ǰ� VAO����Ϊ 0����Ч������ֹ��������Ӱ��� VAO��

### �󶨻����벼��
- `void LinkBufferAndLayout(const VertexBuffer& vb, const VertexBufferLayout& layout)`  
- ��ָ���Ķ��㻺�壨VBO���Ͷ������Բ��֣�Layout���󶨵���ǰ VAO�������ö�������ָ�롣�˺�����������֣���������ÿ���������Ե����͡��������Ƿ��һ������Ϣ��
- ���������VertexBufferLayout���������Ԫ�أ���ÿ��Ԫ�ص��� `glVertexAttribPointer` ���ö�������ָ�룬������`glEnableVertexAttribArray(i)`��Ӧ�Ķ������ԡ�
```cpp

### ��Դ����
- `unsigned int GetID() const`  
  ��ȡ VAO �� OpenGL ��Դ�����ID�������ڵײ���Ի�߼�������

---

## 3. ʹ������ʾ��
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

## 4. ע������
- ����Shader�Ƿ���Ҫ����,VertexArray����Ҫ�󶨡�OpenGL�����Զ����ɶ������ݣ���������shader��д��gl_Position=vec4(...)��Ҳֻ��˵�����������������ʱ��������������
- 