#pragma once


#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include<math.h>
#include <vector>
#include "VectorMath.h"
#include "Renderer.h"
#include "Verlet.h"


template <const int shape>
class Shapes
{
public:

    float RD;
    Vector2 force;


    GameObject Holder;
    Vector2 SendForce;
    float X;
    float Y;

    //const int shape = 4;
    float dmp;
    GameObject List[shape];
    SpringJoint Center[shape];

    SpringJoint ClockSpring[shape];
    SpringJoint AntiClockSpring[shape];
    FixedJoint ClockFix[shape];

public:

    Shapes() : X(400), Y(400)
    {
        force = { rand() % 10.0f, rand() % 10.0f};
        RD = 25;
        dmp = 0.5f;
        GameObject Temp(4, (RD - 8), Vector2(X, Y), Options(1, 0.5f, false, force));
        Holder = Temp;

        delete Temp;
        float angle;
        angle = (360.0f / shape) * PI / 180.0f;
        float IndexAngle = angle;

        for (int i = 0; i < shape; i++)
        {
            Vector2 Position(X + (sin(IndexAngle) * RD), Y + cos(IndexAngle) * RD);
            GameObject Temp(4, 3, Position, Options(1, 0.5f, false, force));

            SpringJoint TempSpring(&Holder, &List[i], RD, 100.0f, true);
            Center[i] = TempSpring;
            delete TempSpring;

            List[i] = Temp;
            IndexAngle += angle;
        }

        for (int i = 0; i < shape; i++)
        {
            if (i >= shape - 2)
            {
                SpringJoint CTempSpring(&List[i], &List[abs(shape - 2 - i)], (List[i].RigidBody.Position - List[abs(shape - 2 - i)].RigidBody.Position).magnitude(), dmp, true);
                ClockSpring[i] = CTempSpring;
            }
            else
            {

                SpringJoint CTempSpring(&List[i], &List[i + 2], (List[i].RigidBody.Position - List[i + 2].RigidBody.Position).magnitude(), dmp, true);
                ClockSpring[i] = CTempSpring;

            }

            /*if (i < 2)
            {
                SpringJoint ACTempSpring(&List[i], &List[shape - 2 + i], (List[i].RigidBody.Position - List[shape - 2 + i].RigidBody.Position).magnitude(), dmp, true);
                AntiClockSpring[i] = ACTempSpring;
            }
            else
            {
                SpringJoint ACTempSpring(&List[i], &List[i - 2], (List[i].RigidBody.Position - List[i - 2].RigidBody.Position).magnitude(), dmp, true);
                AntiClockSpring[i] = ACTempSpring;
            }*/

            if (i != shape - 1)
            {
                FixedJoint JointA(&List[i], &List[i + 1], (List[i].RigidBody.Position - List[i + 1].RigidBody.Position).magnitude());
                ClockFix[i] = JointA;
            }
            else
            {
                FixedJoint JointA(&List[i], &List[0], (List[i].RigidBody.Position - List[0].RigidBody.Position).magnitude());
                ClockFix[i] = JointA;
            }
        }
    }

    Shapes(float x, float y, bool isStatic = false): X(x), Y(y)
    {
        force = { (rand() % 10)* 1.0f, (rand() % 10) * 1.0f };
        X = x;
        Y = y;
        RD = 25;
        dmp = 0.5f;
        GameObject Temp(4, (RD - 8), Vector2(X, Y), Options(1, 0.5f, isStatic, force));
        Holder = Temp;

        float angle;
        angle = (360.0f / shape) * PI / 180.0f;
        float IndexAngle = angle;

        for (int i = 0; i < shape; i++)
        {
            Vector2 Position(X + (sin(IndexAngle) * RD), Y + cos(IndexAngle) * RD);
            GameObject Temp(4, 3, Position, Options(1, 0.5f, isStatic, force));

            SpringJoint TempSpring(&Holder, &List[i], RD, 100.0f, true);
            Center[i] = TempSpring;

            List[i] = Temp;
            IndexAngle += angle;
        }

        for (int i = 0; i < shape; i++)
        {
            if (i >= shape - 2)
            {
                SpringJoint CTempSpring(&List[i], &List[abs(shape - 2 - i)], (List[i].RigidBody.Position - List[abs(shape - 2 - i)].RigidBody.Position).magnitude(), dmp, true);
                ClockSpring[i] = CTempSpring;
            }
            else
            {

                SpringJoint CTempSpring(&List[i], &List[i + 2], (List[i].RigidBody.Position - List[i + 2].RigidBody.Position).magnitude(), dmp, true);
                ClockSpring[i] = CTempSpring;

            }

            /*if (i < 2)
            {
                SpringJoint ACTempSpring(&List[i], &List[shape - 2 + i], (List[i].RigidBody.Position - List[shape - 2 + i].RigidBody.Position).magnitude(), dmp, true);
                AntiClockSpring[i] = ACTempSpring;
            }
            else
            {
                SpringJoint ACTempSpring(&List[i], &List[i - 2], (List[i].RigidBody.Position - List[i - 2].RigidBody.Position).magnitude(), dmp, true);
                AntiClockSpring[i] = ACTempSpring;
            }*/

            if (i != shape - 1)
            {
                FixedJoint JointA(&List[i], &List[i + 1], (List[i].RigidBody.Position - List[i + 1].RigidBody.Position).magnitude());
                ClockFix[i] = JointA;
            }
            else
            {
                FixedJoint JointA(&List[i], &List[0], (List[i].RigidBody.Position - List[0].RigidBody.Position).magnitude());
                ClockFix[i] = JointA;
            }
        }
    }


    void Update(float deltatime)
    {
        Holder.Update(deltatime);
        
        for (int i = 0; i < shape; i++)
        {
            List[i].Update(deltatime);
            Center[i].Update();
            ClockSpring[i].Update();
            //AntiClockSpring[i].Update();

            ClockFix[i].Update();
            //AntiClockFix[i].Update();
            List[i].AddForce(SendForce);
        }
        //cout << "called" << endl;
    }

    void Draw()
    {
        for (int i = 0; i < shape; i++)
        {
            //Holder.DrawThis();
            List[i].DrawThis();
            Center[i].DrawThis();
            //ClockSpring[i].Update();
            //AntiClockSpring[i].Update();

            ClockFix[i].DrawThis();
            //AntiClockFix[i].Update();
            //List[i].AddForce(SendForce);
        }
    }

    void AddForce(Vector2 Force)
    {
        SendForce = Force;
    }
};