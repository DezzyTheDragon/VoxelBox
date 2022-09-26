#include "DirtBlock.h"

DirtBlock::DirtBlock()
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

unsigned int DirtBlock::GetBlockID()
{
	return ID;
}

float* DirtBlock::GetBlockMeshData()
{
	return cubeData;
}

unsigned int* DirtBlock::GetBlockIndicies()
{
	return cubeIndices;
}

int DirtBlock::GetBlockMeshDataSize()
{
	return CUBE_DATA_SIZE;
}

int DirtBlock::GetBlockIndiciesSize()
{
	return CUBE_INDICES_SIZE;
}

BlockFace DirtBlock::GetBlockTopFace()
{
	return topFace;
}

BlockFace DirtBlock::GetBlockBottomFace()
{
	return bottomFace;
}

BlockFace DirtBlock::GetBlockFrontFace()
{
	return frontFace;
}

BlockFace DirtBlock::GetBlockBackFace()
{
	return backFace;
}

BlockFace DirtBlock::GetBlockRightFace()
{
	return rightFace;
}

BlockFace DirtBlock::GetBlockLeftFace()
{
	return leftFace;
}
