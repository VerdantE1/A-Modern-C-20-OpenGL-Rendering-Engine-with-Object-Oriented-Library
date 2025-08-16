## Texture类使用文档（中英对照）

**简介**  
Texture类用于加载、管理和绑定2D纹理资源。它继承自Resource类，处理OpenGL纹理对象的生命周期和状态管理，包括自动分配纹理单元槽位。

**基本用法**
1. **创建纹理对象**
```
// 从文件路径加载纹理
Texture texture("res/textures/example.png");
```

2. **绑定和解绑纹理**
```
// 绑定纹理到其预分配的纹理单元
texture.Bind();

// 使用完成后解绑
texture.Unbind();
```

3. **获取纹理属性**
```
// 获取纹理宽度、高度和每像素字节数
int width = texture.GetWidth();
int height = texture.GetHeight();
int bpp = texture.GetBpp();  // Bits Per Pixel

// 获取分配的纹理单元槽位
unsigned int slot = texture.GetAssignedSlot();
```

4. **在着色器中使用**
```
// 绑定纹理
texture.Bind();

// 将纹理单元信息传递给着色器
shader.SetUniform1i("u_Texture", texture.GetAssignedSlot());

// 渲染使用该纹理的对象
renderer.Draw(...);

// 完成后解绑（可选）
texture.Unbind();
```

**实现细节**
- 纹理单元自动分配：系统会自动为每个Texture实例分配一个唯一的纹理单元槽位，从0开始递增
- 图像加载：使用stb_image库加载多种图像格式
- 纹理参数：默认使用线性过滤（GL_LINEAR）和边缘封装（GL_CLAMP_TO_EDGE）
- 像素格式：所有纹理默认转换为RGBA格式，每通道8位（GL_RGBA8）

**使用总结**  
Texture类封装了OpenGL纹理资源的完整生命周期，提供简单直观的接口用于加载和使用纹理。它自动处理纹理单元分配，简化了多纹理应用程序的开发。通过继承Resource类，它遵循了资源管理的一致模式，包括ID管理和绑定/解绑操作。
Texture类的纹理单元槽位由内部分配，用户无需手动指定。每当带参初始化一个Texture对象时，系统会自动分配一个可用的纹理单元槽位，并在对象销毁时释放该槽位。
每当带参初始化一个Texture对象时，系统自动加载指定路径的图像文件,并将其转换为OpenGL纹理格式。加载完成后，自动申请GPU，自动设置纹理参数，纹理会被绑定到分配的纹理单元槽位，以便在渲染过程中使用。
用户需要在着色器中使用纹理时，需要明确你所使用的纹理在OpenGL中的纹理单元槽位。可以通过`GetAssignedSlot()`方法获取当前纹理的分配槽位，并将其传递给着色器。
换句话说，使用Texture，你只需要知道纹理对象本身即创建一个纹理对象，接着Draw时记得绑定纹理(虽然初始化就有Bind了但确保，绑定的作用是激活槽位，并将该槽位绑定成m_id所指向单元)，然后用户需要知道你所用的材质所在纹理单元槽位并设置给着色器即可。

**注意事项**
- 纹理加载过程会自动垂直翻转图像，以匹配OpenGL纹理坐标系（左下角为原点）
- 默认情况下，图像会被加载为4通道RGBA格式，无论源图像格式如何
- 分配的纹理单元在Texture对象销毁时会被释放并返回池中
- Texture有一个全局静态变量`nextTextureUnit`，用于跟踪下一个可用的纹理单元槽位。
- Texture类在一个进程中按照创建顺序分配纹理单元槽位，不让用户指定纹理单元槽位，以避免冲突和错误。


