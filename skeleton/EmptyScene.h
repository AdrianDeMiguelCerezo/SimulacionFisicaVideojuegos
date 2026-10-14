#pragma once

#include "Scene.h"
#include "RenderUtils.hpp"
#include "Particle.h"
#include <vector>

class EmptyScene : public Scene {
public:
    explicit EmptyScene(std::string name) : Scene(std::move(name)) {}

    void init() override {
        // Ejemplo: Creación de una esfera usando las utilidades de render existentes
        physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(2.0f));
        m_transform = physx::PxTransform(physx::PxVec3(0.0f, 10.0f, 0.0f));

        // Se registra el RenderItem exactamente como en la plantilla original
        //m_renderItem = new RenderItem(shape, &m_transform, Vector4(1.0f, 0.0f, 0.0f, 1.0f));

        //particle = new Particle(Vector3(0, 0, 0), Vector3(10, 0, 0),Vector3(2,0,0),0.8);
        p_gen_uniform = new ParticleGenerator(Vector3D(0, 0, 0),Vector3D(0,0,0), Vector3D(-100.0f, -100.0f, -100.0f), Vector3D(100.0f, 100.0f, 100.0f), Vector3D(0.0f, 0.0f, 0.0f), 0.8f);
        p_gen_normal = new ParticleGenerator(Vector3D(100, 0, 0),Vector3D(100,0,0), 100.0, 50.0, Vector3D(0, 0, 0), 0.8f);
        p_gen_mist = new ParticleGenerator(Vector3D(-100, -100, -100), Vector3D(-100, 100, 100), 500.0f, 300.0f, Vector3D(0.0f, 0.0f, 0.0f), 0.8f,10, ParticleGenerator::MIST_WHITE);
        p_gen_waterfall = new ParticleGenerator(Vector3D(200, 100, 0), Vector3D(200, 100, 100), 150.0f, 50.0f, Vector3D(0, 0, 0), 0.7f,15, ParticleGenerator::WATER_BLUE);
    }

    void update(double dt) override {
        // Lógica/Integración del alumno (por ejemplo, movimiento simple)
        //m_transform.p.y -= static_cast<float>(9.8 * dt);
        if (p_gen_uniform)p_gen_uniform->integrate_gen(dt);
        if (p_gen_normal)p_gen_normal->integrate_gen(dt);
        if (p_gen_mist) p_gen_mist->integrate_gen(dt);
        if (p_gen_waterfall) p_gen_waterfall->integrate_gen(dt);
    }

    void keyPress(unsigned char key, const physx::PxTransform& camera) override {
        if (key == 'r' || key == 'R') {
            m_transform.p = physx::PxVec3(0.0f, 10.0f, 0.0f); // Reset
        }

        //Invocar projectil normal
        //if (key == 'p' || key == 'P') {
        //    Camera* cam = GetCamera();
        //    projectiles.push_back(new Projectile(cam->getTransform().p, cam->getDir() * 25, cam->getDir() * 25, cam->getDir() * 2,0.8));
        //}


        //Cambiar masa
        if (key == 'f' || key == 'F') {
            p_gen_uniform->changeMass(1.0f);
            p_gen_normal->changeMass(1.0f);
            p_gen_mist->changeMass(1.0f);
            p_gen_waterfall->changeMass(1.0f);
        }
        if (key == 'c' || key == 'C') {
            p_gen_uniform->changeMass(-1.0f);
            p_gen_normal->changeMass(-1.0f);
            p_gen_mist->changeMass(-1.0f);
            p_gen_waterfall->changeMass(-1.0f);
        }

        //Cambiar gravedad
        if (key == 'g' || key == 'G') {
            p_gen_uniform->changeGravity(1.0f);
            p_gen_normal->changeGravity(1.0f);
            p_gen_mist->changeGravity(1.0f);
            p_gen_waterfall->changeGravity(1.0f);
        }
        if (key == 'b' || key == 'B') {
            p_gen_uniform->changeGravity(-1.0f);
            p_gen_normal->changeGravity(-1.0f);
            p_gen_mist->changeGravity(-1.0f);
            p_gen_waterfall->changeGravity(-1.0f);
        }
    }

    void cleanup() override {
        if (m_renderItem) {
            m_renderItem->release(); // Deregistra y destruye el item
            m_renderItem = nullptr;
        }
        if (p_gen_uniform) {
            delete p_gen_uniform;
        }
        if (p_gen_normal) {
            delete p_gen_normal;
        }
        if (p_gen_mist) {
            delete p_gen_mist;
        }
        if (p_gen_waterfall) {
            delete p_gen_waterfall;
        }
    }

private:
    physx::PxTransform m_transform;
    RenderItem* m_renderItem{ nullptr };
};