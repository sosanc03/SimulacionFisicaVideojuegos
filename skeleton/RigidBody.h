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
	PxRigidDynamic* solid;
	PxShape* shape;
	RenderItem* render;

	Shape shapeType;
	float lifeTime; 
	bool alive;

public:
	RigidBody(PxScene* scene, PxPhysics* physics,
		const Vector3& Position, const Vector3& Velocity = Vector3(0, 0, 0), const Vector3& Inertia = Vector3(0, 0, 0),
		double Mass = 1, double LifeTime = 30,
		Shape Shape = s_cube, Vector4 Color = Vector4(0, 0, 0, 1)):lifeTime(LifeTime), alive(true), shapeType(Shape) {

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
			shape = CreateShape(PxCapsuleGeometry(1, 1));
			break;
		case s_sphere:
			shape = CreateShape(PxSphereGeometry(1));
			break;
		case s_cube:
			shape = CreateShape(PxBoxGeometry(1, 1, 1));
			break;
		case s_rect:
			shape = CreateShape(PxBoxGeometry(1, 2, 1));
			break;
		}

		solid->attachShape(*shape);

		PxRigidBodyExt::updateMassAndInertia(*solid, 0.15);
		scene->addActor(*solid);
		render = new RenderItem(shape, solid, Color);
	}

	~RigidBody() {
		DeregisterRenderItem(render);
	}

	void integrate(float t) {
		lifeTime -= t;
		if (lifeTime <= 0 || transform.p.y <= -100) alive = false;
	};

	Vector3 getPosition() { return solid->getGlobalPose().p; }
	Vector3 getLinearVelocity() { return solid->getLinearVelocity(); }
	float getMass() { return solid->getMass(); }
	float getInvMass() { return solid->getInvMass(); }
	double getLifeTime() { return lifeTime; }
	bool isAlive() { return alive; }
	Vector4 getColor() { return render->color; }
	Shape getShape() { return shapeType; }

	//void setPosition(Vector3 Pos) {
	//	transform = PxTransform(Pos);
	//	solid->setGlobalPose(transform);
	//}
	void addForce(Vector3 force) { solid->addForce(force); }
};

