#include "config.h"
#define nl '\n'
using std::cout;
using std::cin;
using std::string;
using std::vector;

const char* vertexshadersource;
const char* fragmentshadersource;

// converts file to const char* type
const char* readshadersource(const string& filepath){
	std::ifstream sourcefile(filepath, std::ios::binary);
	if (!sourcefile.is_open()){
		cout << "Error opening shader file" << nl;
		return nullptr;
	}
	std::vector<char> shadersource;
	char c;
	while (sourcefile.get(c)){
		shadersource.push_back(c);
	}
	shadersource.push_back('\0');
	sourcefile.close();
	char* shaderreturn = new char[shadersource.size()];
	std::copy(shadersource.begin(),shadersource.end(),shaderreturn);
	const char* ret=shaderreturn;
	return ret;
}

// resize check
void framebuffer_size_callback(GLFWwindow* window, int width, int height){
	glViewport(0, 0, width, height);
}

/*void changerace(GLFWwindow* window){
	if (glfwGetKey(window,GLFW_KEY_SPACE) == GLFW_PRESS){
		glClearColor(0.75f,0.01f,1.0f,0.5f);
	}
}
void changerace2(GLFWwindow* window){
	if (glfwGetKey(window,GLFW_KEY_TAB) == GLFW_PRESS){
		glClearColor(0.0f,0.0f,1.0f,0.5f);
	}
}*/

void shifttriangle(GLFWwindow* window,unsigned int& VBO){
	if (glfwGetKey(window,GLFW_KEY_SPACE) == GLFW_PRESS){
		float trinagle2[]={
		 0.00f, 0.05f, 0.0f,
		 0.05f,-0.05f, 0.0f,
		 0.1f, 0.1f, 0.0f
		};
		glGenBuffers(1,&VBO);
		glBindBuffer(GL_ARRAY_BUFFER,VBO);
		glBufferData(GL_ARRAY_BUFFER,sizeof(trinagle2),trinagle2,GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float),(void*)0);
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
	glCompileShader(vertexshader);
	int success1; //shader compilation checks
	char erlogs[512];
	glGetShaderiv(vertexshader,GL_COMPILE_STATUS,&success1);
	if(!success1){
		glGetShaderInfoLog(vertexshader,512,NULL,erlogs);
		cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << erlogs << nl;
	}
	//Fragment Shader
	unsigned int fragmentshader;
	fragmentshader=glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentshader,1,&fragmentshadersource,NULL);
	glCompileShader(fragmentshader);
	int success2; //shader compilation checks
	glGetShaderiv(fragmentshader,GL_COMPILE_STATUS,&success2);
	if(!success2){
		glGetShaderInfoLog(fragmentshader,512,NULL,erlogs);
		cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << erlogs << nl;
	}	
	//Creating Shader Program
	unsigned int shaderprogram;
	shaderprogram=glCreateProgram();
	glAttachShader(shaderprogram,vertexshader);
	glAttachShader(shaderprogram,fragmentshader);
	glLinkProgram(shaderprogram);
	glGetProgramiv(shaderprogram,GL_LINK_STATUS,&success1);
	if (!success1){
		glGetProgramInfoLog(shaderprogram,512,NULL,erlogs);
		cout << "SHADER::PROGRAM::ERROR\n" << erlogs;
		return -1;
	}

	
	//------------------------- Generating VAOs -------------------------


	unsigned int VAO[2];
	glGenVertexArrays(2,VAO);
	glBindVertexArray(VAO[0]);


	//------------------------- Setting up Vertex data and buffer -------------------------


	float triangle1[]={
		 0.0f, 0.5f, 0.5f,0.0f,
		 0.5f,-0.5f, 0.5f,0.0f,
		-0.5f,-0.5f, 0.5f,0.0f
	};
	
	unsigned int VBO[2];
	glGenBuffers(2, VBO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO[0]);
	glBufferData(GL_ARRAY_BUFFER,sizeof(triangle1),triangle1,GL_STATIC_DRAW);
	//------------------------- Defining/Linking Vertex Attributes -------------------------
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 4*sizeof(float),(void*)0);
	
	glBindVertexArray(VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER,VBO[1]);
	glBufferData(GL_ARRAY_BUFFER,sizeof(triangle1),triangle1,GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4*sizeof(float),(void*)(1*sizeof(float)));
	glEnableVertexAttribArray(0);

	//Freeing shaders
	glDeleteShader(vertexshader);
	glDeleteShader(fragmentshader);
	delete[] vertexshadersource;
	delete[] fragmentshadersource;
	

	//------------------------- Main Window Loop -------------------------
	

	while (!glfwWindowShouldClose(window)){
		
		
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderprogram);
		glBindVertexArray(VAO[0]);	
		glDrawArrays(GL_TRIANGLES,0,3);
		glBindVertexArray(VAO[1]);
		glDrawArrays(GL_TRIANGLES,0,3);
	
		glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	//------------------------- Terminations -------------------------


	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER,0);
	glfwTerminate();
	return 0;
}
