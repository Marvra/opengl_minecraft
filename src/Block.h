#pragma once

#include<vector>

enum Sides
{
    FRONT,
    BACK,
    UP,
    DOWN,
    LEFT,
    RIGHT
};

static const float faceVertices[6][32] = {
    { // LEFT (-X)
        -0.5f, -0.5f,  0.5f,  0.83f, 0.70f, 0.44f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.83f, 0.70f, 0.44f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.83f, 0.70f, 0.44f,  0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.83f, 0.70f, 0.44f,  1.0f, 1.0f,
    },
    { // RIGHT (+X)
         0.5f, -0.5f,  0.5f,  0.83f, 0.70f, 0.44f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.83f, 0.70f, 0.44f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.83f, 0.70f, 0.44f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.83f, 0.70f, 0.44f,  1.0f, 1.0f,
    },
    { // BOTTOM (-Y)
        -0.5f, -0.5f,  0.5f,  0.83f, 0.70f, 0.44f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.83f, 0.70f, 0.44f,  1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.83f, 0.70f, 0.44f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.83f, 0.70f, 0.44f,  1.0f, 1.0f,
    },
    { // TOP (+Y)
        -0.5f,  0.5f,  0.5f,  0.83f, 0.70f, 0.44f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.83f, 0.70f, 0.44f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.83f, 0.70f, 0.44f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.83f, 0.70f, 0.44f,  1.0f, 1.0f,
    },
    { // FRONT (-Z)
        -0.5f, -0.5f, -0.5f,  0.83f, 0.70f, 0.44f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.83f, 0.70f, 0.44f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.83f, 0.70f, 0.44f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.83f, 0.70f, 0.44f,  1.0f, 1.0f,
    },
    { // BACK (+Z)
        -0.5f, -0.5f,  0.5f,  0.83f, 0.70f, 0.44f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.83f, 0.70f, 0.44f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.83f, 0.70f, 0.44f,  0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.83f, 0.70f, 0.44f,  1.0f, 1.0f,
    }
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
    ~Block();

    int getX() const { return postion_x; }
    int getY() const { return postion_y; }
    int getZ() const { return postion_z; }

    void setX(int x) { postion_x = x; }
    void setY(int y) { postion_y = y; }
    void setZ(int z) { postion_z = z; }

    void addFace(Sides side, int x, int y, int z);
};