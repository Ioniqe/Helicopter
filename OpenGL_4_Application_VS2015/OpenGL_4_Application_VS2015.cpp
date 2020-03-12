#define GLEW_STATIC

#include <iostream>
#include "glm/glm.hpp"//core glm functionality
#include "glm/gtc/matrix_transform.hpp"//glm extension for generating common transformation matrices
#include "glm/gtc/type_ptr.hpp"
#include "GLEW\glew.h"
#include "GLFW\glfw3.h"
#include <string>
#include "Shader.hpp"
#include "Camera.hpp"
#include "OpenGL_4_Application_VS2015.h"

//int glWindowWidth = 640;
//int glWindowHeight = 480;
int glWindowWidth = 1800;
int glWindowHeight = 1000;
int retina_width, retina_height;
GLFWwindow* glWindow = NULL;

//vertex data --- position and color
GLfloat vertices[] = {
	-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, //0
	0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, //1
	0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, //2
	-0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, //3
	-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, //4
	0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, //5
	0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 1.0f, //6
	-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, //7
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, //8   0'
	0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, //9   1'
	0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, //10   2'
	-0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, //11   3'
	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, //12   4'
	0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 1.0f, //13   5'
	0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f, //14   6'
	-0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f, //15   7'
	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, //16   0''
	0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, //17   1''
	0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 1.0f, //18   2''
	-0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 1.0f, //19   3''
	-0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f, //20   4''
	0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f, //21   5''
	0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 1.0f, //22   6''
	-0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 1.0f, //23   7''
};

//GLfloat vertices[] = {
//	-0.5f, -0.5f, -0.5f, 0.5, 1.0, 0.0, //0
//	0.5f, -0.5f, -0.5f,  0.5, 1.0, 0.0, //1
//	0.5f, -0.5f, 0.5f,  0.5, 1.0, 0.0, //2
//	-0.5f, -0.5f, 0.5f, 0.5, 1.0, 0.0, //3
//	-0.5f, 0.5f, -0.5f,  0.5, 1.0, 0.0, //4
//	0.5f, 0.5f, -0.5f,  0.5, 1.0, 0.0, //5
//	0.5f, 0.5f, 0.5f,  0.5, 1.0, 0.0, //6
//	-0.5f, 0.5f, 0.5f,  0.5, 1.0, 0.0, //7
//	-0.5f, -0.5f, -0.5f,  0.5, 1.0, 0.0, //8   0'
//	0.5f, -0.5f, -0.5f,  0.5, 1.0, 0.0, //9   1'
//	0.5f, -0.5f, 0.5f, 0.5, 1.0, 0.0, //10   2'
//	-0.5f, -0.5f, 0.5f,  0.5, 1.0, 0.0, //11   3'
//	-0.5f, 0.5f, -0.5f,  0.5, 1.0, 0.0, //12   4'
//	0.5f, 0.5f, -0.5f,  0.5, 1.0, 0.0, //13   5'
//	0.5f, 0.5f, 0.5f,  0.5, 1.0, 0.0, //14   6'
//	-0.5f, 0.5f, 0.5f,  0.5, 1.0, 0.0, //15   7'
//	-0.5f, -0.5f, -0.5f,  0.5, 1.0, 0.0, //16   0''
//	0.5f, -0.5f, -0.5f,  0.5, 1.0, 0.0, //17   1''
//	0.5f, -0.5f, 0.5f,  0.5, 1.0, 0.0, //18   2''
//	-0.5f, -0.5f, 0.5f,  0.5, 1.0, 0.0, //19   3''
//	-0.5f, 0.5f, -0.5f,  0.5, 1.0, 0.0, //20   4''
//	0.5f, 0.5f, -0.5f,  0.5, 1.0, 0.0, //21   5''
//	0.5f, 0.5f, 0.5f,  0.5, 1.0, 0.0, //22   6''
//	-0.5f, 0.5f, 0.5f,  0.5, 1.0, 0.0, //23   7''
//};


GLuint indices[] = {
	0, 1, 2, 0, 2, 3, // bottom plane triangles
	8, 9, 5, 8, 5, 4, // back plane triangles
	17, 10, 6, 17, 6, 13, // right plane triangles
	16, 12, 7, 16, 7, 11, // left plane triangles
	20, 21, 14, 20, 14, 15, // top plane triangles
	19, 18, 22, 19, 22, 23 // front plane triangles
};

GLuint verticesVBO;
GLuint verticesEBO;
GLuint objectVAO;

