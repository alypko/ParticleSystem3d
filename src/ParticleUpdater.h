#pragma once
#include "ofMain.h"
#include "ParticleSystem.h"



class EulerUpdater : public ParticleUpdater
{
	public:
		ofVec3f m_globalAcceleration{ 0.0f };
	public:
		virtual void update(float dt, ParticleData* p) override;
};

class FloorUpdater : public ParticleUpdater
{
public:
	float m_floorY{ 0.0f };
	float m_bounceFactor{ 0.5f };
public:
	virtual void update(float dt, ParticleData* p) override;
};

class BasicTimeUpdater : public ParticleUpdater
{
public:
	virtual void update(float dt, ParticleData* p) override;
};


class PosColorUpdater : public ParticleUpdater
{
public:
	glm::vec3 m_minPos{ 0.0 };
	glm::vec3 m_maxPos{ 1.0 };
public:
	virtual void update(float dt, ParticleData* p) override;
};