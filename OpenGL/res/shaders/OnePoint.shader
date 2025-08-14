#shader vertex 
#version 330 

void main()
{
	gl_Position = vec4 (0.0,0.0,0.0,1.0);
}


#shader fragment
#version 330 

out vec4 color;
void main()
{
	// Set the color of the point
	if(gl_FragCoord.x < 295) color = vec4(1.0,0.0,0.0,1.0) ; // Red color
	else color = vec4(1.0, 0.0, 1.0, 1.0);
}