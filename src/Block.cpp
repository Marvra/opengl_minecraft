#include "Block.h"

Block::Block(std::vector<float>* vertices, std::vector<unsigned int>* indices)
{
    this->vertices = vertices;
    this->indices = indices;

}


void Block::addFace(Sides side, int x, int y, int z, Types type,int* count)
{
    for(int i = 0; i < 4; i++)
    {
        this->vertices->push_back(faceVertices[side][i * 5] + x);
        this->vertices->push_back(faceVertices[side][(i * 5) + 1] + y);
        this->vertices->push_back(faceVertices[side][(i * 5) + 2] - z);
        this->vertices->push_back(blockTextureCoords[type][i*2]);
        this->vertices->push_back(blockTextureCoords[type][(i*2) + 1]);
    }

    for(int i = 0; i < 6; i++)
    {
        this->indices->push_back(cubeIndices[i] + *count);
    }
    
    *count += 4;
}


