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

    void AdjustCatapultArm(int totalAdjustment, int adjustmentSpeed);

    void moveFore();
    void moveBack();
    void rotLeft();
    void rotRight();

  private:

    // Private object list, so objects created during initialization
    // continue to exist while the program is running
    vector<Object*> objectList;

    // the different bullet object bodies
    btRigidBody* catapultBody;
    btRigidBody* catapultArm;
    btRigidBody* wheelFrontLeft;
    btRigidBody* wheelFrontRight;
    btRigidBody* wheelBackLeft;
    btRigidBody* wheelBackRight;

    // the transform for the full catapult
    btTransform allTransform;

    // the compound shape that composes the entire catapult
    btCompoundShape* fullCat;


};


#endif //_CATAPULT_H
