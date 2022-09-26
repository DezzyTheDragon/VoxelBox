#ifndef VOXELBOX_STRUCTS
#define VOXELBOX_STRUCTS

struct WorldChunkData
{
	short chunkData[16][16][16];
};

struct chunkCluster
{
	short targetChunk[16][16][16];
	short northChunk[16][16][16];
	short southChunk[16][16][16];
	short eastChunk[16][16][16];
	short westChunk[16][16][16];
};

#endif // !VOXELBOX_STRUCTS
