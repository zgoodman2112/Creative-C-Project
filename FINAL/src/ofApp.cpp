#include "ofApp.h"
#include "Album.h"
using namespace std;
//--------------------------------------------------------------
void ofApp::setup(){
    //Setting background image
    background = ofImage("wall.jpeg");

    //Setting initial values and font sizes
    showMenu = true;
    menuCount = 0;
    menu.load("Aller_BdIt.ttf", 20);
    menuSmall.load("Aller_BdIt.ttf", 11);

    //Writing out the strings for each line of text shown in the menu
    menuTxt1 = "Welcome to Zach's Personal MP3 Player!";
    menuTxt2 = "CONTROLS AND DIRECTIONS:";
    
    menuTxt3 = "1. Select a song by pressing numbers 1-9 on your keyboard.";
    
    menuTxt4 = "2. Choose the song from your virtual shelf by pressing ";
    menuTxt5 = "the down arrow button. To send it back on the shelf, press";
    menuTxt6 = "the up arrow button. You can ONLY choose a new song once";
    menuTxt7 = "the player is empty, so be sure to shelve your current";
    menuTxt8 = "song before choosing a new one.";
    
    menuTxt9 = "3. Press [RETURN] to start or restart a song.";
    
    menuTxt10 = "4. Press [SPACEBAR] to pause or resume a song.";
    
    menuTxt11 = "SONG LIST:";
    menuTxt12 = "1. Fly - Apricot Jam";
    menuTxt13 = "2. Mr. Merry - Apricot Jam";
    menuTxt14 = "3. Texicama - Apricot Jam";
    menuTxt15 = "4. Whipping Post - Apricot Jam";
    menuTxt16 = "5. Chameleon - Apricot Jam";
    menuTxt17 = "6. Coming Up Again - Apricot Jam";
    menuTxt18 = "7. Do You Ever Feel? - Zach Goodman";
    menuTxt19 = "8. Ambience - Zach Goodman";
    menuTxt20 = "9. Soundscape - Zach Goodman";
    
    menuTxt21 = "Press [m] to show/hide menu";
}

