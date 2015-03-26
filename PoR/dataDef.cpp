//
//  dataDef.cpp
//  DPOR
//
//  Created by Xiaoqi Yu on 4/2/15.
//  Copyright (c) 2015 Xiaoqi Yu. All rights reserved.
//
#include "stdafx.h"
#include <iostream>
#include "dataDef.h"
// binary operation
#include <bitset>
#include<queue>
using namespace std;


//Binary Tree Definition
BinaryTree::BinaryTree(){
	// construct root node
	root = new TreeNode();
	};

int BinaryTree::init(Block_t bst){
	int size = sizeof(bst),blockSize = 4,i = 0;
	// split the data into blocks of size of blockSize;
	root = getRoot();
	*root->val=bst[i++];
	TreeNode *parent=root;
	for(i;i < size; i++){
		//creat left and right child node and put data into them
		TreeNode *leftchild = new TreeNode();
		parent->lch = leftchild;
		*leftchild->val = bst[i++];
		TreeNode *rightchild = new TreeNode();
		parent->rch = rightchild;
		*rightchild->val=bst[i++];


	}
		 

};
// get the level of tree
size_t BinaryTree::getLevelNum(){
	TreeNode *p=getRoot();
	int count=1;
	while(p){
		p=p->lch;
		count++;
	}
	return count;
};
//Read path p from the binary tree,reside the fetched blocks in vector ret,return 1 if success,else return 0
int BinaryTree::readPath(size_t p, vector<TreeNode> ret){	
	//convert unsigned int p to binary 
	bitset<64> bitVector = p;
	// get LevelNum to pick out the last level-1 bits of bitvector;
	int levelNum=getLevelNum();
	TreeNode *root,*temp;
	int index = 0;
	root = getRoot();
	temp = root;
	ret[index++] = *root;
	for(int i = 64-(levelNum-1);i < 64; i++){
		// left child 
		if(bitVector[i] == 0){
			temp= temp->lch;
			ret[index++] = *temp;
		}
		else{
			//right child
			temp= temp->rch;
			ret[index++] = *temp;
		}
	}
	return 1;
	
 };

  //Read from root to level l,return 1 if success, else return 0
int BinaryTree::readByLevel(size_t l, vector<Block_s> ret){
	LevelOrderTraverse(getRoot(),l,ret);
	return 1;
	// consider return later
};

void LevelOrderTraverse(TreeNode* p, size_t l, vector<Block_s> ret)  
{  
	int index=0;
	queue<TreeNode*> q;  
	TreeNode *temp;
	q.push(p);
	// the number of nodes from level 1 to level l
	int sum=pow(2,l)-1;
    if(p!=NULL  & (index<sum)  )
    {  
        while(!q.empty())  
        {  
			temp= q.front();
			q.pop();
			//read the content of the node
			for(int i=0;i<TREESIZE;i++)
			ret[index++]= temp->val[i];
			if(temp->lch!=NULL) 
				q.push(temp->lch);  
            if(temp->rch!=NULL)
				q.push(temp->rch);  
        }  
 
    }  
	
};
//Write block b into root
int BinaryTree::writBlock(TreeNode* node, Block_s b, vector<Block_s> ret){
	TreeNode* root = getRoot();
	bool empty=false;
	// decide whether root is empty
	for(int i=0;i<TREESIZE;i++)
		if((root->val[i]).val ==0){
			empty=true; 
			root->val[i]=b;
			return 1;
	}
// if there is no space, put b into vector b
	if(empty==false){
		//ret[0]=b;
		ret.push_back(b);
		return 0;
	}
};
    
//replace the block with index bid resided in path p with value DUMMY;return 1 if success;else return 0;
int BinaryTree::delBlock(size_t p, size_t bid){
	//denote whether succeed when readPath
	int sign,size;
	vector<TreeNode> ret;
	Block_s dummy;
	sign = readPath( p, ret);
	size=ret.size();
	if(sign==1){
		for(int i=0;i<size;i++){
			for(int j=0;j<TREESIZE;j++)
		if(ret[i].val[j].idx==bid)
			ret[i].val[j]=dummy;
			return 1;
		}
	}
	else
		return 0;
	
};