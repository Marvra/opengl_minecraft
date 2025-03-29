#pragma once

#include<vector>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include"Block.h"

#define CHUNK_SIZE_X 8
#define CHUNK_SIZE_Y 32
#define CHUNK_SIZE_Z 8


class Chunk
{
private:

    // std::vector<float> vertices;
    // std::vector<unsigned int> indices;

    //int generated = 1;

public:

    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    Chunk();
    ~Chunk();

    void generateChunk();
};