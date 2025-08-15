## Camera��ʹ���ĵ�������棩

** ����**
Camera�����ڹ�����ͼ����View����ͶӰ����Projection������������3D�����еĹ۲�λ�á��������Ұ��Χ��

** �����÷�**
1. * *����Camera���� * *
����λ�á�Ŀ�ꡢ�Ϸ�����Ұ�Ƕȡ���߱ȡ���ƽ�桢Զƽ�棺
```cpp
Camera camera(
    glm::vec3(0, 0, 10), // ���λ��
    glm::vec3(0, 0, 0),  // �۲�Ŀ��
    glm::vec3(0, 1, 0),  // �Ϸ���
    70.0f, aspect, 0.1f, 100.0f // ��Ұ����߱ȡ���ƽ�桢Զƽ��
);
```

2. * *��ȡ��ͼ��ͶӰ���� * *
��Ⱦʱ���ݸ���ɫ����
```cpp
shader.SetUniformMat4fv("view", camera.GetViewMatrix());
shader.SetUniformMat4fv("projection", camera.GetProjectionMatrix());
```

3. * *�볡�����ʾ�� * *
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

**������**
- Frustum�ࣺ���ڼ�����׶�壬�ṩ���߼���ͶӰ���ܡ���ʱ����DEBUG����ֹ��Ϊ�����������Ⱦ�쳣��

** �����ܽ�**
Camera����ǡ��������������������ʵ��Ӱ��һ�������ӽǺ�ͶӰ��ֻ�����ò�������Ⱦʱ�����ľ��󼴿�ʵ�����ɹ۲�ͳ����任��