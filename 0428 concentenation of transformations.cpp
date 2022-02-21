#include <GL/glew.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define my_PI 3.141592

const char* vsSource = "#version 120 \n\
in vec4 aPosition; \n\
in vec4 aColor; \n\
out vec4 vColor; \n\
uniform mat4 umx; \n\
uniform mat4 umy; \n\
uniform mat4 umz; \n\
uniform vec2 u_trans_vec; \n\
void main(void) { \n\
 mat4 transmat = mat4(1.0); \n\
 transmat[3][0] = u_trans_vec[0]; \n\
 transmat[3][1] = u_trans_vec[1]; \n\
  mat4 transinvmat = mat4(1.0); \n\
 transinvmat[3][0] = -u_trans_vec[0]; \n\
 transinvmat[3][1] = -u_trans_vec[1]; \n\
 gl_Position = transmat*umz*umy*umx*transinvmat*aPosition; \n\
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
int DRAW_MODE = 0;
float t = 0.0f;

GLfloat vertices[] = {
0.5, 0.8, 0.0, 1.0, // 0
0.3, 0.3, +0.2, 1.0, // 1
0.7, 0.3, +0.2, 1.0, // 2
0.7, 0.3, -0.2, 1.0, // 3
0.3, 0.3, -0.2, 1.0, // 4
};

GLfloat colors[] = {
1.0, 0.0, 0.0, 1.0, //0
0.0, 1.0, 0.0, 1.0, //1
0.0, 0.0, 1.0, 1.0, //2
1.0, 0.0, 1.0, 1.0, //3
1.0, 1.0, 0.0, 1.0  //4
};

GLushort indices[] = {
0, 1, 2,
2, 3, 0,
4, 0, 3,
1, 0, 4,
2, 3, 1,
3, 4, 1
};

void myinit(void) {
	GLint status;
	printf("***** 2018115542_±ËπŒ¡§ *****\n");

	vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vsSource, NULL);
	glCompileShader(vs);
	glGetShaderiv(vs, GL_COMPILE_STATUS, &status);
	printf("vs compile status = %s\n", (status == GL_TRUE) ? "true" : "false");
	glGetShaderInfoLog(vs, sizeof(buf), NULL, buf);
	printf("vs log = [%s]\n", buf);

	fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fsSource, NULL);
	glCompileShader(fs);
	glGetShaderiv(fs, GL_COMPILE_STATUS, &status);
	printf("fs compile status = %s\n", (status == GL_TRUE) ? "true" : "false");
	glGetShaderInfoLog(fs, sizeof(buf), NULL, buf);
	printf("fs log = [%s]\n", buf);

	prog = glCreateProgram();
	glAttachShader(prog, vs);
	glAttachShader(prog, fs);
	glLinkProgram(prog);

	glGetProgramiv(prog, GL_LINK_STATUS, &status);
	printf("program link status = %s\n", (status == GL_TRUE) ? "true" : "false");
	glGetProgramInfoLog(prog, sizeof(buf), NULL, buf);
	printf("link log = [%s]\n", buf);
	glValidateProgram(prog);
	
	glGetProgramiv(prog, GL_VALIDATE_STATUS, &status);
	printf("program validate status = %s\n", (status == GL_TRUE) ? "true" : "false");
	glGetProgramInfoLog(prog, sizeof(buf), NULL, buf);
	printf("validate log = [%s]\n", buf);
	glUseProgram(prog);

	GLint loc;
	GLuint vbo[1];
	// using vertex buffer object
	glGenBuffers(1, vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, 2 * 5 * 4 * sizeof(GLfloat), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, 5 * 4 * sizeof(GLfloat), vertices);
	glBufferSubData(GL_ARRAY_BUFFER, 5 * 4 * sizeof(GLfloat), 5 * 4 * sizeof(GLfloat), colors);

	loc = glGetAttribLocation(prog, "aPosition");
	glEnableVertexAttribArray(loc);
	glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

	loc = glGetAttribLocation(prog, "aColor");
	glEnableVertexAttribArray(loc);
	glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(5 * 4 * sizeof(GLfloat)));

	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void mykeyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 27: // ESCAPE
		exit(0);
		break;
	}
}

void myidle(void) {
	//t += 0.0005f;
	// redisplay 
	glutPostRedisplay();
}

GLfloat mx[16], my[16], mz[16];
GLfloat tx, ty, tz;

void mydisplay(void) {
	GLuint loc;
	glClearColor(0.7f, 0.7f, 0.7f, 1.0f); // gray
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	tx = 30.0 * my_PI / 180.0;
	ty = 30.0 * my_PI / 180.0;
	tz = 30.0 * my_PI / 180.0;

	// rotation about x-axis
	mx[0] = 1.0;	mx[4] = 0.0;		mx[8] = 0.0;		mx[12] = 0.0;
	mx[1] = 0.0;	mx[5] = cos(tx);	mx[9] = -sin(tx);	mx[13] = 0.0;
	mx[2] = 0.0;	mx[6] = sin(tx);	mx[10] = cos(tx);	mx[14] = 0.0;
	mx[3] = 0.0;	mx[7] = 0.0;		mx[11] = 0.0;		mx[15] = 1.0;
	
	// rotation about y-axis
	my[0] = cos(ty);	my[4] = 0.0;	my[8] = sin(ty);	my[12] = 0.0;
	my[1] = 0.0;		my[5] = 1.0;	my[9] = 0.0;		my[13] = 0.0;
	my[2] = -sin(ty);	my[6] = 0.0;	my[10] = cos(ty);	my[14] = 0.0;
	my[3] = 0.0;		my[7] = 0.0;	my[11] = 0.0;		my[15] = 1.0;
	
	// rotation about z-axis
	mz[0] = cos(tz);	mz[4] = -sin(tz);	mz[8] = 0.0;	mz[12] = 0.0;
	mz[1] = sin(tz);	mz[5] = cos(tz);	mz[9] = 0.0;	mz[13] = 0.0;
	mz[2] = 0.0;		mz[6] = 0.0;		mz[10] = 1.0;	mz[14] = 0.0;
	mz[3] = 0.0;		mz[7] = 0.0;		mz[11] = 0.0;	mz[15] = 1.0;
	
	float utx, uty, utz;
	utx = uty = utz = 0;

	for (int i = 0; i < 20; i++)
	{
		if (i % 4 == 0)
			utx += vertices[i];
		else if (i % 4 == 1)
			uty += vertices[i];
		else if (i % 4 == 2)
			utz += vertices[i];
	}

	float centerx, centery, centerz;
	centerx = utx / 5;
	centery = uty / 5;
	centerz = utz / 5;

	loc = glGetUniformLocation(prog, "umx");
	glUniformMatrix4fv(loc, 1, GL_FALSE, mx);

	loc = glGetUniformLocation(prog, "umy");
	glUniformMatrix4fv(loc, 1, GL_FALSE, my);

	loc = glGetUniformLocation(prog, "umz");
	glUniformMatrix4fv(loc, 1, GL_FALSE, mz);

	float trans_vec[] = { centerx, centery };
	loc = glGetUniformLocation(prog, "u_trans_vec");
	glUniform2fv(loc, 1, trans_vec);

	glDrawElements(GL_TRIANGLES, 6 * 3, GL_UNSIGNED_SHORT, indices);

	glFlush();
	glutSwapBuffers();
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("*** 2018115542_±ËπŒ¡§ ***");
	glutDisplayFunc(mydisplay);
	glutIdleFunc(myidle);
	glutKeyboardFunc(mykeyboard);
	glewInit();
	myinit();
	glutMainLoop();
	return 0;
}