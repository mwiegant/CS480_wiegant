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

  private:

    // Private object list, so objects created during initialization
    // continue to exist while the program is running
    vector<Object*> objectList;

    // the different bullet object bodies
    btRigidBody* catapultBody;
    btRigidBody* catapultArm;


};


#endif //_CATAPULT_H
