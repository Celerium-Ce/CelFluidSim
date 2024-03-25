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
	return 0;
}
