#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class MinecraftCloneApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
};

void MinecraftCloneApp::setup()
{
}

void MinecraftCloneApp::mouseDown( MouseEvent event )
{
}

void MinecraftCloneApp::update()
{
}

void MinecraftCloneApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP( MinecraftCloneApp, RendererGl )
