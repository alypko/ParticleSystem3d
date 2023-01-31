#pragma once

#include "ofMain.h"
#include "ParticleSystem.h"
#include "Generator.h"
#include "ParticleUpdater.h"

class ofApp : public ofBaseApp{

	public:
		ParticleSystem* ps;
		ParticleSystem *ps2;
		OFParticleRenderer* m_renderer;
		OFParticleRenderer* m_renderer2;
		ofEasyCam camera;
		ofImage backgroundImage;
		size_t numParticles;
		size_t numParticles2;

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
		
};
