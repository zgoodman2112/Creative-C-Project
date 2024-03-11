//
//  Speaker.cpp
//  FINAL
//
//  Created by Zach Goodman on 1/2/24.
//
#include "Speaker.h"
#include "ofMain.h"
//-------------------------------------------------------
//Constructs a speaker, sets the parameters to rect, and assigns speakerIMG to an image of a speaker
Speaker::Speaker(int x, int y, int width, int height){
    cout << "Speaker created" << endl;
    rect.set(x,y,width,height);
    
    speakerIMG = ofImage("speaker.jpeg");
}

//-------------------------------------------------------
//Speaker destructor
Speaker::~Speaker(){
    cout << "Speaker destroyed" << endl;
}

//-------------------------------------------------------
//Sets color and draws speaker
void Speaker::draw() {
    //Sets color to transparent white so that the image isn't affected
    ofSetColor(255, 255, 255, 255);
    //draws speaker
    speakerIMG.draw(rect);
}

//-------------------------------------------------------
//Takes in int size and increased the size of the speaker based on the amplitude value
void Speaker::updateSpeakerSize(int size) {
    //Tweaking newSize so that the speaker doesn't get too big or too small
    float newSize = abs(size / 5.0);
    
    // Getting the old size of the speaker
    float oldWidth = rect.width;
    float oldHeight = rect.height;

    // Setting the new sizes. Since it is a rectangle, I calculated the specific width:height ratio
    float newWidth = newSize * 2;
    float newHeight = newSize * 7.258064516129;

    // Update the rectangle width and height
    rect.setWidth(newWidth);
    rect.setHeight(newHeight);

    // Find the position change, and adjust the position accordingly to keep the center of the rectangle the same
    float deltaX = (newWidth - oldWidth) / 2.0;
    float deltaY = (newHeight - oldHeight) / 2.0;
    rect.setPosition(rect.getPosition().x - deltaX, rect.getPosition().y - deltaY);
}
