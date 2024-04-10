#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <cstdio>
#include <string>
#include <ctime>
#include <chrono>
#include <cmath>
#include <iostream>
#include <thread>

#include "Renderer.h"
#include "VectorMath.h"
#include "Verlet.h"
#include "Shapes.h"
#include "collision.h"
Vector2 SendForce;
Vector2 space;

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) 
{
    if (key == GLFW_KEY_UP && action == GLFW_PRESS) 
    {
        SendForce = { 0 , 5 };
    }
    else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
    {
        SendForce = { 0 , -5 };
    }
    else if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
    {
        SendForce = { 3 ,0 };
    }
    else if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
    {
        SendForce = { -3 ,0 };
    }
    else if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
    {
        space = { 0 , 5 };
    }

}


int main(void)
{    
    Screen Window(800, 800);
    World::Gravity = { 0, -500.0f };
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(Window.X * 2 , Window.Y * 2, "Mesh", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwSetKeyCallback(window, keyCallback);
    
    glfwMakeContextCurrent(window);

    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        return 1;
    }
    fprintf(stdout, "GLEW version: %s\n", glewGetString(GLEW_VERSION));
    fprintf(stdout, "GL version: %s\n", glGetString(GL_VERSION));


    //________________________________________________________________________________________________________
    
    

    //GameObject FixA(32, 10, Vector2(300, 600), Options(1, 0.1f, true, Vector2(0, 0)));
    //GameObject FixB(32, 10, Vector2(500, 600), Options(1, 0.1f, true, Vector2(0, 0)));



    //GameObject A(32, 2, Vector2(400, 400) ,Options(1, 0.5f, false, Vector2(-00, 00)));
    //GameObject B(32, 2, Vector2(500, 400), Options(1, 0.5f, false, Vector2(-00, 00)));
    //GameObject C(32, 2, Vector2(500, 300), Options(1, 0.5f, false, Vector2(-00, 00)));
    //GameObject D(32, 2, Vector2(400, 300), Options(1, 0.5f, false, Vector2(-00, 00)));

   
    //FixedJoint JointA(&A, &B, 100.0f);//, 100.0f);
    //FixedJoint JointB(&B, &C, 100.0f);//, 100.0f);
    //FixedJoint JointC(&C, &D, 100.0f);//, 100.0f);
    //FixedJoint JointD(&D, &A, 100.0f);//, 100.0f);
    //FixedJoint JointAC(&A, &C, (A.RigidBody.Position - C.RigidBody.Position).magnitude(), true);
    //FixedJoint JointBD(&B, &D, (B.RigidBody.Position - D.RigidBody.Position).magnitude(), true);

    //SpringJoint SpringA(&FixA, &A, 150.0, 10.0f);
    //SpringJoint SpringB(&FixB, &B, 150.0, 10.0f);
    //

    Shapes<4> circle(400, 400);

    Shapes<4> objs[8] = {Shapes<4>(300, 400),
                          Shapes<4>(rand() % 701 + 100, rand() % 701 + 100),
                          Shapes<4>(rand() % 701 + 100, rand() % 701 + 100),
                          Shapes<4>(rand() % 701 + 100, rand() % 701 + 100),

                          Shapes<4>(rand() % 701 + 100, rand() % 701 + 100),
                          Shapes<4>(rand() % 701 + 100, rand() % 701 + 100),
                          Shapes<4>(rand() % 701 + 100, rand() % 701 + 100),
                          Shapes<4>(rand() % 701 + 100, rand() % 701 + 100),
                      };

   // cout << CircleCollider::Count << endl;

   // std::vector<std::thread> threads;
    //A.AddForce(Vector2(0, 30));   


    SpringJoint spring(&circle.Holder, &objs[0].Holder, 200, 1.0f);

    

  /*  for (size_t i = 0; i < 30; i++)
    {
        objs[i].Update(deltatime);
        objs[i].AddForce(SendForce);
    }*/

    //cout << "Done" << endl;

    bool Flip = true;


    float deltatime = 6.9f / 1000.0f;

    while (!glfwWindowShouldClose(window))
    {
        //glTranslatef(-0.001f, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT);
        
        
      /*FixA.Update(deltatime);
        FixB.Update(deltatime);*/



        /*A.Update(deltatime);
        B.Update(deltatime);
        C.Update(deltatime);
        D.Update(deltatime);

        JointA.Update();
        JointB.Update();
        JointC.Update();
        JointD.Update();
        JointAC.Update();
        JointBD.Update();

        A.AddForce(SendForce);
        B.AddForce(SendForce);
        C.AddForce(SendForce);
        D.AddForce(SendForce);

        A.DrawThis();
        B.DrawThis();
        C.DrawThis();
        D.DrawThis();

        JointA.DrawThis();
        JointB.DrawThis();
        JointC.DrawThis();
        JointD.DrawThis();

        circle.Update(deltatime);
        circle.AddForce(SendForce);
        circle.Draw();*/

        //SpringA.Update();
        //SpringB.Update();

        //objs.Update(deltatime);

        /*threads.clear();

        auto threadFunc = [&](size_t index) 
        {
            objs[index].Update(deltatime);
            objs[index].AddForce(SendForce);
        };

        for (size_t i = 0; i < 30; ++i) 
        {
            threads.emplace_back(threadFunc, i);
        }

        for (auto& thread : threads) 
        {
            thread.join();
        }*/
        if (rand() % 1000 == 53)
        {
            //space = { (rand() % 5) * 1.0f, (rand() % 5) * 1.0f,};
        }
        
       for (size_t i = 0; i < 8; i++)
        {
            objs[i].Update(deltatime);
            objs[i].AddForce(space * (rand() % 2));
            
        }
        circle.Update(deltatime);
        circle.AddForce(SendForce);

        //spring.Update();
        //spring.DrawThis();
        for (size_t i = 0; i < 8; i++)
        {
            objs[i].Draw();
        }
        circle.Draw();


        SendForce = { 0, 0 };
        space = { 0, 0 };

        glfwSwapBuffers(window);
        glfwPollEvents();


        
    }   

    glfwTerminate();
    return 0;
}