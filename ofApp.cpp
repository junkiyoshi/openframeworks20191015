#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofEnableDepthTest();

	auto R = 300.f;
	auto r = 80.f;
	auto u = 0.f;
	auto u_step = 10.f;
	auto v_step = 5.f;

	for (int i = 0; i < 18; i++) {

		float angle = (i * 10) * DEG_TO_RAD;
		auto rotation = glm::rotate(glm::mat4(), angle, glm::vec3(0, 0, 1));

		for (auto v = 0; v < 360; v += v_step) {

			this->mesh.addVertex(glm::vec4(this->make_point(R, r, u, v), 0) * rotation);
			this->mesh.addColor(ofColor(0));
			this->mesh.addVertex(glm::vec4(this->make_point(R, r, u + u_step, v + v_step), 0) * rotation);
			this->mesh.addColor(ofColor(0));
			this->mesh.addVertex(glm::vec4(this->make_point(R, r, u, v + v_step), 0) * rotation);
			this->mesh.addColor(ofColor(0));
			this->mesh.addVertex(glm::vec4(this->make_point(R, r, u - u_step, v), 0) * rotation);
			this->mesh.addColor(ofColor(0));

			auto index = this->mesh.getVertices().size() - 1;

			this->mesh.addIndex(index - 3);
			this->mesh.addIndex(index - 2);
			this->mesh.addIndex(index - 1);

			this->mesh.addIndex(index);
			this->mesh.addIndex(index - 3);
			this->mesh.addIndex(index - 1);

			u += u_step;
		}
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	ofColor color;
	for (auto i = 0; i < this->mesh.getVertices().size(); i += 1) {

		auto location = this->mesh.getVertices()[i];
		auto len = glm::length(location);

		color.setHsb(ofMap(ofNoise(location.x * 0.005, location.y * 0.005, location.z * 0.005, ofGetFrameNum() * 0.01), 0, 1, 72, 192), 200, 255);
		this->mesh.setColor(i, color);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	this->mesh.draw();

	this->cam.end();
}

//--------------------------------------------------------------
glm::vec3 ofApp::make_point(float R, float r, float u, float v) {

	// 数学デッサン教室 描いて楽しむ数学たち　P.31

	u *= DEG_TO_RAD;
	v *= DEG_TO_RAD;

	auto x = (R + r * cos(u)) * cos(v);
	auto y = (R + r * cos(u)) * sin(v);
	auto z = r * sin(u);

	return glm::vec3(x, y, z);
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}