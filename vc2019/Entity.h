#pragma once
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "World.h"
#include "Lua.h"

class Entity
{
protected:
	float JumpHeight;
	bool canJump;
	float gravity;
	float speed;
	bool pause;
	World* world;
	ci::vec3 boundingBox[8];
	LUA lua;
	ci::vec3 pos;
	ci::vec3 velocity;
	void Update();
	Entity(World* world);
};

