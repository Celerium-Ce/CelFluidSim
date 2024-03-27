#include "config.h"
#define nl '\n'
using std::cout;
using std::cin;

int main(){

	GLFWwindow* window;

	if (!glfwInit()){
		cout << "GLFW couldn't start" << nl;	
		return -1;
	}
	window = glfwCreateWindow(640,480,"CelFluidSim",NULL,NULL);
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
		glfwTerminate();
		return -1;
	}

	glClearColor(0.75f,0.01f,1.0f,0.5f);

	while (!glfwWindowShouldClose(window)){
		glClear(GL_COLOR_BUFFER_BIT);	
		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	glfwTerminate();
	return 0;
}
