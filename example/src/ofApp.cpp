#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);

	auto address = dsp.selectDeviceDialog();

	if (address.empty()) {
		ofSystemAlertDialog("Failed to connect to DSP. Exiting.");
		ofExit();
	}

	this->dsp.setup(address);

	auto catalogNames = this->dsp.getCatalogNames();
	for (const auto & catalogName : catalogNames) {
		cout << catalogName << endl;
	}
}

//--------------------------------------------------------------
void ofApp::update(){
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackgroundGradient(40, 0);
	ofDrawBitmapString("Draw a shape with the mouse. Release mouse to send shape", 20, 20);
	this->line.draw();
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
	this->line.addVertex(x, y);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	this->line.clear();
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	dsp.setPicture(this->line);
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
