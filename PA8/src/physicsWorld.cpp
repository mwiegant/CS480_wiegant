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
 * Everything below this line subject to change
 */


//  ground = new Object();
//  ball = new Object();
//
//  // todo - come up with a better way to initialize these, so if the models fail to initialize, physicsworld also fails to initialize
//  ground->Initialize("models/plane.obj");
//  ball->Initialize("models/sphere.obj");
//
//  masterList.push_back(ground);
//  masterList.push_back(ball);
//
//
//
//  //add shapes
//  btCollisionShape* groundShape = new btStaticPlaneShape(btVector3(0, 1, 0), 1);
//
//  btCollisionShape* fallShape = new btSphereShape(1);
//
//
//  //add motion states
//  btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -1, 0)));
//  btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0, groundMotionState, groundShape, btVector3(0, 0, 0));
//  groundRigidBody = new btRigidBody(groundRigidBodyCI);
//  dynamicsWorld->addRigidBody(groundRigidBody);
//
//
//  btDefaultMotionState* fallMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 50, 0)));
//  btScalar mass = 1;
//  btVector3 fallInertia(0, 0, 0);
//  fallShape->calculateLocalInertia(mass, fallInertia);
//  btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass, fallMotionState, fallShape, fallInertia);
//  fallRigidBody = new btRigidBody(fallRigidBodyCI);
//  dynamicsWorld->addRigidBody(fallRigidBody);
//
//  return true;
//}


bool PhysicsWorld::addRigidBody()
{
  return false;
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

  plane->Initialize("models/plane.obj");

  objectList.push_back(plane);

  printf("successfully added a plane to the physics world.\n");

  return true;
}


/*
 * There are two components to adding an object to the physics world:
 *  1. Creating a btRigidBody and adding it to the dynamicsWorld
 *  2. Creating an Object and adding it to the objectList
 */
bool PhysicsWorld::AddSphere(btVector3 position)
{
  /// 1. Creating a btRigidBody and adding it to the dynamicsWorld

  //create a dynamic rigidbody
  btCollisionShape* sphereShape = new btSphereShape( btScalar(1.) );
  collisionShapes.push_back(sphereShape);

  // Create Dynamic Objects
  btTransform startTransform;
  startTransform.setIdentity();
  startTransform.setOrigin(position);

  btScalar mass(1.f);

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

  sphere->Initialize();

  objectList.push_back(sphere);

  printf("successfully added a sphere to the physics world.\n");

  return true;
}


/*
 * There are two components to adding an object to the physics world:
 *  1. Creating a btRigidBody and adding it to the dynamicsWorld
 *  2. Creating an Object and adding it to the objectList
 */
bool PhysicsWorld::AddCube(btVector3 position)
{
  /// 1. Creating a btRigidBody and adding it to the dynamicsWorld

  //create a dynamic rigidbody
  btCollisionShape* boxShape = new btBoxShape(btVector3(0.5, 0.5, 0.5));
  collisionShapes.push_back(boxShape);

  // Create Dynamic Objects
  btTransform boxTransform;
  boxTransform.setIdentity();
  boxTransform.setOrigin(position);

  btScalar mass(4.f);

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

  cube->Initialize("models/cube.obj");

  objectList.push_back(cube);

  printf("successfully added a cube to the physics world.\n");

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


//  //update floor
//  dynamicsWorld->stepSimulation(dt, 10);
//  groundRigidBody->getMotionState()->getWorldTransform(trans);
//  trans.getOpenGLMatrix(m);
//
//  objectList[0]->Update(glm::make_mat4(m));
//
//
//  //update ball
//  dynamicsWorld->stepSimulation(dt, 10);
//  fallRigidBody->getMotionState()->getWorldTransform(trans);
//  trans.getOpenGLMatrix(m);
//
//  objectList[1]->Update(glm::make_mat4(m));
}
