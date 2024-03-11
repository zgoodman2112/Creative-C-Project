#pragma once

#include "ofMain.h"
#include "Album.h"
#include "Speaker.h"
#include "Circle.h"

class ofApp : public ofBaseApp{

	public:
		void setup() override;
		void update() override;
		void draw() override;
		void exit() override;

		void keyPressed(int key) override;
		void keyReleased(int key) override;
		void mouseMoved(int x, int y ) override;
		void mouseDragged(int x, int y, int button) override;
		void mousePressed(int x, int y, int button) override;
		void mouseReleased(int x, int y, int button) override;
		void mouseScrolled(int x, int y, float scrollX, float scrollY) override;
		void mouseEntered(int x, int y) override;
		void mouseExited(int x, int y) override;
		void windowResized(int w, int h) override;
		void dragEvent(ofDragInfo dragInfo) override;
		void gotMessage(ofMessage msg) override;
		
    //Declaring instance of class Album and making it a square in the center of the screen
    Album myAlbum{(ofGetWidth()/2)-150, ofGetHeight()/2-200, 300, 300};
    
    //variable has the value of the additional size that the speakers should have
    int rectChange;
    
    //Declaring instance of both speakers
    Speaker speaker1{186, 50, 124, 450};
    Speaker speaker2{714, 50, 124, 450};

    //Vector containing the tiny circles that rise from the levels meter
    vector<Circle*> circles;
    
    //Contains the background image
    ofImage background;
    
    //menu is bigger, menuSmall is smaller, and each string is a line of text
    ofTrueTypeFont menu;
    ofTrueTypeFont menuSmall;
    string menuTxt1;
    string menuTxt2;
    string menuTxt3;
    string menuTxt4;
    string menuTxt5;
    string menuTxt6;
    string menuTxt7;
    string menuTxt8;
    string menuTxt9;
    string menuTxt10;
    string menuTxt11;
    string menuTxt12;
    string menuTxt13;
    string menuTxt14;
    string menuTxt15;
    string menuTxt16;
    string menuTxt17;
    string menuTxt18;
    string menuTxt19;
    string menuTxt20;
    string menuTxt21;
    
    //Menu shows when showMenu==true. menuCount uses a modulo equation to switch showMenu true or false.
    bool showMenu;
    int menuCount;
};
