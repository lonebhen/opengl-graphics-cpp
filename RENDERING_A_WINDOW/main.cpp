#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


using namespace std;


//Closes window when user presses escape key
void setKeyCallBack(GLFWwindow* window, int, int, int, int);


int main() {


	//Initializing glfw

	glfwInit();

	/*Telling opengl the version we want to use
	and the profile --> core*/

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);



	GLFWwindow* window = glfwCreateWindow(800, 800, "Opengl with cpp", nullptr, nullptr);

	if (window == nullptr) {
		cout << "Failed to generate window!!" << endl;
		glfwTerminate();

		return -1;

	};

	glfwMakeContextCurrent(window);

	/*loading glad*/

	gladLoadGL();


	/*Game loop*/

	while (!glfwWindowShouldClose(window)) {

		glfwPollEvents();

		glfwSetKeyCallback(window, setKeyCallBack);

		/*Changing the default buffer color(WHITE)*/

		glClearColor(0.6f, 0.4f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		glfwSwapBuffers(window);



	}


	glfwTerminate();



	return 0;


}


void setKeyCallBack(GLFWwindow* window, int action, int key, int scancode, int mode) {

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {

		glfwSetWindowShouldClose(window, GL_TRUE);
	};
}
