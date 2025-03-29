#pragma once

#include<vector>
#include<iostream>

enum Sides
{
    FRONT = 0,
    BACK = 1,
    LEFT = 2,
    RIGHT = 3,
    TOP = 4,
    DOWN = 5
};

static const float faceVertices[6][32] = {
    { // FRONT (-Z)
        0.0f, 0.0f, 1.0f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
        1.0f, 0.0f, 1.0f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
        0.0f, 1.0f, 1.0f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
        1.0f, 1.0f, 1.0f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
    },
    { // BACK (+X)
        0.0f, 0.0f, 0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
        1.0f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f,  1.0f, 1.0f,
    },
    { // BOTTOM (-Y)
        0.0f, 0.0f, 1.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
        0.0f, 0.0f, 0.0f,  0.0f, 0.0f, 1.0f,  1.0f, 0.0f,
        0.0f, 1.0f, 1.0f,  0.0f, 0.0f, 1.0f,  0.0f, 1.0f,
        0.0f, 1.0f, 0.0f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f,
    },
    { // TOP (+Y)
        1.0f, 0.0f, 1.0f,  1.0f, 1.0f, 0.0f,  0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,  1.0f, 1.0f, 0.0f,  1.0f, 0.0f,
        1.0f, 1.0f, 1.0f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f,
        1.0f, 1.0f, 0.0f,  1.0f, 1.0f, 0.0f,  1.0f, 1.0f,
    },
    { // RIGHT (-Z)
        0.0f, 1.0f, 1.0f,  1.0f, 0.0f, 1.0f,  0.0f, 0.0f,
        1.0f, 1.0f, 1.0f,  1.0f, 0.0f, 1.0f,  1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,  1.0f, 0.0f, 1.0f,  0.0f, 1.0f,
        1.0f, 1.0f, 0.0f,  1.0f, 0.0f, 1.0f,  1.0f, 1.0f,
    },
    { // LEFT (+Z)
        0.0f, 0.0f, 1.0f,  0.0f, 1.0f, 1.0f,  0.0f, 0.0f,
        1.0f, 0.0f, 1.0f,  0.0f, 1.0f, 1.0f,  1.0f, 0.0f,
        0.0f, 0.0f, 0.0f,  0.0f, 1.0f, 1.0f,  0.0f, 1.0f,
        1.0f, 0.0f, 0.0f,  0.0f, 1.0f, 1.0f,  1.0f, 1.0f,
    }
};

static const unsigned int cubeIndices[6] = {
    0, 1, 2, 2, 1, 3 
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

    void addFace(Sides side, int x, int y, int z, int* count);
};