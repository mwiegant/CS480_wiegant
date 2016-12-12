#ifndef CATAPULT_H
#define CATAPULT_H

#include <cstdio>
#include <vector>
#include <string>

#include <btBulletDynamicsCommon.h>

#include "graphics_headers.h"
#include "physicsWorld.h"
#include "object.h"


using namespace std;

class Catapult {
  public:
    Catapult();
    ~Catapult();

    bool Initialize(PhysicsWorld &physicsWorld);

    void AdjustCatapultArm(bool moveForward, bool enableMovement);

  private:

    // the different bullet object bodies
    btRigidBody* catapultBody;
    btRigidBody* catapultArm;
    btRigidBody* wheelFrontLeft;
    btRigidBody* wheelFrontRight;
    btRigidBody* wheelBackLeft;
    btRigidBody* wheelBackRight;



};


#endif //_CATAPULT_H
