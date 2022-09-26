#include "GrassBlock.h"

GrassBlock::GrassBlock()
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

unsigned int GrassBlock::GetBlockID()
{
	return ID;
}

float* GrassBlock::GetBlockMeshData()
{
	return cubeData;
}

unsigned int* GrassBlock::GetBlockIndicies()
{
	return cubeIndices;
}

int GrassBlock::GetBlockMeshDataSize()
{
	return CUBE_DATA_SIZE;
}

int GrassBlock::GetBlockIndiciesSize()
{
	return CUBE_INDICES_SIZE;
}

BlockFace GrassBlock::GetBlockTopFace()
{
	return topFace;
}

BlockFace GrassBlock::GetBlockBottomFace()
{
	return bottomFace;
}

BlockFace GrassBlock::GetBlockFrontFace()
{
	return frontFace;
}

BlockFace GrassBlock::GetBlockBackFace()
{
	return backFace;
}

BlockFace GrassBlock::GetBlockRightFace()
{
	return rightFace;
}

BlockFace GrassBlock::GetBlockLeftFace()
{
	return leftFace;
}
