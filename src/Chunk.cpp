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
    

    for(int x = 0;  x < CHUNK_SIZE_X; x++)
    {
        for(int y = 0;  y < CHUNK_SIZE_Y; y++)
        {
            for(int z = 0;  z < CHUNK_SIZE_Z; z++)
            {

                unsigned int baseIndex = generated * 24;
                
                Block block(&vertices, &indices);

                

                block.addFace(Sides::BACK, x, y, z, baseIndex);
                block.addFace(Sides::FRONT, x, y, z, baseIndex);
                block.addFace(Sides::DOWN, x, y, z, baseIndex);
                block.addFace(Sides::TOP, x, y, z, baseIndex);
                block.addFace(Sides::LEFT, x, y, z, baseIndex);
                block.addFace(Sides::RIGHT, x, y, z, baseIndex);
                
                generated ++;       
            }
        }
    }
}
