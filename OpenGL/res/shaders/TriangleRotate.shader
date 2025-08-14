#shader vertex
#version 330 core

uniform mat4 transform;
void main()
{

	if(gl_VertexID == 0)
	{
		gl_Position = vec4(0.25, -0.25, 0.0, 1.0); // Set the position of the first vertex
	}
	else if(gl_VertexID == 1)
	{
		gl_Position = vec4(-0.25, -0.25, 0.0, 1.0); // Set the position of the second vertex
	}
	else if(gl_VertexID == 2)
	{
		gl_Position = vec4(0.25, 0.25, 0.0, 1.0); // Set the position of the third vertex
	}	
	gl_Position = transform * gl_Position;

}


#shader fragment
#version 330 core
out vec4 color;
void main()
{
	if(gl_FragCoord.x < 300)
	{
		color = vec4(1.0, 0.0, 0.0, 1.0); // Set the color of the first vertex to red
	}
	else color = vec4(0.0, 1.0, 1.0, 1.0); // Set the color of the other vertices to green

}