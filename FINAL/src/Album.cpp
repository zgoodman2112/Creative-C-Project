#include "Album.h"
#include "ofMain.h"

//This constructor assigns the parameters to the private variables,
//sets the beginning position and size of the album cover
//sets the beginning values for private boolean and int values
//and sets the font type and size
Album::Album(int x, int y, int width, int height){
    cout << "Album created" << endl;
    this->x = x;
    this->y = y;
    //-485 so album begins off-screen
    y = -485;
    this->width = width;
    this->height = height;
    
    cover.set(x,y,width,height);
    
    albumIsUp = true;
    activateUp = false;
    activateDown = false;
    playCount = 0;
    showText = false;
    
    font.load("Aller_Bd.ttf", 24);
}

//--------------------------------------------------------------
//Album destructor
Album::~Album(){
    cout << "Album destroyed" << endl;
}

//--------------------------------------------------------------
//Changes the size of the album cover due to the amplitude at certain frequencies
void Album::updateSize(int newSize){
    //Getting the oldSize of the album cover
    float oldSize = cover.getWidth();

    //Setting the new sizes. Since it is a square, we can use the same variable
    cover.setWidth(newSize);
    cover.setHeight(newSize);

    // Find the position change, and adjust the position accordingly to keep the center of the rectangle the same
    float deltaX = (newSize - oldSize) / 2.0;
    float deltaY = (newSize - oldSize) / 2.0;
    cover.setPosition(cover.getPosition().x - deltaX, cover.getPosition().y - deltaY);
}

//--------------------------------------------------------------
//Uses the "return" key to start or restart a song
void Album::start(){
    if (playCount==2){
        player.play();
        playing=true;
    }
    player.setPaused(false);
    player.play();
    playCount = 1;
    playing = true;

    if (playCount!=1){
        playing = false;
    }
}

//--------------------------------------------------------------
//Uses "spacebar" to pause and unpause
void Album::pausePlay(int key){
    //If albumIsUp, reset the playCount to 0
    if (albumIsUp){
        playCount = 0;
    }
    //If spacebar is hit, increase playcount value by 1.
    if (key==32){
        playCount = playCount + 1;
    }
    //If playCount is even, pause the music. If it is odd, unpause the music. Also update the playing boolean variable
    if (playCount%2==0){
        player.setPaused(true);
        playing = false;
    }else{
        player.setPaused(false);
        playing = true;
    }
}

//--------------------------------------------------------------
//isPlaying returns a variable that allows for the circles to or to not be drawn
bool Album::isPlaying(){
    return playing;
}

//chooseSong chooses the song which as a result changes the song and the album cover
//For each different choice, a new image, text, and mp3 is loaded (album cover, song name - artist name, and song)
void Album::chooseSong(int songChoice){
    
    if (albumIsUp){//If album is up, a new song can be chosen
        if (songChoice==1){
            image = ofImage("shred.jpg");
            text = "Fly - Apricot Jam";
            player.load("Fly.mp3");
        }else if (songChoice==2){
            image = ofImage("Carrollton.jpg");
            text = "Mr. Merry - Apricot Jam";
            player.load("Mr.Merry.mp3");
        }else if (songChoice==3){
            image = ofImage("Texicama.jpeg");
            text = "Texicama - Apricot Jam";
            player.load("Texicama.mp3");
        }else if (songChoice==4){
            image = ofImage("Tips.jpeg");
            text = "Whipping Post - Apricot Jam";
            player.load("Whipping Post.mp3");
        }else if (songChoice==5){
            image = ofImage("TJ.jpeg");
            text = "Chameleon - Apricot Jam";
            player.load("Chameleon.mp3");
        }else if (songChoice==6){
            image = ofImage("CUA.jpeg");
            text = "Coming Up Again - Apricot Jam";
            player.load("CUA.mp3");
        }else if (songChoice==7){
            image = ofImage("Feel.jpeg");
            text = "Do You Ever Feel? - Zach Goodman";
            player.load("Feel.mp3");
        }else if (songChoice==8){
            image = ofImage("Ambience.jpeg");
            text = "Ambience - Zach Goodman";
            player.load("Ambience.mp3");
        }else if (songChoice==9){
            image = ofImage("Soundscape.jpeg");
            text = "Soundscape - Zach Goodman";
            player.load("Soundscape.mp3");
        }
    }
}

//--------------------------------------------------------------
//Toggles the movement of the album up or down using the up/down arrow keys. It also switches playing to false when the album has been sent off the screen
//Takes parameter activationKey from KeyPressed.
void Album::activate(int activationKey){
    if (activationKey == 57357){
        activateUp = true;
        activateDown = false;
        playing = false;
    }
    if (activationKey == 57359){
        activateDown = true;
        activateUp = false;
    }
}

//Moves album up and off of the screen
void Album::moveAlbumUp(){
    if (activateUp) {
        //If the album is about to go off screen, stop showing text
        showText = false;
        
        //Set the target position for Y. This is above and off of the screen.
        float targetY = -1000;

        //Set a value for speed which will change the speed of the animation
        float speed = 1.0;

        //This interpolates the current y position towards the target at a rate of the speed multiplied by the lastFrameTime
        y = ofLerp(y, targetY, ofGetLastFrameTime() * speed);

        //Set the updated position of the album cover
        cover.setPosition(x, y);

        //Check if the album cover has left the screen and change boolean values
        if (y <= -301) {
            albumIsUp = true;
            activateUp = false;
        }
    }
}

//--------------------------------------------------------------
//Moves album down and onto the screen
void Album::moveAlbumDown(){
    if (activateDown){
        //Set the target position for Y. This is on the screen.
        float targetY = 184;
        
        //Set a value for speed which will change the speed of the animation
        float speed = .1;
        
        //This interpolates the current y position towards the target at a rate of the speed
        y = ofLerp(y, targetY, speed);
        
        //If y has reached its target position, stop moving downward, or make activateDown false.
        if (y==targetY){
            activateDown = false;
        }

        //Set the updated position of the album cover
        cover.setPosition(x, y);
        
        //Check if the album cover has reached the center of the screen and change boolean values
        if (y > 100) {
            albumIsUp = false;
            //Now the text can be shown because the album is at the center of the screen
            showText = true;
            
        }
    }
}

//--------------------------------------------------------------
//update allows moveAlbumDown() and moveAlbumUp() to work properly as they need to continue running until conditions are met. It also stops the player when the album is moved off of the screen
void Album::update(){
    //if activateUp is true, moveAlbumUp()
    if (activateUp){
        moveAlbumUp();
    }
    //moveAlbumDown(). This will only work if activateDown is true, which only occurs when the down arrow key is pressed
    moveAlbumDown();
    
    //This stops the music if the album is up and off of the screen
    if (albumIsUp){
        player.stop();
    }
}

//--------------------------------------------------------------
//Draws the album (image and shape), and font
void Album::draw(){
    //Set color of album
    ofSetColor(255, 255, 255, 255);

    //Call update
    update();
    
    //Draw the shape and image using ofRectangle cover's parameters
    ofDrawRectangle(cover);
    image.draw(cover);
    
    //Set font color
    ofSetColor(0, 0, 0);
    //Find width of the string so you can center it
    float strWidth = font.stringWidth(text);
    //Only draws the string once showText is true, which is controlled in moveAlbumUp() and moveAlbumDown()
    if (showText){
        font.drawString(text, (ofGetWidth()/2)-(strWidth/2.0), (ofGetHeight()/2)+150);
    }
}
