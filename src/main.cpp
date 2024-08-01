#include <iostream>
#include <cstdlib>
#include <ctime>
#include "../resources/glfw/include/GLFW/glfw3.h"



#define WIDTH 500
#define HEIGHT 500
#define TITLE "Sand Falling | Hasan Efe Aksoy"

#define PI 3.14159265
#define BIG 1000000




double xpos, ypos;

// enter counts (ex: WIDTH / rowsCount is integer.)
const int rowsCount = 250;
const int columnsCount = 250;

const float cellWidth = WIDTH / rowsCount;
const float cellHeight = HEIGHT / columnsCount;

bool isDrawGrids = false;


int gridStates[columnsCount][rowsCount];
const int cellCount = sizeof(gridStates) / sizeof(int);




int main()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    GLFWwindow* window = nullptr;
    
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_RESIZABLE, 0);
    window = glfwCreateWindow(WIDTH, HEIGHT, TITLE, NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-WIDTH/2, WIDTH/2, -HEIGHT/2, HEIGHT/2, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();



    for (int i = 0; i < columnsCount; i++) {
        for (int j = 0; j < rowsCount; j++) {
            gridStates[i][j] = 0;
        }
    }



    while (!glfwWindowShouldClose(window))
    {   
        double currentTime = glfwGetTime();

        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        
        glColor3f(1.0f, 1.0f, 0.0f);



        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {

            double xpos, ypos;
            glfwGetCursorPos(window, &xpos, &ypos);
            xpos = xpos - WIDTH / 2;
            ypos = HEIGHT / 2 - ypos;


            int gridX = static_cast<int>((xpos + WIDTH / 2) / cellWidth);
            int gridY = static_cast<int>((HEIGHT / 2 - ypos) / cellHeight);

            if (gridX >= 0 && gridX < rowsCount && gridY >= 0 && gridY < columnsCount && gridStates[gridY][gridX] == 0) {
                gridStates[gridY][gridX] = 1;
            }
        }
        else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
            for (int i = 0; i < columnsCount; i++) {
                for (int j = 0; j < rowsCount; j++) {
                    gridStates[i][j] = 0;
                }
            }
        }




        for (int i = 0; i < columnsCount; i++) {
            for (int j = 0; j < rowsCount; j++) {
                if (isDrawGrids) {
                    glBegin(GL_LINE_STRIP);
                    glVertex2f(-WIDTH/2 + j * cellWidth, HEIGHT/2 - i * cellHeight);
                    glVertex2f(-WIDTH/2 + j * cellWidth + cellWidth, HEIGHT/2 - i * cellHeight);
                    glVertex2f(-WIDTH/2 + j * cellWidth + cellWidth, HEIGHT/2 - i * cellHeight - cellHeight);
                    glVertex2f(-WIDTH/2 + j * cellWidth, HEIGHT/2 - i * cellHeight - cellHeight);
                    glVertex2f(-WIDTH/2 + j * cellWidth, HEIGHT/2 - i * cellHeight);
                    glEnd();
                }


                if (gridStates[i][j] == 1) {
                    glBegin(GL_POLYGON);
                    glVertex2f(-WIDTH/2 + j * cellWidth, HEIGHT/2 - i * cellHeight);
                    glVertex2f(-WIDTH/2 + j * cellWidth + cellWidth, HEIGHT/2 - i * cellHeight);
                    glVertex2f(-WIDTH/2 + j * cellWidth + cellWidth, HEIGHT/2 - i * cellHeight - cellHeight);
                    glVertex2f(-WIDTH/2 + j * cellWidth, HEIGHT/2 - i * cellHeight - cellHeight);
                    glEnd();




                    int direction = (rand() % 2) == 0 ? 1 : -1;
                    if (gridStates[i][j] == 1 && i < columnsCount - 1 && gridStates[i + 1][j] == 0) {
                        gridStates[i][j] = 0;
                        gridStates[i + 1][j] = 1;
                    }
                    else if (gridStates[i][j] == 1 && i < columnsCount - 1 && gridStates[i + 1][j] == 1) {
                        if (direction == 1 && j < rowsCount - 1 && gridStates[i + 1][j + 1] == 0) {
                            gridStates[i][j] = 0;
                            gridStates[i + 1][j + 1] = 1;
                        }
                        else if (direction == -1 && j > 0 && gridStates[i + 1][j - 1] == 0) {
                            gridStates[i][j] = 0;
                            gridStates[i + 1][j - 1] = 1;
                        }
                    }
                }
            }
        }



        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    glfwTerminate();
    return 0;
}