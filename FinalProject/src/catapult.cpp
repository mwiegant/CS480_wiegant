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
  Object* wheel_backLeft = new Object();
  Object* wheel_backRight = new Object();
  Object* wheel_frontLeft = new Object();
  Object* wheel_frontRight = new Object();


  // initialize the objects I created
  catapultBody->Initialize("models/Catapult_Base.obj", "textures/granite.jpg");
  catapultArm->Initialize("models/Catapult_Arm.obj", "textures/Mars.jpg");

  wheel_backLeft->Initialize("models/Catapult_BackLeft.obj", "textures/Mars.jpg");
  wheel_backRight->Initialize("models/Catapult_BackRight.obj", "textures/Mars.jpg");
  wheel_frontLeft->Initialize("models/Catapult_FrontLeft.obj", "textures/Mars.jpg");
  wheel_frontRight->Initialize("models/Catapult_FrontRight.obj", "textures/Mars.jpg");

  // add the objects to the internal objectList (so they don't get deleted)
  objectList.push_back(catapultBody);
  objectList.push_back(catapultArm);
  objectList.push_back(wheel_backLeft);
  objectList.push_back(wheel_backRight);
  objectList.push_back(wheel_frontLeft);
  objectList.push_back(wheel_frontRight);

  // use the objects I created to create objects in the physics world
  physicsWorld.AddComplexShape( btVector3(0.0f, 0.0f, 0.0f), btScalar(0.0f), catapultBody );
  physicsWorld.AddComplexShape( btVector3(0.0f, 0.0f, 0.0f), btScalar(0.0f), catapultArm );

  physicsWorld.AddComplexShape( btVector3(0.0f, 0.0f, 0.0f), btScalar(0.0f), wheel_backLeft );
  physicsWorld.AddComplexShape( btVector3(0.0f, 0.0f, 0.0f), btScalar(0.0f), wheel_backRight );
  physicsWorld.AddComplexShape( btVector3(0.0f, 0.0f, 0.0f), btScalar(0.0f), wheel_frontLeft );
  physicsWorld.AddComplexShape( btVector3(0.0f, 0.0f, 0.0f), btScalar(0.0f), wheel_frontRight );

  return true;
}


/*
 *
 */
void Catapult::AdjustCatapultArm(int totalAdjustment, int adjustmentSpeed)
{
  // for now, just making a static adjustment to prove I can make this fucking shit work

  catapultArm->setLinearFactor( btVector3(0.0f, 0.0f, 0.0f) );

  // adjust the angle on the catapultArm

  catapultArm->setLinearFactor( btVector3(0.0f, 0.0f, 0.0f) );


}









