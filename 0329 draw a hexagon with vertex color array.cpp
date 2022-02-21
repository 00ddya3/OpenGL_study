#include <GL/glew.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

const static char* vsSource = "#version 120 \n\
attribute vec4 vertex; \n\
attribute vec4 acolor; \n\
varying vec4 fcolor; \n\
void main(void) { \n\
	gl_Position = vertex; \n\
	fcolor = acolor; \n\
}";

const static char* fsSource = "#version 120 \n\
varying vec4 fcolor; \n\
void main(void) { \n\
	gl_FragColor = fcolor; \n\
}";

GLuint vs = 0;
GLuint fs = 0;
GLuint prog = 0;

char buf[1024];

void myinit(void) {
	GLint status;
	printf("***2018115542 ¼öÇÐ°ú ±è¹ÎÁ¤***\n");

	vs = glCreateShader(GL_VERTEX_SHADER); // vs: vertex shader
	glShaderSource(vs, 1, &vsSource, NULL);
	glCompileShader(vs); // compile to get .OBJ
	glGetShaderiv(vs, GL_COMPILE_STATUS, &status);
	printf("vs compile status = %s\n", (status == GL_TRUE) ? "true" : "false");
	glGetShaderInfoLog(vs, sizeof(buf), NULL, buf);
	printf("vs log = [%s]\n", buf);

	fs = glCreateShader(GL_FRAGMENT_SHADER); // fs: fragment shader
	glShaderSource(fs, 1, &fsSource, NULL);
	glCompileShader(fs); // compile to get .OBJ
	glGetShaderiv(fs, GL_COMPILE_STATUS, &status);
	printf("fs compile status = %s\n", (status == GL_TRUE) ? "true" : "false");
	glGetShaderInfoLog(fs, sizeof(buf), NULL, buf);
	printf("fs log = [%s]\n", buf);

	prog = glCreateProgram(); // prog: program
	glAttachShader(prog, vs);
	glAttachShader(prog, fs);
	glLinkProgram(prog); // link to get .EXE
	glGetProgramiv(prog, GL_LINK_STATUS, &status);
	printf("program link status = %s\n", (status == GL_TRUE) ? "true" : "false");
	glGetProgramInfoLog(prog, sizeof(buf), NULL, buf);
	printf("link log = [%s]\n", buf);
	glValidateProgram(prog);
	glGetProgramiv(prog, GL_VALIDATE_STATUS, &status);
	printf("program validate status = %s\n", (status == GL_TRUE) ? "true" : "false");
	glGetProgramInfoLog(prog, sizeof(buf), NULL, buf);
	printf("validate log = [%s]\n", buf);
	glUseProgram(prog); // execute it !
}

void mykeyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 27: // ESCAPE
		exit(0);
		break;
	}
}

GLfloat vertices[] = { 0.0, 0.8, 0.0, 1.0,
						0.7, 0.4, 0.0, 1.0,
						0.7, -0.4, 0.0, 1.0,
						0.0, -0.8, 0.0, 1.0,
						-0.7, -0.4, 0.0, 1.0,
						-0.7, 0.4, 0.0, 1.0};

GLfloat colors[] = { 1.0, 0.0, 0.0, 1.0,
					0.0, 1.0, 0.0, 1.0,
					0.0, 0.0, 1.0, 1.0,
					1.0, 1.0, 0.0, 1.0,
					0.0, 1.0, 1.0, 1.0,
					1.0, 0.0, 1.0, 1.0};

void mydisplay(void) {
	GLuint loc;
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	
	loc = glGetAttribLocation(prog, "vertex"); // provide the vertex attributes
	glEnableVertexAttribArray(loc);
	glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE, 0, vertices);
	
	loc = glGetAttribLocation(prog, "acolor");  // provide the color attributes
	glEnableVertexAttribArray(loc);
	glVertexAttribPointer(loc, 4, GL_FLOAT,	GL_FALSE, 0, colors);

	glDrawArrays(GL_POLYGON, 0, 6); // draw a polygon
	glFlush(); // Flush all 
	glutSwapBuffers();  //Áö¿ì¸é ¾ÈµÊ
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);  //Áö¿ì¸é ¾ÈµÊ
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);

	// replace ¡°simple¡± by your student number and name
	glutCreateWindow("2018115542_±è¹ÎÁ¤");

	glutDisplayFunc(mydisplay);
	glutKeyboardFunc(mykeyboard);
	glewInit();
	myinit();
	glutMainLoop();
	return 0;
}