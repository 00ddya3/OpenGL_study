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

typedef GLfloat arr[2];
arr vertices[3] = { -0.5, -0.5, 
				0.5, -0.5, 
				-0.5, 0.5 };
arr t = { 0.0, 0.0 };  //initial point : middle point of (-0.5, 0.5) and (0.5, -0.5)


void mydisplay(void) {
	glClearColor(1.0, 1.0, 1.0, 1.0);  //clear in white color
	glClear(GL_COLOR_BUFFER_BIT);
	
	//�ﰢ�� �ݺ��ؼ� �׸���
	int	id;
	for (int i = 0; i < 5000; i++) {
		id = rand() % 3;  //pick a vertex at random
		t[0] = (t[0] + vertices[id][0]) / 2.0;  //�� t�� x���� �� t�� x���� �� id�� x���� �߰����� ���� ������  (vertices[id][0]: vertices�� id�� 0��)
		t[1] = (t[1] + vertices[id][1]) / 2.0;  //�� t�� y���� �� t�� y���� �� id�� y���� �߰����� ���� ������  (vertices[id][1]: vertices�� id�� 1��)
		glBegin(GL_POINTS);  //�����ϰ� ��󼭴� ���� ������ ���鳢�� �� �ߴ°� ���� ����� �� ��û ���� �ݺ��ؼ� �׸�ó�� ���̵��� �� 
		glVertex2fv(t);
		glEnd();
	}
	
	glFlush(); // Flush all 
	glutSwapBuffers();  //����� �ȵ�
} 

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);  //����� �ȵ�
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);

	// replace ��simple�� by your student number and name
	glutCreateWindow("2018115542_�����");

	glutDisplayFunc(mydisplay);
	glutKeyboardFunc(mykeyboard);
	glewInit();
	myinit();
	glutMainLoop();
	return 0;
} 