#include "ofApp.h"
#include "ParticleSystem.h"



//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(60);
	camera.setAutoDistance(true);
	numParticles = 10000;
	ps = new ParticleSystem(numParticles);
	numParticles2 = 1000;
	ps2 = new ParticleSystem(numParticles);
	auto particleEmitter = std::make_shared<ParticleEmitter>();
	{
		particleEmitter->m_emitRate = (float)numParticles * 0.05f;
		
		
		//position
		auto posGenerator = std::make_shared<BoxPosGen>(); //generates particle position
		posGenerator->m_pos = ofVec3f{ 100.0, 100.0, 0.0 };
		posGenerator->m_maxStartPosOffset = ofVec3f{ 5.0, 10.0, 30.0 };
		particleEmitter->addGenerator(posGenerator);

		auto velGenerator = std::make_shared <BasicVelGen>(); //set min/max vel
		velGenerator->m_minStartVel = glm::vec3{ -10.f, 1.0f, -1.f };
		velGenerator->m_maxStartVel = glm::vec3{ -8.f, 6.f, 1.f };
		particleEmitter->addGenerator(velGenerator);

		auto timeGenerator = std::make_shared<BasicTimeGen>(); 
		timeGenerator->m_minTime = 1.0;
		timeGenerator->m_maxTime = 20.0; //10
		particleEmitter->addGenerator(timeGenerator);
	}

	ps->addEmitter(particleEmitter);
	auto particleEmitter2 = std::make_shared<ParticleEmitter>();
	{
		particleEmitter2->m_emitRate = (float)numParticles * 0.45f;
		//position

		auto posGenerator3 = std::make_shared<BoxPosGen>();
		posGenerator3->m_pos = ofVec3f{ -100.0, 100.0, 100.0 };
		posGenerator3->m_maxStartPosOffset = ofVec3f{ 0.0, 0.0, 0.0 };
		particleEmitter2->addGenerator(posGenerator3);

		auto velGenerator2 = std::make_shared < BasicVelGen>();
		velGenerator2->m_minStartVel = glm::vec3{ -5.f, 9.0f, -5.f };
		velGenerator2->m_maxStartVel = glm::vec3{ 5.f, 10.F, 5.f };
		particleEmitter2->addGenerator(velGenerator2);

		auto timeGenerator2 = std::make_shared<BasicTimeGen>();
		timeGenerator2->m_minTime = 1.0;
		timeGenerator2->m_maxTime = 10.0;
		particleEmitter2->addGenerator(timeGenerator2);

	}
	ps->addEmitter(particleEmitter2);

	auto particleEmitter3 = std::make_shared<ParticleEmitter>();
	{
		particleEmitter3->m_emitRate = (float)numParticles2 * 0.45f;
		//position

		auto posGenerator2 = std::make_shared<RoundPosGen>();
		posGenerator2->m_center = ofVec3f(0.0, 120.0, 100.0);
		posGenerator2->m_radX = 50.f;
		posGenerator2->m_radY = 50.f;
		particleEmitter3->addGenerator(posGenerator2);

		auto velGenerator3 = std::make_shared <BasicVelGen>();
		velGenerator3->m_minStartVel = glm::vec3{ -3.0f, -10.0f, 5.f };
		velGenerator3->m_maxStartVel = glm::vec3{ 3.0f, 0.0f, 15.f };
		
		particleEmitter3->addGenerator(velGenerator3);

		auto timeGenerator3 = std::make_shared<BasicTimeGen>();
		timeGenerator3->m_minTime = 1.0;
		timeGenerator3->m_maxTime = 30.0; //10
		particleEmitter3->addGenerator(timeGenerator3);

	}
	ps2->addEmitter(particleEmitter3);
	

	auto timeUpdater = std::make_shared<BasicTimeUpdater>(); //lifetime of particle
	ps->addUpdater(timeUpdater);
	ps2->addUpdater(timeUpdater);

	auto m_eulerUpdater = std::make_shared<EulerUpdater>();
	m_eulerUpdater->m_globalAcceleration = ofVec3f{ 0.0, -10.0, 0.0 };
	ps->addUpdater(m_eulerUpdater);
	ps2->addUpdater(m_eulerUpdater);

	

	auto posColorUpdater = std::make_shared<PosColorUpdater>(); //color based on position
	posColorUpdater->m_minPos = glm::vec4{ 4.5 };
	posColorUpdater->m_maxPos = glm::vec4{ 5.0 };
	ps->addUpdater(posColorUpdater);
	ps2->addUpdater(posColorUpdater);

	auto m_floorUpdater = std::make_shared<FloorUpdater>();
	m_floorUpdater->m_floorY = 50.f;
	ps->addUpdater(m_floorUpdater);
	ps2->addUpdater(m_floorUpdater);

	

	m_renderer = new OFParticleRenderer();
	m_renderer2 = new OFParticleRenderer();
	m_renderer->setup(ps);
	m_renderer2->setup(ps2);
}

//--------------------------------------------------------------
void ofApp::update()
{
	ps->update(0.1);
	ps2->update(0.1);
}

//--------------------------------------------------------------
void ofApp::draw()
{
	ofBackground(0);
	camera.begin();
	m_renderer2->draw();
	m_renderer->draw();
		
	camera.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == '1')
	{
		auto m_mouseUpdater = std::make_shared<MouseAttractor>();
		ps2->addUpdater(m_mouseUpdater);
	}
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
