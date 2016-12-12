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
  Object* obj_catapultBody = new Object();
  Object* obj_catapultArm = new Object();
  Object* obj_wheel_backLeft = new Object();
  Object* obj_wheel_backRight = new Object();
  Object* obj_wheel_frontLeft = new Object();
  Object* obj_wheel_frontRight = new Object();

  // initialize the objects I created
  obj_catapultBody->Initialize("models/Catapult_Base.obj", "textures/granite.jpg");
  obj_catapultArm->Initialize("models/Catapult_Arm.obj", "textures/Mars.jpg");

  obj_wheel_backLeft->Initialize("models/Catapult_BackLeft.obj", "textures/Mars.jpg");
  obj_wheel_backRight->Initialize("models/Catapult_BackRight.obj", "textures/Mars.jpg");
  obj_wheel_frontLeft->Initialize("models/Catapult_FrontLeft.obj", "textures/Mars.jpg");
  obj_wheel_frontRight->Initialize("models/Catapult_FrontRight.obj", "textures/Mars.jpg");


  // use the objects I created to create objects in the physics world
  catapultBody = physicsWorld.AddComplexShape( btVector3(0.0f, 0.0f, 0.0f), btScalar(1.0f), obj_catapultBody );

  catapultArm = physicsWorld.AddComplexShape( btVector3(0.0f, 0.0f, 0.0f), btScalar(1.0f), obj_catapultArm );

  wheelBackLeft = physicsWorld.AddComplexShape( btVector3(0.0f, 0.0f, 0.0f), btScalar(1.0f), obj_wheel_backLeft );

  wheelBackRight = physicsWorld.AddComplexShape( btVector3(0.0f, 0.0f, 0.0f), btScalar(1.0f), obj_wheel_backRight );

  wheelFrontLeft = physicsWorld.AddComplexShape( btVector3(0.0f, 0.0f, 0.0f), btScalar(1.0f), obj_wheel_frontLeft );

  wheelFrontRight = physicsWorld.AddComplexShape( btVector3(0.0f, 0.0f, 0.0f), btScalar(1.0f),     obj_wheel_frontRight );

  // set the identity of allTransform
  allTransform.setIdentity();

  // add the individual objects to the compound shape to create the full catapult
  fullCat -> addChildShape( &allTransform, *catapultBody );
  


  return true;
}


/*
 *
 */
void Catapult::AdjustCatapultArm(int totalAdjustment, int adjustmentSpeed)
{
  btTransform transform;
  btQuaternion quat;

  printf("called adjust cata in Catapult\n");

  transform.setIdentity();

  /// for now, just making a static adjustment to prove I can make this fucking shit work

  catapultArm->setLinearFactor( btVector3(1.0f, 1.0f, 1.0f) );

  // adjust the angle on the catapultArm

//  catapultArm->setLinearFactor( btVector3(0.0f, 0.0f, 0.0f) );


  quat.setEuler( btScalar(3.0f), btScalar(3.0f), btScalar(3.0f) );
  transform.setRotation(quat);

  catapultArm->setCenterOfMassTransform(transform);

//    catapultArm->applyCentralImpulse(btVector3(3.0f, 0.0f, 0.0f));

  catapultArm->setAngularVelocity(btVector3(0.2f, 0.5f, 0.2f));

//  catapultArm->setLinearVelocity(btVector3(3.0f, 0.0f, 0.0f));
}

void Catapult::moveFore()
{

}

void Catapult::moveBack()
{

}

void Catapult::rotLeft()
{

}

void Catapult::rotRight()
{

}








