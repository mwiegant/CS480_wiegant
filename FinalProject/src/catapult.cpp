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
  // set up launch variables
  maxWindUp = 25.0f;
  minWindUp = 15.0f;
  defaultWindUp = 20.0f;
  windUpAmount = defaultWindUp;
  windUpSpeed = 0.50f;
  launchSpeed = -3.0f;
  launchingTheProjectile = false;
  justLaunchedProjectile = false;

  // create the collision groups
  int catapultArmCollidesWith = COL_NOTHING;
  int catapultBodyCollidesWith = COL_NON_CATAPULT;
  int catapultWheelCollidesWith = COL_NOTHING;
  int catapultProjectile = COL_CATAPULT_ARM | COL_NON_CATAPULT | COL_FLOOR;

  // create the objects I need here
  Object* obj_catapultBody = new Object();
  Object* obj_catapultArm = new Object();
  Object* obj_wheel_backLeft = new Object();
  Object* obj_wheel_backRight = new Object();
  Object* obj_wheel_frontLeft = new Object();
  Object* obj_wheel_frontRight = new Object();
  Object* obj_projectile = new Object();


  // initialize the objects I created
  obj_catapultBody->Initialize("models/Catapult_Base.obj", "textures/brownTile.png");
  obj_catapultArm->Initialize("models/Catapult_Arm.obj", "textures/brownTile.png");

  obj_wheel_backLeft->Initialize("models/Catapult_BackLeft.obj", "textures/brownTile.png");
  obj_wheel_backRight->Initialize("models/Catapult_BackRight.obj", "textures/brownTile.png");
  obj_wheel_frontLeft->Initialize("models/Catapult_FrontLeft.obj", "textures/brownTile.png");
  obj_wheel_frontRight->Initialize("models/Catapult_FrontRight.obj", "textures/brownTile.png");

  obj_projectile->Initialize("models/Projectile.obj", "textures/silver.png");

  // use the objects I created to create objects in the physics world
  catapultBody = physicsWorld.AddComplexShape( btVector3(0.0f, 0.0f, 0.0f), btScalar(1.0f),
                                               COL_CATAPULT_BODY, catapultBodyCollidesWith, obj_catapultBody );

  catapultArm = physicsWorld.AddComplexShape( btVector3(0.0f, 0.0f, 0.0f), btScalar(1.0f),
                                              COL_CATAPULT_ARM, catapultArmCollidesWith, obj_catapultArm );

  wheelBackLeft = physicsWorld.AddComplexShape( btVector3(0.0f, 0.0f, 0.0f), btScalar(1.0f),
                                                COL_CATAPULT_WHEEL, catapultWheelCollidesWith, obj_wheel_backLeft );

  wheelBackRight = physicsWorld.AddComplexShape( btVector3(0.0f, 0.0f, 0.0f), btScalar(1.0f),
                                                 COL_CATAPULT_WHEEL, catapultWheelCollidesWith, obj_wheel_backRight );

  wheelFrontLeft = physicsWorld.AddComplexShape( btVector3(0.0f, 0.0f, 0.0f), btScalar(1.0f),
                                                 COL_CATAPULT_WHEEL, catapultWheelCollidesWith, obj_wheel_frontLeft );

  wheelFrontRight = physicsWorld.AddComplexShape( btVector3(0.0f, 0.0f, 0.0f), btScalar(1.0f),
                                                  COL_CATAPULT_WHEEL, catapultWheelCollidesWith, obj_wheel_frontRight );

  projectile = physicsWorld.AddComplexShape( btVector3(0.0f, 0.0f, 0.0f), btScalar(10.0f),
                                              COL_NON_CATAPULT, catapultProjectile, obj_projectile);

  // ensure the body does not go to sleep
  catapultArm->setActivationState(4);
  projectile->setActivationState(4);

  // disable gravity on the catapult
  catapultArm->setGravity( btVector3(0.0f,0.0f,0.0f) );
  catapultBody->setGravity( btVector3(0.0f,0.0f,0.0f) );
  wheelBackLeft->setGravity( btVector3(0.0f,0.0f,0.0f) );
  wheelBackRight->setGravity( btVector3(0.0f,0.0f,0.0f) );
  wheelFrontLeft->setGravity( btVector3(0.0f,0.0f,0.0f) );
  wheelFrontRight->setGravity( btVector3(0.0f,0.0f,0.0f) );
  projectile->setGravity( btVector3(0.0f,-9.81f,0.0f) );

  return true;
}


