//
//  pics.cpp
//  picClick
//
//  Created by Patrick Stefaniak on 4/22/16.
//
//

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "pics.h"


using namespace ci;
using namespace ci::app;
using namespace std;
bool isClicked;

pics::pics(float w, float h, vec2 c){
    pwidth = w;
    pheight = h;
    ppos = c;
    pcol = Color((random() % 255) / 255, (random() % 255) / 255, (random() % 255) / 255 );
}

pics::pics(float w, float h){
    pwidth = w;
    pheight = h;
    ppos = vec2(random() % getWindowWidth(), random() % getWindowHeight());
    pcol = Color((float)(random() % 255) / 255, (float)(random() % 255) / 255, (float)(random() % 255) / 255 );
}

pics::pics(gl::Texture2dRef theP, vec2 c){
    ppos = c;
    thePic = theP;
    pwidth = thePic -> getActualWidth() / 10;
    pheight = thePic -> getActualHeight() / 10;
    isClicked = false;
}

void pics::drawIt(){
    gl::pushMatrices();
    gl::translate(ppos);
    gl::scale(scale,scale);
    gl::color(1,1,1,alph);
    gl::draw(thePic);
    gl::popMatrices();
}

void pics::randomize(){
    pcol = Color((float)(random() % 255) / 255, (float)(random() % 255) / 255, (float)(random() % 255) / 255 );
    movX = ((float)(random() % 200) / 100 ) - 1;
    movY = ((float)(random() % 200) / 100 ) - 1;
}

void pics::movin(){

    ppos.y += movY;
    if(ppos.y < 0 ){
        movY = movY * -1 / abs(movY) * ((float)(random() % 200) / 100 );
        ppos.y = 0;
    }
    if (ppos.y > (getWindowHeight() - pheight)){
        movY = movY * -1 / abs(movY) * ((float)(random() % 200) / 100 );
        ppos.y = getWindowHeight() - pheight;
    }
    ppos.x += movX;
    if(ppos.x < 0 ){
        movX = movX * -1 / abs(movX) * ((float)(random() % 200) / 100 );
        
        ppos.x = 0;
    }
    if (ppos.x > (getWindowWidth() - pwidth)){
        movX = movX * -1 / abs(movX) * ((float)(random() % 200) / 100 );
        ppos.x = getWindowWidth() - pwidth;
    }
    
}

void pics::selectedMovin(){
    ppos.x = anmX;
    ppos.y = anmY;

}

void pics::selectedStart(){
    holdPos = ppos;
    anmX = ppos.x;
    anmY = ppos.y;
    timeline().apply( &scale, 0.5f, 2.0f, EaseOutQuad());
    timeline().apply( &anmX, (float)((getWindowWidth()/2) - ((thePic->getActualWidth() /4 ))), 2.0f, EaseOutQuad());
    timeline().apply( &anmY, (float)((getWindowHeight()/2) - ((thePic->getActualHeight() / 4) )), 2.0f, EaseOutQuad());
    isClicked = true;
}

void endClick(){
    isClicked = false;
}

bool pics::isClickedd(){
    return isClicked;
}

void pics::selectedEnd(){
    timeline().apply( &scale, 0.1f, 2.0f, EaseInQuad());
    timeline().apply( &alph, 1.0f, 2.0f, EaseInQuad());
    timeline().apply( &anmX, holdPos.x , 2.0f, EaseInQuad());
    timeline().apply( &anmY, holdPos.y , 2.0f, EaseInQuad()).finishFn(endClick);
}

void pics::otherStart(){
    holdPos = ppos;
    anmX = ppos.x;
    anmY = ppos.y;
    timeline().apply( &scale, 0.05f, 2.0f, EaseOutQuad());
    timeline().apply( &alph, 0.0f, 2.0f, EaseOutQuad());
    timeline().apply( &anmX, (float)(getWindowWidth()/2), 2.0f, EaseInQuad());
    timeline().apply( &anmY, (float)(getWindowHeight() / 2), 2.0f, EaseInQuad());
}