gps::Shader myCustomShader;

//------
glm::mat4 model; 
glm::mat4 model2; 

glm::mat4 modelCap;
glm::mat4 modelCorp;
glm::mat4 modelCoada;

glm::mat4 modelECap1;
glm::mat4 modelECap2;
glm::mat4 modelECoada1;
glm::mat4 modelECoada2;

glm::mat4 modelElicopter = glm::mat4(1.0f);
GLint  modelLoc;
//------

///
bool pressedKeys[1024];
gps::Camera myCamera(glm::vec3(0.0f, 3.0f, 15.0f), glm::vec3(0.0f, 2.0f, -10.0f));
float cameraSpeed = 0.06f;
//float cameraSpeed = 0.009f;
///


void windowResizeCallback(GLFWwindow* window, int width, int height)
{
	fprintf(stdout, "window resized to width: %d , and height: %d\n", width, height);
	//TODO
}

void initObjects()
{
	glGenVertexArrays(1, &objectVAO);
	glBindVertexArray(objectVAO);

	glGenBuffers(1, &verticesVBO);
	glBindBuffer(GL_ARRAY_BUFFER, verticesVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &verticesEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, verticesEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//vertex position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	//vertex colour attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}
//
void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			pressedKeys[key] = true;
		else if (action == GLFW_RELEASE)
			pressedKeys[key] = false;
	}
}

void mouseCallback(GLFWwindow* window, double xpos, double ypos)
{

}
//

bool initOpenGLWindow()
{
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		return false;
	}

	//for Mac OS X
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glWindow = glfwCreateWindow(glWindowWidth, glWindowHeight, "OpenGL Shader Example", NULL, NULL);
	if (!glWindow) {
		fprintf(stderr, "ERROR: could not open window with GLFW3\n");
		glfwTerminate();
		return false;
	}

	glfwSetWindowSizeCallback(glWindow, windowResizeCallback);
	glfwMakeContextCurrent(glWindow);

	glfwWindowHint(GLFW_SAMPLES, 4);

	// start GLEW extension handler
	glewExperimental = GL_TRUE;
	glewInit();

	// get version info
	const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
	const GLubyte* version = glGetString(GL_VERSION); // version as a string
	printf("Renderer: %s\n", renderer);
	printf("OpenGL version supported %s\n", version);

	//for RETINA display
	glfwGetFramebufferSize(glWindow, &retina_width, &retina_height);

	//
	glfwSetKeyCallback(glWindow, keyboardCallback);
	glfwSetCursorPosCallback(glWindow, mouseCallback);
	//

	return true;
}

//----------
float angl = 0;
float angle = 0;
float angleSecondCube = 0;
float angleEliceCoada = 0;
//----------

void scaleObjects() {

//	//modelElicopter = glm::mat4(1.0f);
//
//	//---------SCALING FOR CAP--------
//	glm::vec3 scaleCap = glm::vec3(2.0f, 2.0f, 2.0f);
//	//modelCap = glm::mat4(1.0f);
//	modelCap = modelElicopter;
//	modelCap = glm::scale(modelCap, scaleCap);
//	//---------/SCALING FOR CAP--------
//
//	//---------SCALING FOR CORP--------
//	glm::vec3 scaleCorp = glm::vec3(0.7f, 0.7f, 2.0f);
//	//modelCorp = glm::mat4(1.0f);
//	modelCorp = modelElicopter;
//	modelCorp = glm::scale(modelCorp, scaleCorp);
//	//---------/SCALING FOR CORP--------
//
//	//---------SCALING FOR COADA--------
//	glm::vec3 scaleCoada = glm::vec3(1.1f, 1.1f, 1.1f);
//	//modelCoada = glm::mat4(1.0f);
//	modelCoada = modelElicopter;
//	modelCoada = glm::scale(modelCoada, scaleCoada);
//	//---------/SCALING FOR COADA--------
//
//	//-------------------------------------------------------------------------------------
//
//	////----------SCALING for modelECap1-----------
//	//glm::vec3 scaleECap1 = glm::vec3(4.0f, 0.1f, 0.5f);
//	//modelECap1 = modelElicopter;
//	//modelECap1 = glm::scale(modelECap1, scaleECap1);
//	////----------/SCALING for modelECap1-----------
//
//	////----------SCALING for modelECap2-----------
//	//glm::vec3 scaleECap2 = glm::vec3(0.5f, 0.1f, 4.0f);
//	//modelECap2 = modelElicopter;
//	//modelECap2 = glm::scale(modelECap2, scaleECap2);
//	////----------/SCALING for modelECap2-----------

	//----------SCALING for modelECoada-----------
	glm::vec3 scaleECoada1 = glm::vec3(0.1f, 0.4f, 1.6f);
	modelECoada1 = modelElicopter;
	modelECoada1 = glm::scale(modelECoada1, scaleECoada1);
	//----------/SCALING for modelECoada-----------

	//----------SCALING for modelECoada-----------
	glm::vec3 scaleECoada2 = glm::vec3(0.1f, 1.6f, 0.4f);
	modelECoada2 = modelElicopter;
	modelECoada2 = glm::scale(modelECoada2, scaleECoada2);
	//----------/SCALING for modelECoada-----------
}

