#pragma once

#include<vector>
#include<chrono>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<math.h>
#include<OpenSimplexNoise.hh>
#include"Block.h"
#include"VAO.h"
#include"EBO.h"
#include"VBO.h"

#define CHUNK_SIZE_X 16
#define CHUNK_SIZE_Y 16
#define CHUNK_SIZE_Z 16

#define MAX_TERRAIN_HEIGHT 30
#define MIN_TERRAIN_HEIGHT 15


class Chunk
{
private:

    Types chunkBlockExists[CHUNK_SIZE_X][CHUNK_SIZE_Y][CHUNK_SIZE_Z];

    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    VAO VAO1;
    VBO VBO1;
    EBO EBO1;

    int chunkPosX;
    int chunkPosY;
    int chunkPosZ;

public:

    Chunk(int chunkPosX, int chunkPosY, int chunkPosZ);
    ~Chunk();

    void generateChunkPattern();

    void generateChunk();

    void render();

    int getIndicesCount();
    int getVerticesCount();
};