#pragma once
#include "Scene.h"
#include "RenderUtils.hpp"
class Vector3D;
class Scene0:public Scene
{
private:
	physx::PxTransform m_transform;
	RenderItem* m_renderItem{ nullptr };

	physx::PxTransform m_transform_x;
	RenderItem* m_renderItem_x{ nullptr };

	physx::PxTransform m_transform_y;
	RenderItem* m_renderItem_y{ nullptr };

	physx::PxTransform m_transform_z;
	RenderItem* m_renderItem_z{ nullptr };

	physx::PxTransform m_transform_P1;
	RenderItem* m_renderItem_P1{ nullptr };

	physx::PxTransform m_transform_P2;
	RenderItem* m_renderItem_P2{ nullptr };

	physx::PxTransform m_transform_P3;
	RenderItem* m_renderItem_P3{ nullptr };

	physx::PxTransform m_transform_P4;
	RenderItem* m_renderItem_P4{ nullptr };

	physx::PxTransform m_transform_A;
	RenderItem* m_renderItem_A{ nullptr };

	physx::PxTransform m_transform_B;
	RenderItem* m_renderItem_B{ nullptr };

	std::vector<physx::PxTransform> pathTrans;
	std::vector<RenderItem*> pathVec;
public:
	Scene0(std::string name) :Scene(std::move(name)) {}
	virtual ~Scene0() {};

	void init() override;
	void cleanup() override;

    void update(double dt) override {
    }

    void keyPress(unsigned char key, const physx::PxTransform& camera) override {
    }

	Vector4 darColorPorEscalar(float esc);
	void renderItemPorPosicion(physx::PxTransform& trans, RenderItem* renderI, float escalar=0);

	void renderPath(Vector3D A, Vector3D B);
};

