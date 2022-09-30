#pragma once
#include <map>
#include <GL/glew.h>
#include <glm.hpp>
#include <utility>
#include "FlyCamera.h"
#include "DrawChunk.h"
#include "Shader.h"
#include "VoxelBoxStructs.h"

class LoadChunk
{
private:
	FlyCamera* player;
	int renderDistance = 2;
	//The model of the chunks, pair is the chunk coord
	std::map<std::pair<int, int>, DrawChunk*> activeChunks;

	void LoadNewChunks(glm::vec2 chunkCoord);
	void DeloadChunks(std::pair<int, int> chunkCoord);
public:
	//The actual data of the chunks, pair is the chunk coord
	std::map<std::pair<int, int>, WorldChunkData*> worldData;
	LoadChunk(FlyCamera* p);
	~LoadChunk();
	void CheckActiveChunks();
	void ShowActiveChunks(glm::mat4 view, glm::mat4 proj, Shader chunkShader);
};