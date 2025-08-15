# Utility ʹ���ĵ�

��ģ��Ϊ OpenGL ��Ⱦ��ص�ͨ�ù��߼��ϣ��ṩ������ꡢ������/��󹤾߼��������̽���������������ڱ��ִ������ͬʱ��������Ч���뽡׳�ԡ������� C++20 ���ִ� OpenGL ������

---

## ���ܸ���

- ��
  - ASSERT(X)������ʧ��ʱ�ڵ��������жϡ�
  - GLCall(X)����� OpenGL �����ִ��������鲢��־���� GL ����
- OpenGL ������
  - void GLClearError()����� OpenGL ������С�
  - bool GLLogCall(const char* function, const char* file, int line)����¼����ӡִ�к������ OpenGL ���󣬷����Ƿ��޴�
- ��/���������
  - template<typename... Args> void BindAll(const Args&... args)���Բ������о߱� Bind() �Ķ�����һ���� Bind()��
  - template<typename... Args> void UnbindAll(const Args&... args)���Բ������о߱� Unbind() �Ķ�����һ���� Unbind()��
- ��Ա̽�⣨C++20��
  - template <typename T> constexpr bool has_bind_v������ T �Ƿ���� Bind() ��Ա��
  - template <typename T> constexpr bool has_unbind_v������ T �Ƿ���� Unbind() ��Ա��

---

## �ӿ�������

### 1) �����������

- ASSERT(X)
  - ���壺�� X Ϊ false ʱ���������жϣ�__debugbreak����
  - �����÷�������У�顢״̬���ԵȽ��ڵ�����ʹ�õļ�顣

- GLCall(X)
  - ���壺��һ�� OpenGL ���ý��С�����ִ�С������װ��
  - ��Ϊ��
    1) GLClearError() �����������
    2) ִ�� X��
    3) GLLogCall(#X, __FILE__, __LINE__) ��ӡ�������Ƿ��޴�ʧ�ܽ����� ASSERT��
  - ���÷�Χ���κο������� GL ������ĵ��ã�gl*���������� gl* �������ᱨ����ֻ����ִ�к��� OpenGL ����״̬��

- void GLClearError()
  - ���壺ѭ������ glGetError() ֱ������ GL_NO_ERROR����մ�����С�

- bool GLLogCall(const char* function, const char* file, int line)
  - ���壺�����������ǰ������������д��󣬸�����������Դ�ļ����кţ������Ƿ��޴���
  - ������־��GL Error [0x0502] at glDrawElements (xxx.cpp:123)

### 2) ������/���

- template<typename... Args> void BindAll(const Args&... args)
  - ���壺�Բ�������ÿ������������� Bind() ��Ա�������֮�������ӡ���档
  - ���Ͷ���VertexArray��VertexBuffer��IndexBuffer��Shader��Texture �ȡ�

- template<typename... Args> void UnbindAll(const Args&... args)
  - ���壺�Բ�������ÿ������������� Unbind() ��Ա�������֮�������ӡ���档

- ��Ա̽�����
  - has_bind_v<T>��ʹ�� requires ���ʽ�ڱ������ж� T �Ƿ�ɵ��� Bind()��
  - has_unbind_v<T>��ʹ�� requires ���ʽ�ڱ������ж� T �Ƿ�ɵ��� Unbind()��

---

## ʹ��ʾ��

- ��Ⱦ֡ѭ���н��л��Ʋ�������
```cpp
Renderer renderer;
renderer.Clear(); BindAll(va, shader, texture1, texture2);
shader.SetUniform4f("u_Color", 1.0f, 0.3f, 0.8f, 1.0f);
// OpenGL ���ý���ʹ�� GLCall ���������ڶ�λ���� GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
UnbindAll(va, ib, shader);
```
- ���������������¼���ѯ����ѡ����
```cpp
GLCall(glfwSwapBuffers(window)); // ִ�к�˳������Ƿ����GL���� GLCall(glfwPollEvents());       
// ͬ�ϣ�GLFW ����� GL ���ã������ǵ���ǰ�� GL ����״̬��

```


---

## ���ʵ��

- Ϊ����Ǳ�ڲ��� GL ����� gl* ���ü��� GLCall�����ٶ�λ���ⷢ����λ�ã�����/�ļ�/�У���
- ��ÿ֡��Ⱦ�Ĺ̶������У�ʹ�� BindAll/UnbindAll ͳһ��Դ��/��󣬱�֤������һ�¡�
- �ڽ�����Ⱦѭ��ǰ����� Shader��VA/IB��Texture �ȶ���ĳ�ʼ����ѭ���н�������С����״̬�л�����ơ�
- ������������� Debug �����п�����Release ��ѡ���Ƴ�����������־��

---

## ���㣨Highlights��

- C++20 requires ��⣺ͨ�� requires ���ʽ�ڱ������ж������Ƿ�߱� Bind/Unbind �ӿڣ������롢�㿪�������麯������ RTTI����
- ���������۵����ʽ��BindAll/UnbindAll ʹ�ò��������۵����ʽ��������������������API ������š�
- һ���Ե������飺GLCall ��������ִ�С������׼��������Դ��׷����������䡢�ļ����кţ����������λЧ�ʡ�
- ������ʽʹ�ã������Դ��ֻ��ʵ�� Bind()/Unbind()������̳л�ʵ�ֶ���ӿڣ����ɱ� BindAll/UnbindAll ʶ��ʹ�á�
- �����д����޷켯�ɣ�����ʾ������Ⱦѭ���й㷺ʹ�ã�����ʵ�ʿ������̡�

---

## ע������

- ���������߳�
  - OpenGL ����״̬�������İ󶨣�����ӵ�е�ǰ GL �����ĵ��̵߳��� GLCall/GLClearError/GLLogCall��
- ������ GL ����
  - GLCall ������ gl* �������� GLFW ���ã������޺���������������ڡ�ִ�к�˳������Ƿ��� GL ���󡱡������ϸ����֣���ֻ�� gl* ����ʹ�� GLCall��
- ����±���ʾ
  - ��ǰʵ���������������˳��� idx Ϊ static ��δ��������־���ʼ�մ�ӡ��ͬ�±꣬����������ʾ֮�á�����׼ȷ�����������۵������������ṹ���󶨡�
- �����жϵ�С����
  - BindAll ��Ӧ���� has_bind_v �������������жϣ�UnbindAll ���� has_unbind_v����ȷ��ʵ�������屣��һ�¡�

---