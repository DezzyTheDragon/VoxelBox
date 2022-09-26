#include "LoadChunk.h"
#include "GenerateTerrainData.h"
#include <list>

void LoadChunk::LoadNewChunks(glm::vec2 chunkCoord)
{
	//Run DrawChunk.ChunkDataToMesh for the target chunk and add to active chunk list

	//std::pair<int, int> coord((int)chunkCoord.x, (int)chunkCoord.y);


	int checkChunkDir[5][2] = {
		{  0,  1 },	//North chunk
		{  1,  0 },	//West chunk
		{  0,  0 },	//Target chunk
		{ -1,  0 },	//East chunk
		{  0, -1 }	//South chunk
	};

	for (int c = 0; c < 5; c++)
	{
		std::map<std::pair<int, int>, WorldChunkData*>::iterator checkChunk = worldData.find(
			std::make_pair((int)chunkCoord.x + checkChunkDir[c][0], (int)chunkCoord.y + checkChunkDir[c][1]));
		if (checkChunk == worldData.end())
		{
			GenerateTerrainData genData;
			genData.GenerateChunkData(std::pair<int, int>((int)chunkCoord.x + checkChunkDir[c][0], (int)chunkCoord.y + checkChunkDir[c][1]), &worldData);
		}
	}


	DrawChunk* newChunk = new DrawChunk();
	activeChunks.insert(std::pair<std::pair<int, int>, DrawChunk*>(std::make_pair((int)chunkCoord.x, (int)chunkCoord.y), newChunk));
	newChunk->ChunkDataToMesh(chunkCoord, worldData);
}

void LoadChunk::DeloadChunks(std::pair<int, int> chunkCoord)
{
	//Remove chunk from active chunk list and deconstruct the acording DrawChunk
	DrawChunk* removeChunk = activeChunks.find(chunkCoord)->second;
	activeChunks.erase(chunkCoord);
	delete removeChunk;
}

LoadChunk::LoadChunk(FlyCamera* p)
{
	//Constructor
	//Get player position and prime load the surrounding land
	player = p;
}

LoadChunk::~LoadChunk()
{
	//Deconstructor
	//Free everything
	for (std::map<std::pair<int, int>, DrawChunk*>::iterator it = activeChunks.begin(); it != activeChunks.end(); ++it)
	{
		delete it->second;
	}
	for (std::map<std::pair<int, int>, WorldChunkData*>::iterator it = worldData.begin(); it != worldData.end(); ++it)
	{
		delete it->second;
	}
}

void LoadChunk::CheckActiveChunks()
{
	//Evaluate player position and see if chunks need to be loaded and unloaded
	//This should be checked in the window loop
	
	//Have a list of all active chunks and cross off still active chunks
	std::list<std::pair<int, int>> chunksToRemove;
	for (std::map<std::pair<int, int>, DrawChunk*>::iterator it = activeChunks.begin(); it != activeChunks.end(); ++it)
	{
		chunksToRemove.push_back(it->first);
	}

	int plrChunkX = (int)player->GetCameraPosition().x / 16;
	int plrChunkY = (int)player->GetCameraPosition().z / 16;

	//Run through the chunks within the render distance and draw them
	for (int x = plrChunkX - renderDistance; x <= plrChunkX + renderDistance; x++)
	{
		for (int y = plrChunkY - renderDistance; y <= plrChunkY + renderDistance; y++)
		{
			//Check if the target chunk isn't already loaded
			std::map<std::pair<int, int>, DrawChunk*>::iterator it;
			std::pair<int, int> find(x, y);
			it = activeChunks.find(find);
			if (it == activeChunks.end())
			{
				//Load chunk
				LoadNewChunks(glm::vec2(x, y));
			}
			else
			{
				//Remove still active chunk
				chunksToRemove.remove(find);
			}
		}
	}

	for (std::list<std::pair<int, int>>::iterator it = chunksToRemove.begin(); it != chunksToRemove.end(); ++it)
	{
		DeloadChunks(*it);
	}
}

void LoadChunk::ShowActiveChunks(glm::mat4 view, glm::mat4 proj, Shader chunkShader)
{
	for (std::map<std::pair<int, int>, DrawChunk*>::iterator it = activeChunks.begin(); it != activeChunks.end(); ++it)
	{
		it->second->DrawChunkMesh(view, proj, chunkShader);
	}
}
