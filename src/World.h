#pragma once

#include<iostream>
#include<unordered_map>
#include"Chunk.h"
#include"PairHash.h"

class World
{
private:
    std::unordered_map<std::pair<int, int>, Chunk, hash_pair> chunks;

public:
    World(){};
    ~World(){};

    void generateChunks();
    void renderChunks();
};