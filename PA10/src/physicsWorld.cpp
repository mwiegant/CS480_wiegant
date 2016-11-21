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

  pinballBody = NULL;

  // set gravity in the environment
  dynamicsWorld->setGravity(btVector3(0, -9.81, 0));

  return true;
}



/*
 * Adds a pinball ball object to the bullet world, and adds a regular object to
 * the drawing world that is tied to the pinbqll bqll object.
 *
 * @param position = the (x,y,z) position of this object in the world
 * @param radius = the radius of the object
 * @param mass = how heavy the object is (i.e. how far it flies when hit)
 * @param modelPath = the path to the model for this object
 * @param texturePath = the path to the texture for this object
 */
bool PhysicsWorld::AddPinball(btVector3 position, btScalar radius, btScalar mass,
                             const char* modelPath, const char* texturePath)
{
  /// 0. Do not add pinball if there is already one on this world
  if( pinballBody != NULL )
  {
    printf("failed to add pinball to the world; one pinball already exists in the world.\n");
    return false;
  }

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

  /// 3. Keep track of this Object
  pinballBody = body;

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
bool PhysicsWorld::AddCylinder(btVector3 position, btVector3 halfwayVectors, btScalar mass,
                               const char* modelPath, const char* texturePath)
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


bool PhysicsWorld::AddTriMeshShape(btVector3 position)
{
  /// 1. Creating an Object and adding it to the objectList

  btTriangleMesh* triMesh = new btTriangleMesh();

  Object* meshObj = new Object();

  meshObj->Initialize("models/pinball_base.obj", triMesh);

  objectList.push_back(meshObj);

  /// 2. Creating a btRigidBody and adding it to the dynamicsWorld

  //create a dynamic rigidbody
  btCollisionShape* shape = new btBvhTriangleMeshShape(triMesh, true);
  collisionShapes.push_back(shape);

  // Create Dynamic Objects
  btTransform shapeTransform;
  shapeTransform.setIdentity();
  shapeTransform.setOrigin(position);

  btScalar mass(0.0f);

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

  return true;
}


/*
 * If there is a pinball, this function provides a way to move it around the board.
 *
 * The intended use case for this function is resetting it to be launched again.
 */
bool PhysicsWorld::MovePinball(btVector3 position)
{
  // check if there is a pinball
  if( pinballBody == NULL)
  {
    printf("Error - tried to move the pinball when there is no pinball in the world.\n");
    return false;
  }

  // todo - this function
  printf("move pinball not imple. yet\n");

  return true;
}


/*
 * If there is a pinball, this function provides a way to set its velocity.
 *
 * The intended use case for this function is setting a velocity for the
 * pinball to have after it gets hit by the plunger, at the start of a new
 * round.
 */
bool PhysicsWorld::setPinballVelocity(btVector3 velocity)
{
  // check if there is a pinball
  if( pinballBody == NULL)
  {
    printf("Error - tried to move the pinball when there is no pinball in the world.\n");
    return false;
  }

  pinballBody->setLinearVelocity(velocity);

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
