#include "Scene0.h"
#include "Vector3D.h"

#include <iostream>


void Scene0::init() {
	/*physx::PxShape* shape1=CreateShape(physx::PxSphereGeometry(2.0f));
	m_transform = physx::PxTransform(physx::PxVec3(0.0f,0.0f,0.0f));
	m_renderItem=new RenderItem(shape1, &m_transform, Vector4(0.0f,0.0f,0.0f,1.0f));*/

	//Reto A
	// 
	//Vector3D u = Vector3D(3.0f, 1.0f, 0.0f);
	//Vector3D v = Vector3D(0.0f, 4.0f, 0.0f);
	//Vector3D w = u.cross(v);
	////Vector3D w = v.cross(u);
	////Si se invierte el producto vectorial la esfera azul cambia de lado perpendicular en el que está.
	////u.cross(v) lo pone en la izquierda y v.cross(u) lo pone en la derecha.

	//u=u.normalize();
	//v=v.normalize();
	//w=w.normalize();
	//u = u * 5.0f;
	//v = v * 5.0f;
	//w = w * 5.0f;

	//physx::PxShape* shapex = CreateShape(physx::PxSphereGeometry(2.0f));
	//m_transform_x = physx::PxTransform(u.operator physx::PxVec3());
	//m_renderItem_x = new RenderItem(shapex, &m_transform_x, Vector4(1.0f, 0.0f, 0.0f, 1.0f));

	//physx::PxShape* shapey = CreateShape(physx::PxSphereGeometry(2.0f));
	//m_transform_y = physx::PxTransform(v.operator physx::PxVec3());
	//m_renderItem_y = new RenderItem(shapey, &m_transform_y, Vector4(0.0f, 1.0f, 0.0f, 1.0f));

	//physx::PxShape* shapez = CreateShape(physx::PxSphereGeometry(2.0f));
	//m_transform_z = physx::PxTransform(w.operator physx::PxVec3());
	//m_renderItem_z = new RenderItem(shapez, &m_transform_z, Vector4(0.0f, 0.0f, 1.0f, 1.0f));

	//Reto B
	/*Vector3D P1 = Vector3D(2.0f, 0.0f, 3.0f);
	Vector3D P2 = Vector3D(-4.0f, 0.0f, 1.0f);
	Vector3D P3 = Vector3D(0.0f, 0.0f, -5.0f);
	Vector3D P4 = Vector3D(3.0f, 0.0f, 0.0f);

	float escP1 = P1.dot(Vector3D(0.0f, 0.0f, 1.0f));
	float escP2 = P2.dot(Vector3D(0.0f, 0.0f, 1.0f));
	float escP3 = P3.dot(Vector3D(0.0f, 0.0f, 1.0f));
	float escP4 = P4.dot(Vector3D(0.0f, 0.0f, 1.0f));

	m_transform_P1 = physx::PxTransform(P1.operator physx::PxVec3());
	m_transform_P2 = physx::PxTransform(P2.operator physx::PxVec3());
	m_transform_P3 = physx::PxTransform(P3.operator physx::PxVec3());
	m_transform_P4 = physx::PxTransform(P4.operator physx::PxVec3());

	renderItemPorPosicion(m_transform_P1, m_renderItem_P1,escP1);
	renderItemPorPosicion(m_transform_P2, m_renderItem_P2,escP2);
	renderItemPorPosicion(m_transform_P3, m_renderItem_P3,escP3);
	renderItemPorPosicion(m_transform_P4, m_renderItem_P4,escP4);*/

	//Reto C
	Vector3D A = Vector3D(-8.0f, 1.0f, -8.0f);
	Vector3D B = Vector3D(8.0f, 8.0f, 8.0f);

	m_transform_A = physx::PxTransform(A.operator physx::PxVec3());
	m_transform_B = physx::PxTransform(B.operator physx::PxVec3());
	m_renderItem_A = new RenderItem(CreateShape(physx::PxSphereGeometry(2.0f)), &m_transform_A, Vector4(0.0f, 0.0f, 1.0f, 1.0f));
	m_renderItem_B = new RenderItem(CreateShape(physx::PxSphereGeometry(2.0f)), &m_transform_B, Vector4(0.0f, 0.0f, 1.0f, 1.0f));
	renderPath(A, B);

	



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
	if (m_renderItem_P1) {
		m_renderItem_P1->release();
		m_renderItem_P1 = nullptr;
	}
	if (m_renderItem_P2) {
		m_renderItem_P2->release();
		m_renderItem_P2 = nullptr;
	}
	if (m_renderItem_P3) {
		m_renderItem_P3->release();
		m_renderItem_P3 = nullptr;
	}
	if (m_renderItem_P4) {
		m_renderItem_P4->release();
		m_renderItem_P4 = nullptr;
	}
	if (m_renderItem_A) {
		m_renderItem_A->release();
		m_renderItem_A = nullptr;
	}
	if (m_renderItem_B) {
		m_renderItem_B->release();
		m_renderItem_B = nullptr;
	}
	for (RenderItem* r : pathVec) {
		r->release();
		r = nullptr;
	}
}

Vector4 Scene0::darColorPorEscalar(float esc) {
	if (esc > 0) {
		return Vector4(0.0f, 1.0f, 0.0f, 1.0f);
	}
	else if (esc < 0) {
		return Vector4(1.0f, 0.0f, 0.0f, 1.0f);
	}
	else {
		return Vector4(0.0f, 1.0f, 1.0f, 1.0f);
	}
}

void Scene0::renderItemPorPosicion(physx::PxTransform& trans, RenderItem* renderI, float escalar) {
	renderI=new RenderItem(CreateShape(physx::PxSphereGeometry(2.0f)), &trans, darColorPorEscalar(escalar));
	//std::cout << trans.p.x << trans.p.y<< trans.p.z<< std::endl;
}

void Scene0::renderPath(Vector3D A, Vector3D B) {
	pathTrans.reserve(10);
	pathTrans.reserve(10);
	for (int i = 0;i < 10;++i) {
		Vector3D veci = A + (B - A) * (i / 9.0f);
		//std::cout << veci.x << " " << veci.y << " " << veci.z << std::endl;
		physx::PxVec3 vecix = veci.operator physx::PxVec3();
		//std::cout << vecix.x << " " << vecix.y << " " << vecix.z << std::endl;
		physx::PxTransform transi = physx::PxTransform(vecix);
		pathTrans.emplace_back(transi);
		//std::cout << transi.p.x << " " << transi.p.y << " " << transi.p.z << std::endl;
		pathVec.emplace_back(new RenderItem(CreateShape(physx::PxSphereGeometry(1.0f)), &pathTrans.back(), Vector4(1.0f, 0.0f, 1.0f, 1.0f)));
	}
}
