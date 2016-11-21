#include "physicsWorld.h"

PhysicsWorld::PhysicsWorld()
{

}

PhysicsWorld::~PhysicsWorld()
{

}

/*
 * Initialize the physics world
 */
bool PhysicsWorld::Initialize() {

  // set up the Bullet environment
  broadphase = new btDbvtBroadphase();
  collisionConfiguration = new btDefaultCollisionConfiguration();
  dispatcher = new btCollisionDispatcher(collisionConfiguration);
  solver = new btSequentialImpulseConstraintSolver();
  dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);

  // set gravity in the environment
  dynamicsWorld->setGravity(btVector3(0, -9.81, 0));

  return true;
}


/*
 * There are two components to adding an object to the physics world:
 *  1. Creating a btRigidBody and adding it to the dynamicsWorld
 *  2. Creating an Object and adding it to the objectList
 */
bool PhysicsWorld::AddFloor()
{
  /// 1. Creating a btRigidBody and adding it to the dynamicsWorld

  //create a dynamic rigidbody
  btCollisionShape* floorShape = new btStaticPlaneShape(btVector3(0, 1, 0), 1);
  collisionShapes.push_back(floorShape);

  // Create Dynamic Objects
  btTransform groundTransform;
  groundTransform.setIdentity();
  groundTransform.setOrigin(btVector3(0,0,0));

  btScalar mass(0.f);

  // the rigidbody is dynamic if and only if mass is non zero, otherwise static
  bool isDynamic = (mass != 0.f);

  btVector3 localInertia(0,0,0);
  if (isDynamic)
  {
    floorShape->calculateLocalInertia(mass,localInertia);
  }

  // using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
  btDefaultMotionState* myMotionState = new btDefaultMotionState( groundTransform );
  btRigidBody::btRigidBodyConstructionInfo rbInfo( mass, myMotionState, floorShape, localInertia );
  btRigidBody* body = new btRigidBody( rbInfo );

  dynamicsWorld->addRigidBody(body);

  /// 2. Creating an Object and adding it to the objectList

  Object* plane = new Object();

  plane->Initialize("models/plane.obj", "textures/Neptune.jpg");

  objectList.push_back(plane);

  return true;
}


/*
 * Adds a sphere object to the bullet world, and adds a regular object to
 * the drawing world that is tied to the sphere object.
 *
 * @param position = the (x,y,z) position of this object in the world
 * @param radius = the radius of the object
 * @param mass = how heavy the object is (i.e. how far it flies when hit)
 * @param modelPath = the path to the model for this object
 * @param texturePath = the path to the texture for this object
 */
bool PhysicsWorld::AddSphere(btVector3 position, btScalar radius, btScalar mass, const char* modelPath, const char* texturePath)
{
  /// 1. Creating a btRigidBody and adding it to the dynamicsWorld

  //create a dynamic rigidbody
  btCollisionShape* sphereShape = new btSphereShape( radius );
  collisionShapes.push_back(sphereShape);

  // Create Dynamic Objects
  btTransform startTransform;
  startTransform.setIdentity();
  startTransform.setOrigin(position);

  // the rigidbody is dynamic if and only if mass is non zero, otherwise static
  bool isDynamic = (mass != 0.f);

  btVector3 localInertia(0,0,0);
  if (isDynamic)
  {
    sphereShape->calculateLocalInertia(mass,localInertia);
  }

  // using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
  btDefaultMotionState* myMotionState = new btDefaultMotionState( startTransform );
  btRigidBody::btRigidBodyConstructionInfo rbInfo( mass, myMotionState, sphereShape, localInertia );
  btRigidBody* body = new btRigidBody( rbInfo );
  
  dynamicsWorld->addRigidBody(body);

  /// 2. Creating an Object and adding it to the objectList

  Object* sphere = new Object();

  sphere->Initialize( modelPath, texturePath );

  objectList.push_back(sphere);

  return true;
}


/*
 * Adds a box/cube to the bullet world, and adds a regular object to the
 * drawing world that is tied to the box/cube object.
 *
 * @param position = the (x,y,z) position of this object in the world
 * @param halfwayVectors = half the total size of the box
 * @param mass = how heavy the object is (i.e. how far it flies when hit)
 * @param modelPath = the path to the model for this object
 * @param texturePath = the path to the texture for this object
 */
bool PhysicsWorld::AddBox(btVector3 position, btVector3 halfwayVectors, btScalar mass, const char* modelPath, const char* texturePath)
{
  /// 1. Creating a btRigidBody and adding it to the dynamicsWorld

  //create a dynamic rigidbody
  btCollisionShape* boxShape = new btBoxShape( halfwayVectors );
  collisionShapes.push_back(boxShape);

  // Create Dynamic Objects
  btTransform boxTransform;
  boxTransform.setIdentity();
  boxTransform.setOrigin(position);

  // the rigidbody is dynamic if and only if mass is non zero, otherwise static
  bool isDynamic = (mass != 0.f);

  btVector3 localInertia(0,0,0);
  if (isDynamic)
  {
    boxShape->calculateLocalInertia(mass,localInertia);
  }

  // using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
  btDefaultMotionState* myMotionState = new btDefaultMotionState( boxTransform );
  btRigidBody::btRigidBodyConstructionInfo rbInfo( mass, myMotionState, boxShape, localInertia );
  btRigidBody* body = new btRigidBody( rbInfo );

  dynamicsWorld->addRigidBody(body);

  /// 2. Creating an Object and adding it to the objectList

  Object* cube = new Object();

  cube->Initialize( modelPath, texturePath );

  objectList.push_back(cube);

  return true;
}


