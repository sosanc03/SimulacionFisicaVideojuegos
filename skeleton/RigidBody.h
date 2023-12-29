#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"
#include "PxRigidBody.h"
#include "PxShape.h"
#include <PxPhysicsAPI.h>
#include <PxPhysics.h>

using namespace physx;

enum Shape { s_cube, s_sphere, s_rect, s_capsule };

class RigidBody {
protected:
	PxTransform transform;
	PxRigidDynamic* solid = nullptr;
	PxShape* shape = nullptr;
	RenderItem* render = nullptr;
	PxScene* scn = nullptr;

	Shape shapeType;
	float lifeTime; 
	bool alive;
	bool time;

public:
	RigidBody(PxScene* scene, PxPhysics* physics,
		const Vector3& Position, const Vector3& Velocity = Vector3(0, 0, 0), const Vector3& Inertia = Vector3(0, 0, 0),
		double Mass = 1, double LifeTime = 30,
		Shape Shape = s_cube, Vector4 Color = Vector4(0, 0, 0, 1), int size = 1):lifeTime(LifeTime), alive(true), shapeType(Shape), scn(scene) {

		time = true;
		transform = physx::PxTransform(Position.x, Position.y, Position.z);
		solid = physics->createRigidDynamic(transform);

		solid->setLinearVelocity(Velocity);
		solid->setAngularVelocity(Vector3(0, 0, 0));
		solid->setLinearDamping(0.0);
		solid->setMassSpaceInertiaTensor(Inertia);
		solid->setGlobalPose(transform);
		solid->setMass(Mass);

		switch (shapeType)
		{
		case s_capsule:
			shape = CreateShape(PxCapsuleGeometry(size, size));
			break;
		case s_sphere:
			shape = CreateShape(PxSphereGeometry(size));
			break;
		case s_cube:
			shape = CreateShape(PxBoxGeometry(size, size, size));
			break;
		case s_rect:
			shape = CreateShape(PxBoxGeometry(size, 2* size, size));
			break;
		}

		solid->attachShape(*shape);

		PxRigidBodyExt::updateMassAndInertia(*solid, 0.15);
		scene->addActor(*solid);
		render = new RenderItem(shape, solid, Color);
		RegisterRenderItem(render);
	}

	~RigidBody() {
		//if (shape) {
		//	solid->detachShape(*shape); // Elimina la forma del objeto rígido si existe
		//	shape->release(); // Libera la memoria de la forma si existe
		//	shape = nullptr; // Establece el puntero a nulo después de liberar la memoria
		//}

		//if (solid) {
		//	scn->removeActor(*solid); // Elimina el objeto rígido de la escena si existe
		//	solid->release(); // Libera la memoria del objeto rígido si existe
		//	solid = nullptr; // Establece el puntero a nulo después de liberar la memoria
		//}

		//if (render) {
		//	DeregisterRenderItem(render); // Elimina el elemento de representación si existe
		//	//delete render; // Libera la memoria del elemento de representación
		//	//render = nullptr; // Establece el puntero a nulo después de liberar la memoria
		//}
	}


	void integrate(float t) {
		transform = solid->getGlobalPose();
		if(time)lifeTime -= t;
		if (lifeTime <= 0 || fueraLimites()) 
			alive = false;
	};

	Vector3 getPosition() { return solid->getGlobalPose().p; }
	Vector3 getLinearVelocity() { return solid->getLinearVelocity(); }
	float getMass() { return solid->getMass(); }
	float getInvMass() { return solid->getInvMass(); }
	double getLifeTime() { return lifeTime; }
	bool isAlive() { return alive; }
	Vector4 getColor() { return render->color; }
	Shape getShape() { return shapeType; }
	void setTime(bool t = true) { time = t; }
	void setLifeTime(float t) { lifeTime = t; }

	//void setPosition(Vector3 Pos) {
	//	transform = PxTransform(Pos);
	//	solid->setGlobalPose(transform);
	//}
	void addForce(Vector3 force) { solid->addForce(force); }
	bool fueraLimites() {
		bool y = transform.p.y <= -10;
		bool fueraSuelo = transform.p.x >= 470 || transform.p.z >= 470 || transform.p.x <= -50 || transform.p.z <= -50;
		return (y || fueraSuelo);
	}
};

