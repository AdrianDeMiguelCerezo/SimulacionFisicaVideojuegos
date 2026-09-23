#include "Scene0.h"
#include "Vector3D.h"


void Scene0::init() {
	physx::PxShape* shape1=CreateShape(physx::PxSphereGeometry(2.0f));
	m_transform = physx::PxTransform(physx::PxVec3(0.0f,0.0f,0.0f));
	m_renderItem=new RenderItem(shape1, &m_transform, Vector4(0.0f,0.0f,0.0f,1.0f));

	Vector3D u = Vector3D(3.0f, 1.0f, 0.0f);
	Vector3D v = Vector3D(0.0f, 4.0f, 0.0f);
	Vector3D w = u.cross(v);
	//Vector3D w = v.cross(u);
	//Si se invierte el producto vectorial la esfera azul cambia de lado perpendicular en el que está.
	//u.cross(v) lo pone en la izquierda y v.cross(u) lo pone en la derecha.

	u=u.normalize();
	v=v.normalize();
	w=w.normalize();
	u = u * 5.0f;
	v = v * 5.0f;
	w = w * 5.0f;

	physx::PxShape* shapex = CreateShape(physx::PxSphereGeometry(2.0f));
	m_transform_x = physx::PxTransform(u.operator physx::PxVec3());
	m_renderItem_x = new RenderItem(shapex, &m_transform_x, Vector4(1.0f, 0.0f, 0.0f, 1.0f));

	physx::PxShape* shapey = CreateShape(physx::PxSphereGeometry(2.0f));
	m_transform_y = physx::PxTransform(v.operator physx::PxVec3());
	m_renderItem_y = new RenderItem(shapey, &m_transform_y, Vector4(0.0f, 1.0f, 0.0f, 1.0f));

	physx::PxShape* shapez = CreateShape(physx::PxSphereGeometry(2.0f));
	m_transform_z = physx::PxTransform(w.operator physx::PxVec3());
	m_renderItem_z = new RenderItem(shapez, &m_transform_z, Vector4(0.0f, 0.0f, 1.0f, 1.0f));

}

void Scene0::cleanup() {
	if (m_renderItem) {
		m_renderItem->release();
		m_renderItem = nullptr;
	}
	if (m_renderItem_x) {
		m_renderItem_x->release();
		m_renderItem_x = nullptr;
	}
	if (m_renderItem_y) {
		m_renderItem_y->release();
		m_renderItem_y = nullptr;
	}
	if (m_renderItem_z) {
		m_renderItem_z->release();
		m_renderItem_z = nullptr;
	}
}
