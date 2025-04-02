#include "World.h"

void World::generateChunks()
{
    for(int x  = 0; x < 4; x++)
    {
        for (int y = 0; y < 4; y++)
        {
            for (int z = 0; z < 4; z++)
            {
                chunks.try_emplace(std::tuple(x,y,z), x * CHUNK_SIZE_X, y * CHUNK_SIZE_Y,z * CHUNK_SIZE_Z);
            }
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
    //std::cout << "Chunk generation time: " << duration.count() * 1000 << " ms" << std::endl;
}