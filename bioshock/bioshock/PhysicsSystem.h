#pragma once

#include "ECS.h"
#include "PhysicsBody.h"
#include "Timer.h"
#include "Shader.h"


struct Box
{
public:
	vec3 m_bottomLeft; 
	vec3 m_bottomRight; 
	vec3 m_topLeft;
	vec3 m_topRight;
	vec3 m_center;
};

struct Circle
{
public:
	vec3 m_center;
	float m_radius; 
};

namespace PhysicsSystem
{
	//Update the system
	void Update(entt::registry * reg, b2World& world); 

	//Runs the collisions
	void Run(b2World& world); 

	//Run our Box-Box Collision detection system
	bool BoxBoxCollision(std::pair<PhysicsBody&, Box> group1, std::pair<PhysicsBody&, Box> group2);

	static Shader physicsDrawShader; 

	//Initalizes the system 
	void Init(); 

	//Draw all entities with physics bodies
	//*only if the static "m_drawBodies" is true
	void Draw(entt::registry* reg); 
}