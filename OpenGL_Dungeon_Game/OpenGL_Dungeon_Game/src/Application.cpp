#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Constants.h"
#include "Game.h"
#include "ResourceManager.h"

#include <iostream>

/* TODO list
*  
* Should be same speed while going diagonally as in x/y axis
* 
*/

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void keyCallback(GLFWwindow* window, int key, int scanCode, int action, int mode);

Game game(constants::screenWidth, constants::screenHeight);

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    glfwWindowHint(GLFW_RESIZABLE, false);

    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(constants::screenWidth, constants::screenHeight, "Dungeon Game", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
        std::cerr << "Error initializing glew\n";
   

    glfwSetKeyCallback(window, keyCallback);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    // OpenGL configuration
    glViewport(0, 0, constants::screenWidth, constants::screenHeight);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // initialize game
    game.init();

    // delta time variables
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* calculate delta time */
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        
        /* Poll for and process events */
        glfwPollEvents();

        /* manage user input */
        game.processInput(deltaTime);

        /* update game state */
        game.update(deltaTime);

        /* Render here */
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        game.render();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);
    }
    // delete all resources as loaded using the resource manager
    ResourceManager::clear();

    glfwTerminate();
    return 0;
}


void keyCallback(GLFWwindow* window, int key, int scanCode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            game.setKey(key, true);
        else if (action == GLFW_RELEASE)
            game.setKey(key, false);
    }
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}