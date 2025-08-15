# Renderer ʹ���ĵ�

## ����
`Renderer` ��װ�˳��õ� OpenGL ��Ⱦ���̣��ṩ���������ơ��߿�ģʽ����Ȳ��Եȹ��ܣ��������ײ�״̬���ñ�׼������������ɶ����븴���ԡ������� C++20 ���ִ� OpenGL ʹ�ó�����

## ���нӿ�
- ``void Clear()``;
  - �����ɫ����Ȼ��壨ȷ����һ֡�Ӹɾ��Ļ��忪ʼ��Ⱦ����
- ``void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const``;
  - ʹ�ø��� VA/IB/Shader�����������ơ�	ͨ�õ���VertexArray, IndexBuffer��Shader����Ⱦ����������ΪͼԪ����Ⱦ�������ú��������BindAll�Զ���VAO, IBO��Shader.
- ``void ClearColor();``
  - ����������ɫ���ڲ�ͨ������ glClearColor����
- ``const Renderer& SetPolygonMode(bool mode) const;``
  - �л��߿�/���ģʽ��true=�߿�false=��䣩��
- ``const Renderer& SetDepthTest(bool enable) const;``
  - ����/�ر���Ȳ��ԡ�

���г�Ա��״̬���أ������ⲿ��ѯ/��ǣ���
- mutable bool UsePolygonMode = false;
- mutable bool UseDepthTest = false;

## ʹ��ʾ��
- ������Ⱦѭ�����붥��/����/��ɫ����ϣ���
 ```cpp
 Renderer renderer;
 renderer.SetPolygonMode(true).SetDepthTest(true); //��ʽ����
 ```