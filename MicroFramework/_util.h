// estudar renderbuffers, muito mais rapidos
struct ofFbo {
public:
	GLuint fbo;
	unsigned int texture;
	unsigned int width, height;
	
	float vertices[24] = {
	//   positions     texture coordinates
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f,  1.0f, 1.0f
	};
	
	ofFbo() { }
	
	void allocate(int w=800, int h=600) {
		glGenFramebuffers(1, &fbo);
//		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		width = w;
		height = h;
		glGenTextures(1, &texture);
		// create texture
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// attach to framebuffer
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

	}
	~ofFbo() {
		glDeleteFramebuffers(1, &fbo);
	}
	void begin() {
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		glViewport(0,0,width, height);
	}
	void end() {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	
	void draw() {
		glDrawBuffer(GL_COLOR_ATTACHMENT0);
//		glDrawBuffer(GL_TEXTURE_2D);
		glViewport(0,0,width, height);
		
		
		glBindTexture(GL_TEXTURE_2D, texture); // color attachment texture
//		glBindBuffer(GL_ARRAY_BUFFER, VBO); // VBO of the quad
		// You can also use VAO or attribute pointers instead of only VBO...
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
};
