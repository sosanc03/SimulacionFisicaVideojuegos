#include "Generator.h"

void Generator::update(float t) {
	cont -= t;
	for (RigidBody* rb : rbs) { // RB
		if (rb->isAlive()) { rb->integrate(t); }
		else { rbsToDelete.push_back(rb); }
	}
	for (RigidBody* shoot : shoots) { // RB
		if (shoot->isAlive()) { shoot->integrate(t); }
		else { shootsToDelete.push_back(shoot); }
	}
	rbRgis->updateForces(t);
	deleteUnusedRB();
	if(win)Fireworks(t);
	if (playing && numObstacles == 0) winGame();
	else if (playing && cont <= 0) gameOver();
}
void Generator::deleteUnusedRB() {
	for (auto it = rbsToDelete.begin(); it != rbsToDelete.end();) {
		rbRgis->deleteRigidBodyRegistry(*it);
		rbs.remove(*it);
		delete(*it);
		it = rbsToDelete.erase(it);
		numObstacles--;
	}
	for (auto it = shootsToDelete.begin(); it != shootsToDelete.end();) {
		rbRgis->deleteRigidBodyRegistry(*it);
		shoots.remove(*it);
		delete(*it);
		it = shootsToDelete.erase(it);
	}
}

void Generator::shootRB() {
	if (playing) {
		Camera* cam = GetCamera();
		Vector3 pos = cam->getEye() + cam->getDir();
		Vector3 dir = Vector3(cam->getDir().x * 190, cam->getDir().y * 450, cam->getDir().z * 150);

		RigidBody* rb_ = new RigidBody(scene, physics, pos, dir, Vector3(0, 0, 0), 100, 20, s_sphere, Vector4(1, 0, 0, 1), 4.5);
		shoots.push_back(rb_);
	}
}

void Generator::shoot(Vector3 dir) {
	if (playing) {
		if (clic) {
			Camera* cam = GetCamera();
			Vector3 pos = cam->getEye() + cam->getDir();
			//Vector3 d = Vector3(x, y, 0.5);
			//d.normalize();
			////Vector3 dir = Vector3(x - cam->getDir().x, y - cam->getDir().y, cam->getDir().z);
			////Vector3 dir = Vector3(cam->getDir().x, d.y - cam->getDir().y, cam->getDir().z);
			//Vector3 dir = Vector3(d.x * -15, d.y*5, d.x*-15);
			////dir.z = 0.5;
			////cout << cam->getDir().x << " " << cam->getDir().y << cam->getDir().z << " " << endl;
			////cout << x << " " << y << endl;
			//cout << d.x << " " << d.y << " " << d.z << endl;
			//dir.normalize();
			cout << dir.x << " " << dir.y << " " << dir.z << endl;
			dir = cam->getDir() - dir;
			//RigidBody* rb_ = new RigidBody(scene, physics, pos, dir*10, Vector3(0, 0, 0), 100, 20, s_sphere, Vector4(1, 0, 0, 1), 4.5);
			//rbs.push_back(rb_);
			clic = false;
		}
		else clic = true;
	}
	//cout << x << " " << y << endl;
}

