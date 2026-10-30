#pragma once

#include "BufferPoolADT.h"
#include "BufferBlock.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <memory>

class LRUBufferPool : public BufferPoolADT {
    private:
    std::vector<std::unique_ptr<BufferBlock>> bufferBlocks;
    std::string filename;
    int poolSize;
    int blockSize;
    std::ifstream fileStream;

    public:
    LRUBufferPool(const std::string& fname, int pSize, int bSize) 
        : filename(fname), poolSize(pSize), blockSize(bSize) {
        bufferBlocks.reserve(poolSize);
        for (int i = 0; i < poolSize; ++i) {
            bufferBlocks.emplace_back(std::make_unique<BufferBlock>());
        }
        fileStream.open(filename, std::ios::binary);
        if (!fileStream) {
            throw std::runtime_error("Failed to open file: " + filename);
        }
    }

    ~LRUBufferPool() {
        if (fileStream.is_open()) {
            fileStream.close();
        }
    }

    void getBytes(char* data, int size, int pos) override {
        if (pos < 0 || size < 0 || pos + size > blockSize * poolSize) {
            throw std::out_of_range("Position or size is out of range");
        }

        int blockIndex = pos / blockSize;
        int offset = pos % blockSize;

        if (blockIndex >= poolSize) {
            throw std::out_of_range("Block index is out of range");
        }

        BufferBlock* block = bufferBlocks[blockIndex].get();
        if (block->getID() != blockIndex) {
            loadBlock(blockIndex);
            block = bufferBlocks[blockIndex].get();
        }

        block->getData(offset, size, data);
    }

    void loadBlock(int blockIndex) {
        if (blockIndex < 0 || blockIndex >= poolSize) {
            throw std::out_of_range("Block index is out of range");
        }

        BufferBlock* block = bufferBlocks[blockIndex].get();
        fileStream.seekg(blockIndex * blockSize);
        char tempBlock[4096];
        fileStream.read(tempBlock, blockSize);
        block->setBlock(tempBlock);
        block->setID(blockIndex);
    }

    void printBufferBlockOrder() override {
        std::cout << "My buffer block order from most recently used to LRU is:\n";
        for (const auto& block : bufferBlocks) {
            std::cout << block->getID() << ", ";
        }
        std::cout << std::endl;
    }
}