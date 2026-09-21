#include "Scene0.h"


void Scene0::init() {
	physx::PxShape* shape1=CreateShape(physx::PxSphereGeometry(2.0f));
	m_transform = physx::PxTransform(physx::PxVec3(0.0f,0.0f,0.0f));
	m_renderItem=new RenderItem(shape1, &m_transform, Vector4(0.0f,0.0f,1.0f,1.0f));
}

void Scene0::cleanup() {
	if (m_renderItem) {
		m_renderItem->release();
		m_renderItem = nullptr;
	}
}