bool Generator::nivel1() 
{
	if (!playing) {
		if (win) borraWin();
		if (lose) borraFlot();
		playing = true;
		numObstacles = 1;
		cont = 50;
		Vector3 pos = Vector3(-15, 10, -15);
		RigidBody* rb_ = new RigidBody(scene, physics, pos, Vector3(0, 0, 0), Vector3(0, 0, 0), 0.00001, 20, s_cube, Vector4(0.7, 0.4, 0.5, 1), 3.5);
		rb_->setTime(false);
		rbs.push_back(rb_);
		return true;
	}
	return false;
}
bool Generator::nivel2() 
{
	if (!playing) {
		if (win) borraWin();
		if (lose) borraFlot();
		playing = true;
		numObstacles = 2;
		cont = 30;
		Vector3 pos = Vector3(-15, 10, -15);
		RigidBody* rb_ = new RigidBody(scene, physics, pos, Vector3(0, 0, 0), Vector3(0, 0, 0), 0.00001, 20, s_cube, Vector4(0.7, 0.4, 0.5, 1), 3.5);
		rb_->setTime(false);
		rbs.push_back(rb_);
		pos = Vector3(-15, 20, -15);
		rb_ = new RigidBody(scene, physics, pos, Vector3(0, 0, 0), Vector3(0, 0, 0), 100, 20, s_cube, Vector4(0.7, 0.4, 0.5, 1), 3.5);
		rb_->setTime(false);
		rbs.push_back(rb_);
		return true;
	}
	return false;
}
bool Generator::nivel3() 
{
	if (!playing) {
		if (win) borraWin();
		if (lose) borraFlot();
		playing = true;
		numObstacles = 3;
		cont = 25;
		Vector3 pos = Vector3(-15, 10, -15);
		RigidBody* rb_ = new RigidBody(scene, physics, pos, Vector3(0, 0, 0), Vector3(0, 0, 0), 0.00001, 20, s_cube, Vector4(0.7, 0.4, 0.5, 1), 3.5);
		rb_->setTime(false);
		rbs.push_back(rb_);
		pos = Vector3(-15, 20, -15);
		rb_ = new RigidBody(scene, physics, pos, Vector3(0, 0, 0), Vector3(0, 0, 0), 10, 20, s_cube, Vector4(0.7, 0.4, 0.5, 1), 3.5);
		rb_->setTime(false);
		rbs.push_back(rb_);
		pos = Vector3(-15, 30, -15);
		rb_ = new RigidBody(scene, physics, pos, Vector3(0, 0, 0), Vector3(0, 0, 0), 200, 20, s_cube, Vector4(0.7, 0.4, 0.5, 1), 3.5);
		rb_->setTime(false);
		rbs.push_back(rb_);
		return true;
	}
	return false;
}
bool Generator::nivel4()
{
	if (!playing) {
		if (win) borraWin();
		if (lose) borraFlot();
		playing = true;
		numObstacles = 4;
		cont = 30;
		Vector3 pos = Vector3(-15, 10, -15);
		RigidBody* rb_ = new RigidBody(scene, physics, pos, Vector3(0, 0, 0), Vector3(0, 10, 0), 0.00001, 20, s_cube, Vector4(0.7, 0.4, 0.5, 1), 3.5);
		rb_->setTime(false);
		rbs.push_back(rb_);
		pos = Vector3(-15, 20, -15);
		rb_ = new RigidBody(scene, physics, pos, Vector3(0, 0, 0), Vector3(0, 0, 0), 10, 20, s_cube, Vector4(0.7, 0.4, 0.5, 1), 3.5);
		rb_->setTime(false);
		rbs.push_back(rb_);
		pos = Vector3(-15, 10, -5);
		rb_ = new RigidBody(scene, physics, pos, Vector3(0, 0, 0), Vector3(0, 0, 0), 300, 20, s_cube, Vector4(0.7, 0.4, 0.5, 1), 3.5);
		rb_->setTime(false);
		rbs.push_back(rb_);
		pos = Vector3(-5, 10, -15);
		rb_ = new RigidBody(scene, physics, pos, Vector3(0, 0, 0), Vector3(0, 0, 0), 25, 20, s_cube, Vector4(0.7, 0.4, 0.5, 1), 3.5);
		rb_->setTime(false);
		rbs.push_back(rb_);
		return true;
	}
	return false;
}

void Generator::winGame() {
	if (!win) {
		win = true;
		playing = false;
		for (auto rb : rbs)rbsToDelete.push_back(rb);
		for (auto shoot : shoots)shootsToDelete.push_back(shoot);
		deleteUnusedRB();
		fires = rand() % 15;
		fires++;
		numFires = 0;
	}
}
void Generator::borraWin() {
	win = false;
	while (!fireworks.empty()) {
		auto n = fireworks.front();
		fireworks.pop_front();
		delete n;
	}
	while (!particles.empty()) {
		auto n = particles.front();
		particles.pop_front();
		delete n;
	}
}

void Generator::gameOver() {
	if (!lose) {
		lose = true;
		playing = false;
		water = new BuoyancyForceGenerator(120, 0.5, 1000);
		for (auto shoot : shoots)shootsToDelete.push_back(shoot);
		deleteUnusedRB();
		for (auto rb : rbs) 
			rbRgis->addRegistry(water, rb);
	}
}
void Generator::borraFlot() {
	while (!rbs.empty()) { rbsToDelete.push_back(rbs.front()); rbs.pop_front(); }
	deleteUnusedRB();
	//	delete water;
	lose = false;
}

void Generator::addFirework(Firework* f) 
{ fireworks.push_back(f); }
void Generator::addParticle(Particle* p) 
{ particles.push_back(p); }
void Generator::Fireworks(float t) {
	Camera* camera = GetCamera();
	double damp = 0.9f; // damping
	Vector3 acc = Vector3(0, 0, 0);
	Vector3 gS = Vector3(0, 0, 0);
	Vector3 vel = Vector3(0, 0, -10);
	//PxTransform tr = PxTransform(0, 20, 0);
	Vector4 color = Vector4(1, 1, 1, 1);
	for (numFires; numFires < fires; numFires++) {
		PxTransform tr = PxTransform(Vector3(camera->getTransform().p.x - numFires * 10,
			camera->getTransform().p.y - numFires * 5, camera->getTransform().p.z - numFires * 10));
		Firework* f = new Firework(tr, vel, acc, gS, damp, color, this);
		addFirework(f);
	}
	auto it = particles.begin();
	while (it != particles.end()) {
		auto aux = it;
		++aux;
		if ((*it)->getDest()) {
			delete* it;
			particles.erase(it);
			numFires--;
			if (numFires < 0)numFires = 0;
		}
		else { (*it)->update(t); }
		it = aux;
	}
	auto it2 = fireworks.begin();
	while (it2 != fireworks.end()) {
		auto aux = it2;
		++aux;
		if ((*it2)->getDest()) {
			delete* it2;
			fireworks.erase(it2);
		}
		else (*it2)->update(t);
		it2 = aux;
	}
}

