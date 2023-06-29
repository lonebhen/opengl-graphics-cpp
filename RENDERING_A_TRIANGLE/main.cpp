#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace std;


// Vertex shader source

const char* vertexShaderSource = "#version 330 core \n"
"layout(location=0) in vec3 aPos;\n"
"void main()\n"
"{\n"
" gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0); \n"
"}\0";

// Fragment shader source
const char* fragmentShaderSource = "#version 330 core \n"
" out vec4 FragColor;\n"
"void main()\n"
"{\n"
" FragColor = vec4(0.8f,0.3f,0.2f,1.0f);\n"
"}\n\0";



int main() {


	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	// Vertices for plotting the triangle

	GLfloat vertices[] = {
		-0.5f,-0.5f * float(sqrt(3)) / 3,0.0f,
		0.5f,-0.5f * float(sqrt(3)) / 3, 0.0f,
		0.0f,0.5f * float(sqrt(3)) * 2 / 3,0.0f
	};


	GLFWwindow* window = glfwCreateWindow(800, 800, "RENDERING A TRIANGLE", nullptr, nullptr);

	if (window == nullptr) {
		cout << "Failed to generate window" << endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	gladLoadGL();

	glViewport(0, 0, 800, 800);


	// Compile shaders

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
	glCompileShader(fragmentShader);


	// Shader program

	GLuint shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);



	// Vertex array and buffer objects

	GLuint VAO, VBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// Bind vertex array and buffer objects
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(0);


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);



	// Game loop

	while (!glfwWindowShouldClose(window)) {

		glClearColor(0.12f, 0.14f, 0.16f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram); // Use the shader program
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3); // Draw the triangles
		glfwSwapBuffers(window);
		glfwPollEvents();

	}


	// Delete objects and shaders

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glDeleteShader(shaderProgram);


	glfwTerminate();


	return 0;
}