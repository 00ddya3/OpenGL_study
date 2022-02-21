#include <GL/glew.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

const char* vsSource = "#version 120 \n\
in vec4 aPosition; \n\
in vec4 aColor; \n\
out vec4 vColor; \n\
//uniform float udist: \n\
void main(void) { \n\
 gl_Position = aPosition; \n\
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
//float dist = 0.0f;

void myinit(void) {
	GLint status;
	printf("***** Your student number and name *****\n");
	// vs: vertex shader
	vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vsSource, NULL);
	glCompileShader(vs); // compile to get .OBJ
	glGetShaderiv(vs, GL_COMPILE_STATUS, &status);
	printf("vs compile status = %s\n", (status == GL_TRUE) ? "true" :
		"false");
	glGetShaderInfoLog(vs, sizeof(buf), NULL, buf);
	printf("vs log = [%s]\n", buf);
	// fs: fragment shader
	fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fsSource, NULL);
	glCompileShader(fs); // compile to get .OBJ
	glGetShaderiv(fs, GL_COMPILE_STATUS, &status);
	printf("fs compile status = %s\n", (status == GL_TRUE) ? "true" :
		"false");
	glGetShaderInfoLog(fs, sizeof(buf), NULL, buf);
	printf("fs log = [%s]\n", buf);
	// prog: program
	prog = glCreateProgram();
	glAttachShader(prog, vs);
	glAttachShader(prog, fs);
	glLinkProgram(prog); // link to get .EXE
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
	glUseProgram(prog); // execute it !
}

void mykeyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 27: // ESCAPE
		exit(0);
		break;
	}
}

GLfloat vertices[] = {
-0.5, -0.5, 0.0, 1.0, //x좌표 : v[0]
+0.5, -0.5, 0.0, 1.0, //x좌표 : v[4]
-0.5, +0.5, 0.0, 1.0, //x좌표 : v[8]
};

GLfloat colors[] = {
1.0, 0.0, 0.0, 1.0, // red
0.0, 1.0, 0.0, 1.0, // green
0.0, 0.0, 1.0, 1.0, // blue
};

void myidle(void) { //이벤트가 없으면 idle 실행
	float step = 0.0001f;
	vertices[0] += step;
	vertices[4] += step;
	vertices[8] += step;
	//vertices 인자가 많다면 for문을 사용해도 좋음
	//dist +=0.0001f;를 사용해도 좋음
	//다시 돌아오게 하고싶다면 if (dist>3) dist=0.0f;
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

	//loc=glGetUniformLocation(prog, "udist");
	//glUniform1f(loc, dist);

	glDrawArrays(GL_TRIANGLES, 0, 3);
	glutSwapBuffers();
	glFlush();
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("*** Your Student number and name ***");
	glutDisplayFunc(mydisplay);
	glutKeyboardFunc(mykeyboard);
	glutIdleFunc(myidle);
	glewInit();
	myinit();
	glutMainLoop();
	return 0;
}
