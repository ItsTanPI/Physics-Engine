#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include<math.h>
#include <vector>

#include "VectorMath.h"
#include "Renderer.h"
#include "collision.h"


#include<iostream>
using namespace std;

class World
{
public:
	static Vector2 Gravity;
	World(){}
};

Vector2 World::Gravity = { 0.0 , 0.0 };

struct Options
{
	float Drag;
	float Mass;
	bool isStatic;
	Vector2 Force;

	Options()
	{
		Mass = 1.0f;
		Drag = 0.00f;
		isStatic = false;
		Force = { 0, 0 };
	}

	Options(float Mass, float Drag, bool IsSatic, Vector2 Force)
	{
		(*this).Mass = Mass;
		(*this).Drag = Drag;
		(*this).isStatic = IsSatic;
		(*this).Force = Force;
	}
};

class PointMass: public World
{

public:
	Vector2 Position;
	bool isStatic;
	Vector2 OldPosition;
protected:
	
	Vector2 Force;
	
	float Drag;
	float Mass;

public:
	PointMass()
	{
		Position = { 0, 0 };
		OldPosition = { 0, 0 };

		Mass = 0;
		Drag = 0;

		isStatic = true;

		Force = { 0, 0 };
	}

	PointMass(Vector2 Position, float Mass, float Drag, bool IsStatic)
	{
		(*this).Position = Position;
		(*this).OldPosition = Position;

		(*this).Mass = Mass;
		(*this).Drag = (1 - Drag);

		(*this).isStatic = IsStatic;

		Force = { 0 , 0 };
	}

	void AddForce(Vector2 Force)
	{
		Force = Force * 10000.0f;
		(*this).Force = (*this).Force + Force;
	}

	void Update(float dt)
	{
		if(!isStatic)
		{
			Vector2 Velocity = Position - OldPosition;

			Velocity = Velocity * Drag; 

			OldPosition = Position;



			Vector2 Acc = Gravity * (Mass);
			Vector2 ExtrAcc = Force * (1.0f / (Mass));


			Acc = Acc + ExtrAcc;

			Vector2 At = Acc * (dt * dt);
			Position = Position + Velocity + At;
		}
		Force = { 0, 0 };
	}

	void Bounce()
	{
		Vector2 Velovity = Position - OldPosition;

		if (Position.x < 0)
		{
			Position.x = 0;
			OldPosition.x = Position.x + Velovity.x;
			//Force = { 0, 0 };
		}
		else if(Position.x > 800)
		{
			Position.x = 800;
			OldPosition.x = Position.x + Velovity.x;
			//Force = { 0, 0 };
		}
		else if (Position.y < 0)
		{
			Position.y = 0;
			OldPosition.y = Position.y + Velovity.y;
		}
		else if(Position.y >800)
		{
			Position.y = 800;
			OldPosition.y = Position.y + Velovity.y;
		}
	}

	void ReturnVec(Vector2* Temp) const
	{
		*(Temp) = Position;
	}
};

class GameObject
{
private:
	Mesh MeshRenderer;
public:
	float Radius;
	int Sides;
	PointMass RigidBody;
	Vector2 Position;
	CircleCollider Collider;
	static int Count;

	GameObject() {}

	GameObject(const int Sides, const float Radius, Vector2 Position, Options opt = Options()) : Collider(Radius, Position)
	{
		//cout << Radius << endl;
		Count++;
		(*this).Sides = Sides;
		(*this).Radius = Radius;
		(*this).Position = Position;

		float* Vertices = new float[(*this).Sides * 2 + 2];
		int* Indexex = new int[(*this).Sides * 3];

		Polygon(Sides, Radius, Vertices, Indexex);

		Mesh TempMesh(Sides * 2 + 2, &(*Vertices), Sides * 3, &(*Indexex));
		MeshRenderer = TempMesh;

		MeshRenderer.Position(Position);


		PointMass TempMass(Position, opt.Mass, opt.Drag / 100, opt.isStatic);
		RigidBody = TempMass;
		RigidBody.AddForce(opt.Force);

		delete[] Vertices;
		delete[] Indexex;
	}

	void AddForce(Vector2 f)
	{
		RigidBody.AddForce(f);
	}

