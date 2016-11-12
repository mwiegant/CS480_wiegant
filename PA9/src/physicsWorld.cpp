#include "physicsWorld.h"

PhysicsWorld::PhysicsWorld()
{

}

PhysicsWorld::~PhysicsWorld()
{
  delete broadphase;
  delete collisionConfiguration;
  delete dispatcher;
  delete solver;
  delete dynamicsWorld;
  delete groundRigidBody;
  delete fallRigidBody;
  delete ball;
  delete ground;
}

bool PhysicsWorld::Initialize()
{
  ground = new Object();
  ball = new Object();
  ground->Initialize("models/plane.obj");
  ball->Initialize();

  masterList.push_back(ground);
  masterList.push_back(ball);

  broadphase = new btDbvtBroadphase();
  collisionConfiguration = new btDefaultCollisionConfiguration();
  dispatcher = new btCollisionDispatcher(collisionConfiguration);
  solver = new btSequentialImpulseConstraintSolver();
  dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);

  //gravity
  dynamicsWorld->setGravity(btVector3(0, -9.81, 0));

  //add shapes
  btCollisionShape* groundShape = new btStaticPlaneShape(btVector3(0, 1, 0), 1);

  btCollisionShape* fallShape = new btSphereShape(1);


  //add motion states
  btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -1, 0)));
  btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0, groundMotionState, groundShape, btVector3(0, 0, 0));
  groundRigidBody = new btRigidBody(groundRigidBodyCI);
  dynamicsWorld->addRigidBody(groundRigidBody);


  btDefaultMotionState* fallMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 50, 0)));
  btScalar mass = 1;
  btVector3 fallInertia(0, 0, 0);
  fallShape->calculateLocalInertia(mass, fallInertia);
  btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass, fallMotionState, fallShape, fallInertia);
  fallRigidBody = new btRigidBody(fallRigidBodyCI);
  dynamicsWorld->addRigidBody(fallRigidBody);

  return true;
}

bool PhysicsWorld::addRigidBody()
{
  
}

void PhysicsWorld::Update(unsigned int dt)
{
  btTransform trans;
  btScalar m[16]; 

  //update floor
  dynamicsWorld->stepSimulation(dt, 10); 
  groundRigidBody->getMotionState()->getWorldTransform(trans);
  trans.getOpenGLMatrix(m);
  
  masterList[0]->Update(glm::make_mat4(m));


  //update ball
  dynamicsWorld->stepSimulation(dt, 10); 
  fallRigidBody->getMotionState()->getWorldTransform(trans);
  trans.getOpenGLMatrix(m);

  masterList[1]->Update(glm::make_mat4(m));
}


