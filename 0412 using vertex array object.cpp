#include <GL/glew.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

//»ï°¢Çü source
const char* vsSource = "#version 120 \n\
in vec4 aPosition; \n\
in vec4 aColor; \n\
out vec4 vColor; \n\
void main(void) { \n\
 gl_Position = aPosition; \n\
 vColor = aColor; \n\
}";

const char* fsSource = "#version 120 \n\
in vec4 vColor; \n\
void main(void) { \n\
 gl_FragColor = vColor; \n\
}";

//»ç°¢Çü source
const char* vsSource2 = "#version 120 \n\
in vec4 aPosition; \n\
in vec4 aColor; \n\
out vec4 vColor; \n\
void main(void) { \n\
 gl_Position = aPosition; \n\
 vColor = aColor; \n\
}";

const char* fsSource2 = "#version 120 \n\
in vec4 vColor; \n\
void main(void) { \n\
 gl_FragColor = vColor; \n\
}";

//¿À°¢Çü source
const char* vsSource3 = "#version 120 \n\
in vec4 aPosition; \n\
in vec4 aColor; \n\
out vec4 vColor; \n\
void main(void) { \n\
 gl_Position = aPosition; \n\
 vColor = aColor; \n\
}";

const char* fsSource3 = "#version 120 \n\
in vec4 vColor; \n\
void main(void) { \n\
 gl_FragColor = vColor; \n\
}";

GLint vs[3] = {0, 0, 0};
GLint fs[3] = {0, 0, 0};
GLint prog[3] = {0, 0, 0};

char buf[1024];
GLuint vbo[3], vao[3];


//»ï°¢Çü ÁÂÇ¥&»ö
GLfloat vertices[] = {
-0.8, 0.8, 0.0, 1.0,
-0.5, 0.8, 0.0, 1.0,
-0.8, 0.3, 0.0, 1.0,
};
GLfloat colors[] = {
1.0, 0.0, 0.0, 1.0, // red
0.0, 1.0, 0.0, 1.0, // green
0.0, 0.0, 1.0, 1.0, // blue
};

//»ç°¢Çü ÁÂÇ¥&»ö
GLfloat vertices2[] = {
0.6, 0.2, 0.0, 1.0,
0.9, 0.2, 0.0, 1.0,
0.9, 0.5, 0.0, 1.0,
0.6, 0.5, 0.0, 1.0
};
GLfloat colors2[] = {
1.0, 0.0, 0.0, 1.0, // red
0.0, 1.0, 0.0, 1.0, // green
0.0, 0.0, 1.0, 1.0, // blue
1.0, 1.0, 0.0, 1.0  // yellow
};

//¿À°¢Çü ÁÂÇ¥&»ö
GLfloat vertices3[] = {
-0.2, -0.2, 0.0, 1.0,
0.0, 0.0, 0.0, 1.0,
0.2, -0.2, 0.0, 1.0,
0.1, -0.4, 0.0, 1.0,
-0.1, -0.4, 0.0, 1.0
};
GLfloat colors3[] = {
1.0, 0.0, 0.0, 1.0, // red
0.0, 1.0, 0.0, 1.0, // green
0.0, 0.0, 1.0, 1.0, // blue
0.0, 1.0, 1.0, 1.0, // aquamarin
1.0, 0.0, 1.0, 1.0  // purple
};

