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

        particle = new Particle(Vector3(0, 0, 0), Vector3(10, 0, 0),Vector3(2,0,0),0.8);
    }

    void update(double dt) override {
        // Lógica/Integración del alumno (por ejemplo, movimiento simple)
        //m_transform.p.y -= static_cast<float>(9.8 * dt);
        particle->integrate(dt);
        for (Projectile* p : projectiles) {
            p->integrate(dt);
        }
    }

    void keyPress(unsigned char key, const physx::PxTransform& camera) override {
        if (key == 'r' || key == 'R') {
            m_transform.p = physx::PxVec3(0.0f, 10.0f, 0.0f); // Reset
        }

        //Invocar projectil normal
        if (key == 'p' || key == 'P') {
            Camera* cam = GetCamera();
            projectiles.push_back(new Projectile(cam->getTransform().p, cam->getDir() * 10, cam->getDir() * 2, cam->getDir() * 2,0.8));
        }
        //Invocar projectil cubico y lento
        if (key == 'o' || key == 'O') {
            Camera* cam = GetCamera();
            projectiles.push_back(new Projectile(cam->getTransform().p, cam->getDir() * 10, cam->getDir() * 5, cam->getDir() * 2, 0.5,physx::PxBoxGeometry(2.0f,2.0f,2.0f)));
        }


        //Cambiar masa
        if (key == 'f' || key == 'F') {
            for (Projectile* p : projectiles) {
                p->changeMass(1.0f);
            }
        }
        if (key == 'c' || key == 'C') {
            for (Projectile* p : projectiles) {
                p->changeMass(-1.0f);
            }
        }

        //Cambiar gravedad
        if (key == 'g' || key == 'G') {
            for (Projectile* p : projectiles) {
                p->changeGravity(0.5f);
            }
        }
        if (key == 'b' || key == 'B') {
            for (Projectile* p : projectiles) {
                p->changeGravity(-0.5f);
            }
        }
    }

    void cleanup() override {
        if (m_renderItem) {
            m_renderItem->release(); // Deregistra y destruye el item
            m_renderItem = nullptr;
        }
        if (particle) {
            delete particle;
            particle = nullptr;
        }
        for (Projectile* p : projectiles) {
            delete p;
        }
    }

private:
    physx::PxTransform m_transform;
    RenderItem* m_renderItem{ nullptr };

    Particle* particle;
};