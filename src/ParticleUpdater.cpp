#include "ParticleUpdater.h"


void EulerUpdater::update(float dt, ParticleData* p)
{
    const ofVec3f globalA{ dt * m_globalAcceleration.x, dt * m_globalAcceleration.y, dt * m_globalAcceleration.z};
    const float localDT = (float)dt;

    const unsigned int endId = p->m_countAlive;
    for (size_t i = 0; i < endId; ++i)
        p->m_acc[i] += globalA;

    for (size_t i = 0; i < endId; ++i)
        p->m_vel[i] += localDT * p->m_acc[i];

    for (size_t i = 0; i < endId; ++i)
        p->m_pos[i] += localDT * p->m_vel[i];
}

void MouseAttractor::update(float dt, ParticleData* p)
{
    const unsigned int endId = p->m_countAlive;

    
    for (size_t i = 0; i < endId; ++i)
    {
        ofVec3f attractPt(ofGetMouseX(), ofGetMouseY(), 0);
        force = attractPt - p->m_pos[i];
        force = glm::normalize(force);
        p->m_vel[i] *= drag;
        p->m_vel[i] += force * dt * 10.0;
    }
}

void FloorUpdater::update(float dt, ParticleData* p)
{
    const float localDT = (float)dt;

    const size_t endId = p->m_countAlive;
    for (size_t i = 0; i < endId; ++i)
    {
        if (p->m_pos[i].y < m_floorY)
        {
            ofVec3f force = p->m_acc[i];
            float normalFactor = force.dot(ofVec3f(0.0f, 1.0f, 0.0f));
            if (normalFactor < 0.0f)
                force -= ofVec3f(0.0f, 1.0f, 0.0f) * normalFactor;

            float velFactor = p->m_vel[i].dot(ofVec3f(0.0f, 1.0f, 0.0f));
            
            p->m_vel[i] -= ofVec3f(0.0f, 1.0f, 0.0f) * (1.0f + m_bounceFactor) * velFactor;

            p->m_acc[i] = force;
        }
    }
}

void BasicTimeUpdater::update(float dt, ParticleData* p)
{
    unsigned int endId = p->m_countAlive;
    const float localDT = (float)dt;

    if (endId == 0) return;

    for (size_t i = 0; i < endId; ++i)
    {
        p->m_time[i].x -= localDT;
	

        if (p->m_time[i].x < (float)0.0)
        {
            p->kill(i);
            endId = p->m_countAlive < p->m_count ? p->m_countAlive : p->m_count;
        }
    }
}


void PosColorUpdater::update(float dt, ParticleData* p)
{
    const size_t endId = p->m_countAlive;
    float scaler, scaleg, scaleb;
    float diffr = m_maxPos.x - m_minPos.x;
    float diffg = m_maxPos.y - m_minPos.y;
    float diffb = m_maxPos.z - m_minPos.z;
    for (size_t i = 0; i < endId; ++i)
    {
        scaler = (p->m_pos[i].x - m_minPos.x) / diffr;
        scaleg = (p->m_pos[i].y - m_minPos.y) / diffg;
        scaleb = (p->m_pos[i].z - m_minPos.z) / diffb;
        p->m_col[i].r = scaler;
        p->m_col[i].g = scaleg;
        p->m_col[i].b = scaleb;
        p->m_col[i].a = glm::mix(p->m_startCol[i].a, p->m_endCol[i].a, p->m_time[i].z);
    }
}