void elice() {
	////-------------elice Cap 1----
	//modelECap1 = glm::translate(modelECap1, glm::vec3(0, 10.5, 8));
	//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelECap1));
	//myCustomShader.useShaderProgram();
	//glBindVertexArray(objectVAO);
	//glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	////-------------/elice Cap 1----

	////-------------elice Cap 2----
	//modelECap2 = glm::translate(modelECap2, glm::vec3(0, 10.5, 1));
	//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelECap2));
	//myCustomShader.useShaderProgram();
	//glBindVertexArray(objectVAO);
	//glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	////-------------/elice Cap 2----

	//-------------elice coada 1----
	modelECoada1 = glm::translate(modelECoada1, glm::vec3(6, 0, 2.2)); 
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelECoada1));
	myCustomShader.useShaderProgram();
	glBindVertexArray(objectVAO);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//-------------/elice coada 1----

	//-------------elice coada 2----
	modelECoada2 = glm::translate(modelECoada2, glm::vec3(6, 0, 8.8));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelECoada2));
	myCustomShader.useShaderProgram();
	glBindVertexArray(objectVAO);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//-------------/elice coada 2----
}

void helicopterBody() {

	//-------------Cap----
	modelCap = glm::scale(modelElicopter, glm::vec3(2.0f, 2.0f, 2.0f));
	//modelCap = glm::translate(modelCap, glm::vec3(0, 0, 2)); 
	modelCap = glm::translate(modelCap, glm::vec3(0, 0, 0)); 
	
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelCap));
	myCustomShader.useShaderProgram();
	glBindVertexArray(objectVAO);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//-------------/Cap----

	//-------------Corp----
	modelCorp = glm::scale(modelElicopter, glm::vec3(0.7f, 0.7f, 2.0f));
	//modelCorp = glm::translate(modelCorp, glm::vec3(0, 0, 3));
	modelCorp = glm::translate(modelCorp, glm::vec3(0, 0, 1));
	
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelCorp));
	myCustomShader.useShaderProgram();
	glBindVertexArray(objectVAO);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//-------------/Corp----

	//-------------Coada----
	modelCoada = glm::scale(modelElicopter, glm::vec3(1.1f, 1.1f, 1.1f));
	//modelCoada = glm::translate(modelCoada, glm::vec3(0, 0, 6.79));
	modelCoada = glm::translate(modelCoada, glm::vec3(0, 0, 3.25));
	
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelCoada));
	myCustomShader.useShaderProgram();
	glBindVertexArray(objectVAO);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//-------------/Coada----


	//-------------------------modelECap1-----------------------------------------
	modelECap1 = glm::rotate(modelElicopter, angl, glm::vec3(0, 1, 0));
	modelECap1 = glm::scale(modelECap1, glm::vec3(4.0f, 0.1f, 0.5f));
	modelECap1 = glm::translate(modelECap1, glm::vec3(0, 10.5, 0));
	
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelECap1));
	myCustomShader.useShaderProgram();
	glBindVertexArray(objectVAO);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//-------------------------/modelECap1-----------------------------------------

	//-------------------------modelECap2-----------------------------------------
	modelECap2 = glm::rotate(modelElicopter, angl, glm::vec3(0, 1, 0));
	modelECap2 = glm::scale(modelECap2, glm::vec3(0.5f, 0.1f, 4.0f));
	modelECap2 = glm::translate(modelECap2, glm::vec3(0, 10.5, 0));
	
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelECap2));
	myCustomShader.useShaderProgram();
	glBindVertexArray(objectVAO);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//-------------------------/modelECap2-----------------------------------------

	////-------------------------modelECoada1-----------------------------------------
	//modelECoada1 = glm::translate(modelECoada1, glm::vec3(0, 0, 1));
	//modelECoada1 = glm::rotate(modelElicopter, angl, glm::vec3(1, 0, 0));
	//modelECoada1 = glm::translate(modelECoada1, -glm::vec3(0, 0, 1));
	//modelECoada1 = glm::scale(modelECoada1, glm::vec3(0.1f, 0.4f, 1.6f));
	////modelECoada1 = glm::translate(modelECoada1, glm::vec3(6, 0, 1));
	//display(modelECoada1);
	////-------------------------/modelECoada1-----------------------------------------
}

