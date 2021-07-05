#pragma once
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include <Windows.h>
#include "Entity.h"
#include "Util.h"
#include "World.h"
class Player :
    public Entity
{
	typedef Entity super;
	ci::CameraPersp					mViewCam;
	float mDegree;
	float mDegree2;
	float cursorSpeed;

	ci::vec3 lastpos;
	ci::ivec2 lastMousepos;
	time_t lastFrame;
	int renderDist;

	bool IsChunkLoader;
	bool forward;
	bool backward;
	bool left;
	bool right;
	bool crouch;

public:
	Player(World * world);
	ci::vec3 GetCurrentChunkPos();
	ci::vec3 GetLastChunkPos();
	ci::vec3 GetCurrentPos();
	ci::vec3 GetLastPos();
	ci::CameraPersp* getCam();
	void KeyDown(ci::app::KeyEvent event);
	void KeyUp(ci::app::KeyEvent event);
	void MouseMove(ci::app::MouseEvent event);
	void Update();
};

