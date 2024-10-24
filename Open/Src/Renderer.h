#pragma once


#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include<math.h>
#include <vector>

#include "VectorMath.h"

using namespace std;

class Screen
{
public:
    static int X;
    static int Y;

public:
    Screen() {}
    Screen(int X, int Y)
    {
        (*this).X = X / 2;
        (*this).Y = Y / 2;
    }

    void SetScreen(int X, int Y)
    {
        (*this).X = X/2;
        (*this).Y = Y/2;
    }

    void ScrToNorm(float* Vertices, int Size) const
    {
        for (int i = 0; i < Size; i++)
        {
            if (i%2 == 0)
            {
                Vertices[i] = (Vertices[i]-X)/X;
            }
            else
            {
                Vertices[i] = (Vertices[i] - Y)/ Y;
            }
            
        }
    }
};
int Screen::X = 0;
int Screen::Y = 0;


class Mesh: public Screen
{
private:

    vector<float> Vertices;
    unsigned int VerticesId;
    int VerticesLen;

    vector<int> Indices;
    unsigned int IndicesId;
    int IndicesLen;


public:

    Mesh()
    {
        glGenBuffers(1, &VerticesId);
        glGenBuffers(1, &IndicesId);
    }


    Mesh(int Vsize, float* Vertices,int Isize,  int* Indices) :Vertices(Vsize), Indices(Isize)
    {
        
        VerticesId = 0;
        IndicesId = 0;
        VerticesLen = Vsize;
        IndicesLen = Isize;

        for (int i = 0; i < VerticesLen; i++)
        {
            (*this).Vertices[i] = Vertices[i];
            //cout << (*this).Vertices[i] << endl;
        }

        for (int i = 0; i < IndicesLen; i++)
        {
            (*this).Indices[i] = Indices[i];
            //cout << (*this).Indices[i] << endl;
        }
        glGenBuffers(1, &VerticesId);
        glGenBuffers(1, &IndicesId);
    }
 

    void Position(Vector2 Offset)
    {
        for (int i = 2; i < VerticesLen;  i += 2)
        {
            float lenX = Vertices[i] - Vertices[0];
            float lenY = Vertices[i + 1] - Vertices[1];

            Vertices[i] = lenX + Offset.x;
            Vertices[i+1] = lenY + Offset.y;
        }

        Vertices[0] = Offset.x;
        Vertices[1] = Offset.y;

        //cout << Vertices[0] << " , " << Vertices[1] << endl;
    }


    void BoundVertices()
    {
       
        glBindBuffer(GL_ARRAY_BUFFER, VerticesId);

        float* Array;
        Array = new float[VerticesLen];
        
        for (int i = 0; i < VerticesLen; i++)
        {
           Array[i] = (*this).Vertices[i];  
        }

        ScrToNorm(Array, VerticesLen);

        glBufferData(GL_ARRAY_BUFFER, VerticesLen * sizeof(float), Array, GL_DYNAMIC_DRAW);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
        glEnableVertexAttribArray(0);
        delete[] Array;

    }

    void BoundIndices()
    {
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndicesId);

        int* Array;
        Array = new int[IndicesLen];
        
        for (int i = 0; i < IndicesLen; i++)
        {
            Array[i] = (*this).Indices[i];
            //cout << Array[i] << endl;
        }
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, IndicesLen * sizeof(int), Array, GL_DYNAMIC_DRAW);
        delete[] Array;
    }


    void Draw()
    {
        BoundVertices();
        BoundIndices();
        glDrawElements(GL_TRIANGLES, IndicesLen, GL_UNSIGNED_INT, nullptr);
    }
};


class Line: public Screen
{
private:

    Vector2* PointA;
    Vector2* PointB;
    float Thickness;

    float Vertices[8];
    unsigned int VerticesId;
    int VerticesLen;

    int Indices[6];
    unsigned int IndicesId;
    int IndicesLen;


public:
    Line()
    {}

    Line(Vector2* PointA, Vector2* PointB, float Thickness = 5.0f): Indices {0, 1, 2, 0, 3, 2},  Vertices{ 0, 0, 0, 0, 0, 0, 0, 0}
    {
        (*this).PointA = PointA;
        (*this).PointB = PointB;
        (*this).Thickness = Thickness;

        VerticesLen = 8;
        IndicesLen = 6;


        VerticesId = 0;
        IndicesId = 0;

        glGenBuffers(1, &VerticesId);
        glGenBuffers(1, &IndicesId);
    }

    void Update()
    {
        Vector2 dist = (*PointB) - (*PointA);
        Vector2 Norm = dist.normalize();
          

        Vertices[0] = (*PointA).x + (Thickness * Norm.y);
        Vertices[1] = (*PointA).y + (Thickness * -Norm.x);

        Vertices[2] = (*PointB).x + (Thickness * Norm.y);
        Vertices[3] = (*PointB).y + (Thickness * -Norm.x);

        Vertices[6] = (*PointA).x - (Thickness * Norm.y);
        Vertices[7] = (*PointA).y - (Thickness * -Norm.x);

        Vertices[4] = (*PointB).x - (Thickness * Norm.y);
        Vertices[5] = (*PointB).y - (Thickness * -Norm.x);
    }


    void BoundVertices()
    {
        glBindBuffer(GL_ARRAY_BUFFER, VerticesId);

        float* Array;
        Array = new float[VerticesLen];
        
        for (int i = 0; i < VerticesLen; i++)
        {
           Array[i] = (*this).Vertices[i];  
        }

        ScrToNorm(Array, VerticesLen);

        glBufferData(GL_ARRAY_BUFFER, VerticesLen * sizeof(float), Array, GL_DYNAMIC_DRAW);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
        glEnableVertexAttribArray(0);
        delete[] Array;
        

    }

    void BoundIndices()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndicesId);

        int* Array;
        Array = new int[IndicesLen];
        
        for (int i = 0; i < IndicesLen; i++)
        {
            Array[i] = (*this).Indices[i];
            //cout << Array[i] << endl;
        }
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, IndicesLen * sizeof(int), Array, GL_DYNAMIC_DRAW);
        delete[] Array;
        
    }


    void Draw()
    {
        Update();
        BoundVertices();
        BoundIndices();
        glDrawElements(GL_TRIANGLES, IndicesLen, GL_UNSIGNED_INT, nullptr);
    }
};