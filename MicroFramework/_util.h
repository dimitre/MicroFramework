// estudar renderbuffers, muito mais rapidos

struct fbod {
public:
	int const fbo_width = 512;
	int const fbo_height = 512;

	GLuint fb, color, depth;
	
	float const light_dir[4]={1,1,1,0};
	float const light_color[4]={1,0.95,0.9,1};

	void CHECK_FRAMEBUFFER_STATUS()
	{
		GLenum status;
		status = glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER);
		switch(status) {
		case GL_FRAMEBUFFER_COMPLETE:
			break;

		case GL_FRAMEBUFFER_UNSUPPORTED:
		/* choose different formats */
			break;

		default:
			/* programming error; will fail on all hardware */
			fputs("Framebuffer Error\n", stderr);
			exit(-1);
		}
	}
	
	void init()
	{
		glGenFramebuffers(1, &fb);
		glGenTextures(1, &color);
		glGenRenderbuffers(1, &depth);

		glBindFramebuffer(GL_FRAMEBUFFER, fb);

		glBindTexture(GL_TEXTURE_2D, color);
		glTexImage2D(   GL_TEXTURE_2D,
				0,
				GL_RGBA,
				fbo_width, fbo_height,
				0,
				GL_RGBA,
				GL_UNSIGNED_BYTE,
				NULL);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, color, 0);

		glBindRenderbuffer(GL_RENDERBUFFER, depth);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, fbo_width, fbo_height);
		glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depth);

		CHECK_FRAMEBUFFER_STATUS();
	}
	

	void prepare()
	{
//		static float a=0, b=0, c=0;

		glBindTexture(GL_TEXTURE_2D, 0);
		glEnable(GL_TEXTURE_2D);
		glBindFramebuffer(GL_FRAMEBUFFER, fb);

		glViewport(0,0, fbo_width, fbo_height);

//		glClearColor(1,1,1,0);
//		glClearColor(.3,.3,.3,0);
		glClearColor(0,0,0,1);
		
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45, 1, 1, 10);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

//		glEnable(GL_LIGHT0);
//		glEnable(GL_LIGHTING);

		glEnable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);

//		glLightfv(GL_LIGHT0, GL_POSITION, light_dir);
//		glLightfv(GL_LIGHT0, GL_DIFFUSE, light_color);
//
//		glTranslatef(0,0,-5);
//
//		glRotatef(a, 1, 0, 0);
//		glRotatef(b, 0, 1, 0);
//		glRotatef(c, 0, 0, 1);
//
//		glutSolidTeapot(0.75);
//
//		a=fmod(a+0.1, 360.);
//		b=fmod(b+0.5, 360.);
//		c=fmod(c+0.25, 360.);
	}
	
	void final()
	{
//		static float a=0, b=0, c=0;
		float b = 0;

		const int win_width  = glutGet(GLUT_WINDOW_WIDTH);
		const int win_height = glutGet(GLUT_WINDOW_HEIGHT);
		const float aspect = (float)win_width/(float)win_height;

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		glViewport(0,0, win_width, win_height);

//		glClearColor(1.,1.,1.,0.);
		glClearColor(0,0,0,0);
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45, aspect, 1, 10);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(0,0,-5);

		glRotatef(b, 0, 1, 0);

		b=fmod(b+0.5, 360.);

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, color);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);

//		glEnable(GL_BLEND);
//		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//
//		glDisable(GL_LIGHTING);

		float cube[][5]=
		{
			{-1, -1, -1,  0,  0},
			{ 1, -1, -1,  1,  0},
			{ 1,  1, -1,  1,  1},
			{-1,  1, -1,  0,  1},

			{-1, -1,  1, -1,  0},
			{ 1, -1,  1,  0,  0},
			{ 1,  1,  1,  0,  1},
			{-1,  1,  1, -1,  1},
		};
		unsigned int faces[]=
		{
			0, 1, 2, 3,
			1, 5, 6, 2,
			5, 4, 7, 6,
			4, 0, 3, 7,
			3, 2, 6, 7,
			4, 5, 1, 0
		};

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		glVertexPointer(3, GL_FLOAT, 5*sizeof(float), &cube[0][0]);
		glTexCoordPointer(2, GL_FLOAT, 5*sizeof(float), &cube[0][3]);

		glCullFace(GL_BACK);
		glDrawElements(GL_QUADS, 24, GL_UNSIGNED_INT, faces);

		glCullFace(GL_FRONT);
		glDrawElements(GL_QUADS, 24, GL_UNSIGNED_INT, faces);

		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	}
};

fbod test;

struct ofFbo {
public:
//	GLuint fbo;
	GLuint frameBuffer;
//	unsigned int texture;
	GLuint texColorBuffer;

	unsigned int width, height;
	
	GLuint vboQuad;
    GLuint vaoQuad;

	
	ofFbo() { }
	
	void allocate(int w=800, int h=600) {
//		glGenFramebuffers(1, &fbo);
		
		GLfloat quadVertices[] = {
			-1.0f,  1.0f,  0.0f, 1.0f,
			 1.0f,  1.0f,  1.0f, 1.0f,
			 1.0f, -1.0f,  1.0f, 0.0f,

			 1.0f, -1.0f,  1.0f, 0.0f,
			-1.0f, -1.0f,  0.0f, 0.0f,
			-1.0f,  1.0f,  0.0f, 1.0f
		};

		glBindBuffer(GL_ARRAY_BUFFER, vboQuad);
		glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
		
		
		glGenFramebuffers(1, &frameBuffer);

//		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		width = w;
		height = h;
		
		glGenTextures(1, &texColorBuffer);
		glBindTexture(GL_TEXTURE_2D, texColorBuffer);
//		glGenTextures(1, &texture);
		// create texture
//		glBindTexture(GL_TEXTURE_2D, texture);
//		glTexImage2D(
//			GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexImage2D(
			GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL
		);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// attach to framebuffer
		glFramebufferTexture2D(
			GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texColorBuffer, 0
		);
//		glFramebufferTexture2D(
//			GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

	}
	~ofFbo() {
//		glDeleteFramebuffers(1, &fbo);
		glDeleteFramebuffers(1, &frameBuffer);

	}
	void begin() {
		glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
//		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
//		glViewport(0,0,width, height);
	}
	void end() {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	
	void draw() {
		glDrawBuffer(GL_COLOR_ATTACHMENT0);
//		glDrawBuffer(GL_TEXTURE_2D);
		glViewport(0,0,width, height);
		
		
		glBindTexture(GL_TEXTURE_2D, texColorBuffer); // color attachment texture
//		glBindBuffer(GL_ARRAY_BUFFER, VBO); // VBO of the quad
		// You can also use VAO or attribute pointers instead of only VBO...
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		
		
		
		
//		glBindVertexArray(vaoQuad);
		glDisable(GL_DEPTH_TEST);
//		glUseProgram(screenShaderProgram);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texColorBuffer);

		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
};
