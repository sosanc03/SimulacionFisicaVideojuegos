#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>
#include <list>
#include "Particle.h"
#include "ParticleGenerator.h"
#include "RigidBodySystem.h"
#include "Generator.h"
#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"

#include <iostream>

std::string display_text = "Sofia Sanchez Fernandez";
std::string display_gameOver = "GAME OVER!";
std::string display_win = "YOU WIN!";

bool displayWinText;
bool displayGameOverText;


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

Generator* Gen = nullptr;
RigidBodySystem* RBSys = nullptr;


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
	PxRigidStatic* suelo = gPhysics->createRigidStatic(PxTransform{ 280,0, 280 });
	PxShape* shape = CreateShape(PxBoxGeometry(300, 0.1, 300));
	suelo->attachShape(*shape);
	gScene->addActor(*suelo);
	RenderItem* item = new RenderItem(shape, suelo, { 0.8,0.8,0.8,1 });

	RBSys = new RigidBodySystem(gScene, gPhysics);
	Gen = new Generator(gScene, gPhysics);
}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);

	RBSys->update(t);
	Gen->update(t);
	if (Gen->win) displayWinText = true;

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

	delete Gen;
}

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);

	switch(toupper(key))
	{
	//case 'B': break;
	//case ' ':	break;
	case '1':
		if(Gen->nivel1())
			{ displayWinText = false; displayGameOverText = false;}
		break;
	case '2':
		if (Gen->nivel2())
			{ displayWinText = false; displayGameOverText = false;}
		break;
	case '3':
		if (Gen->nivel3()) 
			{ displayWinText = false; displayGameOverText = false; }
		break;
	case 'T':
		//RBSys->addWind();
		RBSys->shootRB();
		break;
	case 'L':
		Gen->gameOver();
		displayGameOverText = true;
		break;
	case 'O':
		Gen->addWind();
		break;
	default:break;
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