#pragma once

#include "ofMain.h"
#include <iostream>

class ParticleData
{
    public:
        std::unique_ptr<ofVec3f[]> m_pos;
        std::unique_ptr<glm::vec4[]> m_col;
        std::unique_ptr<glm::vec4[]> m_startCol;
        std::unique_ptr<glm::vec4[]> m_endCol;
        std::unique_ptr<ofVec3f[]> m_vel;
        std::unique_ptr<ofVec3f[]> m_acc;
        std::unique_ptr<ofVec3f[]> m_time;
        std::unique_ptr<bool[]> m_alive;

        size_t m_count{ 0 };
        size_t m_countAlive{ 0 };
    public:
        ParticleData() { }
        explicit ParticleData(size_t maxCount) { generate(maxCount); }
        ~ParticleData() { }

        ParticleData(const ParticleData&) = delete;
        ParticleData& operator=(const ParticleData&) = delete;

        void generate(size_t maxSize);
        void kill(size_t id);
        void wake(size_t id);
        void swapData(size_t a, size_t b);
};

class ParticleGenerator
{
    public:
        ParticleGenerator() { }
        virtual ~ParticleGenerator() { }

        virtual void generate(double dt, ParticleData* p, size_t startId, size_t endId) = 0;
};

class ParticleEmitter
{
    protected:
        std::vector<std::shared_ptr<ParticleGenerator>> m_generators;
    public:
        float m_emitRate{ 0.0 };
    public:
        ParticleEmitter() { }
        virtual ~ParticleEmitter() { }

        virtual void emit(double dt, ParticleData* p);

        void addGenerator(std::shared_ptr<ParticleGenerator> gen) { m_generators.push_back(gen); }
};

class ParticleUpdater
{
    public:
        ParticleUpdater() { }
        virtual ~ParticleUpdater() { }

        virtual void update(float dt, ParticleData* p) = 0;
};



class ParticleSystem : public ofSpherePrimitive
{
    protected:
        ParticleData m_particles;
        ParticleData m_aliveParticles;

        size_t m_count;

        std::vector<std::shared_ptr<ParticleEmitter>> m_emitters;
        std::vector<std::shared_ptr<ParticleUpdater>> m_updaters;

    public:
        explicit ParticleSystem(size_t maxCount);
        virtual ~ParticleSystem() { }

        ParticleSystem(const ParticleSystem&) = delete;
        ParticleSystem& operator=(const ParticleSystem&) = delete;

        virtual void update(double dt);

        virtual size_t numAllParticles() const { return m_particles.m_count; }
        virtual size_t numAliveParticles() const { return m_particles.m_countAlive; }

        void addEmitter(std::shared_ptr<ParticleEmitter> em) { m_emitters.push_back(em); }
        void addUpdater(std::shared_ptr<ParticleUpdater> up) { m_updaters.push_back(up); }

        ParticleData* finalData() { return &m_particles; }

    

};

class OFParticleRenderer {
public:
    void setup(ParticleSystem* sys) {
        m_system = sys;

        /*cout << m_system->finalData()->m_pos.get()->x << "\n";
        m_vbo.setVertexData(sys->finalData()->m_pos.get() + 1024, count, GL_DYNAMIC_DRAW);
        m_vbo.setColorData(sys->finalData()->m_col.get(), count, GL_DYNAMIC_DRAW);*/
        /*ofEnablePointSprites();*/
        //cout << m_vbo << ;
        //glEnable(GL_DEPTH_TEST);
    }


    void draw() {
        const size_t count = m_system->numAliveParticles();
        
        if (count > 0) {
            //ofTranslate(ofGetWidth()/2, ofGetHeight()/2, 100);
            //ofRotate(ofGetElapsedTimef() * 20.0, 1, 1, 0
            /*ofEnableBlendMode(OF_BLENDMODE_ADD);
            ofEnablePointSprites();*/
            //m_vbo.draw(GL_POINTS, 0, count);
            for (size_t i = 0; i < count; ++i)
            {
                ofPushStyle();
                ofSetColor(m_system->finalData()->m_col[i].r, m_system->finalData()->m_col[i].g, m_system->finalData()->m_col[i].b);
                ofDrawSphere(m_system->finalData()->m_pos[i], 0.5);
                ofPopStyle();
            }
            
        }
    }

private:
    ParticleSystem* m_system;
    ofVbo m_vbo;
};