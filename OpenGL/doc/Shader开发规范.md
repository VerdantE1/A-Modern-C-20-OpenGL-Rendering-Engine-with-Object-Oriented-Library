# Shader�����淶��C++��Ŀ���䣩

## 1. ��������

- Shader����ɫ������������ GPU �ϵĳ�������ʵ�ֶ��㴦��ƬԪ�����ͼ����Ⱦ���̡�
- �ڱ���Ŀ�У�Shader ��Դ�ฺ����ء������͹��� Shader �ļ������ڹ���ʱ�Զ����� Shader Դ�룬���벢����Ϊ OpenGL �������ͬʱ�ڴ�����ͬʱ������䵽�������С�
```cpp
	std::shared_ptr<Shader> shader = std::make_shared<Shader>("res/shaders/Basic.shader");
	//����ʱ����,��������ͬʱ����󶨵���ǰ������
```

## 2. ȫ�ֱ�������Լ��

- ���� Shader ��ȫ�ֱ�����Uniform���������ͳһǰ׺ `u_`��������������ƺ���ţ����ж��ͬ���������
- ʾ����`u_Texture1`, `u_Texture2`, `u_Color`, `u_ModelMatrix`��
- �������� C++ ��ͨ�� `SetUniform*` �ӿڽ��б����󶨺͸�ֵ����֤��Դ�� Shader ����һһ��Ӧ��

## 3. C++��Shader������

- C++ ��ͨ�� `Shader::SetUniform*` �������� Shader ����ֵ������������ Shader �ļ��е� Uniform ������ȫһ�¡�
- ���磬Square ͼ�������� `shader->SetUniform1i("u_Texture1", texture->GetAssignedSlot());`����Ӧ Shader �ļ��е� `uniform sampler2D u_Texture1;`��


| C++����         | Shader����         | ����ʾ��           |
|-----------------|-------------------|--------------------|
| int             | uniform int       | u_Index            |
| float           | uniform float     | u_Alpha            |
| glm::vec3       | uniform vec3      | u_LightPos         |
| glm::mat4       | uniform mat4      | u_ModelMatrix      |
| Texture����      | uniform sampler2D | u_Texture1, u_Texture2 |

## 4. ����Դ����

- ���ж��ͬ����Դ������������������������ţ�`u_Texture1`, `u_Texture2`��C++��ͨ��ѭ�����ΰ󶨡�
- ʾ����
```cpp
 for (size_t i = 0; i < textures.size(); ++i) { shader->SetUniform1i("u_Texture" + std::to_string(i + 1), textures[i]->GetAssignedSlot()); }
```

��Ӧ Shader �ļ���
```glsl
uniform sampler2D u_Texture1;
uniform sampler2D u_Texture2;
```

## 5. �任��������

- �任��ر�������ͳһ����Ϊ `u_ModelMatrix`, `u_ViewMatrix`, `u_ProjectionMatrix`������ C++ �˴��ݱ任����

## 6. ��������

- ���� Shader Uniform ����Ӧ����ȷ��;��ע�ͣ����� C++ �˿���������ά����
- ��ֹ�� Shader ��ʹ��δ�� C++ �˰󶨵� Uniform����������ʱ��������
- �Ƽ��� Shader ���������淶д���Ŷӿ����ĵ�������һ���ԡ�
- ���鶥���pos��������3ά��������ʽ����(for c++)��
---

