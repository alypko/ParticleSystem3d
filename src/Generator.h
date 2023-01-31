#pragma once
#include "ParticleSystem.h"




class BoxPosGen : public ParticleGenerator
{
	public:
		ofVec3f m_pos{ 0.0 };
		ofVec3f m_maxStartPosOffset{ 0.0 };
	public:
		BoxPosGen() { }

		virtual void generate(double dt, ParticleData* p, size_t startId, size_t endId) override;
};

class RoundPosGen : public ParticleGenerator
{
	public:
		ofVec3f m_center{ 0.0 };
		float m_radX{ 0.0 };
		float m_radY{ 0.0 };
	public:
		RoundPosGen() { }
		RoundPosGen(const ofVec3f& center, double radX, double radY)
			: m_center(center)
			, m_radX((float)radX)
			, m_radY((float)radY)
		{ }

	virtual void generate(double dt, ParticleData* p, size_t startId, size_t endId) override;
};

class BasicTimeGen : public ParticleGenerator
{
	public:
		float m_minTime{ 0.0 };
		float m_maxTime{ 0.0 };
	public:
		BasicTimeGen() { }

	virtual void generate(double dt, ParticleData* p, size_t startId, size_t endId) override;
};


class BasicVelGen : public ParticleGenerator
{
public:
	glm::vec3 m_minStartVel{ 0.0 };
	glm::vec3 m_maxStartVel{ 0.0 };
public:
	BasicVelGen() { }

	virtual void generate(double dt, ParticleData* p, size_t startId, size_t endId) override;
};