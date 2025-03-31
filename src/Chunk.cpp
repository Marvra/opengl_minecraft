#include "Chunk.h"

Chunk::Chunk(int chunkPosX, int chunkPosZ) : chunkPosX(chunkPosX), chunkPosZ(chunkPosZ)
{
    generateChunk();

    VAO1.Gen();
    VAO1.Bind();

    VBO1.Generate(&vertices, vertices.size() * sizeof(float));
    EBO1.Generate(&indices, indices.size() * sizeof(unsigned int));


    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();
}

Chunk::~Chunk()
{
    // THIS SEGFAULTS WHEN SCREEN IS CLOSED
    // VAO1.Delete();
	// VBO1.Delete();
	// EBO1.Delete();
}

void Chunk::generateChunkPattern()
{
    OSN::Noise<2> surface;

    for (int x = 0; x < CHUNK_SIZE_X; x++) {
        for (int z = 0; z < CHUNK_SIZE_Z; z++) {

            float noiseY = surface.eval((float)(chunkPosX+x) * 0.03f, (float)(chunkPosZ+z) * 0.03f);
            int terrainHeight = (int)((noiseY + 1.0f) * 0.5f * (CHUNK_SIZE_Y - 1));

            for (int y = 0; y < CHUNK_SIZE_Y; y++) {

                if (y <= terrainHeight) {
                    chunk_block[x][y][z] = true;
                } else {
                    chunk_block[x][y][z] = false;
                }

                // CHECKERBOARD
                // if( (x + y + z) % 2 == 0)
                // {
                //     this->chunk_block[x][y][z] = true;
                // }

                //  ALL FILLED
                // this->chunk_block[x][y][z] = true;


//                TUNNEL
                // if ((x >= (CHUNK_SIZE_X / 2)-1 && x <= (CHUNK_SIZE_X / 2)+1 ) 
                //     && (y >= (CHUNK_SIZE_Y / 2)-1 && y <= (CHUNK_SIZE_Y / 2)+1 ) ) {
                //     chunk_block[x][y][z] = false;
                // } else {
                //     chunk_block[x][y][z] = true;
                // }    
            }
        }
    }

}

void Chunk::generateChunk()
{
    int baseIndex = 0;

    generateChunkPattern();
    

    for(int x = 0;  x < CHUNK_SIZE_X; x++)
    {
        for(int y = 0;  y < CHUNK_SIZE_Y; y++)
        {
            for(int z = 0;  z < CHUNK_SIZE_Z; z++)
            {
                if (!chunk_block[x][y][z]) continue; 

                Block block(&vertices, &indices);

                if (z == 0 || !chunk_block[x][y][z - 1])  
                    block.addFace(Sides::FRONT, chunkPosX + x, y, chunkPosZ + z, &baseIndex);

                if (z == CHUNK_SIZE_Z - 1 || !chunk_block[x][y][z + 1])  
                    block.addFace(Sides::BACK, chunkPosX + x, y, chunkPosZ + z, &baseIndex);

                if (y == 0 || !chunk_block[x][y - 1][z])  
                    block.addFace(Sides::DOWN, chunkPosX + x, y, chunkPosZ + z, &baseIndex);

                if (y == CHUNK_SIZE_Y - 1 || !chunk_block[x][y + 1][z])  
                    block.addFace(Sides::TOP,chunkPosX + x, y, chunkPosZ + z, &baseIndex);

                if (x == 0 || !chunk_block[x - 1][y][z])  
                    block.addFace(Sides::LEFT, chunkPosX + x, y, chunkPosZ + z, &baseIndex);

                if (x == CHUNK_SIZE_X - 1 || !chunk_block[x + 1][y][z])  
                    block.addFace(Sides::RIGHT, chunkPosX + x, y, chunkPosZ + z, &baseIndex);
            }
        }
    }
}

void Chunk::render()
{
    VAO1.Bind();

	glDrawElements(GL_TRIANGLES,indices.size(), GL_UNSIGNED_INT, 0);
    
}

int Chunk::getIndicesCount()
{
    return indices.size();
}

int Chunk::getVerticesCount()
{
    return vertices.size();
}
