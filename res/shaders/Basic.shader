#version 330 core
layout(location = 0) in vec2 position;
void main()
{
 gl_Position = position;\n
};

#version 330 core\n
layout(location = 0) out vec4 color;
void main()
{
 color = vec4(1.0,0.0,0.0,1.0);\n
};
