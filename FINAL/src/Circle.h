//
//  Circle.hpp
//  FINAL
//
//  Created by Zach Goodman on 1/4/24.
//

#ifndef Circle_h
#define Circle_h

#include <stdio.h>
#include "ofMain.h"

using namespace glm;

class Circle{


    public:
    //Circle constructor. Takes the color, size, speed, and coordinates of the circle
    Circle(ofColor color, float size, vec2 speed, vec2 coords);
    //Circle destroyer
    ~Circle();

    //Sets color and draws circle
        void draw();
    //Calls move() which allows the circle to continually move
        void update();
//    //Changes the coordinates based on the speed at which it is moving
//        void move();
    
    private:
    //Changes the coordinates based on the speed at which it is moving
        void move();
    
    //contains the color of each circle
    ofColor color;
    //determines the size of each circle
    float size;
    //determines the speed of each circle
    vec2 speed;
    //contains the coordinates of each circle's location
    vec2 coords;
        
};

#endif /* Circle_h */
