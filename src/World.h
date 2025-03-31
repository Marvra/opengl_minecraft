#pragma once

#include<iostream>
#include<unordered_map>
#include"Chunk.h"

class World
{
private:
    std::unordered_map<std::pair<int, int>, Chunk> chunks;

public:
    World(/* args */);
    ~World();

    void generateChunks();
};