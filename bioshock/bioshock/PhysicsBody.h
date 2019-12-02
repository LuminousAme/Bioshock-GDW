#pragma once

#include <GL/glew.h>
#include <Box2D/Box2D.h>
#include "JSON.h"
#include "Vector.h"
#include "VertexManager.h"
#include "EntityIdentifier.h"
#include "Transform.h"

enum class BodyType
{
	BOX,
	CIRCLE,

	NUM_TYPES
};

struct CollisionIDs
{
public:
	//Gets different IDs
	static unsigned int Player(); 
	static unsigned int Environment(); 
	static unsigned int Enemy(); 
private:
	//Holds the different IDs 
	static unsigned int m_playerID; 
	static unsigned int m_environmentID; 
	static unsigned int m_enemyID; 
};

class PhysicsBody
{
public:
	//default constructor
	PhysicsBody() {};
	//Constructs a circle collider 
	PhysicsBody(b2Body* body, float radius, vec2 centerOffset, bool isDynamic); 
	//Constructs a box collider 
	PhysicsBody(b2Body* body, float width, float height, vec2 centerOffSet, bool isDynamic); 
	//Destroys the physicsBody
	~PhysicsBody();

	//Update physics stuffs
	void Update(Transform* trans); 

	//Apply a force to the physics body
	void ApplyForce(vec3 force); 

	//Initializes body for drawing 
	void InitBody(); 

	//Draws body 
	void DrawBody(); 

	//Getters 
	//Get the box2D physics body 
	b2Body* GetBody() const; 
	//Get position of the body 
	b2Vec2 GetPosition() const; 

	//gets current force 
	vec3 GetForce() const;
	//gets the current acceleration 
	vec3 GetAcceleration() const; 
	//Gets max velocity for each indiviual axis 
	float GetMaxVelo() const; 
	//Gets current velocity 
	vec3 GetVelocity() const; 
	//Gets the coefficient of friction
	float GetFriction() const; 

	//Gets the current gravitational acceleration 
	static vec3 GetGravityAcceleration(); 
	//Gets if gravity is applied to this object 
	bool GetGravity() const; 

	//Gets the mass of the physics body 
	float GetMass() const; 

	//Gets the body type enum
	BodyType GetBodyType() const; 
	//Gets the center offset of the body (0,0 means corner are relative to acutal sprite) 
	vec2 GetCenterOffset() const; 
	//Gets the corners of the body 
	vec2 GetBottomLeft() const; 
	vec2 GetBottomRight() const; 
	vec2 GetTopLeft() const; 
	vec2 GetTopRight() const; 
	//Gets the width of the physics body 
	float GetWidth() const; 
	//Gets the height of the physics body 
	float GetHeight() const; 
	//Gets the radius of the physics body 
	float GetRadius() const; 

	//Gets this body's type
	unsigned int GetBodyID() const; 
	//what types does this body collied with 
	unsigned int GetCollidedID() const; 

	//Get wheter or not the body moves (is dynamic) 
	bool GetDynamic() const;

	//Get wheter or not we are currently drawing our physics bodies
	static bool GetDraw(); 

	//Setters 
	//Sets the pointer to the box2D body 
	void SetBody(b2Body* body);
	//Sets position (just sets the variable, doesn't actually set the position)
	void SetPosition(b2Vec2 bodyPos); 

	//Sets applied force 
	void SetForce(vec3 force);
	//Sets the accleration
	void SetAcceleration(vec3 acel); 
	//Sets the max velocity 
	void SetMaxVelo(float velo);
	//Sets the current velocity 
	void SetVelocity(vec3 velo); 

	//Sets the coefficient of friction 
	void SetFriction(float fric); 

	//Sets the gravitational acceleration 
	static void SetGravityAcceleration(vec3 grav); 
	//Sets wheter this body is affected by gravity 
	void SetGravity(bool grav); 

	//Sets the mass of the object 
	void SetMass(float mass); 

	//Set bodytypes
	void SetBodyType(BodyType type); 
	//Sets the offset of the center, if 0,0 then the corners are relative to the sprite
	void SetCenterOffset(vec2 cent); 
	//Sets the corners of the body 
	void SetBottomLeft(vec2 BL); 
	void SetBottomRight(vec2 BR); 
	void SetTopLeft(vec2 TL); 
	void SetTopRigth(vec2 TR); 
	//Sets the width of the body 
	void SetWidth(float width); 
	//Setst the height of the body
	void SetHeight(float height); 
	//Sets the radius of the entity
	void SetRadius(float radius); 

	//Set Body ID 
	void SetBodyID(unsigned int bodyID); 
	//Set Collide ID
	void SetCollideID(unsigned int collideID); 

	//Sets if the object moves (dynamic) 
	void SetDynamic(bool isDynamic); 

	//Sets wheter the bodies are being drawn 
	static void SetDraw(bool drawBodies); 
private: 
	//Do you draw the bodies?
	static bool m_drawBodies;