void myinit(void) {
	GLint status;
	printf("***** 2018115542_±è¹ÎÁ¤ *****\n");

	for (int i = 0; i < 3; i++) {
		vs[i] = glCreateShader(GL_VERTEX_SHADER);
		if (i == 0)
			glShaderSource(vs[i], 1, &vsSource, NULL);
		else if (i == 1)
			glShaderSource(vs[i], 1, &vsSource2, NULL);
		else
			glShaderSource(vs[i], 1, &vsSource3, NULL);

	
		glCompileShader(vs[i]);
		glGetShaderiv(vs[i], GL_COMPILE_STATUS, &status);
		printf("vs compile status = %s\n", (status == GL_TRUE) ? "true" : "false");
		glGetShaderInfoLog(vs[i], sizeof(buf), NULL, buf);
		printf("vs log = [%s]\n", buf);

		fs[i] = glCreateShader(GL_FRAGMENT_SHADER);
		if (i == 0)
			glShaderSource(fs[i], 1, &fsSource, NULL);
		else if (i == 1)
			glShaderSource(fs[i], 1, &fsSource2, NULL);
		else
			glShaderSource(fs[i], 1, &fsSource3, NULL);
		glCompileShader(fs[i]);
		glGetShaderiv(fs[i], GL_COMPILE_STATUS, &status);
		printf("fs compile status = %s\n", (status == GL_TRUE) ? "true" : "false");
		glGetShaderInfoLog(fs[i], sizeof(buf), NULL, buf);
		printf("fs log = [%s]\n", buf);

		prog[i] = glCreateProgram();
		glAttachShader(prog[i], vs[i]);
		glAttachShader(prog[i], fs[i]);
		glLinkProgram(prog[i]);
		glGetProgramiv(prog[i], GL_LINK_STATUS, &status);
		printf("program link status = %s\n", (status == GL_TRUE) ? "true" :	"false");
		glGetProgramInfoLog(prog[i], sizeof(buf), NULL, buf);
		printf("link log = [%s]\n", buf);
		glValidateProgram(prog[i]);
		glGetProgramiv(prog[i], GL_VALIDATE_STATUS, &status);
		printf("program validate status = %s\n", (status == GL_TRUE) ? "true" :	"false");
		glGetProgramInfoLog(prog[i], sizeof(buf), NULL, buf);
		printf("validate log = [%s]\n", buf);
		glUseProgram(prog[i]);
		printf("\n");
	}

	glGenVertexArrays(3, vao);
	glBindVertexArray(vao[0]);

	glGenBuffers(3, vbo); 

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, 2 * 3 * 4 * sizeof(GLfloat), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, 3 * 4 * sizeof(GLfloat), vertices);
	glBufferSubData(GL_ARRAY_BUFFER, 3 * 4 * sizeof(GLfloat), 3 * 4 * sizeof(GLfloat), colors);
	
	GLuint loc;
	loc = glGetAttribLocation(prog[0], "aPosition");
	glEnableVertexAttribArray(loc);
	glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	loc = glGetAttribLocation(prog[0], "aColor");
	glEnableVertexAttribArray(loc);
	glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(3 * 4 * sizeof(GLfloat)));
	
	glBindVertexArray(vao[1]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, 2 * 4 * 4 * sizeof(GLfloat), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, 4 * 4 * sizeof(GLfloat), vertices2);
	glBufferSubData(GL_ARRAY_BUFFER, 4 * 4 * sizeof(GLfloat), 4 * 4 * sizeof (GLfloat),	colors2);
	
	loc = glGetAttribLocation(prog[1], "aPosition");
	glEnableVertexAttribArray(loc);
	glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	loc = glGetAttribLocation(prog[1], "aColor");
	glEnableVertexAttribArray(loc);
	glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(4 * 4 * sizeof(GLfloat)));

	glBindVertexArray(vao[2]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	glBufferData(GL_ARRAY_BUFFER, 2 * 5 * 4 * sizeof(GLfloat), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, 5 * 4 * sizeof(GLfloat), vertices3);
	glBufferSubData(GL_ARRAY_BUFFER, 5 * 4 * sizeof(GLfloat), 5 * 4 * sizeof(GLfloat), colors3);

	loc = glGetAttribLocation(prog[2], "aPosition");
	glEnableVertexAttribArray(loc);
	glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	loc = glGetAttribLocation(prog[2], "aColor");
	glEnableVertexAttribArray(loc);
	glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(5 * 4 * sizeof(GLfloat)));
}

void mykeyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 27: // ESCAPE
		exit(0);
		break;
	}
}

void mydisplay(void) {
	GLint loc;
	glClearColor(0.7f, 0.7f, 0.7f, 1.0f); // gray
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(prog[0]);
	loc = glGetAttribLocation(prog[0], "aPosition");
	glBindVertexArray(vao[0]);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glUseProgram(prog[1]);
	loc = glGetAttribLocation(prog[1], "aPosition");
	glBindVertexArray(vao[1]);
	glDrawArrays(GL_QUADS, 0, 4);

	glUseProgram(prog[2]);
	loc = glGetAttribLocation(prog[2], "aPosition");
	glBindVertexArray(vao[2]);
	glDrawArrays(GL_POLYGON, 0, 5);
	
	glFlush();
	glutSwapBuffers();
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("2018115542_±è¹ÎÁ¤");
	glutDisplayFunc(mydisplay);
	glutKeyboardFunc(mykeyboard);
	glewInit();
	myinit();
	glutMainLoop();
	return 0;
}