//--------------------------------------------------------------
void ofApp::update(){
    //Assigning newSize to the original size (300), plus the additional size (rectChange)
    //newSize is assigned in the for loop in draw()
    int newSize = rectChange + 300;
    
    //I CHOSE TO LEAVE THIS OUT, BUT IF YOU WANT TO SEE THE ALBUM COVER CHANGE SIZE LIKE THE SPEAKERS, UNCOMMENT THIS
    //call updateSize, which makes the album cover change size due to the amplitude at certain frequencies
    //myAlbum.updateSize(newSize);
    
    //This allows the speakers' size to be changed due to the amplitude at certain frequencies
    speaker1.updateSpeakerSize(newSize);
    speaker2.updateSpeakerSize(newSize);
    
    //For each circle in the vector circles, if music is playing, update the circles (move them).
    for (int i=0; i<circles.size(); i++){
        if (myAlbum.isPlaying()){
            circles[i]->update();
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    //Set the color of the image to be white and transparent, then draw the image so it covers the whole screen
    ofSetColor(255, 255, 255, 255);
    background.draw(0, 0, ofGetWidth(), ofGetHeight());

    //Every 60 frames, clear the circles vector. If this wasn't done, the movement of the circles would be very slow and laggy.
    if (ofGetFrameNum()%60==0){
        circles.clear();
    }

    
    //The following code produces the rainbow meter level and the circles
    //rainbow is the ofColor color
    ofColor rainbow;
    //rectWidth is the width of each band
    float rectWidth = 2.5;
    //numBands is so that there will be 512 rectangles. This means the entire range of frequencies is split into 512 bands, and each will have it's own level of amplitude, measured by ofSoundGetSpectrum.
    float numBands = 512;
    //ofSoundGetSpectrum returns a pointer to an array of floats which contain the amplitude of each band
    float * freq = ofSoundGetSpectrum(numBands);
    //velocitY with an uppercase Y is because this variable will be used for the y value of each circle's velocity.
    float velocitY;

    //Iterate through each of the 512 bands
    for (int i = 0; i < numBands; i++){
        //This value is used above in Speaker.updateSpeakerSize() in update()
        //It uses the 24th band's amplitude value because the level at that frequency is usually large
        rectChange = ofMap(freq[24], .10, .20, 0, 25);
        //Here I am setting the color of the meter. With HSB, we set the hue, saturation, and brightness. Keeping the saturation and brightness the same, from values 1-255 in H range from red to violet. This equation in the H value allows for a rainbow gradient to strech across the length of the 512 bands.
        rainbow.setHsb(255/numBands*i, 255, 255);
        //Setting color
        ofSetColor(rainbow);
        //Different area of the meter had different levels. The high frequencies were much stronger than the mids and lows, so I boosted the heights of their bands and circle velocities with these if statements.
        if (i<100){
            velocitY = -(freq[i])*200;
            ofDrawRectangle(rectWidth*i, ofGetHeight()-50, rectWidth, velocitY);
        }else if (i<250){
            
            velocitY = -(freq[i])*1000;
            ofDrawRectangle(rectWidth*i, ofGetHeight()-50, rectWidth, velocitY);
        }else{
            velocitY = -(freq[i])*10000;
            ofDrawRectangle(rectWidth*i, ofGetHeight()-50, rectWidth, velocitY);
        }

        //Assigning variables to plug into new instance of Circle
        //color, size, speed, and coordinates of the circle
        ofColor color = ofColor(rainbow);
        float size = 1;
        vec2 speed = vec2(0, velocitY);
        vec2 coords = vec2(rectWidth*i, ofGetHeight()-50);

        //Dynamically allocate memory for a new circle and push onto vector circles
        Circle* cir = new Circle{color, size, speed, coords};
        circles.push_back(cir);
    }

    //If music isn't playing and there is more than 1 circle in the vector, clear the entire vector. This means no circles will be flying around when the music is stopped
    if (myAlbum.isPlaying()==false){
        if (circles.size()>=1){
            circles.clear();
        }
    }

    //For each circle in vector circles, if music is playing, draw each circle
    for (int i=0; i<circles.size(); i++){
        if (myAlbum.isPlaying()){
            circles[i]->draw();
            }
        }

    //Draw myAlbum and draw left and right speakers
    myAlbum.draw();
    speaker1.draw();
    speaker2.draw();
        
    //Get the width of each string so that it is centered and looks nice and neat
    float strWidth1 = menu.stringWidth(menuTxt1);
    float strWidth2 = menu.stringWidth(menuTxt2);
    float strWidth3 = menuSmall.stringWidth(menuTxt3);
    float strWidth4 = menuSmall.stringWidth(menuTxt4);
    float strWidth5 = menuSmall.stringWidth(menuTxt5);
    float strWidth6 = menuSmall.stringWidth(menuTxt6);
    float strWidth7 = menuSmall.stringWidth(menuTxt7);
    float strWidth8 = menuSmall.stringWidth(menuTxt8);
    float strWidth9 = menuSmall.stringWidth(menuTxt9);
    float strWidth10 = menuSmall.stringWidth(menuTxt10);
    float strWidth11 = menu.stringWidth(menuTxt11);
    float strWidth12 = menuSmall.stringWidth(menuTxt12);
    float strWidth13 = menuSmall.stringWidth(menuTxt13);
    float strWidth14 = menuSmall.stringWidth(menuTxt14);
    float strWidth15 = menuSmall.stringWidth(menuTxt15);
    float strWidth16 = menuSmall.stringWidth(menuTxt16);
    float strWidth17 = menuSmall.stringWidth(menuTxt17);
    float strWidth18 = menuSmall.stringWidth(menuTxt18);
    float strWidth19 = menuSmall.stringWidth(menuTxt19);
    float strWidth20 = menuSmall.stringWidth(menuTxt20);
    float strWidth21 = menu.stringWidth(menuTxt21);

    //Set menu text color to black
    ofSetColor(0, 0, 0);
    //If showMenu is true (switched on and off by 'm') draw all of these strings
    if (showMenu){
        menu.drawString(menuTxt1, (ofGetWidth()/2)-(strWidth1/2.0), 35);
        menu.drawString(menuTxt2, (ofGetWidth()/2)-(strWidth2/2.0), 65);
        menuSmall.drawString(menuTxt3, (ofGetWidth()/2)-(strWidth3/2.0), 100);
        menuSmall.drawString(menuTxt4, (ofGetWidth()/2)-(strWidth4/2.0), 130);
        menuSmall.drawString(menuTxt5, (ofGetWidth()/2)-(strWidth5/2.0), 145);
        menuSmall.drawString(menuTxt6, (ofGetWidth()/2)-(strWidth6/2.0), 160);
        menuSmall.drawString(menuTxt7, (ofGetWidth()/2)-(strWidth7/2.0), 175);
        menuSmall.drawString(menuTxt8, (ofGetWidth()/2)-(strWidth8/2.0), 190);
        menuSmall.drawString(menuTxt9, (ofGetWidth()/2)-(strWidth9/2.0), 220);
        menuSmall.drawString(menuTxt10, (ofGetWidth()/2)-(strWidth10/2.0), 250);
        menu.drawString(menuTxt11, (ofGetWidth()/2)-(strWidth11/2.0), 290);
        menuSmall.drawString(menuTxt12, (ofGetWidth()/2)-(strWidth12/2.0), 320);
        menuSmall.drawString(menuTxt13, (ofGetWidth()/2)-(strWidth13/2.0), 335);
        menuSmall.drawString(menuTxt14, (ofGetWidth()/2)-(strWidth14/2.0), 350);
        menuSmall.drawString(menuTxt15, (ofGetWidth()/2)-(strWidth15/2.0), 365);
        menuSmall.drawString(menuTxt16, (ofGetWidth()/2)-(strWidth16/2.0), 380);
        menuSmall.drawString(menuTxt17, (ofGetWidth()/2)-(strWidth17/2.0), 395);
        menuSmall.drawString(menuTxt18, (ofGetWidth()/2)-(strWidth18/2.0), 410);
        menuSmall.drawString(menuTxt19, (ofGetWidth()/2)-(strWidth19/2.0), 425);
        menuSmall.drawString(menuTxt20, (ofGetWidth()/2)-(strWidth20/2.0), 440);
        menu.drawString(menuTxt21, (760)-(strWidth20/2.0), 750);
    }
}

//--------------------------------------------------------------
void ofApp::exit(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

     
    //ints to keep track of what albumCover/song
    int albumChoice;
    
    if (key==49){//key "1"
        albumChoice = 1;
    }else if (key == 50){//key "2"
        albumChoice = 2;
    }else if (key ==51){//key "3"
        albumChoice = 3;
    }else if (key ==52){//key "4"
        albumChoice = 4;
    }else if (key ==53){//key "5"
        albumChoice = 5;
    }else if (key ==54){//key "6"
        albumChoice = 6;
    }else if (key ==55){//key "7"
        albumChoice = 7;
    }else if (key ==56){//key "8"
        albumChoice = 8;
    }else if (key ==57){//key "9"
        albumChoice = 9;
    }
    
    //If "return" is pressed, start or restart the song
    int playCount;
    if (key==13){
        myAlbum.start();
    }
    
    //If "spacebar" is pressed, pause or resume the music
    if (key==32){
        myAlbum.pausePlay(key);
    }
    
    //Send albumChoice to the chooseSong() method of Album
    myAlbum.chooseSong(albumChoice);
    
    //If you press the up arrow, the album will move off of the screen back onto the virtual shelf
    //If you press a number to choose an album, then press the down arrow, an album will be dropped onto the screen from above
    myAlbum.activate(key);
    
    //This is controlled by key "m" which shows/hides the menu
    if (key==109){
        menuCount = menuCount + 1;
        if (menuCount%2==0){
            showMenu = true;
        }else{
            showMenu = false;
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
