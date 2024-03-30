#include "config.h"
#include <filesystem>
#define nl '\n'
using std::cout;
using std::cin;
using std::string;


const char* vertexshadersource;
const char* fragmentshadersource;

// converts file to const char* type
const char* readshadersource(const string& filepath){
	std::ifstream sourcefile(filepath);
	if (!sourcefile.is_open()){
		cout << "Error opening shader file" << nl;
		return nullptr;
	}
	string shadersource;
	string line;
	while (getline(sourcefile,line)){
		if (line==""){continue;}
	shadersource+=line+"\n";}
	sourcefile.close();
	const char* shaderreturn = shadersource.c_str();
	return shaderreturn;
}

// resize check
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
	// Lpading shaders
	vertexshadersource = readshadersource("../src/vertexshader");	
	fragmentshadersource = readshadersource("../src/fragmentshader");

	//--------------------- Initial GLFW Setup --------------------- 
	if (!glfwInit()){
		cout << "GLFW couldn't start" << nl;	
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//3.x
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//x.3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//core profile
	
	GLFWwindow* window = glfwCreateWindow(800,600,"CelFluidSim",NULL,NULL); //Creating Window
	
	//Window Check
	if (window==NULL){
		cout << "Window couldnt be created" << nl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	//GLAD initialize check
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
		cout << "Failed to initialize GLAD" << nl;
		glfwTerminate();
		return -1;
	}

	glViewport(0,0,800,600);
	glClearColor(0.0f,0.0f,0.0f,1.0f);


	//------------------------- Building and Compiling Shaders -------------------------
	
	//Vertex Shader 
	unsigned int vertexshader;
	vertexshader=glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexshader,1,&vertexshadersource,NULL);


	//------------------------- Main Window Loop -------------------------
	while (!glfwWindowShouldClose(window)){
		changerace(window);
		changerace2(window);
		glClear(GL_COLOR_BUFFER_BIT);	
		glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}
