#include "StoneBlock.h"

StoneBlock::StoneBlock()
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

unsigned int StoneBlock::GetBlockID()
{
	return ID;
}

float* StoneBlock::GetBlockMeshData()
{
	return cubeData;
}

unsigned int* StoneBlock::GetBlockIndicies()
{
	return cubeIndices;
}

int StoneBlock::GetBlockMeshDataSize()
{
	return CUBE_DATA_SIZE;
}

int StoneBlock::GetBlockIndiciesSize()
{
	return CUBE_INDICES_SIZE;
}

BlockFace StoneBlock::GetBlockTopFace()
{
	return topFace;
}

BlockFace StoneBlock::GetBlockBottomFace()
{
	return bottomFace;
}

BlockFace StoneBlock::GetBlockFrontFace()
{
	return frontFace;
}

BlockFace StoneBlock::GetBlockBackFace()
{
	return backFace;
}

BlockFace StoneBlock::GetBlockRightFace()
{
	return rightFace;
}

BlockFace StoneBlock::GetBlockLeftFace()
{
	return leftFace;
}
