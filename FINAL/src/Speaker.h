//
//  Speaker.h
//  FINAL
//
//  Created by Zach Goodman on 1/2/24.
//

#ifndef Speaker_h
#define Speaker_h

#include <stdio.h>

#include "ofMain.h"

class Speaker{
    
    public:
    //Speaker constructor
    //x&y are the coordinates of the rectangle, and width and height are the width and height
        Speaker(int x, int y, int width, int height);
    //Speaker destroyed
        ~Speaker();
        
    //draws the speakers
        void draw();
    //Changes the size of the speaker due to the amplitude at certain frequencies
    //newSize is the input from the ofSoundGetSpectrum code which is changing as the music changes
        void updateSpeakerSize(int newSize);
    
    
    private:
    //rect is the ofRectangle object that makes up the speaker
        ofRectangle rect;
    //speakerIMG is the image that allows the speaker to have an image of a speaker
        ofImage speakerIMG;
};

#endif /* Speaker_h */
