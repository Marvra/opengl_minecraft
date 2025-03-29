#include "Chunk.h"

Chunk::Chunk()
{
}

Chunk::~Chunk()
{
}

void Chunk::generateChunk()
{

    int baseIndex = 0;
    

    for(int x = 0;  x <= CHUNK_SIZE_X; x++)
    {
        for(int y = 0;  y <= CHUNK_SIZE_Y; y++)
        {
            for(int z = 0;  z <= CHUNK_SIZE_Z; z++)
            {
                
                Block block(&vertices, &indices);

                if(z == 0)              block.addFace(Sides::FRONT, x, y, z, &baseIndex);
                if(z == CHUNK_SIZE_Z)   block.addFace(Sides::BACK, x, y, z, &baseIndex);
                if(y == 0)              block.addFace(Sides::DOWN, x, y, z, &baseIndex);
                if(y == CHUNK_SIZE_Y)   block.addFace(Sides::TOP, x, y, z, &baseIndex);
                if(x == 0)              block.addFace(Sides::LEFT, x, y, z, &baseIndex);
                if(x == CHUNK_SIZE_X)   block.addFace(Sides::RIGHT, x, y, z, &baseIndex);
                
                //block.addFace(Sides::FRONT, x, y, z, &baseIndex);
                //block.addFace(Sides::BACK, x, y, z, &baseIndex);
                //block.addFace(Sides::DOWN, x, y, z, &baseIndex);
                //block.addFace(Sides::TOP, x, y, z, &baseIndex);
                //block.addFace(Sides::LEFT, x, y, z, &baseIndex);
                //block.addFace(Sides::RIGHT, x, y, z, &baseIndex);
            }
        }
    }
}
