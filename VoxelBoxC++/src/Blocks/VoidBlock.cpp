#include "VoidBlock.h"

VoidBlock::VoidBlock()
{
	topFace.vertecies = topFaceVert;
	topFace.indicies = faceInd;
	bottomFace.vertecies = bottomFaceVert;
	bottomFace.indicies = bottomFaceInd;
	frontFace.vertecies = frontFaceVert;
	frontFace.indicies = faceInd;
	backFace.vertecies = backFaceVert;
	backFace.indicies = faceInd;
	rightFace.vertecies = rightFaceVert;
	rightFace.indicies = faceInd;
	leftFace.vertecies = leftFaceVert;
	leftFace.indicies = faceInd;
}

unsigned int VoidBlock::GetBlockID()
{
	return ID;
}

float* VoidBlock::GetBlockMeshData()
{
	return cubeData;
}

unsigned int* VoidBlock::GetBlockIndicies()
{
	return cubeIndices;
}

int VoidBlock::GetBlockMeshDataSize()
{
	return CUBE_DATA_SIZE;
}

int VoidBlock::GetBlockIndiciesSize()
{
	return CUBE_INDICES_SIZE;
}

BlockFace VoidBlock::GetBlockTopFace()
{
	return topFace;
}

BlockFace VoidBlock::GetBlockBottomFace()
{
	return bottomFace;
}

BlockFace VoidBlock::GetBlockFrontFace()
{
	return frontFace;
}

BlockFace VoidBlock::GetBlockBackFace()
{
	return backFace;
}

BlockFace VoidBlock::GetBlockRightFace()
{
	return rightFace;
}

BlockFace VoidBlock::GetBlockLeftFace()
{
	return leftFace;
}
