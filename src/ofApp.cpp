#include "ofApp.h"

#define NR_BANDS 64

float alphaSmooth[NR_BANDS];
//float alphaMid = 255.f;
ofPoint pos;


//--------------------------------------------------------------
void ofApp::setup(){
    
    song.load("song.mp3");
    while (! song.isLoaded()); // spin wheels till loaded
    song.play();
    
    fftSmoothed = new float[8192];
    midValues = new float[8192];
    highValues = new float[8192];

    for (int i = 0; i < 8192; i++){
        fftSmoothed[i] = 0;
        midValues [i] = 0;
    }
    

    
    nBassBands = NR_BANDS;  // up to 512
    
    nMidBands = NR_BANDS * 2;
    
    nHighBands = NR_BANDS * 4;
    
    cover.load("cover.png");
    
    midFbo.clear();
    midFbo.allocate(ofGetWindowWidth(), ofGetWindowHeight());
    
   
}

//--------------------------------------------------------------
void ofApp::update(){
    
    ofBackground(1,108,150);
    
    // update the sound playing system:
    // ofSoundUpdate();
    
   
    
    // (5) grab the fft, and put in into a "smoothed" array,
    float *val = ofSoundGetSpectrum(nBassBands);  // get array of floats (1 for each band)
    
    float *valMid = ofSoundGetSpectrum(nMidBands);
    
    float *valHigh = ofSoundGetSpectrum(nHighBands);

    //		by taking maximums, as peaks and then smoothing downward
    for (int i = 0;i < nBassBands; i++){
        
        // let the smoothed calue sink to zero:
        fftSmoothed[i] *= 0.975f;
        
        alphaSmooth[i] = ofMap(fftSmoothed[i], 0, 1, 0, 255);
        
        // take the max, either the smoothed or the incoming:
        if (fftSmoothed[i] < val[i+4]) fftSmoothed[i] = val[i+4];
        
    }
    
    for (int i = 0; i < nMidBands; i++) {
        
        
        midValues[i] *= 0.93f;
        
        
        if  (midValues[i] < valMid[i+8]) midValues[i] = valMid[i+8];
        
        
        
    }
    
    
    for (int i = 0; i < nHighBands; i++) {
        highValues[i] *= 0.96f;
        
        if (highValues[i] < valHigh[i + 100]) highValues[i] = valHigh[i+100];
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    
    // Bass
    float bassBands = nBassBands/8;
    
    float width = (float)(ofGetWindowWidth());
    float height = (float)(ofGetWindowHeight() / bassBands);
    for (int i = 0;i < bassBands; i++){
        // (we use negative height here, because we want to flip them
        // because the top corner is 0,0)
        ofSetColor(1,72,100,alphaSmooth[i]);

        ofDrawRectangle(0,i*height, fftSmoothed[i] * width, height);
    }
    
    
    
    
    ofSetColor(255, 255, 255);
    cover.draw(ofGetWindowWidth() - 170, ofGetWindowHeight() - 170);
    
    
    //Middle
    midFbo.begin();

    for(int i; i < nMidBands; i++) {
        
        
        
                ofPushMatrix();

            ofSetColor(255, 186, 55);
        ofRotateZ(midValues[i]*180);

            ofDrawEllipse(9 * i,  9 , 6, 6);

              
    ofPopMatrix();
    ofSetColor(1,108,150, 1);
        

        
    };
    ofDrawRectangle(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
    midFbo.end();
    midFbo.draw(0,0);
    
    for (int i; i < nHighBands; i++) {
        
        
        ofSetColor(86,169, 119, highValues[i] * 255);
        
        ofDrawCircle(ofGetWindowWidth()/2, ofGetWindowHeight()/2, highValues[i] * ofGetWindowHeight()/2 );
        
    }

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
