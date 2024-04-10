#pragma once

#include<iostream>
#include<cmath>

#define PI 3.14159265f

struct Vector2
{
    float x;
    float y;

    Vector2()
    {
        x = 0;
        y = 0;
    }

    Vector2(float x, float y)
    {
        (*this).x = x;
        (*this).y = y;
    }

    void setVector2(float x, float y)
    {
        (*this).x = x;
        (*this).y = y;
    }

    Vector2 operator+(Vector2& V)
    {
        Vector2 Temp;
        Temp.x = x + V.x;
        Temp.y = y + V.y;
        return Temp;
    }

    Vector2 operator-(Vector2& V)
    {
        Vector2 Temp;
        Temp.x = x - V.x;
        Temp.y = y - V.y;
        return Temp;
    }

    Vector2 operator*(float len)
    {
        Vector2 Temp;
        Temp.x = x * len;
        Temp.y = y * len;
        return Temp;
    }

    friend Vector2 operator*(float lhs, Vector2& rhs)
    {
        Vector2 Temp;
        Temp.x = rhs.x * lhs;
        Temp.y = rhs.y * lhs;
        return Temp;
    }

    Vector2 dot(Vector2 Vect)
    {
        return Vector2((Vect.x * x), (Vect.y * y));
    }

    float angle(Vector2 Vect)
    {
        float angle;
        Vector2 Dot = dot(Vect);
        float MagDot = Dot.magnitude();
        float MagThis = magnitude();
        float MagVect = Vect.magnitude();

        float CosInverse = MagDot / (MagThis * MagVect);

        angle = acos(CosInverse); //* (180.0f / PI);
        return angle;
    }

    float magnitude() const
    {
        float sum = (x * x) + (y * y);
        return sqrt(sum);
    }

    Vector2 normalize() const
    {
        float mag = magnitude();
        Vector2 Temp;
        Temp.x = x / mag;
        Temp.y = y / mag;
        return Temp;
    }

};

void Polygon(int sides, float Radius, float* Vertices, int* Indices)
{
    float angle;
    angle = (360.0f / sides) * PI/180.0f;
    float IndexAngle = angle;
    
    int Index = (sides * 2) + 2;

    Vertices[0] = 0.0f;
    Vertices[1] = 0.0f;
    
    for (int i = 2; i < Index; i+=2)
    {   
        Vertices[i] = sin(IndexAngle) * Radius;
        Vertices[i + 1] = cos(IndexAngle) * Radius;
        IndexAngle += angle;
    }


    for (int i = 0;i < sides * 3; i += 3)
    {
        if (i == (sides * 3) - 3)
        {
            Indices[i] = 0;
            Indices[i + 1] = (i / 3) + 1;
            Indices[i + 2] = 1;
        }
        else
        {
            Indices[i] = 0;
            Indices[i + 1] = (i / 3) + 1;
            Indices[i + 2] = (i / 3) + 2;
        }
    }
}
