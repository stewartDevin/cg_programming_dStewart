// Main.cpp
////////////////////////////////////////////////////////////////////////

#include "Application.h"

GLFWwindow* window = NULL;

int InitGlew() {
	glfwMakeContextCurrent(window); // Initialize GLEW
	glewExperimental = true; // has to do with core profile. 
	if(glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW.");
		return EXIT_WITH_ERROR;
	}

	return EXIT_WITH_SUCCESS;
}

int InitWindow() {
	if(!glfwInit()) {
		fprintf(stderr, "Failed to initialize GLFW.");
		return EXIT_WITH_ERROR;
	}

	glfwWindowHint(GLFW_SAMPLES, ANTIALIASING);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPEN_GL_VERSION);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPEN_GL_VERSION);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // get mac up and running.
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // we don't want the old openGL, gives the new one.

	window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, APP_NAME, NULL, NULL);

	if(window == NULL) {
		fprintf(stderr, "Failed to initialize window.");
		glfwTerminate();
		return EXIT_WITH_ERROR;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	return EXIT_WITH_SUCCESS;
}

int main() {
	if(InitWindow() | InitGlew()) {
		return EXIT_WITH_ERROR;
	}

	do {
		//Update();
		//Render();
		glfwSwapBuffers(window);
		glfwPollEvents();

	} while (glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0 );


	return EXIT_WITH_SUCCESS;
	//// Init GLFW
	//if (!glfwInit()) {
	//	fprintf(stderr, "Failed to init GLFW\n");
	//	return -1;
	//}

	//glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL 

	//// Open a window and create its OpenGL context 
	//GLFWwindow* window; // (In the accompanying source code, this variable is global) 
	//window = glfwCreateWindow( 1024, 768, "Tutorial 01", NULL, NULL); 
	//if( window == NULL ){
	//	fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
	//	glfwTerminate();
	//	return -1;
	//}
	//glfwMakeContextCurrent(window); // Initialize GLEW 
	//glewExperimental=true; // Needed in core profile 
	//if (glewInit() != GLEW_OK) {
	//	fprintf(stderr, "Failed to initialize GLEW\n");
	//	return -1;
	//}

	//// Ensure we can capture the escape key being pressed below
	//glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	//GLuint VertexArrayID;
	//glGenVertexArrays(1, &VertexArrayID);
	//glBindVertexArray(VertexArrayID);

	//// An array of 3 vectors which represents 3 vertices
	//static const GLfloat g_vertex_buffer_data[] = {
	//	-1.0f, -1.0f, 0.0f,
	//	1.0f, -1.0f, 0.0f,
	//	0.0f,  1.0f, 0.0f,
	//};

	//// This will identify our vertex buffer
	//GLuint vertexbuffer;

	//// Generate 1 buffer, put the resulting identifier in vertexbuffer
	//glGenBuffers(1, &vertexbuffer);

	//// The following commands will talk about our 'vertexbuffer' buffer
	//glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

	//// Give our vertices to OpenGL.
	//glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);


	//// on frame
	//do{
	//	// Draw nothing, see you in tutorial 2 !
	//	// 1rst attribute buffer : vertices
	//	glEnableVertexAttribArray(0);
	//	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	//	glVertexAttribPointer(
	//		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
	//		3,                  // size
	//		GL_FLOAT,           // type
	//		GL_FALSE,           // normalized?
	//		0,                  // stride
	//		(void*)0            // array buffer offset
	//		);

	//	// Draw the triangle !
	//	glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle

	//	glDisableVertexAttribArray(0);
	//	// Swap buffers
	//	glfwSwapBuffers(window);
	//	glfwPollEvents();

	//} // Check if the ESC key was pressed or the window was closed
	//while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
	//	glfwWindowShouldClose(window) == 0 );

	///////////////////////////////////////////////////////////////////////////////////////////////


}