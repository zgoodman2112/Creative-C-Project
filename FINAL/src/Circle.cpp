//
//  Circle.cpp
//  FINAL
//
//  Created by Zach Goodman on 1/4/24.
//
#include "ofMain.h"
#include "Circle.h"
//-------------------------------------------------------
//Constructs a circle and assigns the parameters to the proper variables
Circle::Circle(ofColor col, float sze, vec2 spd, vec2 coordinates)
{
//    cout << "Constructed a Circle" << endl;
    color = col;
    size = sze;
    speed = spd;
    coords = coordinates;
}

//--------------------------------------------------------------
//Destructs a circle
Circle::~Circle(){
//    cout << "Circle destroyed" << endl;
}

//--------------------------------------------------------------
//sets color and draws circle
void Circle::draw(){
    ofSetColor(color);
    ofDrawCircle(coords, size);
}

//--------------------------------------------------------------
//Calls move() which allows the circle to continually move
void Circle::update(){
    move();
}

//--------------------------------------------------------------
//Changes the coordinates based on the speed at which it is moving
void Circle::move(){
        coords += speed;
}



