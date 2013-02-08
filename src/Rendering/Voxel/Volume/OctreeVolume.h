#ifndef OCTREE_VOLUME_H
#define OCTREE_VOLUME_H



#include "../../Util/octree/octree.h"
#include "Volume.h"
#include <iostream>

class OctreeVolume:public Volume
{
public:

	
	OctreeVolume(unsigned int size,unsigned int dummyY = 0,unsigned int dummyZ = 0);
	~OctreeVolume(void);

	 void set(int x,int y,int z,BlockType type);
	 BlockType get(int x,int y,int z);

	 bool isInvisible();
	 bool isEmpty();
	 void setInvisible(bool invisible);

	unsigned int getWidth();
	unsigned int getHeight();
	unsigned int getDepth();

private:
	bool invisible;
	unsigned int numBlocks;
	Octree<BlockType> * blocks;
	unsigned int size;
};

#endif