#include "Chunk.h"

Chunk::Chunk()
{
    generateChunk();
}

Chunk::~Chunk()
{
    VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
}

void Chunk::generateChunkPattern()
{
    for (int x = 0; x < CHUNK_SIZE_X; x++) {
        for (int y = 0; y < CHUNK_SIZE_Y; y++) {
            for (int z = 0; z < CHUNK_SIZE_Z; z++) {

                // CHECKERBOARD
                // if( (x + y + z) % 2 == 0)
                // {
                //     this->chunk_block[x][y][z] = true;
                // }

                //  ALL FILLED
                this->chunk_block[x][y][z] = true;


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
    auto start = std::chrono::high_resolution_clock::now();

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
                    block.addFace(Sides::FRONT, x, y, z, &baseIndex);

                if (z == CHUNK_SIZE_Z - 1 || !chunk_block[x][y][z + 1])  
                    block.addFace(Sides::BACK, x, y, z, &baseIndex);

                if (y == 0 || !chunk_block[x][y - 1][z])  
                    block.addFace(Sides::DOWN, x, y, z, &baseIndex);

                if (y == CHUNK_SIZE_Y - 1 || !chunk_block[x][y + 1][z])  
                    block.addFace(Sides::TOP, x, y, z, &baseIndex);

                if (x == 0 || !chunk_block[x - 1][y][z])  
                    block.addFace(Sides::LEFT, x, y, z, &baseIndex);

                if (x == CHUNK_SIZE_X - 1 || !chunk_block[x + 1][y][z])  
                    block.addFace(Sides::RIGHT, x, y, z, &baseIndex);
                
                //block.addFace(Sides::FRONT, x, y, z, &baseIndex);
                //block.addFace(Sides::BACK, x, y, z, &baseIndex);
                //block.addFace(Sides::DOWN, x, y, z, &baseIndex);
                //block.addFace(Sides::TOP, x, y, z, &baseIndex);
                //block.addFace(Sides::LEFT, x, y, z, &baseIndex);
                //block.addFace(Sides::RIGHT, x, y, z, &baseIndex);
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration = end - start;
    std::cout << "Chunk generation time: " << duration.count() * 1000 << " ms" << std::endl;
}

void Chunk::render()
{
    VAO1.Bind();

    VBO1.Generate(&vertices, vertices.size() * sizeof(float));
    // Generates Element Buffer Object and links it to indices
    EBO1.Generate(&indices, indices.size() * sizeof(unsigned int));

    // VBO VBO1(vertices, sizeof(vertices));
    // EBO EBO1(indices, sizeof(indices));
    

    // Links VBO to VAO
    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    // Unbind all to prevent accidentally modifying them
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    VAO1.Bind();
	glDrawElements(GL_TRIANGLES,indices.size(), GL_UNSIGNED_INT, 0);
    
}