void incrAngle() {
	angleEliceCoada += 0.05f;
	angl += 0.05f;
}

void doAlways() {
//	modelECap1 = glm::translate(modelECap1, glm::vec3(0, 10.5, 8));
//	modelECap1 = glm::rotate(modelECap1, angleEliceCap1, glm::vec3(0, 1, 0));
//	modelECap1 = glm::translate(modelECap1, glm::vec3(0, -10.5, -8));
//
//
//	modelECap2 = glm::translate(modelECap2, glm::vec3(0, 10.5, 1));
//	modelECap2 = glm::rotate(modelECap2, angleEliceCap2, glm::vec3(0, 1, 0));
//	modelECap2 = glm::translate(modelECap2, -glm::vec3(0, 10.5, 1));
//
	modelECoada1 = glm::translate(modelECoada1, glm::vec3(6, 0, 2.2));
	modelECoada1 = glm::rotate(modelECoada1, angleEliceCoada, glm::vec3(1, 0, 0));
	modelECoada1 = glm::translate(modelECoada1, -glm::vec3(6, 0, 2.2));

	modelECoada2 = glm::translate(modelECoada2, glm::vec3(6, 0, 8.8));
	modelECoada2 = glm::rotate(modelECoada2, angleEliceCoada, glm::vec3(1, 0, 0));
	modelECoada2 = glm::translate(modelECoada2, -glm::vec3(6, 0, 8.8));
}

void processMovement() {

	if (glfwGetKey(glWindow, GLFW_KEY_Q)) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	if (glfwGetKey(glWindow, GLFW_KEY_E)) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	model = glm::mat4(1.0f);
	if (glfwGetKey(glWindow, GLFW_KEY_R)) {
		angle += 0.002f;
	}

	model2 = glm::mat4(1.0f);
	if (glfwGetKey(glWindow, GLFW_KEY_P)) {
		angleSecondCube += 0.002f;

		//angleEliceCap1 += 0.02f;
		//angleEliceCap2 += 0.02f;
		//angleEliceCoada1 += 0.02f;
		//angleEliceCoada2 += 0.02f;
	}

	if (pressedKeys[GLFW_KEY_W]) {
		//myCamera.move(gps::MOVE_FORWARD, cameraSpeed);
		modelElicopter = glm::translate(modelElicopter, glm::vec3(0.0, 0.0, -0.03));
	}

	if (pressedKeys[GLFW_KEY_A]) {
		//myCamera.move(gps::MOVE_LEFT, cameraSpeed);
		modelElicopter = glm::translate(modelElicopter, glm::vec3(-0.03, 0.0, 0.0));
	}

	if (pressedKeys[GLFW_KEY_S]) {
		//myCamera.move(gps::MOVE_BACKWARD, cameraSpeed);
		modelElicopter = glm::translate(modelElicopter, glm::vec3(0.0, 0.0, 0.03));
	}

	if (pressedKeys[GLFW_KEY_D]) {
		//myCamera.move(gps::MOVE_RIGHT, cameraSpeed);
		modelElicopter = glm::translate(modelElicopter, glm::vec3(0.03, 0.0, 0.0));
	}
	//----------------------------------------------------------------------
	if (pressedKeys[GLFW_KEY_T]) {
		myCamera.move(gps::MOVE_FORWARD, cameraSpeed);
	}

	if (pressedKeys[GLFW_KEY_F]) {
		myCamera.move(gps::MOVE_LEFT, cameraSpeed);
	}

	if (pressedKeys[GLFW_KEY_G]) {
		myCamera.move(gps::MOVE_BACKWARD, cameraSpeed);
	}

	if (pressedKeys[GLFW_KEY_H]) {
		myCamera.move(gps::MOVE_RIGHT, cameraSpeed);
	}

	if (pressedKeys[GLFW_KEY_I]) {
		myCamera.move(gps::MOVE_UP, cameraSpeed);
	}

	if (pressedKeys[GLFW_KEY_J]) {
		myCamera.move(gps::ROTATE_LEFT, cameraSpeed);
	}

	if (pressedKeys[GLFW_KEY_K]) {
		myCamera.move(gps::MOVE_DOWN, cameraSpeed);
	}


	if (pressedKeys[GLFW_KEY_L]) {
		myCamera.move(gps::ROTATE_RIGHT, cameraSpeed);
	}

	//----------------------------------------------------------------------

	//
	if (pressedKeys[GLFW_KEY_UP]) {
		//myCamera.move(gps::MOVE_UP, cameraSpeed);
		modelElicopter = glm::translate(modelElicopter, glm::vec3(0.0, 0.03, 0.0));
	}

	if (pressedKeys[GLFW_KEY_DOWN]) {
		//myCamera.move(gps::MOVE_DOWN, cameraSpeed);
		modelElicopter = glm::translate(modelElicopter, glm::vec3(0.0, -0.03, 0.0));
	}

	if (pressedKeys[GLFW_KEY_LEFT]) {
		//myCamera.move(gps::ROTATE_LEFT, cameraSpeed);
		modelElicopter = glm::translate(modelElicopter, glm::vec3(0, 0, 3));
		modelElicopter = glm::rotate(modelElicopter, 0.03f, glm::vec3(0, 1, 0));
		modelElicopter = glm::translate(modelElicopter, glm::vec3(0, 0, -3));
	}

	if (pressedKeys[GLFW_KEY_RIGHT]) {
		//myCamera.move(gps::ROTATE_RIGHT, cameraSpeed);
		modelElicopter = glm::translate(modelElicopter, glm::vec3(0, 0, 3));
		modelElicopter = glm::rotate(modelElicopter, 0.03f, glm::vec3(0, -1, 0));
		modelElicopter = glm::translate(modelElicopter, glm::vec3(0, 0, -3));
	}
}

