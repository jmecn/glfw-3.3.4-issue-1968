#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void errorCallback(int error, const char* description) {
    fprintf(stderr, "Error: %s\n", description);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    printf("callback fbSize=%dx%d\n", width, height);
}

void printFrameBufferSize(GLFWwindow* window, int frame) {
    int w, h;
    float xscale, yscale;
    glfwGetFramebufferSize(window, &w, &h);
    glfwGetWindowContentScale(window, &xscale, &yscale);
    printf("frame#%d, fbSize=%dx%d, scale=%.2fx%.2f\n", frame, w, h, xscale, yscale);
}

int main(int argc, char const *argv[]) {
    int frame = -2;// two frame before loops
    int useRetinaFrameBuffer = GLFW_FALSE;
    int isPollEventBeforeLoop = GLFW_FALSE;

    for (int i = 0; i < argc; i++) {
        if (strncmp("retina", argv[i], 6) == 0) {
            useRetinaFrameBuffer = GLFW_TRUE;
        }
        if (strncmp("poll", argv[i], 4) == 0) {
            isPollEventBeforeLoop = GLFW_TRUE;
        }
    }

    glfwSetErrorCallback(errorCallback);

    if (!glfwInit()) {
        exit(-1);
    }

    // hint
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#endif
    glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, useRetinaFrameBuffer);

    GLFWwindow* window = glfwCreateWindow(640, 400, "Test FrameBuffer Size", NULL, NULL);
    if (!window) {
        glfwTerminate();
        exit(-1);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glfwSetKeyCallback(window, keyCallback);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    // loop
    printFrameBufferSize(window, frame++);

    if (isPollEventBeforeLoop) {
        glfwPollEvents();// <------- this is the point which changed glfwGetFramebufferSize result
    }

    printFrameBufferSize(window, frame++);

    printf("\n");

    while (!glfwWindowShouldClose(window)) {
        if (frame < 10) {
            printFrameBufferSize(window, frame++);
        } else {
            glfwSetWindowShouldClose(window, GLFW_TRUE);// close it
        }

        glfwSwapBuffers(window);
        glfwPollEvents();// <------- this is the point which changed glfwGetFramebufferSize result
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}