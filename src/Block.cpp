#include "Block.h"

Block::Block(std::vector<float>* vertices, std::vector<unsigned int>* indices)
{
    this->vertices = vertices;
    this->indices = indices;

}


void Block::addFace(Sides side, int x, int y, int z)
{
    switch (side)
    {
    case UP:
        break;
    
    default:
        break;
    }
}
