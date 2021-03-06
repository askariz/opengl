# OpenGL 学习

## 开发环境搭建
 
 系统：macOS 10.13.6
 
 IDE：clion 2018.2.6
 
 工具： cmake 3.10.2
 
### OpenGL 简介

 [opengl官网](https://www.opengl.org/) 
 
 OpenGL 中文译为"开发式图形库"号称 The Industry's Foundation for High Performance Graphics，即高性能图形绘制的业界基石，是最广泛
 被采用的图形应用标准。
 
 官方提供了3个比较典型版本的参考手册，分别是OpenGL 2.1 OpenGL 3.3和OpenGL 4 
 
 [参考教程1](https://learnopengl.com/)  
 
 [参考教程github](https://github.com/JoeyDeVries/LearnOpenGL)
 
 [参考教程2](https://learnopengl-cn.github.io/)
 
 一般说OpenGL被认为是一个API，但其实其本身并不是一个API而是由Khronos组织制定并维护的一套规范
 
 本教程关注点在Modern OpenGL 也就是3.2版本以上，现在互联网上有大量的文档和资源在讨论OpenGL的的立即渲染模式（Immediate Mode）也就是旧的
 OpenGL，这个模式下绘图会很方便，但大多数功能被库隐藏起来了，开发者很少控制OpenGL进行自由的运算，所以开发者迫切希望更多的灵活性，随着时间的
 推移，OpenGL规范越来越灵活，开发者也能对绘图的细节更多的掌握，所以从3.2开始，OpenGL规范开始废除立即渲染模式，鼓励开发者在核心模式（core mode）
 下开发。
 
 #### 状态机
 OpenGL 自身是一个大的状态机，一系列的变量描述OpenGL此时该如何运行，其状态成为OpenGL的上下文（context）,当要告诉OpenGL要画线段而不是三角形的时候
 就可以通过改变上下文变量来改变OpenGL的状态
 
 #### 对象
 OpenGL 的对象是指一些选项的集合，代表OpenGL状态的一个子集，可以把对象看成一个C风格的结构体
 
 工作流：
 - 创建对象，用一个id保存其引用  glGenObject(1,&objectID)
 - 将对象绑定到上下文的目标位置  glBingObject(GL_WINDOW_TARGET, objectID)
 - 接着设置对象中的选项         glSetObjectOption(GL_WINDOW_TARGET, GL_OPTION_WINDOW_WIDTH, 800)
 - 重新绑定目标位置为默认0的时候，选项就会生效 glBingObject(GL_WINDOW_TARGET, 0)
 
 ### 创建窗体
 在使用OpenGL之前，需要创建一个显示的窗口和OpenGL上下文(context),这两个在不同的操作系统下都是不一样的，OpenGL有目的的将这些操作剥离，这样就
 要求我们自己来完成这部分工作，幸运的是，有几个比较流行的库已经帮我们完成了这部分工作
 * GLFW 专门针对OpenGL的C语言库 (http://www.glfw.org/download.html) 只需要其生成的库和头文件即可
 * FreeGLUT
 * GLAD 由于OpenGL只是一个规范，具体的实现是由驱动开发商针对具体的显卡实现的，由于其驱动实在是太多了，大多数函数的位置无法再编译时确定下来，需要在运行时候
   查询，所以开发者需要在运行时获取函数的地址并保存在一个函数指针中使用，GLAD就是来帮助我们查找函数地址的工具，其使用一个[在线服务](http://glad.dav1d.de/)
         

首先需要初始glfwInit()，其次在glfw我们要使用的OpenGL版本号与渲染模式，可以通过glfwWindowHint()暗示函数来告诉glfw
````
glfwInit()
glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR 3);
glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR_3);
glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

// 创建窗体
GLFWwindow *window = glCreateWindow(800,600,"LearnOpenGL",flase);
 ````
 
 #### glViewport 
 在开始渲染之前，需要告诉OpenGL要渲染window窗口大小，这里可以使用glViewport(0,0,800,600)函数,前两个参数是屏幕坐标左下角的坐标，后面两个参数代表窗口的宽和高
 这样在OpenGL坐标中，就可以将比如(-0.5 0.5)转为屏幕坐标(200,450)了.
 Note:这里需要注意,通常屏幕坐标在左下角是(0,0)，但是当我们在表示放置窗口的位置的时候,左上角一般为(0,0)
 
 
 ### 使用Cmake 创建一个最基本的OpenGL程序
 ````
 依赖安装 
 linux : $ sudo apt-get install libglm-dev libglfw-dev 
 mac: $ brew install glm glfw
 ````
 * GLFW3  一般在/usr/lib/x86_64-linux-gnu/libglfw.so.3
 * GLM OpenGL数学头文件库,只由头文件组成,一般位于/usr/include下
 
 使用cmake的find_package()函数 QUIET找不到包的时候继续执行 REQUIRED找不到就不继续往下执行,并报错.
 cmake 首先会在${CMAKE_MODULE_PATH}中查找.cmake文件,再ubuntu中/usr/share/cmake-3.5/Modules中提供了很多.cmake的文件来供我们使用
 如果没有则需要需要我们自己写.cmake文件,然后Include该文件后再执行find_package()
 
 FIND_PATH(VAR xx.h search_path) 
 FIND_LIBRARY(VAR xx.so search_path)
 
 
 ### GLSL 着色器语言shader
 着色器语言是独立的GPU小程序,语言风格和C类似
 
 顶点着色器
 ````
 
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 ourColor;
out vec2 TexCoord;

void main()
{
    gl_Position = vec4(aPos, 1.0);
    ourColor = aColor;
    TexCoord = aTexCoord;
}
 ````
 片段着色器
 ````
 #version 330 core
 out vec4 FragColor;
   
 in vec3 ourColor;
 in vec2 TexCoord;
 
 uniform sampler2D ourTexture;
 
 void main()
 {
     FragColor = texture(ourTexture, TexCoord);
 }
 ````
 * attribute: 通过layout (location = 0) 来将CPU数据传到到GPU,每次绘制的时候都需要传递该属性
 * uniform：也用于CPU将数据传递到GPU,与attribute稍微不同的是,uniform是全局的,只要设置一次就会一直保持
 
 ### 纹理 texture
 每一个顶点都要有同一个对应的纹理坐标,纹理坐标如下![image](resources/images/tex_coords.png)
 左下角(0,0),右上角(1,1),纹理的填充形式(wrapper)有几种:
 * GL_REPEAT 默认的纹理填充形式
 * GL_MIRRORED_REPEAT 镜像重复填充
 * GL_CLAMP_TO_EDGE 这个不是很能理解
 * GL_CLAMP_TO_BOARDER 这种对应就是显示框比较大,纹理比较小的情况,多余的地方直接填充用户制定和的颜色
 
 #### 纹理滤波 filter 
 用来告诉OpenGL纹理的颜色有两种：
 * GL_NEAREST 纹理坐标所在的颜色
 * GL_LINEAR 纹理坐标周围的颜色的插值
 
 #### Mipmaps
 根据到viewer之间的距离来,远端的贴图是近端的二分之一,这样不断的重复下去
 
 #### 创建纹理
 ````
 1. glGenTextures(1,&textureID) 生成纹理对象object
 2. glBindTexture(GL_TEXTURE_2D, textureID) 绑定纹理对象到OpenGL纹理的上下文(context 状态机)
 3. glTexImage2D() 根据图像数据生成上下文
 4. glGenerateMipmap(GL_TEXTURE_2D) 生成mipmap对象
 5. 生成完成后就可以开始绘制了，注意绘制完成后要删除glDeleteTexture(1,textureID)来释放内存
 6. 使用着色器绘制纹理,片段fragment shader是如何回去上面创建的纹理对象的,OpenGL提供了一个内置的方法叫sampler2D
    并使用了texture方法来确定纹理的颜色
 7. 如何叠加多层纹理texture units,默认激活的纹理层为0
 
片段找色器
#version 330 core
...

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
}

绘制
glActiveTexture(GL_TEXTURE0);
glBindTexture(GL_TEXTURE_2D, texture1);
glActiveTexture(GL_TEXTURE1);
glBindTexture(GL_TEXTURE_2D, texture2);

glBindVertexArray(VAO);
glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); 

 ````
 
 ### 变化 Transformation 
 
 - 标量向量 scalar vector 加减乘除
 - 向量点积v¯⋅k¯=||v¯||⋅||k¯||⋅cosθ
 - 向量叉积
 
 [参考地址](https://learnopengl.com/Getting-started/Transformations)
 
 ### 坐标系统
 OpenGL 希望每个顶点都是可见都在(-1,1)之间,在次之外都是不可见的,通常对象的顶点坐标都是经过多次变换之后才到屏幕的2D坐标
 - local space 也叫对象坐标
 - world space 世界坐标
 - view space  视图坐标
 - clip space 
 - screen space 屏幕坐标
 
 ![坐标](resources/images/coordinate_systems.png)
 
 其中有几个比较重要的转换矩阵
 - model matrix 
 - view matrix  
 - projection matrix (view space -> clip space即将坐标归一到-1,1,该变换决定试图中哪些部分是可见的哪些市不可见的)
 
 ### 如何管理一个gui 
 - widget
 - layout 主要用于管理组内所有成员的位置和大小.所以再Layout中需要做setPosition,setSize等函数
 - theme