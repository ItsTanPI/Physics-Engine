#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include<math.h>
#include <vector>
#include "VectorMath.h"
#include "Renderer.h"

class CircleCollider
{
	float Radius;
	Vector2 Position;

public:
	static vector<CircleCollider*> Instances;
	static int Count;

	CircleCollider()
	{
		Instances.push_back(this);
		//cout << "added: " << this << endl;
		//cout << Instances.size() << endl;
		Count++;
		//cout << "I am Default" << endl;
	}

	CircleCollider(float Radius, Vector2 Position)
	{
		/*cout << "called" << endl;
		cout << this << endl;
		cout << endl;*/


		(*this).Radius = Radius;
		(*this).Position = Position;
		//cout << "I am nonDefault" << endl;
	}

	void UpdatePosition(Vector2 NewPos)
	{
		(*this).Position = NewPos;
		//cout << Position.x << ", " << Position.y << endl;
	}

	Vector2 Update()
	{
		//cout << Instances.size() << endl;
		
		for (int i = 0; i < Count; i++)
		{
			if (Instances[i] != this)
			{
				
				Vector2 DistVector = ((*this).Position - (*Instances[i]).Position).normalize();

				float Dist = ((*this).Position - (*Instances[i]).Position).magnitude();
				//cout << Position.x << ", " << Position.y << endl;
				//cout << (*Instances[i]).Position.x << ", " << (*Instances[i]).Position.y << endl << endl;

				//cout << Dist << endl;

				float totalRadius = (*this).Radius + (*Instances[i]).Radius;
				float diff = totalRadius - abs(Dist);
				if (Dist < totalRadius)
				{

					//cout << "Colliding: " << diff << endl;
					return (DistVector * (diff / 2.0f));
				}

			}

		}
		
		return Vector2(0, 0);
	}

	~CircleCollider()
	{
		//cout << "I was Called \n";
	}
};

int CircleCollider::Count = 0;
vector<CircleCollider*> CircleCollider::Instances = {};
