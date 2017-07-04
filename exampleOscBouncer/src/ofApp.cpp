#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetVerticalSync(true);
	ofSetWindowShape(1024, 1024);

	//setup dsp
	{
		auto address = dsp.selectDeviceDialog();

		if (address.empty()) {
			ofSystemAlertDialog("Failed to connect to DSP. Exiting.");
			ofExit();
		}

		this->dsp.setup(address);
	}

	//setup osc receiver
	{
		this->oscReceiver.setup(4444);
	}
}

//--------------------------------------------------------------
void ofApp::update() {
	ofxOscMessage message;
	while (this->oscReceiver.getNextMessage(message)) {
		if (message.getAddress() == "/line") {
			auto count = message.getArgAsInt(0);

			this->line.clear();
			for (auto i = 0; i < count; i++) {
				auto xNorm = message.getArgAsFloat(i * 2 + 0 + 1);
				auto yNorm = message.getArgAsFloat(i * 2 + 1 + 1);

				this->line.addVertex(ofMap(xNorm, -1, +1, 0, ofGetWidth(), true)
					, ofMap(yNorm, +1, -1, 0, ofGetHeight(), true));
			}

			dsp.setPicture(this->line);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	ofBackgroundGradient(40, 0);

	ofDrawBitmapString("Listening for messages on OSC port 4444", 20, 20);
	ofDrawBitmapString("Also feel free to draw a line by hand using the mouse", 20, 30);
	ofDrawBitmapString(ofToString(this->line.getVertices().size()) + " vertices.", 20, 40);

	if (this->line.getVertices().size() == 1) {
		//special case where we draw a cross when we're doing a single point
		ofPushMatrix();
		{
			ofTranslate(this->line.getVertices()[0]);
			ofDrawLine(-10, 0, 10, 0);
			ofDrawLine(0, -10, 0, 10);
		}
		ofPopMatrix();
	}
	else {
		this->line.draw();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == ' ') {
		this->line.clear();
		this->dsp.setPicture(this->line);
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
	this->line.addVertex(x, y);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	this->line.clear();
	this->mouseDragged(x, y, button); // add the first point
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
	dsp.setPicture(this->line);
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
