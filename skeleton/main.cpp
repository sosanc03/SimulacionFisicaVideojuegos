#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>
#include <list>
#include "Particle.h"
#include "ParticleGenerator.h"
#include "RigidBodySystem.h"
#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"

#include <iostream>

std::string display_text = "Sofia Sanchez Fernandez";


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
RigidBodySystem* RBSys = nullptr;
list<Particle*> shots;


// Initialize physics engine
void initPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport, PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(), true, gPvd);

	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	// For Solid Rigids +++++++++++++++++++++++++++++++++++++
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;
	gScene = gPhysics->createScene(sceneDesc);

	//SUELO
	PxRigidStatic* suelo = gPhysics->createRigidStatic(PxTransform{ 0,0,0 });
	PxShape* shape = CreateShape(PxBoxGeometry(100, 0.1, 100));
	suelo->attachShape(*shape);
	gScene->addActor(*suelo);
	RenderItem* item = new RenderItem(shape, suelo, { 0.8,0.8,0.8,1 });

	partGen = new ParticleGenerator();
	RBSys = new RigidBodySystem(gScene, gPhysics);
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
	RBSys->update(t);


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
	case '5':
		partGen->getSys()->generateSpringDemo(partGen->getSys()->ANCHORED);
		break;
	case '6':
		partGen->getSys()->generateSpringDemo(partGen->getSys()->SPRING);
		break;
	case '7':
		partGen->getSys()->generateSpringDemo(partGen->getSys()->FLOTABILITY);
		break;
	case '8':
		partGen->getSys()->generateSpringDemo(partGen->getSys()->GOMAELASTICA);
		break;
	case '9':
		//partGen->getSys()->generateSpringDemo(partGen->getSys()->BUOYANCY);
		partGen->getSys()->generateBuoyancy();
		break;
	case 'K':
		int k;
		cin >> k;
		partGen->getSys()->addK(k);
		break;
	case 'E':
		RBSys->addExplosion();
		break;
	case 'R':
		RBSys->addVortex();
		break;
	case 'T':
		RBSys->addWind();
		break;
	case 'Y':
		RBSys->addGravity();
		break;
	case 'M':
		RBSys->createGenerators(g_cube);
		break;
	case 'N':
		RBSys->createGenerators(g_sphere);
		break;
	case 'B':
		RBSys->createGenerators(g_capsule);
		break;
	case 'V':
		RBSys->shootRB();
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