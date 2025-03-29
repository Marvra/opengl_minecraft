#include "Block.h"

Block::Block(std::vector<float>* vertices, std::vector<unsigned int>* indices)
{
    this->vertices = vertices;
    this->indices = indices;

}


void Block::addFace(Sides side, int x, int y, int z, int* count)
{
    for(int i = 0; i < 4; i++)
    {
        this->vertices->push_back(faceVertices[side][i * 8] + x);
        this->vertices->push_back(faceVertices[side][(i * 8) + 1] + y);
        this->vertices->push_back(faceVertices[side][(i * 8) + 2] - z);
        this->vertices->push_back(faceVertices[side][(i * 8) + 3]);
        this->vertices->push_back(faceVertices[side][(i * 8) + 4]);
        this->vertices->push_back(faceVertices[side][(i * 8) + 5]);
        this->vertices->push_back(faceVertices[side][(i * 8) + 6]);
        this->vertices->push_back(faceVertices[side][(i * 8) + 7]);
    }

    for(int i = 0; i < 6; i++)
    {
        this->indices->push_back(cubeIndices[i] + *count);
    }
    
    *count += 4;
}


