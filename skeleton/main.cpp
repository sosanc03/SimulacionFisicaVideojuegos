#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>
#include <list>
#include "Particle.h"
#include "ParticleGenerator.h"
#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"

#include <iostream>

std::string display_text = "This is a test";


using namespace physx;
using namespace std;

PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;

PxFoundation*			gFoundation = NULL;
PxPhysics*				gPhysics	= NULL;


PxSphereGeometry		sphereGeometry = NULL;
PxMaterial*				gMaterial	= NULL;

PxPvd*                  gPvd        = NULL;

PxDefaultCpuDispatcher*	gDispatcher = NULL;
PxScene*				gScene      = NULL;
ContactReportCallback gContactReportCallback;
Particle* part = nullptr;
ParticleGenerator* partGen = nullptr;
list<Particle*> shots;


// Initialize physics engine
void initPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport,PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(),true,gPvd);

	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);
	/*PxShape* s = CreateShape(PxSphereGeometry(5));
	PxTransform tr;
	tr.p = Vector3(-20, 0, 10);
	Vector3 vel = Vector3(0, 10, 0);
	Vector3 acc = Vector3(0, 0.01, 0);// 0.01
	Vector3 gS = Vector3(0, 0, 0);// gravedad
	float damp = 0.01;// 0.1
	Vector4& color = Vector4(0.9, 0.1, 0.1, 1);*/

	//part = new Particle(s, tr, vel, acc, gS, damp, color);

	//RegisterRenderItem(part->getRenderItem());

	partGen = new ParticleGenerator();

	// For Solid Rigids +++++++++++++++++++++++++++++++++++++
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;
	gScene = gPhysics->createScene(sceneDesc);
	}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);

	//part->update();
	auto it = shots.begin();
	while (it != shots.end())
	{
		auto aux = it;
		++aux;
		PxTransform* trans = (*it)->getTransform();
		if ((*it)->getDest())
		{
			delete *it;
			shots.erase(it);
		}
		else (*it)->update(t);
		it = aux;
	}

	partGen->update(t);


	gScene->simulate(t);
	gScene->fetchResults(true);
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	// Rigid Body ++++++++++++++++++++++++++++++++++++++++++
	gScene->release();
	gDispatcher->release();
	// -----------------------------------------------------
	gPhysics->release();	
	PxPvdTransport* transport = gPvd->getTransport();
	gPvd->release();
	transport->release();
	gFoundation->release();

	//delete part;
	for (auto& shot : shots)delete shot;
	shots.clear();

	delete partGen;

}

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);

	switch(toupper(key))
	{
	//case 'B': break;
	//case ' ':	break;
	case 'Z':
	{
		Camera* cam = GetCamera();

		PxShape* s = CreateShape(PxSphereGeometry(5));
		PxTransform tr = cam->getTransform();
		Vector3 vel = cam->getDir() * 45;// velocidad simulada 45 m/s
		Vector3 acc = Vector3(0, 0, 0);
		Vector3 gS = Vector3(0, -0.02245925758, 0);// gravedad simulada 
		float damp = 1;
		Vector4& color = Vector4(0.9, 0.1, 0.1, 1);

		Particle* shot = new Particle(s, tr, vel, acc, gS, damp, color);
		shot->getRenderItem()->transform = shot->getTransform();
		RegisterRenderItem(shot->getRenderItem());
		shots.push_back(shot);
		break;
	}
	case 'G':
		partGen->generate();
		break;
	case '1':
		partGen->generate(0);
		break;
	case '2':
		partGen->generate(1);
		break;
	case '3':
		partGen->generate(2);
		break;
	case '4':
		partGen->generate(3);
		break;
	default:
		break;
	}
}

void onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
	PX_UNUSED(actor1);
	PX_UNUSED(actor2);
}


int main(int, const char*const*)
{
#ifndef OFFLINE_EXECUTION 
	extern void renderLoop();
	renderLoop();
#else
	static const PxU32 frameCount = 100;
	initPhysics(false);
	for(PxU32 i=0; i<frameCount; i++)
		stepPhysics(false);
	cleanupPhysics(false);
#endif

	return 0;
}