	//Physics body drawing sutff
	GLuint m_vao = GL_NONE;
	GLuint m_vboPos = GL_NONE;

	//The acutal box2D body
	b2Body* m_body = nullptr; 
	b2Vec2 m_position = b2Vec2(0.f, 0.f); 

	//The applied force 
	vec3 m_appliedForce = vec3(0.f, 0.f, 0.f); 
	//The frictional force 
	vec3 m_frictionForce = vec3(0.f, 0.f, 0.f); 
	//Stores the net force 
	vec3 m_netForce = vec3(0.f, 0.f, 0.f); 
	//Stores the acceleration
	vec3 m_acceleration = vec3(0.f, 0.f, 0.f); 
	//max velocity in each axis 
	float m_maxVelo = 80.f; 
	//Stores the max velocity 
	vec3 m_velocity = vec3(0.f, 0.f, 0.f); 

	//Coefficient of friction
	float m_friction = 0.35f; 

	//The acceleration due to gravity * mass 
	static vec3 m_gravityAcceleration; 
	//Is gravity being applied to this body 
	bool m_applyGravity = false; 

	//mass of the body 
	float m_mass = 1.f; 

	//Body type 
	BodyType m_bodyType = BodyType::CIRCLE; 
	//How far from the center of the sprite is it 
	vec2 m_centerOffset = vec2(); 
	//each corner 
	vec2 m_bottomLeft = vec2(); 
	vec2 m_bottomRight = vec2(); 
	vec2 m_topLeft = vec2(); 
	vec2 m_topRight = vec2(); 
	//Width and height of the body 
	float m_width = 0.f; 
	float m_height = 0.f; 
	//radius of the body 
	float m_radius = 0.f; 

	//the type of this physics body 
	unsigned int m_bodyID; 
	//the types of bodies this body collides with
	unsigned int m_collideID;

	//can the object move 
	bool m_dynamic = false; 
};

//Sends body TO json file
inline void to_json(nlohmann::json& j, const PhysicsBody& phys)
{
	//Position
	j["BodyPosition"] = { phys.GetPosition().x, phys.GetPosition().y }; 
	//stores the bodytype
	j["BodyType"] = phys.GetBodyType(); 
	//Center offset
	j["CenterOffset"] = { phys.GetCenterOffset().x, phys.GetCenterOffset().y };
	//Stores corners
	j["BottomLeft"] = { phys.GetBottomLeft().x, phys.GetBottomLeft().y }; 
	j["BottomRight"] = { phys.GetBottomRight().x, phys.GetBottomRight().y }; 
	j["TopLeft"] = { phys.GetTopLeft().x, phys.GetTopLeft().y }; 
	j["TopRight"] = { phys.GetTopRight().x, phys.GetTopRight().y }; 
	//width and height 
	j["Width"] = phys.GetWidth(); 
	j["Height"] = phys.GetHeight(); 
	//Radius
	j["Radius"] = phys.GetRadius(); 

	//Max velocity
	j["MaxVelo"] = phys.GetMaxVelo(); 

	//Friction strenght 
	j["Friction"] = phys.GetFriction(); 

	//Gravity enabled?
	j["Gravity"] = phys.GetGravity(); 

	//Collision type (body ID) and what this body collides *with*
	j["BodyID"] = phys.GetBodyID(); 
	j["CollideID"] = phys.GetCollidedID(); 

	//Wheter the object is moving 
	j["IsDynamic"] = phys.GetDynamic(); 
}

//Reads body in FROM json file
inline void from_json(const nlohmann::json& j, PhysicsBody& phys)
{
	//Sets position
	phys.SetPosition(b2Vec2(j["BodyPosition"][0], j["BodyPosition"][1])); 
	//Sets body type
	phys.SetBodyType(j["BodyType"]); 
	//Set the center offset
	phys.SetCenterOffset(vec2(j["CenterOffset"][0], j["CenterOffset"][1])); 
	//Sets the corners
	phys.SetBottomLeft(vec2(j["BottomLeft"][0], j["BottomLeft"][1])); 
	phys.SetBottomRight(vec2(j["BottomRight"][0], j["BottomRight"][1])); 
	phys.SetTopLeft(vec2(j["TopLeft"][0], j["TopLeft"][1]));
	phys.SetTopRigth(vec2(j["TopRight"][0], j["TopLeft"][1])); 
	//Set the width and height 
	phys.SetRadius(j["Radius"]); 

	//Sets Max velocity
	phys.SetMaxVelo(j["Maxvelo"]); 

	//Sets friction strenght 
	phys.SetFriction(j["Friction"]); 

	//Set does gravity affect this body?
	phys.SetGravity(j["Gravity"]); 

	//Set collision type (body ID) and what this body collides *with*
	phys.SetBodyID(j["BodyID"]); 
	phys.SetCollideID(j["CollideID"]); 

	//Set wheter the object is moving 
	phys.SetDynamic(j["IsDynamic"]); 
}