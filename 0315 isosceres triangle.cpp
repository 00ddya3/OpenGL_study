#include <GL/glew.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

const static char* vsSource = "#version 120 \n\
attribute vec4 vertex; \n\
void main(void) { \n\
	gl_Position = vertex; \n\
}";

const static char* fsSource = "#version 120 \n\
void main(void) { \n\
	gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0); \n\
}";

GLuint vs = 0;
GLuint fs = 0;
GLuint prog = 0;

void myinit(void) {
	vs = glCreateShader(GL_VERTEX_SHADER); // vs: vertex shader
	glShaderSource(vs, 1, &vsSource, NULL);
	glCompileShader(vs); // compile to get .OBJ
	fs = glCreateShader(GL_FRAGMENT_SHADER); // fs: fragment shader
	glShaderSource(fs, 1, &fsSource, NULL);
	glCompileShader(fs); // compile to get .OBJ
	prog = glCreateProgram(); // prog: program

	glAttachShader(prog, vs);
	glAttachShader(prog, fs);
	glLinkProgram(prog); // link to get .EXE
	glUseProgram(prog); // execute it !
}

void mykeyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 27: // ESCAPE
		exit(0);
		break;
	}
}

GLfloat vertices[] = { -0.5, -0.5, 0.0, 1.0,
						+0.5, -0.5, 0.0, 1.0,
						-0.0, +1.0, 0.0, 1.0,
						-0.5, -0.5, 0.0, 1.0};

void mydisplay(void) {
	GLuint loc;
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	loc = glGetAttribLocation(prog, "vertex"); // provide the vertex attributes
	glEnableVertexAttribArray(loc);
	glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE, 0, vertices);
	glDrawArrays(GL_LINES, 0, 3); // draw a line
	glDrawArrays(GL_LINES, 1, 3); // draw a line
	glDrawArrays(GL_LINES, 2, 3); // draw a line
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