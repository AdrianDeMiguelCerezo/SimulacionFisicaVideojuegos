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
        //p_gen_uniform = new ParticleGenerator(Vector3D(0, 0, 0),Vector3D(0,0,0), Vector3D(-100.0f, -100.0f, -100.0f), Vector3D(100.0f, 100.0f, 100.0f), Vector3D(0.0f, 0.0f, 0.0f), 0.8f);
        //p_gen_normal = new ParticleGenerator(Vector3D(100, 0, 0),Vector3D(100,0,0), 100.0, 50.0, Vector3D(0, 0, 0), 0.8f);
        //p_gen_mist = new ParticleGenerator(Vector3D(-100, -100, -100), Vector3D(-100, 100, 100), 500.0f, 300.0f, Vector3D(0.0f, 0.0f, 0.0f), 0.8f,10, ParticleGenerator::MIST_WHITE);
        //p_gen_waterfall = new ParticleGenerator(Vector3D(200, 100, 0), Vector3D(200, 100, 100), 150.0f, 50.0f, Vector3D(0, 0, 0), 0.7f,15, ParticleGenerator::WATER_BLUE);

        //p_gen_grav = new ParticleGenerator(Vector3D(0, 0, 0), Vector3D(0, 0, 0), 100.0, 50.0, Vector3D(0, 0, 0), 0.8, 1,false);
        //p_gen_grav_force = new ParticleGenerator(Vector3D(0, 0, 0), Vector3D(0, 0, 0), 100.0, 50.0, Vector3D(0, 0, 0), 0.8, 10);

        projectiles = new ParticleSystem();
        part_syst_1 = new ParticleSystem();
        part_syst_2 = new ParticleSystem();

        

        grav_force = new GravityForceGenerator(Vector3(0, -10, 0));
        wind_force = new WindForceGenerator(Vector3D(20, 100, -20), Vector3D(-20, -100, 0), Vector3D(0, 0, 100), Vector3D(0, 50, 50), 0.8);
        twister = new TwisterGenerator(Vector3D(0, 0, 0), 500,0.1);
        explosion = new ExplosionGenerator(50.0f, Vector3D(0, 0, 0), 10000.0f, 0.2);

        projectiles->addForceGenerator(grav_force);
        part_syst_1->addForceGenerator(grav_force);
        part_syst_1->addForceGenerator(twister);
        part_syst_2->addForceGenerator(wind_force);
        part_syst_2->addForceGenerator(explosion);

        ParticleGenerator* part_gen_1 = new ParticleGenerator(part_syst_1, Vector3D(0, 0, 0), Vector3D(0, 0, 0), Vector3D(-10, -10, -10), 
            Vector3D(10, 10, 10), 0.8, 2, 5,ParticleGenerator::MIST_WHITE);
        part_syst_1->addParticleGenerator(part_gen_1);

        ParticleGenerator* part_gen_2 = new ParticleGenerator(part_syst_2, Vector3D(-20, -20, -20), Vector3D(20, 20, -20),
            100, 50, 0.8, 2, 3, ParticleGenerator::WATER_BLUE);
        part_syst_2->addParticleGenerator(part_gen_2);
    }

    void update(double dt) override {
        // Lógica/Integración del alumno (por ejemplo, movimiento simple)
        //m_transform.p.y -= static_cast<float>(9.8 * dt);
        //if (p_gen_uniform)p_gen_uniform->integrate_gen(dt);
        //if (p_gen_normal)p_gen_normal->integrate_gen(dt);
        //if (p_gen_mist) p_gen_mist->integrate_gen(dt);
        //if (p_gen_waterfall) p_gen_waterfall->integrate_gen(dt);
        //if (p_gen_grav)p_gen_grav->integrate_gen(dt);
        //if (p_gen_grav_force)p_gen_grav_force->integrate_gen(dt);

        projectiles->integrateSystem(dt);
        part_syst_1->integrateSystem(dt);
        part_syst_2->integrateSystem(dt);

        explosion->addTime(dt);
    }

    void keyPress(unsigned char key, const physx::PxTransform& camera) override {
        if (key == 'r' || key == 'R') {
            m_transform.p = physx::PxVec3(0.0f, 10.0f, 0.0f); // Reset
        }

        //Disparar proyectil
        if (key == 'p') {
            Camera* cam = GetCamera();
            projectiles->addProjectile(new Particle(projectiles, cam->getTransform().p, Vector3D(50, 50, 50) * Vector3D(cam->getDir()), 1, 0.6, true));
        }

        //Disparar proyectil cubicoo que vaya mas lento
        if (key == 'P') {
            Camera* cam = GetCamera();
            projectiles->addProjectile(new Particle(projectiles, cam->getTransform().p, Vector3D(10, 10, 10) * Vector3D(cam->getDir()), 1, 0.6, true,
                physx::PxBoxGeometry(2.0f,2.0f,2.0f), Vector4(1, 1, 1, 1)));
        }

        //Cambiar estado de activo de la gravedad
        if (key == 'g' || key == 'G') {
            grav_force->setActive(!grav_force->getActive());
        }

        //Cambiar el estado de activo del viento
        if (key == 'h' || key == 'H') {
            wind_force->setActive(!wind_force->getActive());
        }

        //Cambiar el estado de activo del torbellino
        if (key == 'j' || key == 'J') {
            twister->setActive(!twister->getActive());
        }

        //Cambiar el estado de activo de la explosion
        if (key == 'E') {
            explosion->setActive(!explosion->getActive());
        }


        //Explotar
        if (key == 'e') {
            explosion->explode();
        }


    }

    void cleanup() override {
        if (m_renderItem) {
            m_renderItem->release(); // Deregistra y destruye el item
            m_renderItem = nullptr;
        }
        if (projectiles) {
            delete projectiles;
        }
        if (part_syst_1) {
            delete part_syst_1;
        }
        if (part_syst_2) {
            delete part_syst_2;
        }
        if (grav_force) {
            delete grav_force;
        }
        if (wind_force) {
            delete wind_force;
        }
        if (twister) {
            delete twister;
        }
        if (explosion) {
            delete explosion;
        }
    }

private:
    physx::PxTransform m_transform;
    RenderItem* m_renderItem{ nullptr };
};