#include "Block.h"

class VoidBlock : public Block
{
private:
	const int CUBE_DATA_SIZE = 240;
	const int CUBE_INDICES_SIZE = 36;
	const unsigned int ID = 1;
	float cubeData[240] = {
		//position				| normal				| textcoord		| atlas index
		//Top Face Y+
		-0.5f,  0.5f, -0.5f,	 0.0f,  1.0f,  0.0f,	0.0f, 0.0f,		0.0f, 0.0f,		//0
		 0.5f,  0.5f, -0.5f,	 0.0f,  1.0f,  0.0f,	1.0f, 0.0f,		0.0f, 0.0f,		//1
		 0.5f,  0.5f,  0.5f,	 0.0f,  1.0f,  0.0f,	1.0f, 1.0f,		0.0f, 0.0f,		//2
		-0.5f,  0.5f,  0.5f,	 0.0f,  1.0f,  0.0f,	0.0f, 1.0f,		0.0f, 0.0f,		//3
		//Bottom Face Y-
		-0.5f, -0.5f, -0.5f,	 0.0f, -1.0f,  0.0f,	0.0f, 0.0f,		0.0f, 0.0f,		//4
		 0.5f, -0.5f, -0.5f,	 0.0f, -1.0f,  0.0f,	1.0f, 0.0f,		0.0f, 0.0f,		//5
		 0.5f, -0.5f,  0.5f,	 0.0f, -1.0f,  0.0f,	1.0f, 1.0f,		0.0f, 0.0f,		//6
		-0.5f, -0.5f,  0.5f,	 0.0f, -1.0f,  0.0f,	0.0f, 1.0f,		0.0f, 0.0f,		//7
		//Front Face Z+
		-0.5f,  0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,	0.0f, 0.0f,		0.0f, 0.0f,		//8
		 0.5f,  0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,	1.0f, 0.0f,		0.0f, 0.0f,		//9
		 0.5f, -0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,	1.0f, 1.0f,		0.0f, 0.0f,		//10
		-0.5f, -0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,	0.0f, 1.0f,		0.0f, 0.0f,		//11
		//Back Face Z-
		-0.5f, -0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,	0.0f, 1.0f,		0.0f, 0.0f,		//12
		 0.5f, -0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,	1.0f, 1.0f,		0.0f, 0.0f,		//13
		 0.5f,  0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,	1.0f, 0.0f,		0.0f, 0.0f,		//14
		-0.5f,  0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,	0.0f, 0.0f,		0.0f, 0.0f,		//15
		//Right Face X+
		 0.5f,  0.5f,  0.5f,	 1.0f,  0.0f,  0.0f,	0.0f, 0.0f,		0.0f, 0.0f,		//16
		 0.5f,  0.5f, -0.5f,	 1.0f,  0.0f,  0.0f,	1.0f, 0.0f,		0.0f, 0.0f,		//17
		 0.5f, -0.5f, -0.5f,	 1.0f,  0.0f,  0.0f,	1.0f, 1.0f,		0.0f, 0.0f,		//18
		 0.5f, -0.5f,  0.5f,	 1.0f,  0.0f,  0.0f,	0.0f, 1.0f,		0.0f, 0.0f,		//19
		//Left Face X-
		-0.5f,  0.5f, -0.5f,	-1.0f,  0.0f,  0.0f,	0.0f, 0.0f,		0.0f, 0.0f,		//20
		-0.5f,  0.5f,  0.5f,	-1.0f,  0.0f,  0.0f,	1.0f, 0.0f,		0.0f, 0.0f,		//21
		-0.5f, -0.5f,  0.5f,	-1.0f,  0.0f,  0.0f,	1.0f, 1.0f,		0.0f, 0.0f,		//22
		-0.5f, -0.5f, -0.5f,	-1.0f,  0.0f,  0.0f,	0.0f, 1.0f,		0.0f, 0.0f		//23
	};
	unsigned int cubeIndices[36] = {
		//Top Face
		0, 1, 2,
		0, 2, 3,
		//Bottom Face
		6, 5, 4,
		7, 6, 4,
		//Front Face
		8, 9, 10,
		8, 10, 11,
		//Back Face
		12, 13, 14,
		12, 14, 15,
		//Right Face
		16, 17, 18,
		16, 18, 19,
		//Left Face
		20, 21, 22,
		20, 22, 23
	};

	//position				| normal				| textcoord		| atlas index
	float topFaceVert[40] = {
		-0.5f,  0.5f, -0.5f,	 0.0f,  1.0f,  0.0f,	0.0f, 0.0f,		0.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,	 0.0f,  1.0f,  0.0f,	1.0f, 0.0f,		0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,	 0.0f,  1.0f,  0.0f,	1.0f, 1.0f,		0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,	 0.0f,  1.0f,  0.0f,	0.0f, 1.0f,		0.0f, 0.0f
	};
	float bottomFaceVert[40] = {
		-0.5f, -0.5f, -0.5f,	 0.0f, -1.0f,  0.0f,	0.0f, 0.0f,		0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,	 0.0f, -1.0f,  0.0f,	1.0f, 0.0f,		0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,	 0.0f, -1.0f,  0.0f,	1.0f, 1.0f,		0.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,	 0.0f, -1.0f,  0.0f,	0.0f, 1.0f,		0.0f, 0.0f

	};
	float frontFaceVert[40] = {
		-0.5f,  0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,	0.0f, 0.0f,		0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,	1.0f, 0.0f,		0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,	1.0f, 1.0f,		0.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,	0.0f, 1.0f,		0.0f, 0.0f
	};
	float backFaceVert[40] = {
		-0.5f, -0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,	0.0f, 1.0f,		0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,	1.0f, 1.0f,		0.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,	1.0f, 0.0f,		0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,	0.0f, 0.0f,		0.0f, 0.0f
	};
	float rightFaceVert[40] = {
		 0.5f,  0.5f,  0.5f,	 1.0f,  0.0f,  0.0f,	0.0f, 0.0f,		0.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,	 1.0f,  0.0f,  0.0f,	1.0f, 0.0f,		0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,	 1.0f,  0.0f,  0.0f,	1.0f, 1.0f,		0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,	 1.0f,  0.0f,  0.0f,	0.0f, 1.0f,		0.0f, 0.0f
	};
	float leftFaceVert[40] = {
		-0.5f,  0.5f, -0.5f,	-1.0f,  0.0f,  0.0f,	0.0f, 0.0f,		0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,	-1.0f,  0.0f,  0.0f,	1.0f, 0.0f,		0.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,	-1.0f,  0.0f,  0.0f,	1.0f, 1.0f,		0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,	-1.0f,  0.0f,  0.0f,	0.0f, 1.0f,		0.0f, 0.0f
	};
	unsigned int faceInd[6] = {
		0, 1, 2,
		0, 2, 3
	};

	unsigned int bottomFaceInd[6] = {
		2, 1, 0,
		3, 2, 0
	};

	BlockFace topFace;
	BlockFace bottomFace;
	BlockFace frontFace;
	BlockFace backFace;
	BlockFace rightFace;
	BlockFace leftFace;
public:
	VoidBlock();
	unsigned int GetBlockID();
	float* GetBlockMeshData();
	unsigned int* GetBlockIndicies();
	int GetBlockMeshDataSize();
	int GetBlockIndiciesSize();
	BlockFace GetBlockTopFace();
	BlockFace GetBlockBottomFace();
	BlockFace GetBlockFrontFace();
	BlockFace GetBlockBackFace();
	BlockFace GetBlockRightFace();
	BlockFace GetBlockLeftFace();

};