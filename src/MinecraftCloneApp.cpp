#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Fbo.h"
#include "cinder/gl/Batch.h"
#include "cinder/CinderImGui.h"
#include "cinder/CameraUi.h"
#include "../vc2019/World.h"
#include <math.h>
#include "../vc2019/Player.h"
#include "Resources.h"
#include "../vc2019/Util.h"
#include <time.h>

using namespace ci;
using namespace ci::app;
using namespace std;

class MinecraftCloneApp : public App {
  public:
	void setup() override;
	void keyDown(KeyEvent event) override;
	void keyUp(KeyEvent event) override;
	void mouseDown( MouseEvent event ) override;
	void mouseMove(MouseEvent event);
	void mouseDrag(MouseEvent event);
	void update() override;
	void setDefaultValues();
	void draw() override;

	World world;

	CameraUi					mCamUi;
	CameraPersp					mViewCam;
	// params for the main camera
	float						mRadius;
	float						mDegree;
	float						mDegree2;
	float						mHeight;
	vec3						mLookAt;
	float						mFov;
	float						mAspectRatio;
	float						mNearPlane;
	float						mFarPlane;
	vec2						mLensShift;
	ivec2						mLastMousePos;

	gl::BatchRef		mCube;
	gl::TextureRef		mTexture;
	gl::GlslProgRef		mGlsl;
	time_t lastFrame;

	Player p = Player(&world);
};

void MinecraftCloneApp::setup()
{
	//custom cursor
	//HCURSOR Cursor = LoadCursor(NULL, MAKEINTRESOURCE(IDI_CURSOR1));
	//SetCursor(Cursor);
	//HWND nativeWindow = (HWND)getWindow()->getNative();
	//SetClassLongPtr(nativeWindow, GCLP_HCURSOR, reinterpret_cast<LONG_PTR>(Cursor));

	hideCursor();

	srand(time(0));
	//auto img = loadImage(loadAsset("../resources/checkerboard.jpg"));
	//mTexture = gl::Texture::create(img);
	//mTexture->bind();

	//auto shader = gl::ShaderDef().texture().lambert();
	//mGlsl = gl::getStockShader(shader);
	//auto cube = geom::Cube();
	//mCube = gl::Batch::create(cube, mGlsl);

	gl::enableDepthRead();
	gl::enableDepthWrite();
	gl::enableAlphaBlending();

	setDefaultValues();
	ImGui::Initialize();
	mViewCam.setPerspective(60, getWindowWidth() / getWindowHeight(), 1, 1000);
	mCamUi = CameraUi(&mViewCam);

	gen.setSeed(255);
	//gen.setOctaves(12);
	int f = 0;
	for (int i = -2; i < 2; i++) {
		for (int j = -2; j < 2; j++) {
			for (int k = -2; k < 2; k++) {
				world.LoadChunk(ci::vec3(i, j, k));
				f++;
			}
		}
	}
	console() << f;
}

void MinecraftCloneApp::keyDown(KeyEvent event)
{
	p.KeyDown(event);
	/*switch (event.getCode())
	{
	case KeyEvent::KEY_a:
			mDegree -= .01;
			break;
	case KeyEvent::KEY_d:
			mDegree += .01;
			break;
	case KeyEvent::KEY_s:
			mDegree2 -= .01;
			break;
	case KeyEvent::KEY_w:
			mDegree2 += .01;
			break;
	default:
		break;
	}*/
}

void MinecraftCloneApp::keyUp(KeyEvent event)
{
	p.KeyUp(event);
}

void MinecraftCloneApp::mouseDown(MouseEvent event)
{
	mCamUi.mouseDown(event);
}

void MinecraftCloneApp::mouseMove(MouseEvent event)
{
	mLastMousePos = event.getPos();
	p.MouseMove(event);
}

void MinecraftCloneApp::mouseDrag(MouseEvent event)
{
	Rectf r = Rectf(getWindowWidth(), 0, getWindowWidth(), getWindowHeight());
	if (r.contains(event.getPos())) {
		mCamUi.mouseDrag(event);
	}
}

void MinecraftCloneApp::update()
{

	//ImGui::Begin("CameraPersp");
	//ImGui::DragFloat("Radius", &mRadius, 0.01f);
	//ImGui::DragFloat("Degree", &mDegree, 0.01f,0.0f,360.0f);
	//ImGui::DragFloat("Degree2", &mDegree2, 0.01f,0.0f,360.0f);
	//ImGui::DragFloat("height", &mHeight, 0.01f,0.0f,360.0f);
	//ImGui::DragFloat3("Look At", &mLookAt, 0.01f);
	//ImGui::DragFloat("FOV", &mFov, 1.0f, 1.0f, 179.0f);
	//ImGui::DragFloat("Near Plane", &mNearPlane, 0.02f, 0.1f, FLT_MAX);
	//ImGui::DragFloat("Far Plane", &mFarPlane, 0.02f, 0.1f, FLT_MAX);
	//ImGui::DragFloat2("Lens Shift X", &mLensShift, 0.01f);
	//ImGui::Separator();
	//if (ImGui::Button("Reset Defaults")) {
	//	setDefaultValues();
	//}
	//ImGui::End();
	float X = mLookAt.x + (mRadius *sin(mDegree)* cos(mDegree2));
	float Y = mLookAt.y + (mRadius *sin(mDegree)* sin(mDegree2));
	float Z = mLookAt.z + (mRadius * cos(mDegree));

	mViewCam.setEyePoint(vec3(X,Y,Z));
	mViewCam.lookAt(mLookAt);
	mViewCam.setLensShift(mLensShift);
	mViewCam.setNearClip(mNearPlane);
	mViewCam.setFarClip(mFarPlane);
	mViewCam.setFov(mFov);
	mViewCam.setAspectRatio(getWindowAspectRatio());

	
	p.Update();
	int l = 1;
	//for (int i = -(l / 2); i < l / 2; i++) {
	//	for (int j = -(l / 2); j < l / 2; j++) {
	//		for (int k = -(l / 2); k < l / 2; k++) {
	//			world.LoadChunk(i, j, k);
	//		}
	//	}
	//}
}

void MinecraftCloneApp::setDefaultValues()
{
	mRadius = 20;
	mDegree = 0;
	mDegree2 = 0;
	mHeight = 20;
	mLookAt = vec3(6.0f,1.0f,7.0f);
	mFov = 25.0f;
	mNearPlane = .5f;
	mFarPlane = 200.0f;
	mLensShift = vec2(0);
}

void MinecraftCloneApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) ); 
	gl::setMatrices(*p.getCam());


	//draw cubes
	world.Draw();
	//finish drawing cubes
}

CINDER_APP( MinecraftCloneApp, RendererGl )
