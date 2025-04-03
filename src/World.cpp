#include "World.h"

void World::generateChunks(int camPosX, int camPosZ)
{

    int renderByX = floor((float)camPosX / CHUNK_SIZE_X);
    int renderByZ = floor((float)camPosZ / CHUNK_SIZE_Z);
    int render = 4;


    for(int x  = renderByX - render ; x <= renderByX + render; x++)
    {
        for (int y = 0; y < 1; y++)
        {
            for (int z = renderByZ - render; z <= renderByZ + render; z++)
            {
                std::tuple<int,int,int> chunkPos(x,y,z);

                if(chunks.find(chunkPos) == chunks.end())
                {
                    chunks.try_emplace(chunkPos, x * CHUNK_SIZE_X, y * CHUNK_SIZE_Y,-(z * CHUNK_SIZE_Z));
                }
            }
        }
    }
}

void World::destroyChunks(int camPosX, int camPosZ)
{
    int renderByX = floor((float)camPosX / CHUNK_SIZE_X);
    int renderByZ = floor((float)camPosZ / CHUNK_SIZE_Z);
    int chunkDeletionRange = 4;
    for(auto chunk = chunks.begin(); chunk != chunks.end();)
    {
        int x = std::get<0>(chunk->first);
        //int y = std::get<1>(chunk->first);
        int z = std::get<2>(chunk->first);

        if (x < renderByX - chunkDeletionRange 
            || x > renderByX + chunkDeletionRange 
            || z < renderByZ - chunkDeletionRange 
            || z > renderByZ + chunkDeletionRange)
        {
            //chunks.find(chunk->first)->second.~Chunk(); // find chunk and call destructor
            chunk = chunks.erase(chunk); // erase calls destructor also i think  ^ this line causes double free (segfault)
            // maybe removing it from chunks isnt good because random generation of the dirt isnt the same
        }
        else
        {
            ++chunk;
        }
    }

}

void World::renderChunks()
{
    //auto start = std::chrono::high_resolution_clock::now();

    for(auto chunk = chunks.begin(); chunk != chunks.end(); ++chunk)
    {
        chunk->second.render();
        
    }

    //auto end = std::chrono::high_resolution_clock::now();
    //std::chrono::duration<float> duration = end - start;
    //std::cout << "Chunk generation time: " << duration.count() * 1000 << " ms" << std::endl;
}