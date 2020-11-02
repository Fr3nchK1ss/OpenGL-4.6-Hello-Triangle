/**
 * Hello colorful triangle
 *
 * An OpenGL "Hello Triangle" using
 * - glad instead of glew (because reason), and glfw3,
   - pieces from learnopengl.com
 * - the gl_utils lib of Anton Gerdelan tutos
 * - DSA, looking at fendevel/Guide-to-Modern-OpenGL-Functions @github
 * - heavy comments! This is the way.
 *
 * @author ludo456 / the opensourcedev @github
 */

#include "include/gl_utils.h" //includes glad.h & glfw3.h
#include <iostream>

// Forward declarations
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);


int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(800, 600, "Hello Colorful Triangle", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    if ( !GLAD_GL_ARB_direct_state_access )
    {
       /* see
       * https://www.khronos.org/registry/OpenGL/extensions/ARB/ARB_direct_state_access.txt
       * https://www.khronos.org/opengl/wiki/Direct_State_Access. This is the way.
       */
      std::cout << "DSA not supported!" << std::endl;
      return -1;
    }

    // Setting up the triangle data
    // ----------------------------

    float vertices[] = {
      -1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
       1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
       0.0f, 1.0f, 0.0f,  0.0f, 0.0f, 1.0f
    };
    GLuint attribPos = 0;
    GLuint attribCol = 1;

    /**************** VBO ***************/
    unsigned int hctVBO; // hello colorful triangle vbo
    //glGenBuffers(1, &VBO); // Way to go before openGl 4.5
    //glBindBuffer(GL_ARRAY_BUFFER, VBO); // Binding to openGl context was necessary
    //  replaced with:
    glCreateBuffers(1, &hctVBO);//uses DSA. This is the way.

    //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    //  replaced with:
    glNamedBufferStorage(hctVBO, sizeof(vertices), vertices, GL_DYNAMIC_STORAGE_BIT);
    //                    ^^^  needed, since there is no context binding.

    /**************** VAO ***************/
    unsigned int hctVAO;
    //glGenVertexArrays(1, &VAO);
    //glBindVertexArray(VAO);
    //  replaced with:
    glCreateVertexArrays(1, &hctVAO);// This is the way.

    // As there is, by definition, no context binding in DSA, then we need to
    //"bind" vao with vbo explicitely, like linking 2 indexes in a database.

    GLuint vaoBindingPoint = 0;//A binding point in VAO. See GL_MAX_VERTEX_ATTRIB_BINDINGS
    glVertexArrayVertexBuffer(
      hctVAO,             // vao to bind
      vaoBindingPoint,    // Could be 1, 2... if there were several vbo to source.
      hctVBO,             // VBO to bound at "vaoBindingPoint".
      0,                  // offset of the first element in the buffer hctVBO.
      6*sizeof(float));   // stride == 3 position floats + 3 color floats.

    //glEnableVertexAttribArray(attribPos);
    //glEnableVertexAttribArray(attribCol);
    //  replaced with:
    glEnableVertexArrayAttrib(hctVAO, attribPos);// Need to precise vao, as there is no context binding in DSA style
    glEnableVertexArrayAttrib(hctVAO, attribCol);// Meaning no current vao is bound to the opengl context.

    //glVertexAttribPointer(attribPos, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    //glVertexAttribPointer(attribCol, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)( 3*sizeof(float) ));
    //  replaced with:
    glVertexArrayAttribFormat(hctVAO, attribPos, 3, GL_FLOAT, false, 0);// Need to precise vao, as there is no context binding in DSA
    glVertexArrayAttribFormat(hctVAO, attribCol, 3, GL_FLOAT, false, 3*sizeof(float));//https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glVertexAttribFormat.xhtml

    //Explicit binding of an attribute to a vao binding point
    glVertexArrayAttribBinding(hctVAO, attribPos, vaoBindingPoint);
    glVertexArrayAttribBinding(hctVAO, attribCol, vaoBindingPoint);


    //Create shader using gl_utils
    // ---------------------------
    GLuint shader_prog =
      create_programme_from_files( "shader_triangle.vert", "shader_triangle.frag" );
    glUseProgram(shader_prog); // Could be copy-pasted in render loop too...


    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//Wireframe rendering
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(1.0f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(hctVAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
