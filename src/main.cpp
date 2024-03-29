#include "config.h"
#define nl '\n'
using std::cout;
using std::cin;
void framebuffer_size_callback(GLFWwindow* window, int width, int height){
glViewport(0, 0, width, height);
}

void changerace(GLFWwindow* window){
	if (glfwGetKey(window,GLFW_KEY_SPACE) == GLFW_PRESS){
		glClearColor(0.75f,0.01f,1.0f,0.5f);
	}
}
void changerace2(GLFWwindow* window){
	if (glfwGetKey(window,GLFW_KEY_TAB) == GLFW_PRESS){
		glClearColor(0.0f,0.0f,1.0f,0.5f);
	}
}
int main(){
	
	if (!glfwInit()){
		cout << "GLFW couldn't start" << nl;	
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(800,600,"CelFluidSim",NULL,NULL);

	
	if (window==NULL){
		cout << "Window couldnt be created" << nl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
		glfwTerminate();
		return -1;
	}

	glViewport(0,0,800,600);
	glClearColor(0.0f,0.0f,0.0f,1.0f);
	while (!glfwWindowShouldClose(window)){
		changerace(window);
		changerace2(window);
		glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);
		glClear(GL_COLOR_BUFFER_BIT);	
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}
