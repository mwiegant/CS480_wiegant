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

    void Update();

    void AdjustCatapultArm(bool moveForward, bool enableMovement);
    void TriggerLaunchControls();

    void moveFore();
    void moveBack();
    void rotLeft();
    void rotRight();

  private:

    void LaunchTheCatapult();
    void AbortTheLaunch();

    // the different bullet object bodies
    btRigidBody* catapultBody;
    btRigidBody* catapultArm;
    btRigidBody* wheelFrontLeft;
    btRigidBody* wheelFrontRight;
    btRigidBody* wheelBackLeft;
    btRigidBody* wheelBackRight;

    btRigidBody* projectile;

    // variables for implementing wind up, release, and the rewind up after launching
    float maxWindUp;
    float minWindUp;
    float defaultWindUp;
    float windUpAmount;
    float windUpSpeed;
    float launchSpeed;
    bool launchingTheProjectile;
    bool justLaunchedProjectile;
};


#endif //_CATAPULT_H
