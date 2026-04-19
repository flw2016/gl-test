#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

struct Mat3 { // матрица 3х3
	float m[9]; 
};

struct Vec3 { // вектор 3х1
	float x, y, z;
};

void mat3_identity(Mat3* out) { // единичная матрица 3х3
	out->m[0] = 1.0f; out->m[1] = 0.0f; out->m[2] = 0.0f;
	out->m[3] = 0.0f; out->m[4] = 1.0f; out->m[5] = 0.0f;
	out->m[6] = 0.0f; out->m[7] = 0.0f; out->m[8] = 1.0f;
};

void mat3_rotation_y(float angle, Mat3* out){ // матрица поворота по Y 3x3
	float c = cosf(angle);
	float s = sinf(angle);

	out->m[0] = c; out->m[1] = 0.0f; out->m[2] = s;
	out->m[3] = 0.0f; out->m[4] = 1.0f; out->m[5] = 0.0f;
	out->m[6] = -s; out->m[7] = 0.0f; out->m[8] = c;
};

void mat3_mul_vec3(const Mat3* mat, const Vec3* in, Vec3* out) { // функция умножения матрицы 3x3 на вектор 3x1
	out->x = in->x * mat->m[0] + in->y * mat->m[1] + in->z * mat->m[2];
	out->y = in->x * mat->m[3] + in->y * mat->m[4] + in->z * mat->m[5];
	out->z = in->x * mat->m[6] + in->y * mat->m[7] + in->z * mat->m[8];
}

double lastTime = 0.d;
int frameCount = 0;

int main(){
	if (!glfwInit()){ // инициализируем GLFW
		std::cerr << "failed to initialize GLFW\n";
		return -1;
	}
	
	GLFWwindow* window = glfwCreateWindow(800, 600, "flw2016 opengl test", NULL, NULL); // создаем окно
	if (!window) {
		std::cerr << "failed to create GLFW window \n";
		glfwTerminate();
		return -1;
	}
	
	Vec3 original[3] = {
	{0.0f, 1.0f, 0.0f},
	{-1.0f, -1.0f, 0.0f},
	{1.0f, -1.0f, 0.0f},
	};
	Vec3 rotated[3];

	glfwMakeContextCurrent(window); // выбираем где работать
	float angle = 0.0f;
	lastTime = glfwGetTime();
	while (!glfwWindowShouldClose(window)){
		frameCount ++;
		double currentTime = glfwGetTime();
		float dt = (float)(currentTime - lastTime);
		angle += dt * 0.5f; // скорость поворота треугольника
		if(currentTime - lastTime >= 1.0){
			std::string title = "flw2016 opengl test | fps: " + std::to_string(frameCount);

			glfwSetWindowTitle(window, title.c_str());
			frameCount = 0;
			lastTime = currentTime;
		}

		Mat3 rotMat;
		mat3_rotation_y(angle, &rotMat);

		mat3_mul_vec3(&rotMat, &original[0], &rotated[0]); // считаем
		mat3_mul_vec3(&rotMat, &original[1], &rotated[1]);
		mat3_mul_vec3(&rotMat, &original[2], &rotated[2]);

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GLFW_TRUE);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // цвет закраски
		glClear(GL_COLOR_BUFFER_BIT);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity(); // сбрасываем настройки камеры до стандартных
		float aspect = 800.0f / 600.0f; // соотношение ширины/высоты
		glFrustum(-aspect, aspect, -1.0f, 1.0f, 2.0f, 10.0f); // левая граница, правая граница экрана, верхня, нижняя, ближе x = не видим, дальше x = не видим

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(0.0f, 0.0f, -5.0f); // отодвигаем мир на 5 по z, чтобы увидеть треугольник на координатах 0 0 0

		glColor3f(0.0f, 1.0f, 0.0f);
		glBegin(GL_LINE_LOOP);
			glVertex3f(rotated[0].x, rotated[0].y, rotated[0].z);
			glVertex3f(rotated[1].x, rotated[1].y, rotated[1].z);
			glVertex3f(rotated[2].x, rotated[2].y, rotated[2].z);
		glEnd();

		glfwSwapBuffers(window); // показываем нарисованное

		glfwPollEvents(); // обрабатываем события (клавиатуру, мышь)
	}

	glfwTerminate();
	return 0;
}
