#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "pics.h"
#include "allPics.h"


using namespace ci;
using namespace ci::app;
using namespace std;


class picClickApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
    allPics pic;
    

};

void picClickApp::setup()
{
    setWindowSize(1000,600);
    pic.getPics();
    pic.catInfo = gl::TextureFont::create( Font("Arial", 30));
    pic.infoAlpha = 0.0f;
    pic.infoX = 100.0f;
    pic.selected = &pic.vPics.back();
    pic.meow = audio::Voice::create( audio::load(app::loadAsset("meow.mp3")));
}

void picClickApp::mouseDown( MouseEvent event )
{
    if(!pic.isClicked()){
        pic.clicked(event.getPos());
    }else{
        pic.endingSelected();
    }


}

void picClickApp::update()
{
    if(!pic.isClicked()){
        for(pics &picz : pic.vPics){
            picz.movin();

        }
        pic.colliding();
    }else{
        for(pics &picz : pic.vPics){
            picz.selectedMovin();
            
        }
    }
 
}

void picClickApp::draw()
{
	gl::clear( Color( .5, .2, .8 ) );
    pic.drawPics();

}


CINDER_APP( picClickApp, RendererGl )
