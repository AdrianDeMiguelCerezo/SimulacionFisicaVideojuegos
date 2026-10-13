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
        p_gen = new ParticleGenerator(Vector3D(0, 0, 0), Vector3D(50.0f, 50.0f, 50.0f), Vector3D(100.0f, 100.0f, 100.0f), Vector3D(10.0f, 10.0f, 10.0f), 0.8f);
    }

    void update(double dt) override {
        // Lógica/Integración del alumno (por ejemplo, movimiento simple)
        //m_transform.p.y -= static_cast<float>(9.8 * dt);
        p_gen->integrate_gen(dt);
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
            p_gen->changeMass(1.0f);
        }
        if (key == 'c' || key == 'C') {
            p_gen->changeMass(-1.0f);
        }

        //Cambiar gravedad
        if (key == 'g' || key == 'G') {
            p_gen->changeGravity(1.0f);
        }
        if (key == 'b' || key == 'B') {
            p_gen->changeGravity(-1.0f);
        }
    }

    void cleanup() override {
        if (m_renderItem) {
            m_renderItem->release(); // Deregistra y destruye el item
            m_renderItem = nullptr;
        }
        if (p_gen) {
            delete p_gen;
        }
    }

private:
    physx::PxTransform m_transform;
    RenderItem* m_renderItem{ nullptr };
};