//
//  dataDef.h
//  DPOR
//
//  Created by Xiaoqi Yu on 4/2/15.
//  Copyright (c) 2015 Xiaoqi Yu. All rights reserved.
//
//Definition of the data structure in the project

#ifndef DPOR_dataDef_h
#define DPOR_dataDef_h

#include <iostream>
#include "gDef.h"
#include <vector>

using namespace std;

#define BLOCKSIZE 32768 //bit size of block
#define BLOCKNUM 100
#define MEMSIZE BLOCKSIZE*BLOCKNUM
#define MEMCELLSIZE 64
#define LAMBDA 128
#define CODERATE 128
#define TREESIZE 4
#define DUMMY 0;


#define TESTBT
//#define REALBT

#ifdef REALBT
//Definition of Memory cell val
struct MemNodeVal{
    unsigned long int val;
    MemNodeVal(unsigned long int v){val=v;};
    
};

#endif

#ifdef REALBT
//Definition of Memory Cell
struct MemCell_s{
    unsigned long int val;
    size_t idx;
    size_t getIdx(){return idx;}
};
#endif

#ifdef TESTBT
//Define Memory Cell for test binary tree
struct MemCell_s{
    int val;
    int idx;
    size_t getIdx(){return idx;}
};
#endif

//Definition of Block
struct Block_s{
    MemCell_s val[BLOCKSIZE/MEMCELLSIZE];
    size_t idx;
    size_t pos;
    Block_s(){
        memset(val, 0, sizeof(MemCell_s)*BLOCKSIZE);
        idx = 0;
    }
    void setIdx(size_t i){idx = i;}
    void setPos(size_t p){pos = p;}
    size_t getIdx(){return idx;}
    size_t getPos(){return pos;}
};

typedef struct MemCell_s* MemCell_t;
typedef struct Block_s* Block_t;
typedef vector<size_t> POSMAP;


//Definition of TreeNode
struct TreeNode{
    struct Block_s val[TREESIZE];
    TreeNode *lch;
    TreeNode *rch;
    
};

//Definition of Binary Tree
class BinaryTree{
public:
    BinaryTree(){root = nullptr;};
    ~BinaryTree(){};
    
    //init; init a new binary tree with MemCell list mct; return 1 if success; else return 0;
   // int init(MemCell_t mct);
    
    //init; init a new binary tree with Block list BS; return 1 if success; else return 0;
    int init(Block_t bst);
	// get the level of tree
	size_t getLevelNum();
    
    //Read path p from the binary tree,reside the fetched blocks in vector ret,return 1 if success,else return 0
    int readPath(size_t p, vector<TreeNode> ret);
    
    
    //Call a flush of the data cell from root to the leaf with randomly chosen one path;put the blocks in ret that fails to reside in the tree;return 1 if success,else return 0
    int flush(vector<Block_s> ret);
    
    //Write block b into   
    int writBlock(TreeNode * node, Block_s b, vector<Block_s> ret);
    
    //replace the block with index bid resided in path p with value DUMMY;return 1 if success;else return 0;
    int delBlock(size_t p, size_t bid);
    
    //Read from root to level l,return 1 if success, else return 0
    int readByLevel(size_t l, vector<Block_s> ret);

	//Get root
	TreeNode* getRoot(){
		return root;}
private:
    TreeNode *root;
};

//Definition of Client
class Client{
public:
    Client(){};
    ~Client(){};
    
    //return 1 if success;else return 0;
    int init(MemCell_s mem[MEMSIZE],Block_s bs[BLOCKNUM]);
    int init_1(Block_s bs[BLOCKNUM]);
   // MemCell_s readMemCell(size_t p, size_t idx);
    //will need it ????????????????
    MemCell_s readMemCell(size_t idx, size_t bid);
    int evict(MemCell_s mc);
    int getPos();
    void setPos(MemCell_s mc);
    size_t getPos(MemCell_s mc);
    void getIdx(MemCell_s mc);
    
private:
    vector<MemCell_s> stash;
};

//Definition of Server
class Server{
public:
    Server();
    Server(MemCell_s mem[]);
    ~Server(){};
    
    int init(MemCell_s mem[MEMSIZE]);
    int init(Block_s bs[BLOCKNUM]);
    
    //read back the blocks in the path with block bid
    int readPath(size_t bid, vector<Block_s> ret);
    int delBlock(size_t bid);
    
    MemCell_t readPath(size_t p);
    MemCell_s readCell(size_t p, size_t idx);
    void updatePos(size_t bid);
	
    
private:
    BinaryTree storage;
    POSMAP pm;
};

#endif
