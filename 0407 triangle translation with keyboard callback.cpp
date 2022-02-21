#include <GL/glew.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

const char* vsSource = "#version 120 \n\
in vec4 aPosition; \n\
in vec4 aColor; \n\
out vec4 vColor; \n\
uniform float udist; \n\
uniform float vdist; \n\
void main(void) { \n\
 gl_Position.x = aPosition.x + udist;\n\
 gl_Position.y = aPosition.y + vdist;\n\
 gl_Position.zw = aPosition.zw; \n\
 vColor = aColor; \n\
}";

const char* fsSource = "#version 120 \n\
in vec4 vColor; \n\
void main(void) { \n\
 gl_FragColor = vColor; \n\
}";

GLint vs = 0;
GLint fs = 0;
GLint prog = 0;

char buf[1024];
float dist = 0.0f;
float distt = 0.0f;

void myinit(void) {
	GLint status;
	printf("***** 2018115542_±è¹ÎÁ¤ *****\n");

	vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vsSource, NULL);
	glCompileShader(vs);
	glGetShaderiv(vs, GL_COMPILE_STATUS, &status);
	printf("vs compile status = %s\n", (status == GL_TRUE) ? "true" :
		"false");
	glGetShaderInfoLog(vs, sizeof(buf), NULL, buf);
	printf("vs log = [%s]\n", buf);

	fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fsSource, NULL);
	glCompileShader(fs);
	glGetShaderiv(fs, GL_COMPILE_STATUS, &status);
	printf("fs compile status = %s\n", (status == GL_TRUE) ? "true" :
		"false");
	glGetShaderInfoLog(fs, sizeof(buf), NULL, buf);
	printf("fs log = [%s]\n", buf);
	
	prog = glCreateProgram();
	glAttachShader(prog, vs);
	glAttachShader(prog, fs);
	glLinkProgram(prog);
	glGetProgramiv(prog, GL_LINK_STATUS, &status);
	printf("program link status = %s\n", (status == GL_TRUE) ? "true" :
		"false");
	glGetProgramInfoLog(prog, sizeof(buf), NULL, buf);
	printf("link log = [%s]\n", buf);
	glValidateProgram(prog);
	glGetProgramiv(prog, GL_VALIDATE_STATUS, &status);
	printf("program validate status = %s\n", (status == GL_TRUE) ? "true" :
		"false");
	glGetProgramInfoLog(prog, sizeof(buf), NULL, buf);
	printf("validate log = [%s]\n", buf);
	glUseProgram(prog);

	printf("\n");
}

int mode = 0;
void mykeyboard(unsigned char key, int x, int y) {
	
	do {
		switch (key) {
		case 'w':
			printf("w\n");
			dist = 0.0f;
			mode = 1;
			break;
		case 's':
			printf("s\n");
			distt = 0.0f;
			mode = 2;
			break;
		case 'a':
			printf("a\n");
			distt = 0.0f;
			mode = 3;
			break;
		case 'd':
			printf("d\n");
			dist = 0.0f;
			mode = 4;
			break;
		case 'i':
			printf("i");
			mode = 0;
			break;
		case 27: // ESCAPE
			exit(0);
			break;
		} 
	} while (key == 27);
}

GLfloat vertices[] = {
0.0, 0.0, 0.0, 1.0,
0.3, 0.0, 0.0, 1.0,
0.0, 0.3, 0.0, 1.0,
};

GLfloat colors[] = {
1.0, 0.0, 0.0, 1.0, // red
0.0, 1.0, 0.0, 1.0, // green
0.0, 0.0, 1.0, 1.0, // blue
};

void myidle(void) {
	dist += 0.0001f;
	if (dist > 1.5)
		dist = 0.0f;
	// redisplay 

	distt -= 0.0001f;
	if (distt < -1.5)
		distt = 0.0f;
	// redisplay 

	glutPostRedisplay();
}

void mydisplay(void) {
	GLint loc;
	glClearColor(0.7f, 0.7f, 0.7f, 1.0f); // gray
	glClear(GL_COLOR_BUFFER_BIT);

	loc = glGetAttribLocation(prog, "aPosition");
	glEnableVertexAttribArray(loc);
	glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE, 0, vertices);

	loc = glGetAttribLocation(prog, "aColor");
	glEnableVertexAttribArray(loc);
	glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE, 0, colors);

	if (mode == 1) {
		loc = glGetUniformLocation(prog, "vdist");
		glUniform1f(loc, dist);
	}
	if (mode == 2) {
		loc = glGetUniformLocation(prog, "vdist");
		glUniform1f(loc, distt);
	}
	if (mode == 3) {
		loc = glGetUniformLocation(prog, "udist");
		glUniform1f(loc, distt);
	}
	if (mode == 4) {
		loc = glGetUniformLocation(prog, "udist");
		glUniform1f(loc, dist);
	}
	if (mode == 0) {
	}
	
	glDrawArrays(GL_TRIANGLES, 0, 3);
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
	glutIdleFunc(myidle);
	glutKeyboardFunc(mykeyboard);
	glewInit();
	myinit();
	glutMainLoop();
	return 0;
}