#include "GenerateTerrainData.h"

void GenerateTerrainData::GenerateChunkData(std::pair<int, int> chunkCoord, std::map<std::pair<int, int>, WorldChunkData*> *worldData)
{
	//For now just add a flat chunk to the world data
	WorldChunkData* newChunkData = new WorldChunkData;
	memcpy_s(newChunkData->chunkData, sizeof(short) * (16 * 16 * 16), testChunkData, sizeof(short) * (16 * 16 * 16));
	worldData->insert(std::make_pair(std::pair<int, int>(chunkCoord.first, chunkCoord.second), newChunkData));
}