/*
 * Adds a cylinder to the bullet world, and adds a regular object to the
 * drawing world that is tied to the cylinder object.
 *
 * @param position = the (x,y,z) position of this object in the world
 * @param halfwayVectors = half the dimensions of the cylinder (x,y,z dimensions)
 * @param mass = how heavy the object is (i.e. how far it flies when hit)
 * @param modelPath = the path to the model for this object
 * @param texturePath = the path to the texture for this object
 */
bool PhysicsWorld::AddCylinder(btVector3 position, btVector3 halfwayVectors, btScalar mass, const char* modelPath, const char* texturePath)
{
  /// 1. Creating a btRigidBody and adding it to the dynamicsWorld

  //create a dynamic rigidbody
  btCollisionShape* cylinderShape = new btCylinderShape( halfwayVectors );
  collisionShapes.push_back(cylinderShape);

  // Create Dynamic Objects
  btTransform cylinderTransform;
  cylinderTransform.setIdentity();
  cylinderTransform.setOrigin(position);

  // the rigidbody is dynamic if and only if mass is non zero, otherwise static
  bool isDynamic = (mass != 0.f);

  btVector3 localInertia(0,0,0);
  if (isDynamic)
  {
    cylinderShape->calculateLocalInertia(mass,localInertia);
  }

  // using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
  btDefaultMotionState* myMotionState = new btDefaultMotionState( cylinderTransform );
  btRigidBody::btRigidBodyConstructionInfo rbInfo( mass, myMotionState, cylinderShape, localInertia );
  btRigidBody* body = new btRigidBody( rbInfo );

  dynamicsWorld->addRigidBody(body);

  /// 2. Creating an Object and adding it to the objectList

  Object* cube = new Object();

  cube->Initialize( modelPath, texturePath );

  objectList.push_back(cube);

  return true;
}


/*
 * There are two components to adding an object to the physics world:
 *  1. Creating a btRigidBody and adding it to the dynamicsWorld
 *  2. Creating an Object and adding it to the objectList
 */
bool PhysicsWorld::AddFrontFacingWall(btVector3 position)
{
  /// 1. Creating a btRigidBody and adding it to the dynamicsWorld

  //create a dynamic rigidbody
  btCollisionShape* shape = new btBoxShape(btVector3(6.0f, 3.0f, 0.5f));
  collisionShapes.push_back(shape);

  // Create Dynamic Objects
  btTransform shapeTransform;
  shapeTransform.setIdentity();
  shapeTransform.setOrigin(position);

  btScalar mass(1000.0f);

  // the rigidbody is dynamic if and only if mass is non zero, otherwise static
  bool isDynamic = (mass != 0.f);

  btVector3 localInertia(0,0,0);
  if (isDynamic)
  {
    shape->calculateLocalInertia(mass,localInertia);
  }

  // using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
  btDefaultMotionState* myMotionState = new btDefaultMotionState( shapeTransform );
  btRigidBody::btRigidBodyConstructionInfo rbInfo( mass, myMotionState, shape, localInertia );
  btRigidBody* body = new btRigidBody( rbInfo );

  dynamicsWorld->addRigidBody(body);

  /// 2. Creating an Object and adding it to the objectList

  Object* cube = new Object();

  cube->Initialize("models/frontFacingWall.obj", "textures/Neptune.jpg");

  objectList.push_back(cube);

  return true;
}


/*
 * There are two components to adding an object to the physics world:
 *  1. Creating a btRigidBody and adding it to the dynamicsWorld
 *  2. Creating an Object and adding it to the objectList
 */
bool PhysicsWorld::AddSideFacingWall(btVector3 position)
{
  /// 1. Creating a btRigidBody and adding it to the dynamicsWorld

  //create a dynamic rigidbody
  btCollisionShape* shape = new btBoxShape(btVector3(0.5f, 3.0f, 6.0f));
  collisionShapes.push_back(shape);

  // Create Dynamic Objects
  btTransform shapeTransform;
  shapeTransform.setIdentity();
  shapeTransform.setOrigin(position);

  btScalar mass(1000.0f);

  // the rigidbody is dynamic if and only if mass is non zero, otherwise static
  bool isDynamic = (mass != 0.f);

  btVector3 localInertia(0,0,0);
  if (isDynamic)
  {
    shape->calculateLocalInertia(mass,localInertia);
  }

  // using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
  btDefaultMotionState* myMotionState = new btDefaultMotionState( shapeTransform );
  btRigidBody::btRigidBodyConstructionInfo rbInfo( mass, myMotionState, shape, localInertia );
  btRigidBody* body = new btRigidBody( rbInfo );

  dynamicsWorld->addRigidBody(body);

  /// 2. Creating an Object and adding it to the objectList

  Object* cube = new Object();

  cube->Initialize("models/sideFacingWall.obj", "textures/Neptune.jpg");

  objectList.push_back(cube);

  return true;
}


void PhysicsWorld::Update(unsigned int dt)
{
  btCollisionObject* dynamicsWorldObject;
  btRigidBody* body;
  btTransform trans;
  btScalar m[16];

  dynamicsWorld->stepSimulation(dt, 1);

  // update each object in the physics world
  for( int i = 0; i < objectList.size(); i++)
  {
    dynamicsWorldObject = dynamicsWorld->getCollisionObjectArray()[i];
    body = btRigidBody::upcast( dynamicsWorldObject );

    // get the transformation matrix
    if (body && body->getMotionState())
    {
      body->getMotionState()->getWorldTransform(trans);
    } else
    {
      trans = dynamicsWorldObject->getWorldTransform();
    }

    // convert the transformation matrix to a model matrix
    trans.getOpenGLMatrix(m);

    objectList[i]->Update(glm::make_mat4(m));

  }

}
