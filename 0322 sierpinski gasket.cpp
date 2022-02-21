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
	
	//삼각형 반복해서 그리기
	int	id;
	for (int i = 0; i < 5000; i++) {
		id = rand() % 3;  //pick a vertex at random
		t[0] = (t[0] + vertices[id][0]) / 2.0;  //점 t의 x값에 점 t의 x값과 점 id의 x값의 중간값을 새로 대입함  (vertices[id][0]: vertices의 id행 0열)
		t[1] = (t[1] + vertices[id][1]) / 2.0;  //점 t의 y값에 점 t의 y값과 점 id의 y값의 중간값을 새로 대입함  (vertices[id][1]: vertices의 id행 1열)
		glBegin(GL_POINTS);  //랜덤하게 골라서는 같은 수준의 점들끼리 선 긋는게 힘들어서 점찍는 걸 엄청 많이 반복해서 그림처럼 보이도록 함 
		glVertex2fv(t);
		glEnd();
	}
	
	glFlush(); // Flush all 
	glutSwapBuffers();  //지우면 안됨
} 

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);  //지우면 안됨
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);

	// replace “simple” by your student number and name
	glutCreateWindow("2018115542_김민정");

	glutDisplayFunc(mydisplay);
	glutKeyboardFunc(mykeyboard);
	glewInit();
	myinit();
	glutMainLoop();
	return 0;
} 