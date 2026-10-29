#pragma once

#include "BufferBlockADT.h"
#include "BufferBlock.h"
#include <cstring>

class BufferBlock : public BufferBlockADT {
    private:
    char block[4096];

    public:
    BufferBlock() {}

    void getData(int pos, int sz, char* data) override {
        if (pos < 0 || pos >= sizeof(block)) {
            throw std::out_of_range("Position is out of range");
        }
        if (sz < 0 || pos + sz > sizeof(block)) {
            throw std::out_of_range("Size is out of range");
        }
        std::memcpy(data, block + pos, sz);
    }

    void setID(int id) override {
        std::memcpy(block, &id, sizeof(int));
    }

    int getID() const override {
        int id = 0;
        std::memcpy(&id, block, sizeof(int));
        return id;
    }

    int getBlockSize() const override {
        return sizeof(block);
    }

    char* getBlock() const override {
        return const_cast<char*>(block);
    }

    void setBlock(char* blk) override {
        std::memcpy(block + 4, blk, 4092);
    }
};