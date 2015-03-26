#include "stdafx.h"
#include <iostream>
#include "string.h"
#include "dataDef.h"

using namespace std;
int main(int argc, const char * argv[]) {
    cout<<"start tree sim."<<endl;
	// create data
	struct Block_s bs[7];
	for(int i = 0; i < 7; ++i){
		bs[i].setIdx(i);
		bs[i].setPos(i);
	}
	BinaryTree tree ;
	tree.init(bs);
    return 0;
}
