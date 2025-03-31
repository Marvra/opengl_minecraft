#include "World.h"

void World::generateChunks()
{
    for(int x  = 0; x < 8; x++)
    {
        for (int z = 0; z < 8; z++)
        {
            chunks.try_emplace(std::pair(x,z), x * CHUNK_SIZE_X, z * CHUNK_SIZE_Z);
        }
        
    }
}

void World::renderChunks()
{
    auto start = std::chrono::high_resolution_clock::now();

    for(auto chunk = chunks.begin(); chunk != chunks.end(); ++chunk)
    {
        chunk->second.render();
    }


    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration = end - start;
    std::cout << "Chunk generation time: " << duration.count() * 1000 << " ms" << std::endl;
}