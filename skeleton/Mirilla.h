#pragma once
#include <PxPhysicsAPI.h>
#include "RenderUtils.hpp"
using namespace physx;
struct limits {
	int up;
	int down;
	int right;
	int left;
};
class Mirilla
{
private:
	RenderItem* rend;
	PxTransform tr;
	Camera* cam;
	limits l;
	bool ocult;
public:
	Mirilla() : ocult(false){
		l.up = 200; l.down = -10; l.right = 0; l.left = 0;
		cam = GetCamera();
		//tr.p = Vector3(cam->getEye().x - 15, cam->getEye().y + 10, cam->getEye().z - 15);
		tr = cam->getTransform();
		rend = new RenderItem();
		rend->color = Vector4(1, 0, 0, 1);
		rend->shape = CreateShape(PxSphereGeometry(0.5));
		rend->transform = &tr;
		RegisterRenderItem(rend);
	}
	void update() { tr.p.x = cam->getTransform().p.x; tr.p.z = cam->getTransform().p.z; rend->transform = &tr; }
	void moveUp() {
		if (!ocult) {
			tr.p.y += 2;
			if (tr.p.y > l.up)tr.p.y = l.up;
			rend->transform = &tr;
		}
	}
	void moveDown() {
		if (!ocult) {
			tr.p.y -= 2;
			if (tr.p.y < l.down)tr.p.y = l.down;
			rend->transform = &tr;
		}
	}
	void moveRight() {
		if (!ocult) {
			rend->transform = &tr;
		}
	}
	void moveLeft() {
		if (!ocult) {
			rend->transform = &tr;
		}
	}

	Vector3 getPos() { return tr.p; }
	void oculta() { ocult = true; rend->shape = CreateShape(PxSphereGeometry(0.01)); }
	void muestra() { ocult = false; rend->shape = CreateShape(PxSphereGeometry(0.5)); }
};