/*
 * If the catapult is currently launching, disable its movement once it
 * reaches a certain point in it's rotation.
 *
 * If the catapult has just launched, wind the arm back up again.
 *
 */
void Catapult::Update()
{

  if(launchingTheProjectile)
  {
//    printf("launching the projectile....\n");
//    printf("windUpAmount: %f\n", windUpAmount);

    windUpAmount += 0.25f * launchSpeed;

    // disable the launch once the arm has rotated as far as it should go
    if(windUpAmount < minWindUp)
    {
      catapultArm->setAngularVelocity(btVector3(0.0f, 0.0f, 0.0f));
      launchingTheProjectile = false;
      justLaunchedProjectile = true;
    }
  }

  if(justLaunchedProjectile)
  {
//    printf("windUpAmount: %f\n", windUpAmount);

    // wind up the arm again
    windUpAmount += windUpSpeed;

    catapultArm->setAngularVelocity(btVector3(0.0f, 0.0f, windUpSpeed));

    // disable rewind of arm once it has wound up to its default position
    if(windUpAmount >= defaultWindUp)
    {
      catapultArm->setAngularVelocity(btVector3(0.0f, 0.0f, 0.0f));
      justLaunchedProjectile = false;
    }
  }

}


/*
 * Adjusts the movement of the catapult arm
 */
void Catapult::AdjustCatapultArm(bool moveForward, bool enableMovement)
{

//  printf("windUpAmount: %f\n", windUpAmount);
//  printf("maxWindUp: %f\n", maxWindUp);
//  printf("minWindUp: %f\n", minWindUp);

  // disable arm adjustments while rewinding the arm to its default position
  if(!justLaunchedProjectile && !launchingTheProjectile)
  {

    // disable movement
    if(!enableMovement)
    {
      catapultArm->setAngularVelocity(btVector3(0.0f, 0.0f, 0.0f));
    }
    // move the arm forward
    else if(moveForward && windUpAmount > minWindUp)
    {
      catapultArm->setAngularVelocity(btVector3(0.0f, 0.0f, -1.0f * windUpSpeed));
      windUpAmount -= windUpSpeed;
    }
    // move the arm backward
    else if(!moveForward && windUpAmount < maxWindUp)
    {
      catapultArm->setAngularVelocity(btVector3(0.0f, 0.0f, 1.0f * windUpSpeed));
      windUpAmount += windUpSpeed;
    }
    // disable the catapult if it doesn't meet the conditions above to keep moving
    else
    {
      catapultArm->setAngularVelocity(btVector3(0.0f, 0.0f, 0.0f));
    }

  }

}


/*
 * Trigger the launch to begin if not currently launching or recovering from a launch,
 * or abort the launch if it has already started.
 */
void Catapult::TriggerLaunchControls()
{
  if(!launchingTheProjectile && !justLaunchedProjectile)
  {
    LaunchTheCatapult();
  }
  else if(launchingTheProjectile)
  {
    AbortTheLaunch();
  }
}



/*
 * Activates the flag which will cause the catapult arm to begin
 * launching the projectile out of the basket.
 */
void Catapult::LaunchTheCatapult()
{
  launchingTheProjectile = true;

  catapultArm->setAngularVelocity(btVector3(0.0f, 0.0f, launchSpeed));
}

/*
 * If the catapult is currently launching the projectile, stops
 * the catapult arm from moving any further which will allow the
 * projectile to fly out of the basket.
 */
void Catapult::AbortTheLaunch()
{
  if(launchingTheProjectile)
  {
    launchingTheProjectile = false;
    justLaunchedProjectile = true;
  }
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








