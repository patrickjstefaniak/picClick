//
//  allPics.h
//  picClick
//
//  Created by Patrick Stefaniak on 4/22/16.
//
//

#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "pics.h"
#include "cinder/Json.h"
#include "cinder/audio/Voice.h"
#include "cinder/audio/Source.h"



using namespace ci;
using namespace ci::app;
using namespace std;

class allPics{
public:
    allPics(){}
    std::vector<pics> vPics;
    void makePics();
    void drawPics();
    bool clicked(vec2 m);
    void colliding();
    void getPics();
    ci::JsonTree jsont;
    pics *selected;
    void endingSelected();
    bool isClicked();
    gl::TextureFontRef catInfo;
    Anim<float> infoAlpha, infoX;
    audio::VoiceRef meow;
};


