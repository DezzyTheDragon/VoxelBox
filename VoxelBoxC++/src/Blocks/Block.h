#ifndef BLOCK_BASE
#define BLOCK_BASE

struct BlockFace
{
	float* vertecies;
	unsigned int* indicies;
};

class Block
{
public:
	virtual unsigned int GetBlockID() = 0;
	virtual float* GetBlockMeshData() = 0;
	virtual unsigned int* GetBlockIndicies() = 0;
	virtual int GetBlockMeshDataSize() = 0;
	virtual int GetBlockIndiciesSize() = 0;
	virtual BlockFace GetBlockTopFace() = 0;
	virtual BlockFace GetBlockBottomFace() = 0;
	virtual BlockFace GetBlockFrontFace() = 0;
	virtual BlockFace GetBlockBackFace() = 0;
	virtual BlockFace GetBlockRightFace() = 0;
	virtual BlockFace GetBlockLeftFace() = 0;
};
#endif // !BLOCK_BASE