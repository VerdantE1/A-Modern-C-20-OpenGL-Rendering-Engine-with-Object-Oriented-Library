# Shaper ʹ���ĵ�

## ����
`Shaper` ��һ��������࣬���ڷ�װһ���뼸������ص� OpenGL ��Դ��`VertexArray`��`VertexBuffer`��`IndexBuffer`��`VertexBufferLayout`��  
����ʵ����ʱ��� VAO/VBO/IBO �Ĵ����벼�ֹ�������������ṩ�������������ݼ���רע�ڻ����߼���

> ��Ҫ�����ݹ�������Դ���ʵ�֣���Щ��Դ�ڹ�������ӽ׶λ���ø��Ե� `Bind()` �󶨵�ǰ OpenGL �����ġ���ˣ��κ� `Shaper` ��ʵ��������Ӱ�쵱ǰ������״̬���ұ����ڡ�����������Ϊ��ǰ���� OpenGL �������߳��н��С�
> Shaper����Ҫְ�����ṩ������������ݵķ�װ�����ڹ���ʱ��� VAO/VBO/IBO �Ĵ����벼�ְ󶨡�Draw����ֻ�Ƿ��������չʹ�á�
�������඼����AllShaperTypes.h��ע�ᣬ����ͳһ�����ʹ�á�

Shaper������Ӧ�ð���������Դʵ�塣���������ڴ���Ҫע�⣬����������ʹ����֤Shaper��������������㹻����������Դ����ǰ�ͷš�
�κ���չShaper������ע��IndexSize����������VerticeSize���ֽ���
---

## ��������Դ��������

����ǩ����
- `Shaper(float* vertices, unsigned int verticesSize, unsigned int* indices, unsigned int indicesSize, std::vector<VertexBufferLayout::SupportedTypes> acnt_vec)`

�������壺
- `vertices`/`verticesSize`����������ָ���롰�ֽ�������bytes������ `VertexBuffer(const void* data, unsigned int size)` һ�¡�
- `indices`/`indicesSize`����������ָ���롰Ԫ�ظ�������count�����ֽ��������� `IndexBuffer(const unsigned int* data, unsigned int count)` һ�¡�
- `acnt_vec`�����㲼��ÿ�����Եķ����������ͣ����� `{3.0f, 3.0f, 2.0f}` ��ʾλ��3������3��UV2��������Ϊ `std::vector<std::variant<float, unsigned int, unsigned char>>`��

�ڲ���Ϊ��
- ���� `VertexBuffer`��`IndexBuffer`��`VertexBufferLayout`����ͨ�� `VertexArray::LinkBufferAndLayout` �󶨲��֡�
- ����Щ�����л�� VAO/VBO/IBO ���а󶨣�Ӱ�쵱ǰ OpenGL �����ġ�

��Դ���У�protected����
- `VertexArray va;`
- `VertexBuffer vb;`
- `IndexBuffer ib;`
- `VertexBufferLayout layout;`

��������const ���÷��أ���
- `GetVertexArray()`
- `GetVertexBuffer()`
- `GetIndexBuffer()`
- `GetVertexBufferLayout()`

������
- ��������ȷ�����లȫ�ͷţ��ײ���Դ��������Ĺ����ͷš�

---

## ����ӿ�
- `virtual void Draw(Shader& shader, Renderer& renderer) = 0;`
  - ����ʵ�־�������߼������� uniform/������/���� `renderer.Draw` �ȣ���

---

## ����ʵ�ֹ淶

����ְ��
1) �ṩ��̬���Ա��ʽ�� `vertices` �� `indices`��
2) �����๹�캯���н������벼�ִ��ݸ� `Shaper` ���๹�캯����
3) �� `Draw` ����ɰ󶨺͵��� `renderer.Draw(...)`��

���ֲ���ʾ����
- ֱ�ӹ��죨�Ƽ�����`std::vector<VertexBufferLayout::SupportedTypes>{3.0f, 3.0f, 2.0f}`
- ��������ָ���װ���ο� VertexBuffer.md��������ʽ���� `std::vector`������ `{}` �ƶ�ʧ�ܡ�

