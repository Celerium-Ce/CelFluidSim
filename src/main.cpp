#include "config.h"
#define nl '\n'
using std::cout;
using std::cin;
using std::string;
using std::vector;
using std::pow;

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


	unsigned int VAO;
	glGenVertexArrays(1,&VAO);
	glBindVertexArray(VAO);


	//------------------------- Setting up Vertex data and buffer -------------------------


	float vertices[]={
		 0.0f,0.1f,0.0f,1.0f,0.0f,0.0f, 
		 -0.0866f,-0.05f,0.0f,1.0f,0.0f,0.0f,
		 0.0866f,-0.05f,0.0f,1.0f,0.0f,0.0f
	};

	unsigned int VBO;
	glGenBuffers(1,&VBO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

	
	//------------------------- Defining/Linking Vertex Attributes -------------------------
	

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float),(void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float),(void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);
	
	//Activating and freeing objects
	glDeleteShader(vertexshader);
	glDeleteShader(fragmentshader);
	

	//------------------------- Main Window Loop -------------------------
	
	float delta=0.001f;
	while (!glfwWindowShouldClose(window)){
		//glUseProgram(shaderprogram);
		//glBindVertexArray(VAO);
		
		vertices[0]+=delta;
		vertices[1]=pow((0.1f-(float)pow(vertices[0],2)),0.5f);
		vertices[6]+=delta;
		vertices[7]=pow((0.1f-(float)pow(vertices[6],2)),0.5f);
		vertices[12]+=delta;
		vertices[13]=pow((0.1f-(float)pow(vertices[12],2)),0.5f);
		glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderprogram);
		glBindVertexArray(VAO);	
		glDrawArrays(GL_TRIANGLES,0,3);
		//glBindVertexArray(VAO[1]);
		//glDrawArrays(GL_TRIANGLES,0,3);
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
