#pragma once

#include "LGDspDll.h"
#include "ofMain.h"

class ofxSollingerDSP {
public:
	static string selectDeviceDialog();

	bool setup(const string & address);
	bool getIsConnected() const;

	vector<string> getCatalogNames() const;

	void setPicture(const ofPolyline &, const ofRectangle & bounds = ofGetCurrentViewport());
protected:
	bool isConnected = false;
	void printError() const;
};