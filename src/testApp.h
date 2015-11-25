#pragma once

#include "ofMain.h"
#include "ofxAruco.h"
#include "ofxCvContourFinder.h"
#include "ofxCvHaarFinder.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

        ofVideoGrabber cam;
		ofVideoPlayer player;
        ofMesh mesh;

		ofBaseVideoDraws * video;
        ofBaseVideoDraws * videoTest;
		ofxAruco aruco;
        ofxCvContourFinder contour;
        int img_width, img_height;

        ofxCvColorImage img;
        ofxCvColorImage img2;
        ofxCvColorImage hsvImg;

        ofxCvGrayscaleImage grayImg0;
        ofxCvGrayscaleImage grayImg;


        ofColor targetColorHsv;
        ofImage videoImage;

        ofxCvGrayscaleImage image;
};
