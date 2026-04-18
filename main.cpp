#include <GLFW/glfw3.h>
#include <iostream>

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
	
	glfwMakeContextCurrent(window); // выбираем где работать

	while (!glfwWindowShouldClose(window)){
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GLFW_TRUE);

		float r, g, b;
		if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
			r = 1.0f; g = 0.2f; b = 0.2f;
		} else {
			r = 0.2f; g = 0.8f; b = 0.3f;
		}
		glClearColor(r, g, b, 1.0f); // цвет закраски
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window); // показываем нарисованное

		glfwPollEvents(); // обрабатываем события (клавиатуру, мышь)
	}

	glfwTerminate();
	return 0;
}
