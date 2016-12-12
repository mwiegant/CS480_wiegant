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
  dynamicsWorld->setGravity(btVector3(0.0f, -9.81f, 0.0f));

  return true;
}


/*
 * Adds a spherical object to the bullet world, and adds a regular object to
 * the drawing world that is tied to that object.
 *
 * @param position = the (x,y,z) position of this object in the world
 * @param radius = the radius of the object
 * @param mass = how heavy the object is (i.e. how far it flies when hit)
 * @param object = the object that will correspond to the shape being created in this function
 */
btRigidBody* PhysicsWorld::AddSimpleSphere(btVector3 position, btScalar radius, btScalar mass, Object* object)
{
  /// 1. Create a btRigidBody and add it to the dynamicsWorld

  //create a dynamic rigidbody
  btCollisionShape* sphereShape = new btSphereShape( radius );
  collisionShapes.push_back(sphereShape);

  // Create Dynamic Objects
  btTransform startTransform;
  startTransform.setIdentity();
  startTransform.setOrigin(position);

  // the rigidbody is dynamic if and only if mass is non zero, otherwise static
  bool isDynamic = (mass != 0.0f);

  btVector3 localInertia(0.0f,0.0f,0.0f);
  if (isDynamic)
  {
    sphereShape->calculateLocalInertia(mass,localInertia);
  }

  // using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
  btDefaultMotionState* myMotionState = new btDefaultMotionState( startTransform );
  btRigidBody::btRigidBodyConstructionInfo rbInfo( mass, myMotionState, sphereShape, localInertia );
  btRigidBody* body = new btRigidBody( rbInfo );

  dynamicsWorld->addRigidBody(body);

  /// 2. Add the Object to the objectList

  objectList.push_back(object);


  return body;
}


/*
 * Adds a cylinder to the bullet world, and adds a regular object to the
 * drawing world that is tied to the cylinder object.
 *
 * @param position = the (x,y,z) position of this object in the world
 * @param halfwayVectors = half the dimensions of the cylinder (x,y,z dimensions)
 * @param mass = how heavy the object is (i.e. how far it flies when hit)
 * @param object = the object that will correspond to the shape being created in this function
 */
btRigidBody* PhysicsWorld::AddSimpleCylinder(btVector3 position, btVector3 halfwayVectors, btScalar mass, Object* object)
{
  /// 1. Create a btRigidBody and add it to the dynamicsWorld

  //create a dynamic rigidbody
  btCollisionShape* cylinderShape = new btCylinderShape( halfwayVectors );
  collisionShapes.push_back(cylinderShape);

  // Create Dynamic Objects
  btTransform cylinderTransform;
  cylinderTransform.setIdentity();
  cylinderTransform.setOrigin(position);

  // the rigidbody is dynamic if and only if mass is non zero, otherwise static
  bool isDynamic = (mass != 0.f);

  btVector3 localInertia(0.0f,0.0f,0.0f);
  if (isDynamic)
  {
    cylinderShape->calculateLocalInertia(mass,localInertia);
  }

  // using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
  btDefaultMotionState* myMotionState = new btDefaultMotionState( cylinderTransform );
  btRigidBody::btRigidBodyConstructionInfo rbInfo( mass, myMotionState, cylinderShape, localInertia );
  btRigidBody* body = new btRigidBody( rbInfo );

  dynamicsWorld->addRigidBody(body);

  /// 2. Add the Object to the objectList

  objectList.push_back(object);

  return body;
}


/*
 * Adds some sort of complex shape to the bullet world, and adds a regular object
 * to the drawing world that is tied to that object.
 *
 * @param position = the (x,y,z) position of this object in the world
 * @param mass = how heavy the object is (i.e. how far it flies when hit)
 * @param object = the object that will correspond to the shape being created in this function
 */
btRigidBody* PhysicsWorld::AddComplexShape(btVector3 position, btScalar mass, Object* object)
{

  /// 1. Get the Triangle Mesh from the Object

  btTriangleMesh* triMesh = object->GetTriangleMesh();

  /// 2. Create a btRigidBody and add it to the dynamicsWorld

  //create a dynamic rigidbody
  btCollisionShape* shape = new btConvexTriangleMeshShape(triMesh, true);
  collisionShapes.push_back(shape);

  // Create Dynamic Objects
  btTransform shapeTransform;
  shapeTransform.setIdentity();
  shapeTransform.setOrigin(position);

  // the rigidbody is dynamic if and only if mass is non zero, otherwise static
  bool isDynamic = (mass != 0.f);

  btVector3 localInertia(0.0f,0.0f,0.0f);
  if (isDynamic)
  {
    shape->calculateLocalInertia(mass,localInertia);
  }

  // using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
  btDefaultMotionState* myMotionState = new btDefaultMotionState( shapeTransform );
  btRigidBody::btRigidBodyConstructionInfo rbInfo( mass, myMotionState, shape, localInertia );
  btRigidBody* body = new btRigidBody( rbInfo );

  dynamicsWorld->addRigidBody(body);

  /// 3. Add the Object to the objectList

  objectList.push_back(object);

  return body;
}


/*
 * For updating the position of objects in the world.
 */
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
