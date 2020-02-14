// ler mais aqui
//https://learnopengl.com/Getting-started/Shaders
//https://learnopengl.com/Getting-started/Shaders

bool useShader = false;

std::string vertex_source = R"V0G0N(
varying vec2 texcoord0;
void main()
{
    gl_Position = ftransform();
    texcoord0 = vec2(gl_TextureMatrix[0] * gl_MultiTexCoord0);
}
)V0G0N";


std::string fragment_source = R"V0G0N(

uniform sampler2DRect tex0;
varying vec2 texcoord0;

void main (void)
{
	vec4 cor = texture2DRect(tex0, texcoord0);
//	gl_FragColor = vec4(1.0 - cor.r, 1.0, 1.0 - cor.b, 1.0);
	gl_FragColor = vec4(1.0 , 1.0, 0.0, 1.0);
}

	
)V0G0N";





bool check_shader_compile_status(GLuint obj) {
	GLint status;
	glGetShaderiv(obj, GL_COMPILE_STATUS, &status);
	if(status == GL_FALSE) {
		GLint length;
		glGetShaderiv(obj, GL_INFO_LOG_LENGTH, &length);
		char loga[length];
//		vector<char> loga(length);
		glGetShaderInfoLog(obj, length, &length, &loga[0]);
		cout << &loga[0];
		return false;
	}
	return true;
}

// helper to check and display for shader linker error
bool check_program_link_status(GLuint obj) {
	GLint status;
	glGetProgramiv(obj, GL_LINK_STATUS, &status);
	if(status == GL_FALSE) {
		GLint length;
		glGetProgramiv(obj, GL_INFO_LOG_LENGTH, &length);
		char loga[length];
//		vector<char> log(length);
		glGetProgramInfoLog(obj, length, &length, &loga[0]);
		cout << &loga[0];
		return false;
	}
	return true;
}



GLuint shader_program, vertex_shader, fragment_shader;

void setupShader() {
	cout << "shader lang: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;

	// key_pressed(key, x, y, win);

	// shader source code

	
		// "#version 330\n"
		// "in vec4 fcolor;\n"
		// "layout(location = 0) out vec4 FragColor;\n"
		// "void main() {\n"
		// "	FragColor = fcolor;\n"
		// "}\n";

//		"#version 120\n"
//		"uniform sampler2DRect tex0;
//		varying vec2 texcoord0;"
//		"vec4 cor = texture2DRect(tex0, texcoord0);"
//		"void main()\n"
//		"{\n"
//		"	 gl_FragColor = vec4(0.0, 0.0, 1.0, 1.0);\n"
//		"}\n";

	// we need these to properly pass the strings
	const char *source;
	int length;





	// create and compiler vertex shader
	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	source = vertex_source.c_str();
	length = vertex_source.size();
	glShaderSource(vertex_shader, 1, &source, &length);
	glCompileShader(vertex_shader);
	if(!check_shader_compile_status(vertex_shader)) {
		cout << "vertex shader failed to compile" << endl;
//		return 1;
	}

	// create and compiler fragment shader
	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	source = fragment_source.c_str();
	length = fragment_source.size();
	glShaderSource(fragment_shader, 1, &source, &length);
	glCompileShader(fragment_shader);
	if(!check_shader_compile_status(fragment_shader)) {
		cout << "fragment shader failed to compile" << endl;
//		return 1;
	}

	// create program
	shader_program = glCreateProgram();

	// attach shaders
	
//	glBindAttribLocation(shader_program, 1, "tex0");
	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);

	glBindAttribLocation(shader_program, 0, "InVertex");

//	if(bindTexCoord0)
		glBindAttribLocation(shader_program, 1, "InTexCoord0");

//	if(bindNormal)
		glBindAttribLocation(shader_program, 2, "InNormal");

//	if(bindColor)
		glBindAttribLocation(shader_program, 3, "InColor");
	
	
	// link the program and check for errors
	glLinkProgram(shader_program);
	if(!check_program_link_status(shader_program)) {
		cout << "program linking failed" << endl;
//		return 1;
	}
}


void beginShader() {
	//	cout << useShader << endl;
		if (useShader) {
			glUseProgram(shader_program);
	//		makeTex();
	//		readTex();
	//		glActiveTexture(GL_TEXTURE0);
	//		glBindTexture(GL_TEXTURE_2D, texName);
			
			GLuint textures[2];
			glGenTextures(2, textures);
			
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
			glGenTextures(1, &texName);
			glActiveTexture(GL_TEXTURE0 + 0);
			
			glReadBuffer(GL_FRONT);
			glReadPixels(0,0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, checkImage);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,  width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, checkImage);

			
			glBindTexture(GL_TEXTURE_2D, texName);
			
//			glBindTexture(GL_TEXTURE_2D, texName);
//			glBindTexture(GL_TEXTURE_2D, textures[0]);
//			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, checkImage);

			glUniform1i(glGetUniformLocation(shader_program, "tex0"), 0);


//			int location;
//			location = glGetUniformLocation(shader_program, "tex0");
//			glUniform1i(location, 0);
			
	//		mixmapUniformLocation = glGetUniformLocation(shader_program, "MixMap"); //get the uniform associated with "MixMap"
	//		glUniform1i(mixmapUniformLocation, 0); //set MixMap uniform to 0 (sampler 0);
		} else {
			glUseProgram(0);
		}
}