	void Update(float Dt)
	{

		//for (size_t i = 0; i < 6; i++)
		//{
		//	Vector2 pos;
		//	Vector2 Offset = Collider.Update();
		//	if (Offset.magnitude()==0)
		//	{
		//		break;
		//	}
		//	RigidBody.Position = RigidBody.Position + Offset;
		//	//RigidBody.OldPosition = RigidBody.OldPosition + Offset;
		//	//RigidBody.AddForce(Offset);
		//	RigidBody.ReturnVec(&pos);
		//	MeshRenderer.Position(pos);
		//	Position = pos;
		//	Collider.UpdatePosition(pos);

		//	
		//}
		Vector2 Offset = Collider.Update();
		RigidBody.AddForce(Offset);


		if (!RigidBody.isStatic)
		{
			Vector2 pos;
			RigidBody.Update(Dt);
			RigidBody.Bounce();
			RigidBody.ReturnVec(&pos);
			MeshRenderer.Position(pos);
			Position = pos;
		
		}
		Collider.UpdatePosition(Position);
	}

	void DrawThis()
	{
		MeshRenderer.Draw();
	}

};

int GameObject::Count = 0;


class SpringJoint : public World
{
private:
	GameObject* PointA;
	GameObject* PointB;

	Line LineRendere;
	
	bool Hide;
	float RestLength;
	float SpringConstant;

public:
	SpringJoint() {}

	SpringJoint(GameObject* PointA, GameObject* PointB, float RestLength = 100.0f, float SpringConstant = 0.1f, bool Hide = false, float Thickness = 3.0f)
	{
		(*this).PointA = PointA;
		(*this).PointB = PointB;
		(*this).RestLength = RestLength;
		(*this).SpringConstant = SpringConstant/100.0f;
		(*this).Hide = Hide;

		Line TempLine(&((*PointA).Position), &((*PointB).Position), Thickness);
		LineRendere = TempLine;

	}
	void Update()
	{
		Vector2 Direction = (*PointB).RigidBody.Position - (*PointA).RigidBody.Position;

		float displacment = Direction.magnitude() - RestLength;
		Direction = Direction.normalize();
		Vector2 Force = Direction * displacment * SpringConstant;

		(*PointA).AddForce(Force * 0.99f);
		(*PointB).AddForce(Force * -0.99f);
	}

	void DrawThis()
	{
		if (!Hide)
		{
			LineRendere.Draw();
		}
	}

};


class FixedJoint : public World
{
private:
	GameObject* PointA;
	GameObject* PointB;

	Line LineRendere;

	float RestLength;
	bool Hide;
public:
	FixedJoint() {}
	

	FixedJoint(GameObject* PointA, GameObject* PointB, float RestLength = 100.0f, bool Hide = false, float Thickness = 3.0f)
	{
		(*this).PointA = PointA;
		(*this).PointB = PointB;
		(*this).RestLength = (RestLength>0)? RestLength: 0.01f;
		(*this).Hide = Hide;

		Line TempLine(&((*PointA).Position), &((*PointB).Position), Thickness);
		LineRendere = TempLine;
		
	}

	void Update()
	{
		Vector2 Distance = (*PointB).RigidBody.Position - (*PointA).RigidBody.Position;
		float Length = Distance.magnitude();

		float Difference = RestLength - Length;

		//cout << Difference << endl;

		float percent = (Difference / Length) / 2.0f;

		Vector2 Offset = { Distance.x * percent, Distance.y * percent };

		//cout << Offset.x << ", " << Offset.y << endl;

		if (!(*PointA).RigidBody.isStatic)
		{
			(*PointA).RigidBody.Position = (*PointA).RigidBody.Position - Offset;
			(*PointA).RigidBody.OldPosition = (*PointA).RigidBody.OldPosition - Offset;
		}
		
		if (!(*PointB).RigidBody.isStatic)
		{
			(*PointB).RigidBody.Position = (*PointB).RigidBody.Position + Offset;
			(*PointA).RigidBody.OldPosition = (*PointA).RigidBody.OldPosition + Offset;
		}
		
	}
	void DrawThis()
	{
		if (!Hide)
		{
			LineRendere.Draw();
		}
	}
};



