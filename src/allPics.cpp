//
//  allPics.cpp
//  picClick
//
//  Created by Patrick Stefaniak on 4/22/16.
//
//

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "pics.h"
#include "allPics.h"
#include "cinder/Timeline.h"
#include "cinder/Log.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"


using namespace ci;
using namespace ci::app;
using namespace std;

#define LOG_EXCEPTION( exc )	{ CI_LOG_E( "exception caught: " << System::demangleTypeName( typeid( exc ).name() ) << ", what: " << exc.what() ); }


void allPics::drawPics(){
    for( pics &pic : vPics){
        pic.drawIt();
    }
    gl::color(1,1,0, infoAlpha);
    catInfo->drawString(selected->name , vec2(getWindowWidth() / 2 - 20,
                                              infoX));

}

bool allPics::clicked(vec2 m){
    int p = 0;
    for(pics &pic : vPics){
        if((pic.ppos.x < m.x) && (m.x < pic.ppos.x + pic.pwidth) && (pic.ppos.y < m.y) && (m.y < pic.ppos.y + pic.pheight)){
            pic.holdPos = pic.ppos;
            selected = &pic;
            selected->selectedStart();
            p = 1;
        }
    }
    if(p == 1){
        timeline().apply(&infoAlpha, 1.0f, 2.0f, EaseOutSine());
        timeline().apply(&infoX, 80.0f, 2.0f, EaseOutSine());
        if(meow->isPlaying()){
            meow->stop();
        }
        meow->start();
        for(pics &pic : vPics){
            if(pic.ppos != selected->ppos){
                pic.holdPos = pic.ppos;
                pic.otherStart();
            }
        }
        return true;
    }
    return false;
}

void allPics::colliding(){
    for(pics &pic1: vPics){
        for(pics &pic2: vPics){
            if(pic2.ppos != pic1.ppos){
                if((pic1.ppos.x < (pic2.ppos.x + pic2.pwidth)) &&
                   ((pic1.ppos.x + pic1.pwidth) > pic2.ppos.x) &&
                   (pic1.ppos.y < (pic2.ppos.y + pic2.pheight))&&
                   ((pic1.ppos.y + pic1.pheight) > pic2.ppos.y)){
                        pic1.movX = -pic1.movX;
                        pic1.movY = -pic1.movY;
                }
            }
        }
    }
}

void allPics::getPics(){
    
    try {
        jsont = JsonTree( app::loadAsset( "config.json"));
        
        vPics.clear();
        int i = 0;
        for( const auto &cat : jsont["cats"]) {
            string fileName = cat["file"].getValue();
            auto tex = gl::Texture::create( loadImage( app::loadAsset( fileName)));
            pics pic1 = pics(tex, vec2(0,0));
            pic1.name = cat["name"].getValue();
            pic1.randomize();
            pic1.scale = .1;
            pic1.alph = 1.0;
            pic1.ppos = vec2((i % 4) * 200 + 10, floor(i / 4) * 100 + 10);
            i ++;
            vPics.push_back(pic1);
            
        }
        selected = &vPics.back();
        //CI_LOG_V("succesfully loaded jsontree");
    }
    catch(Exception &exc) {
        LOG_EXCEPTION( exc);
    }
}

void allPics::endingSelected(){
    selected->selectedEnd();
    for(pics &picz: vPics){
        if(picz.scale != selected->scale){
            picz.selectedEnd();
        }
    }
    timeline().apply(&infoAlpha, 0.0f, 2.0f, EaseOutSine());
    timeline().apply(&infoX, 100.0f, 2.0f, EaseOutSine());
}

bool allPics::isClicked(){
    for(pics &picz: vPics){
        if(picz.isClickedd()){
            return true;
        }
    }
    return false;
}