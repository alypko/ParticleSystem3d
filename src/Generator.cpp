#include <glm/gtc/random.hpp>
#include "Generator.h"



void BoxPosGen::generate(double dt, ParticleData* p, size_t startId, size_t endId)
{
	glm::vec3 posMin{ m_pos.x - m_maxStartPosOffset.x, m_pos.y - m_maxStartPosOffset.y, m_pos.z - m_maxStartPosOffset.z };
	glm::vec3 posMax{ m_pos.x + m_maxStartPosOffset.x, m_pos.y + m_maxStartPosOffset.y, m_pos.z + m_maxStartPosOffset.z };

	for (size_t i = startId; i < endId; ++i)
	{
		p->m_pos[i] = glm::linearRand(posMin, posMax);
	}
}

void RoundPosGen::generate(double dt, ParticleData* p, size_t startId, size_t endId)
{
	for (size_t i = startId; i < endId; ++i)
	{
		double ang = glm::linearRand(0.0, PI * 2.0);
		p->m_pos[i] = m_center + ofVec3f(m_radX * sin(ang), m_radY * cos(ang), 0.0);
	}
}

void BasicTimeGen::generate(double dt, ParticleData* p, size_t startId, size_t endId)
{
	for (size_t i = startId; i < endId; ++i)
	{
		p->m_time[i].x  = glm::linearRand(m_minTime, m_maxTime);
	}
}


void BasicVelGen::generate(double dt, ParticleData* p, size_t startId, size_t endId)
{
	for (size_t i = startId; i < endId; ++i)
	{
		p->m_vel[i] = glm::linearRand(m_minStartVel, m_maxStartVel);
	}
}