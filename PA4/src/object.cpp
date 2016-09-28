#include "object.h"

Object::Object()
{  
//  Vertices = {
//    {{0.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}},
//    {{-1.0f, -1.0f, 0.0f}, {1.0f, 0.0f, 0.0f}},
//    {{1.0f, -1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}}
//  };
//
//  Indices = {
//    1, 2, 3
//  };
//
//  // The index works at a 0th index
//  for(unsigned int i = 0; i < Indices.size(); i++)
//  {
//    Indices[i] = Indices[i] - 1;
//  }
//
//  angle = 0.0f;
//
//  glGenBuffers(1, &VB);
//  glBindBuffer(GL_ARRAY_BUFFER, VB);
//  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * Vertices.size(), &Vertices[0], GL_STATIC_DRAW);
//
//  glGenBuffers(1, &IB);
//  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
//  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * Indices.size(), &Indices[0], GL_STATIC_DRAW);
}

Object::~Object()
{
  Vertices.clear();
  Indices.clear();
}

bool Object::Initialize(char* modelPath)
{
  return loadModel(modelPath);
}

void Object::Update(unsigned int dt)
{
  model = glm::mat4(1.0f);
}

glm::mat4 Object::GetModel()
{
  return model;
}

void Object::Render()
{
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, VB);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,color));

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);

  glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
}


bool Object::loadModel(char* filepath)
{

  // variable initialization
  bool flag = false;
  std::ifstream fin;
  std::string string_line;
  float v1, v2, v3;
  std::string i1, i2, i3;
  glm::vec3 color = glm::vec3(1.0f,0.0f,0.0f);

  fin.clear();
  fin.open(filepath);

  // flag to true and skip some lines
  if( fin.good() )
  {
    flag = true;

    // skip the first four lines from the file
    for(int i = 0; i < 4; i++)
    {
      std::getline(fin, string_line);
    }
  }

  // read in the file while it has contents
  while(fin.good())
  {
    fin >> string_line;

    // check if the first token is a 'v'
    if( string_line != "" && string_line[0] == 'v' && string_line[1] != 'n' )
    {
      fin >> v1 >> v2 >> v3;
      Vertices.push_back({ glm::vec3(v1, v2, v3), color });
    }

      // else, check if the first token is a 'f'
    else if( string_line != "" && string_line[0] == 'f' )
    {
      fin >> i1 >> i2 >> i3;

      // push each of the 3 tokens into indices (so that's 3 separate pushes)
      Indices.push_back((unsigned int)(i1[0]-'0'));
      Indices.push_back((unsigned int)(i2[0]-'0'));
      Indices.push_back((unsigned int)(i3[0]-'0'));
    }
  }

  fin.close();

  // initialize buffers if the file was read in successfully
  if(flag)
  {
    // The indexes in Indices work at a 0th index, not the 1th index as found in the input file
    for(unsigned int i = 0; i < Indices.size(); i++)
    {
      Indices[i] = Indices[i] - 1;
    }

    glGenBuffers(1, &VB);
    glBindBuffer(GL_ARRAY_BUFFER, VB);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * Vertices.size(), &Vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &IB);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * Indices.size(), &Indices[0], GL_STATIC_DRAW);
  }


//  std::cout << "size of Vertices: " << Vertices.size() << std::endl;
//  std::cout << "size of Indices: " << Indices.size() << std::endl;

  // return true if file was read at least once
  return flag;
}