void stuffFromLabs() {

	//----------rotation of first cube
	/// create rotation matrix 
	model = glm::rotate(model, angle, glm::vec3(0, 1, 0));
	/// send matrix data to vertex shader 
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	//----------/rotation of first cube

	myCustomShader.useShaderProgram();
	glBindVertexArray(objectVAO);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	//------rotation for second cube----
	/// create rotation matrix  

	model2 = glm::rotate(model2, angleSecondCube, glm::vec3(2, 0, 0));

	/// send matrix data to vertex shader  
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
	//------/rotation for second cube----

	//-------------second cube----
	/// create a translation matrix  
	model2 = glm::translate(model2, glm::vec3(5, 0, 0));
	/// send matrix data to vertex shader  
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
	/// draw the second cube  
	myCustomShader.useShaderProgram();
	glBindVertexArray(objectVAO);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//-------------/second cube----

}

void renderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.8, 0.8, 0.8, 1.0);
	glViewport(0, 0, retina_width, retina_height);

	processMovement();
	scaleObjects();
	incrAngle();

	doAlways();
	helicopterBody();
	elice();


	//initialize the view matrix
	glm::mat4 view = myCamera.getViewMatrix();
	//send matrix data to shader
	GLint viewLoc = glGetUniformLocation(myCustomShader.shaderProgram, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

	stuffFromLabs();
}

int main(int argc, const char * argv[]) {

	initOpenGLWindow();
	initObjects();
	glEnable(GL_DEPTH_TEST);

	myCustomShader.loadShader("shaders/shaderStart.vert", "shaders/shaderStart.frag");
	myCustomShader.useShaderProgram();

	//--------------
	model = glm::mat4(1.0f);  
	modelLoc = glGetUniformLocation(myCustomShader.shaderProgram, "model");  
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	
	/// initialize the view matrix  
	glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, -10.0f), glm::vec3(0.0f, 1.0f, 0.0f)); 
	///send the matrix data to shader
	GLint viewLoc = glGetUniformLocation(myCustomShader.shaderProgram, "view"); 
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	///initialize the projection matrix
	glm::mat4 projection = glm::perspective(70.0f, (float)glWindowWidth / (float)glWindowHeight, 0.1f, 1000.0f);
	///send matrix data to shader
	GLint projLoc = glGetUniformLocation(myCustomShader.shaderProgram, "projection"); 
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	while (!glfwWindowShouldClose(glWindow)) {
		renderScene();

		glfwPollEvents();
		glfwSwapBuffers(glWindow);
	}

	//close GL context and any other GLFW resources
	glfwTerminate();

	return 0;
}
