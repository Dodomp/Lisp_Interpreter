#ifndef BLOCKMANAGER_H
#define BLOCKMANAGER_H
#include <vector>

#include "Block.h"

class BlockManager {
public:
    BlockManager() = default;
    //distruttore
    ~BlockManager() {
        auto i = allocated.begin();
        for (; i != allocated.end(); i++) {
            delete(*i);
        }
    }

    BlockManager(const BlockManager& other) = delete;
    BlockManager& operator= (const BlockManager& other) = delete;

    //metodo per allocare un oggetto di tipo Block
    Block* makeBlock(Block b) {
        Block* bl = new Block(b);
        allocated.push_back(bl);
        return bl;
    }

   
private:
    vector<Block*> allocated;
};

#endif 