#include "Chunk.h"

Chunk::Chunk()
{
}

Chunk::~Chunk()
{
}

void Chunk::generateChunk()
{

    int generated = 1;
    

    for(int x = 0;  x <= CHUNK_SIZE_X; x++)
    {
        for(int y = 0;  y <= CHUNK_SIZE_Y; y++)
        {
            for(int z = 0;  z <= CHUNK_SIZE_Z; z++)
            {
                
                float cubeVertices[] = {
                    //  X      Y      Z      R    G    B      U    V
                    -0.5f+x, -0.5f+y,  0.5f-z,  0.83f, 0.70f, 0.44f,  0.0f, 0.0f,
                     0.5f+x, -0.5f+y,  0.5f-z,  0.83f, 0.70f, 0.44f,  1.0f, 0.0f,
                    -0.5f+x,  0.5f+y,  0.5f-z,  0.83f, 0.70f, 0.44f,  0.0f, 1.0f,
                     0.5f+x,  0.5f+y,  0.5f-z,  0.83f, 0.70f, 0.44f,  1.0f, 1.0f,
            
                    -0.5f+x, -0.5f+y, -0.5f-z,  0.83f, 0.70f, 0.44f,  0.0f, 0.0f,
                     0.5f+x, -0.5f+y, -0.5f-z,  0.83f, 0.70f, 0.44f,  1.0f, 0.0f,
                    -0.5f+x,  0.5f+y, -0.5f-z,  0.83f, 0.70f, 0.44f,  0.0f, 1.0f,
                     0.5f+x,  0.5f+y, -0.5f-z,  0.83f, 0.70f, 0.44f,  1.0f, 1.0f,
            
                    -0.5f+x, -0.5f+y,  0.5f-z,  0.83f, 0.70f, 0.44f,  0.0f, 0.0f,
                    -0.5f+x, -0.5f+y, -0.5f-z,  0.83f, 0.70f, 0.44f,  1.0f, 0.0f,
                    -0.5f+x,  0.5f+y,  0.5f-z,  0.83f, 0.70f, 0.44f,  0.0f, 1.0f,
                    -0.5f+x,  0.5f+y, -0.5f-z,  0.83f, 0.70f, 0.44f,  1.0f, 1.0f,
            
                     0.5f+x, -0.5f+y,  0.5f-z,  0.83f, 0.70f, 0.44f,  0.0f, 0.0f,
                     0.5f+x, -0.5f+y, -0.5f-z,  0.83f, 0.70f, 0.44f,  1.0f, 0.0f,
                     0.5f+x,  0.5f+y,  0.5f-z,  0.83f, 0.70f, 0.44f,  0.0f, 1.0f,
                     0.5f+x,  0.5f+y, -0.5f-z,  0.83f, 0.70f, 0.44f,  1.0f, 1.0f,
            
                    -0.5f+x,  0.5f+y,  0.5f-z,  0.83f, 0.70f, 0.44f,  0.0f, 0.0f,
                     0.5f+x,  0.5f+y,  0.5f-z,  0.83f, 0.70f, 0.44f,  1.0f, 0.0f,
                    -0.5f+x,  0.5f+y, -0.5f-z,  0.83f, 0.70f, 0.44f,  0.0f, 1.0f,
                     0.5f+x,  0.5f+y, -0.5f-z,  0.83f, 0.70f, 0.44f,  1.0f, 1.0f,
            
                    -0.5f+x, -0.5f+y,  0.5f-z,  0.83f, 0.70f, 0.44f,  0.0f, 0.0f,
                     0.5f+x, -0.5f+y,  0.5f-z,  0.83f, 0.70f, 0.44f,  1.0f, 0.0f,
                    -0.5f+x, -0.5f+y, -0.5f-z,  0.83f, 0.70f, 0.44f,  0.0f, 1.0f,
                     0.5f+x, -0.5f+y, -0.5f-z,  0.83f, 0.70f, 0.44f,  1.0f, 1.0f
                };
            
                unsigned int baseIndex = generated * 24;

                unsigned int cubeIndices[] = {
                    baseIndex+1, baseIndex+0, baseIndex+2,      //FRONT
                    baseIndex+1, baseIndex+2, baseIndex+3,      //FRONT
            
                    baseIndex+4, baseIndex+5, baseIndex+6,      //BACK
                    baseIndex+6, baseIndex+5, baseIndex+7,      //BACK
            
                    baseIndex+8, baseIndex+9, baseIndex+10,     //LEFT
                    baseIndex+10, baseIndex+9, baseIndex+11,    //LEFT    
            
                    baseIndex+13, baseIndex+12, baseIndex+14,   //RIGHT
                    baseIndex+13, baseIndex+14, baseIndex+15,   //RIGHT
            
                    baseIndex+17, baseIndex+16, baseIndex+18,   //TOP
                    baseIndex+17, baseIndex+18, baseIndex+19,   //TOP
            
                    baseIndex+20, baseIndex+21, baseIndex+22,   //BOTTOM
                    baseIndex+22, baseIndex+21, baseIndex+23    //BOTTOM
                };

                vertices.insert(vertices.end(), std::begin(cubeVertices), std::end(cubeVertices));
                indices.insert(indices.end(), std::begin(cubeIndices), std::end(cubeIndices));         
                generated ++;       
            }
        }
    }
}
