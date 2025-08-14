# Shaper ʹ��˵��

## 1. ��������

`Shaper` ������ͼ����״��ĳ�����࣬ͳһ������Ⱦ��Դ���� Shader��Texture���ͱ任�ӿڡ����о�����״���� Square��Rectangle��Circle��Cube �ȣ���Ӧ�̳��� `Shaper`��

---

## 2. ��Դ���������

- ��״�಻ֱ�Ӵ��� Shader �� Texture������**���ⲿ����**��ͨ�����캯���� `SetShader`/`AddTexture` ��������ʵ����Դ����͸��á�
- �Ƽ�ʹ������ָ�루�� `std::shared_ptr`������ Shader �� Texture�������ڴ�й©���ظ��ͷš�

---

## 3. �任�ӿ�

- ������״��Ĭ�����ɵ�λ�����壨�絥λ�����Ρ���λ���εȣ���
- �������š�ƽ�ơ���ת�ȱ任����ͨ�� `SetTransform(const glm::mat4&)` �ӿ����ñ任����
- �任��������Ϊ `glm::mat4`��Ĭ�ϳ�ʼ��Ϊ��λ����

---

## 4. ��Ⱦ�ӿ� Draw

- ������״����ʵ�� `Draw(Renderer& renderer)` ������ͳһ��Ⱦ���̡�
- ��Ⱦʱ���Զ��� Shader��Texture ��Դ�������� Renderer �� `Draw` ������
- ����OpenGL�Ĺ涨,�ڰ�Texture֮ǰ�������Ȱ�Shader��
```cpp
	oid Shaper::Draw(Renderer& renderer) {
	if (shader) {
		shader->Bind();
		for (const auto& texture : textures) {
			texture->Bind();
		}
		renderer.Draw(*this);
	}
}
```

---

## 5. ��չ�淶

- ������״��ʱ����̳��� `Shaper`������ѭ��Դ���ݺͱ任�ӿڹ淶��

---

## 6. ʾ������
