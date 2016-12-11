#include "catapult.h"

Catapult::Catapult()
{

}

Catapult::~Catapult()
{

}


/*
 * Creates and initializes the objects that make up the catapult.
 *
 * Adds the objects to the physics world.
 *
 * @param physicsWorld = a copy of the object that holds all physics world information
 */
bool Catapult::Initialize(PhysicsWorld &physicsWorld)
{
  // create the objects I need here
  Object* catapultBody = new Object();
  Object* catapultArm = new Object();

  // initialize the objects I created
  catapultBody->Initialize("models/Base.obj", "textures/granite.jpg");
  catapultArm->Initialize("models/Arm.obj", "textures/Mars.jpg");

  // add the objects to the internal objectList (so they don't get deleted)
  objectList.push_back(catapultBody);
  objectList.push_back(catapultArm);

  // use the objects I created to create objects in the physics world
  physicsWorld.AddComplexShape( btVector3(0.0f, 0.0f, 0.0f), btScalar(0.0f), catapultBody );
  physicsWorld.AddComplexShape( btVector3(0.0f, 0.0f, 0.0f), btScalar(0.0f), catapultArm );


  return true;
}



