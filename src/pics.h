//
//  pics.h
//  picClick
//
//  Created by Patrick Stefaniak on 4/22/16.
//
//

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Timeline.h"


using namespace ci;
using namespace ci::app;
using namespace std;



#pragma once

class pics {
public:
    pics () {}
    pics(float w, float h, vec2 c);
    pics(float w, float h);
    pics(gl::Texture2dRef thePic, vec2 c);
    float pwidth;
    float pheight;
    void drawIt();
    Anim<float> anmX, anmY, scale, alph;
    vec2 ppos, holdPos;
    Color pcol;
    void randomize();
    void movin();
    void selectedMovin();
    float movX, movY;
    gl::Texture2dRef thePic;
    void selectedStart();
    void selectedEnd();
    void otherStart();
    bool isClickedd();
    string name;
};