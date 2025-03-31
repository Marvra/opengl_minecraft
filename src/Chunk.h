#pragma once

#include<vector>
#include<chrono>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include"Block.h"
#include"VAO.h"
#include"EBO.h"
#include"VBO.h"

#define CHUNK_SIZE_X 8
#define CHUNK_SIZE_Y 16
#define CHUNK_SIZE_Z 8


class Chunk
{
private:

    bool chunk_block[CHUNK_SIZE_X][CHUNK_SIZE_Y][CHUNK_SIZE_Z];

    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    VAO VAO1;
    VBO VBO1;
    EBO EBO1;

    // std::vector<float> vertices;
    // std::vector<unsigned int> indices;

    //int generated = 1;

public:

    Chunk();
    ~Chunk();

    void generateChunkPattern();

    void generateChunk();

    void render();
};