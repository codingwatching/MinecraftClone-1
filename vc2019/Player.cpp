#include "Player.h"

Player::Player(World * wrld):Entity(wrld)
{
	///* Load a standard Lua function from global table: */
	//lua_getglobal(lua.GetLuaState(), "print");

	///* Push an argument onto Lua C API stack: */
	//lua_pushstring(lua.GetLuaState(), "Hello C API!");

	///* Call Lua function with 1 argument and 0 results: */
	//lua_call(lua.GetLuaState(), 1, 0);
	world = wrld;

	JumpHeight = .30;
	speed = .1;
	gravity = .01;
	cursorSpeed = .0005;
	mDegree = 0;
	mDegree2 = 0;
	renderDist = 4;
	mViewCam.setEyePoint(ci::vec3(0,0,0));
	pause = false;
	IsChunkLoader = false;
	forward = false;
	backward = false;
	left = false;
	right = false;
	crouch = false;

	if (IsChunkLoader) {
		for (int i = 0; i < renderDist; i++)
		{
			for (int j = 0; j < renderDist; j++)
			{
				for (int k = 0; k < renderDist; k++)
				{
					world->LoadChunk(i + GetCurrentChunkPos().x, j + GetCurrentChunkPos().y, k + GetCurrentChunkPos().z);
				}
			}
		}
	}
}

ci::vec3 Player::GetCurrentChunkPos(){
	return ci::vec3(floor(pos.x / 16), floor(pos.y / 16), floor(pos.z / 16));
}
ci::vec3 Player::GetLastChunkPos(){
	return ci::vec3(floor(lastpos.x / 16), floor(lastpos.y / 16), floor(lastpos.z / 16));
}

ci::vec3 Player::GetCurrentPos() {
	return pos;
}
ci::vec3 Player::GetLastPos() {
	return lastpos;
}

ci::CameraPersp* Player::getCam()
{
	return &mViewCam;
}

void Player::KeyDown(ci::app::KeyEvent event)
{

	switch (event.getCode())
	{
	case ci::app::KeyEvent::KEY_ESCAPE:
		pause = !pause;
		break;
	case ci::app::KeyEvent::KEY_w:
			forward = true;
		
		break;
	case ci::app::KeyEvent::KEY_s:
			backward = true;
		
		break;
	case ci::app::KeyEvent::KEY_a:
			left = true;
		break;
	case ci::app::KeyEvent::KEY_d:
			right = true;
		break;
	case ci::app::KeyEvent::KEY_LSHIFT:
			velocity -= (mViewCam.getWorldUp()*JumpHeight);
		break;
	case ci::app::KeyEvent::KEY_LCTRL:
		speed = .4;
		break;
	case ci::app::KeyEvent::KEY_SPACE:
		if (canJump) {
			velocity += (mViewCam.getWorldUp() * JumpHeight);
			canJump = false;
		}
		break;
	default:
		break;
	}
}

void Player::KeyUp(ci::app::KeyEvent event)
{

	switch (event.getCode())
	{
	case ci::app::KeyEvent::KEY_w:
			forward = false;
		
		break;
	case ci::app::KeyEvent::KEY_s:
			backward = false;
		
		break;
	case ci::app::KeyEvent::KEY_a:
			left = false;
		
		break;
	case ci::app::KeyEvent::KEY_d:
			right = false;
		
		break;
	case ci::app::KeyEvent::KEY_LCTRL:
			speed=.1;
		break;
	default:
		break;
	}
}

void Player::MouseMove(ci::app::MouseEvent event)
{
	if (!pause) {
		//camera control
		ci::ivec2 pos = event.getPos();

		mDegree -= (pos.x -lastMousepos.x) * cursorSpeed;
		mDegree2 += (pos.y -lastMousepos.y) * (0);
		glm::mat4 m_mat4ViewMatrix = glm::mat4();

		m_mat4ViewMatrix = glm::rotate(m_mat4ViewMatrix, mDegree, ci::vec3(0.0f, 1.0f, 0.0f));

		m_mat4ViewMatrix = glm::rotate(m_mat4ViewMatrix, mDegree2, ci::vec3(m_mat4ViewMatrix[0][0], m_mat4ViewMatrix[0][1], m_mat4ViewMatrix[0][2]));

		m_mat4ViewMatrix = glm::translate(m_mat4ViewMatrix, mViewCam.getEyePoint());
		mViewCam.setOrientation(glm::quat(0, 0, 0, 0));

		//mDegree = event.getX();
		//mDegree2 = event.getY();
		lastMousepos = pos;
		if (pos.x > event.getWindow().get()->getCenter().x + 10 || pos.y > event.getWindow().get()->getCenter().y + 10 || pos.x < event.getWindow().get()->getCenter().x - 10 || pos.y < event.getWindow().get()->getCenter().y - 10) {
			SetCursorPos(event.getWindow().get()->getCenter().x + event.getWindow().get()->getPos().x, event.getWindow().get()->getCenter().y + event.getWindow().get()->getPos().y);
			lastMousepos = ci::ivec2(event.getWindow().get()->getCenter().x, event.getWindow().get()->getCenter().y);
		}
		
	}
}

void Player::Update()
{
	if (!pause) {
		lastpos = pos;
		super::Update();

		if (forward) {
			if (!pause) {
				pos.x += (mViewCam.getViewDirection().x * speed);
				pos.z += (mViewCam.getViewDirection().z * speed);
			}
		}
		if (backward) {
			if (!pause) {
				pos.x -= (mViewCam.getViewDirection().x * speed);
				pos.z -= (mViewCam.getViewDirection().z * speed);
			}
		}
		if (right) {
			if (!pause) {
				pos.z += (mViewCam.getViewDirection().x * speed);
				pos.x += (-mViewCam.getViewDirection().z * speed);
			}
		}
		if (left) {
			if (!pause) {
				pos.z -= (mViewCam.getViewDirection().x * speed);
				pos.x -= (-mViewCam.getViewDirection().z * speed);
			}
		}

		//camera control
		float X = mViewCam.getEyePoint().x + (1 * sin(mDegree) * cos(mDegree2));
		float Y = mViewCam.getEyePoint().y + (1 * sin(mDegree) * sin(mDegree2));
		float Z = mViewCam.getEyePoint().z + (1 * cos(mDegree));

		mViewCam.lookAt(ci::vec3(X, Y, Z));
		mViewCam.setEyePoint(ci::vec3(pos.x, pos.y + 2, pos.z));

		if (IsChunkLoader) {
			for (int i =-(renderDist/2); i < renderDist/2; i++)
			{
				for (int j = -(renderDist/2); j < renderDist/2; j++)
				{
					for (int k = -(renderDist/2); k < renderDist/2; k++)
					{
						world->LoadChunk(i + GetCurrentChunkPos().x, j + GetCurrentChunkPos().y, k + GetCurrentChunkPos().z);
					}
				}
			}
		}
	}
	lastFrame = time(0);
}
