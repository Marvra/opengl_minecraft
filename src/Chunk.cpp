#include "Chunk.h"

Chunk::Chunk(int chunkPosX, int chunkPosY, int chunkPosZ) : chunkPosX(chunkPosX), chunkPosY(chunkPosY), chunkPosZ(chunkPosZ)
{
    generateChunk();

    VAO1.Gen();
    VAO1.Bind();

    VBO1.Generate(&vertices, vertices.size() * sizeof(float));
    EBO1.Generate(&indices, indices.size() * sizeof(unsigned int));


    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
    VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));

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
    OSN::Noise<3> cave;

    for (int x = 0; x < CHUNK_SIZE_X; x++) {
        std::cout << "  ChunkPos : " << chunkPosX << " " << chunkPosY<< " " << chunkPosZ <<  std::endl;
        for (int z = 0; z < CHUNK_SIZE_Z; z++) {

            float surfaceNoise = surface.eval((float)(chunkPosX+x) * 0.02f,(float)(chunkPosZ+z) * 0.02f);

            int height = (int)((surfaceNoise) * 0.5f * (120 - 50) + 50);


            for (int y = 0; y < CHUNK_SIZE_Y; y++) {

                float caveNoise = cave.eval((float)(chunkPosX+x) * 0.07f, (float)(chunkPosY+y) * 0.07f ,(float)(chunkPosZ+z) * 0.07f);

                //std::cout << "  CaveNoise : " << caveNoise <<  std::endl;

                if (y + chunkPosY > height || caveNoise > 0.5f) {
                    chunkBlockExists[x][y][z] = AIR;
                }
                else if (y + chunkPosY == height) {
                    chunkBlockExists[x][y][z] = GRASS;
                }
                else if (y + chunkPosY > height - 5 - (int)rand() % 10 + 1) {
                    chunkBlockExists[x][y][z] = DIRT;
                }
                else {
                    chunkBlockExists[x][y][z] = STONE;
                }

                //std::cout << " TYPE : " << chunkBlockExists[x][y][z] << std::endl; 
                // CHECKERBOARD
                // if( (x + y + z) % 2 == 0)
                // {
                //     this->chunkBlockExists[x][y][z] = true;
                // }

                //  ALL FILLED
                //this->chunkBlockExists[x][z][y] = true;


//                TUNNEL
                // if ((x >= (CHUNK_SIZE_X / 2)-1 && x <= (CHUNK_SIZE_X / 2)+1 ) 
                //     && (y >= (CHUNK_SIZE_Y / 2)-1 && y <= (CHUNK_SIZE_Y / 2)+1 ) ) {
                //     chunkBlockExists[x][y][z] = false;
                // } else {
                //     chunkBlockExists[x][y][z] = true;
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
                if (chunkBlockExists[x][y][z] == AIR) continue; 

                Block block(&vertices, &indices);

                if (z == 0 || chunkBlockExists[x][y][z - 1] == AIR)  
                    block.addFace(Sides::FRONT, chunkPosX + x, chunkPosY + y, chunkPosZ + z, chunkBlockExists[x][y][z], &baseIndex);

                if (z == CHUNK_SIZE_Z - 1 || chunkBlockExists[x][y][z + 1]  == AIR)  
                    block.addFace(Sides::BACK, chunkPosX + x, chunkPosY + y, chunkPosZ + z, chunkBlockExists[x][y][z], &baseIndex);

                if (y == 0 || chunkBlockExists[x][y - 1][z]  == AIR)  
                    block.addFace(Sides::DOWN, chunkPosX + x, chunkPosY + y, chunkPosZ + z, chunkBlockExists[x][y][z], &baseIndex);

                if (y == CHUNK_SIZE_Y - 1 || chunkBlockExists[x][y + 1][z] == AIR)  
                    block.addFace(Sides::TOP,chunkPosX + x, chunkPosY + y, chunkPosZ + z, chunkBlockExists[x][y][z], &baseIndex);

                if (x == 0 || chunkBlockExists[x - 1][y][z] == AIR)  
                    block.addFace(Sides::LEFT, chunkPosX + x, chunkPosY + y, chunkPosZ + z, chunkBlockExists[x][y][z], &baseIndex);

                if (x == CHUNK_SIZE_X - 1 || chunkBlockExists[x + 1][y][z] == AIR)  
                    block.addFace(Sides::RIGHT, chunkPosX + x, chunkPosY + y, chunkPosZ + z, chunkBlockExists[x][y][z], &baseIndex);
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
