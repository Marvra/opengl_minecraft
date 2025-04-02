#pragma once

#include<iostream>
#include<unordered_map>
#include<tuple>
#include"Chunk.h"
#include"TupleHash.h"

class World
{
private:
    std::unordered_map<std::tuple<int, int, int>, Chunk, TupleHash> chunks;

public:
    World(){};
    ~World(){};

    void generateChunks();
    void renderChunks();
};