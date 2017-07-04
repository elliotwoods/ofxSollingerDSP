#include "ofxSollingerDSP.h"

//----------
string ofxSollingerDSP::selectDeviceDialog() {
	char buffer[256];

	if (!LGDspDll_SelectDialog(buffer, 256))
	{
		// Aborted by user => No error
		return "";
	}

	return string(buffer);
}

//----------
bool ofxSollingerDSP::setup(const string & address) {
	if (!LGDspDll_Connect(address.c_str()))
	{
		this->printError();
		this->isConnected = false;
		return false;
	}
	else {
		this->isConnected = true;
		return true;
	}
}

//----------
bool ofxSollingerDSP::getIsConnected() const {
	return this->isConnected;
}

//----------
vector<string> ofxSollingerDSP::getCatalogNames() const {
	if (!LGDspDll_GetCatalogNames()) {
		this->printError();
		return vector<string>();
	}

	char buffer[256];
	vector<string> results;
	while (LGDspDll_GetNextCatalogName(buffer, 256)) {
		results.push_back(string(buffer));
	}

	return results;
}

//----------
void ofxSollingerDSP::setPicture(const ofPolyline & line, const ofRectangle & bounds /*= ofGetCurrentViewport()*/) {
	vector<DspPoint> dspPoints;
	dspPoints.reserve(line.size());

	for (const auto & point : line.getVertices()) {
		dspPoints.emplace_back(

			(short)ofMap(point.x
				, bounds.getLeft()
				, bounds.getRight()
				, numeric_limits<short>::min()
				, numeric_limits<short>::max()
				, true)

			,

			(short)ofMap(point.y
				, bounds.getTop()
				, bounds.getBottom()
				, numeric_limits<short>::max()
				, numeric_limits<short>::min()
				, true)
			, 0
			, 0
			, 1
			, 0
			, false
			, false
			, & point == & line.getVertices().back()
		);
	}

	//if empty then add a blank point
	if (dspPoints.empty()) {
		dspPoints.push_back(DspPoint(0, 0, 0, 0, 0, 0, true, false, true));
	}

	if (!LGDspDll_SetPicture("TestCat", "TestPic", dspPoints.size(), (DspPoint*) dspPoints.data())) {
		this->printError();
	}
}

//----------
void ofxSollingerDSP::printError() const {
	char buffer[256];

	if (LGDspDll_GetLastError(buffer, 256))
	{
		ofLogError("ofxSollingerDSP") << buffer;
	}
}

