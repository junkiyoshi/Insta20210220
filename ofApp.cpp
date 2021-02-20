#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetLineWidth(3);
	ofEnableDepthTest();
	ofSetRectMode(ofRectMode::OF_RECTMODE_CENTER);

	this->rect_size = 30;
	for (int x = -360; x < 360; x += this->rect_size) {

		for (int y = -360; y < 360; y += this->rect_size) {

			this->location_list.push_back(glm::vec3(x, y, 0));
		}
	}
}

//--------------------------------------------------------------
void ofApp::update() {


	for (int i = 0; i < this->location_list.size(); i++) {

		auto noise_value = ofNoise(glm::vec3(this->location_list[i].x * 0.005, this->location_list[i].y * 0.005, ofGetFrameNum() * 0.005));
		if (noise_value > 0.85) {

			this->moving_location_list.push_back(this->location_list[i]);
		}
	}

	for (int i = this->moving_location_list.size() - 1; i >= 0; i--) {

		this->moving_location_list[i] += glm::vec3(0, 0, 8);

		if (this->moving_location_list[i].z > 200) {

			this->moving_location_list.erase(this->moving_location_list.begin() + i);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	for (int i = 0; i < this->location_list.size(); i++) {

		ofSetColor(239);
		ofFill();
		ofDrawRectangle(this->location_list[i], this->rect_size, this->rect_size);

		ofSetColor(39);
		ofNoFill();
		ofDrawRectangle(this->location_list[i], this->rect_size, this->rect_size);
	}

	for (int i = 0; i < this->moving_location_list.size(); i++) {

		ofSetColor(239);
		ofFill();
		ofDrawRectangle(this->moving_location_list[i], this->rect_size, this->rect_size);

		ofSetColor(39);
		ofNoFill();
		ofDrawRectangle(this->moving_location_list[i], this->rect_size, this->rect_size);
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}