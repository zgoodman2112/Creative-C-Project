//
//  Album.hpp
//  FINAL
//
//  Created by Zach Goodman on 1/2/24.
//

#ifndef Album_h
#define Album_h

#include <stdio.h>

#include "ofMain.h"

class Album{
    
    public:
    //Album constructor
    //x&y are the coordinates of the rectangle/square, and width and height are the width and height
        Album(int x, int y, int width, int height);
    //Album destructor
        ~Album();
    
    //Draws the album and the font
        void draw();

    //Changes the size of the album cover due to the amplitude at certain frequencies
    //newSize is the input from the ofSoundGetSpectrum code which is changing as the music changes
        void updateSize(int newSize);

//activate takes activationKey, an input from KeyPressed which toggles the movement of the album up or down. For up, it is the up arrow, and for down, the down arrow. It also adjusts the playing boolean variable appropriately.
        void activate(int activationKey);
    
    //chooseSong chooses the song which as a result changes the song and the album cover
    //songChoice is an input from KeyPressed which allows you to choose different songs from the keyboard
        void chooseSong(int songChoice);
    //pausePlay is also taking in input from KeyPressed with key, and uses the spacebar to pause and play the song as the user pleases.
        void pausePlay(int key);
    //start takes in input from KeyPressed using the return button as a switch to begin or restart a song
        void start();
        
    //isPlaying returns the boolean variable: playing. This is used in ofApp to determine whether or not to keep the circles on the screen
        bool isPlaying();

    
    private:
    //update allows moveAlbumDown() and moveAlbumUp() to work properly as they need to continue running until conditions are met. It also stops the player when the album is moved off of the screen
        void update();
    
    //moveAlbumDown moves the album onto the screen which enables it to be played
        void moveAlbumDown();
    //moveAlbumUp moves the album off the screen and back onto the "shelf"
        void moveAlbumUp();
    //activate takes activationKey, an input from KeyPressed which toggles the movement of the album up or down. For up, it is the up arrow, and for down, the down arrow. It also adjusts the playing boolean variable appropriately.
    

    //This is responsible for all the sound that is being played and heard
        ofSoundPlayer player;
    //This is the ofRectangle object that makes up the square album cover
        ofRectangle cover;
    
    //This is the font type that allows font to be shown
        ofTrueTypeFont font;
    //This is the string text that contains the album and artist name
        std::string text;

    //This is the image type that allows the album to have an album cover/photograph
        ofImage image;
    
    //x is the x coordinate which is used throughout the class
        int x;
    //y is the y coordinate which is used throughout the class
        int y;
    //width contains the width value, which is used throughout the class
        int width;
    //height contains the height value, which is used throughout the class
        int height;
    
    //These are all boolean variables that act as switches to do many things.
    //This confirms the album is off of the screen
    bool albumIsUp;
    //This allows the album to be moved off of the screen
    bool activateUp;
    //This allows the album to be moved onto the screen
    bool activateDown;
    //This decides whether or not the text can be shown. This is based on the height of Y and whether the album is on the screen or not.
    bool showText;
    
    //This keeps track of the amount of times the spacebar has been hit and uses a modulo equation because the spacebar can either pause, or unpause
    int playCount;
    
    //playing is used to determine whether or not there is music playing, which allows ofApp to know whether or not to draw the circles
    bool playing;
};

#endif /* Album_h */
