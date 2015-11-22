#include "testApp.h"
#include "ofxCv.h"
#include "ofBitmapFont.h"

int tolerance = 30;
ofxCvBlob theBlob;

//--------------------------------------------------------------
void drawMarker(float size, const ofColor & color){
    ofDrawAxis(size);
    ofPushMatrix();
        // move up from the center by size*.5
        // to draw a box centered at that point
        ofTranslate(0,size*0.5,0);
        ofFill();
        ofSetColor(color,50);
        ofBox(size);
        ofNoFill();
        ofSetColor(color);
        ofBox(size);
    ofPopMatrix();
}
//--------------------------------------------------------------
void testApp::setup(){

    string boardName = "boardConfiguration.yml";
    ofSetVerticalSync(true);
    img_width = 640;
    img_height = 480;
    cam.setDeviceID(0);
    cam.setDesiredFrameRate(30.0);
    cam.initGrabber(640,480);
    video = &cam;

    img.allocate(img_width,img_height);
    img2.allocate(img_width,img_height);

    hsvImg.allocate(img_width, img_height);
    grayImg0.allocate(img_width,img_height);
    grayImg.allocate(img_width,img_height);
    grayImg2.allocate(img_width,img_height);
    grayImg3.allocate(img_width,img_height);
    grayImg4.allocate(img_width,img_height);
    image.allocate(img_width, img_height);
    videoImage.allocate(img_width, img_height,OF_IMAGE_COLOR);


    // TODO: initialize ArUco
    aruco.setup("intrinsics.int", video->getWidth(), video->getHeight(), boardName);

    std::cout<< "w=" << video->getWidth() << std::endl;
    
    
    ofEnableAlphaBlending();
}

//--------------------------------------------------------------
void testApp::update(){



    video->update();
    if(video->isFrameNew()){

        ofPixels pixels;
        ofPixels alphaPixels;
        cam.getTextureReference().readToPixels(pixels);
        alphaPixels.allocate(pixels.getWidth(),pixels.getHeight(),OF_PIXELS_RGBA);
        // TODO: detect board
        aruco.detectBoards(video->getPixelsRef());


        img.setFromPixels(cam.getPixelsRef());
        //img.mirror(false,true);

        //img.convertRgbToHsv();
//        hsvImg = img;
//        hsvImg.convertRgbToHsv();

        grayImg0=img;

        img2=img;

        hsvImg = grayImg0;
        hsvImg.convertRgbToHsv();

        grayImg=img;



        for (int j =0; j<img_height; ++j)
        {
            for (int i=0; i<img_width ; ++i)
            {

                if( ofInRange(hsvImg.getPixelsRef().getColor(i,j).getBrightness(),0,50))
                {

                  grayImg.getPixelsRef().setColor(i,j,ofColor::black);


                }


                else
                {
                  if( ofInRange(hsvImg.getPixelsRef().getColor(i,j).getBrightness(),150,255))
                      grayImg.getPixelsRef().setColor(i,j,ofColor::black);
                  else
                      grayImg.getPixelsRef().setColor(i,j,ofColor::white);


                 }


            }
        }

        grayImg.erode_3x3();

        grayImg.flagImageChanged();

        for (int j =0; j<pixels.getHeight()/*img_height*/; ++j)
        {
            for (int i=0; i<pixels.getWidth()/*img_width*/ ; ++i)
            {

                if(grayImg.getPixelsRef().getColor(i,j)==ofColor::black)
                {//ofSetColor(255, 255, 255, 0);
                 //img2.getPixelsRef().setColor(i,j,ofColor(0,0,0,0));
                    ofColor ct= ofColor(0,0,0,0);
                    alphaPixels.setColor(i,j,ct);

                }
                else
                {

                    ofColor c=img.getPixelsRef().getColor(i,j);
                    alphaPixels.setColor(i,j,c);

                }
//                ofColor c=ofColor(0,255,255,70);
//                alphaPixels.setColor(i,j,c);
            }
        }



//        for(int i=0;i<aruco.getNumMarkers();i++){
//                    aruco.begin(i);

//                    aruco.end();
//                }



        //img2.setFromPixels(alphaPixels);
        videoImage.setFromPixels(alphaPixels);

    }

}

//--------------------------------------------------------------
void testApp::draw(){
    ofSetColor(255);
    video->draw(0,0);
    grayImg.draw(640,0);
    //img.d
//    videoImage.draw(0,0);

    //videoTest->draw(0,0);

    //TODO: draw detected markers and board
for(int i=0;i<aruco.getNumMarkers();i++){
            aruco.begin(i);
            //ofDrawAxis(0.2);
            //ofDrawPlane(0.15,0.15);

            //drawMarker(0.15,ofColor::red);
            aruco.end();
        }


if(aruco.getBoardProbability()>0.2){
        for(int i=0;i<aruco.getNumBoards();i++){
            aruco.beginBoard(i);
            ofSetColor(ofColor::red,75);
            ofDrawBox(0.2,0.2,0.2);
            //videoImage.draw(640,0);

            aruco.end();
        }
    }
ofSetColor(255);
videoImage.draw(0,0);


}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){

}
