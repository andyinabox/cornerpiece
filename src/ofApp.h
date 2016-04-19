#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

    bool showGui = true;
  
    ofImage image;
    ofTexture imageTexture;
//    ofPoint points[4];
//    int cornerIndex = 0;
		
    ofLight light;
    ofEasyCam cam;
    ofMesh tri1;
    ofMesh tri2;
    ofMesh tri3;
  
  
    ofxToggle showGrid;
    ofxToggle drawWireframe;
  
    ofxFloatSlider tri1Tx0s;
    ofxFloatSlider tri1Tx0t;
    ofxFloatSlider tri1Tx1s;
    ofxFloatSlider tri1Tx1t;
    ofxFloatSlider tri1Tx2s;
    ofxFloatSlider tri1Tx2t;

    ofxFloatSlider tri2Tx0s;
    ofxFloatSlider tri2Tx0t;
    ofxFloatSlider tri2Tx1s;
    ofxFloatSlider tri2Tx1t;
    ofxFloatSlider tri2Tx2s;
    ofxFloatSlider tri2Tx2t;

    ofxFloatSlider tri3Tx0s;
    ofxFloatSlider tri3Tx0t;
    ofxFloatSlider tri3Tx1s;
    ofxFloatSlider tri3Tx1t;
    ofxFloatSlider tri3Tx2s;
    ofxFloatSlider tri3Tx2t;
  
//    ofxFloatSlider cornerScale;
    float cornerScale = 100;
    ofxPanel gui;
  
};
