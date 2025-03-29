#pragma once

#include<vector>
#include<iostream>

enum Sides
{
    FRONT = 0,
    BACK = 1,
    TOP = 2,
    DOWN = 3,
    LEFT = 4,
    RIGHT = 5 
};

static const float faceVertices[6][32] = {
    { // FRONT (-Z)
        -0.5f, -0.5f,  0.5f,  0.83f, 0.70f, 0.44f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.83f, 0.70f, 0.44f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.83f, 0.70f, 0.44f,  0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.83f, 0.70f, 0.44f,  1.0f, 1.0f,
    },
    { // BACK (+X)
        -0.5f, -0.5f, -0.5f,  0.83f, 0.70f, 0.44f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.83f, 0.70f, 0.44f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.83f, 0.70f, 0.44f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.83f, 0.70f, 0.44f,  1.0f, 1.0f,
    },
    { // LEFT (-Y)
        -0.5f, -0.5f,  0.5f,  0.83f, 0.70f, 0.44f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.83f, 0.70f, 0.44f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.83f, 0.70f, 0.44f,  0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.83f, 0.70f, 0.44f,  1.0f, 1.0f,
    },
    { // RIGHT (+Y)
         0.5f, -0.5f,  0.5f,  0.83f, 0.70f, 0.44f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.83f, 0.70f, 0.44f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.83f, 0.70f, 0.44f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.83f, 0.70f, 0.44f,  1.0f, 1.0f,
    },
    { // TOP (-Z)
        -0.5f,  0.5f,  0.5f,  0.83f, 0.70f, 0.44f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.83f, 0.70f, 0.44f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.83f, 0.70f, 0.44f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.83f, 0.70f, 0.44f,  1.0f, 1.0f,
    },
    { // BOTTOM (+Z)
        -0.5f, -0.5f,  0.5f,  0.83f, 0.70f, 0.44f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.83f, 0.70f, 0.44f,  1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.83f, 0.70f, 0.44f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.83f, 0.70f, 0.44f,  1.0f, 1.0f,
    }
};

static const unsigned int cubeIndices[6][6] = {
    { 1, 0, 2, 1, 2, 3 },   // FRONT (-X)
    { 4, 5, 6, 6, 5, 7 },   // BACK (+X)
    { 8, 9, 10, 10, 9, 11 }, // LEFT (-Y)
    { 13, 12, 14, 13, 14, 15 }, // RIGHT (+Y)
    { 17, 16, 18, 17, 18, 19 }, // TOP (-Z)
    { 20, 21, 22, 22, 21, 23 }  // BOTTOM (+Z)
};



class Block
{
private:
    //bool type = false;
    int postion_x;
    int postion_y;
    int postion_z;

    std::vector<float>* vertices;
    std::vector<unsigned int>* indices;


public:
    Block( std::vector<float>* vertices,  std::vector<unsigned int>* indices);

    int getX() const { return postion_x; }
    int getY() const { return postion_y; }
    int getZ() const { return postion_z; }

    void setX(int x) { postion_x = x; }
    void setY(int y) { postion_y = y; }
    void setZ(int z) { postion_z = z; }

    void addFace(Sides side, int x, int y, int z, int count);
};