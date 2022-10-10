#include "DrawChunk.h"
#include <iostream>
#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>
#include "stb_image.h"



void DrawChunk::LoadFaceData(BlockFace face, float* tempVert, unsigned int* tempInd, int x, int y, int z, int &indicieOffset, int faceCount)
{
	float* tempFace = new float[40];
	unsigned int* tempFaceInd = new unsigned int[6];

	memcpy_s(tempFace, sizeof(float) * 40, face.vertecies, sizeof(float) * 40);
	memcpy_s(tempFaceInd, sizeof(unsigned int) * 6, face.indicies, sizeof(unsigned int) * 6);

	//float* tempFace = face.vertecies;
	//unsigned int* tempFaceInd = face.indicies;
	for (int t = 0; t < 4; t++)
	{
		float* target = tempFace + (10 * t);
		*target += x;
		target++;
		*target += y;
		target++;
		*target += z;
	}
	for (int i = 0; i < 6; i++)
	{
		unsigned int* target = tempFaceInd + i;
		*target += indicieOffset;
	}
	memcpy_s(tempVert + (faceCount * 40), sizeof(float) * 40, tempFace, sizeof(float) * 40);
	memcpy_s(tempInd + (faceCount * 6), sizeof(unsigned int) * 6, tempFaceInd, sizeof(unsigned int) * 6);
	indicieOffset += 4;
	delete[40] tempFace;
	delete[6] tempFaceInd;
}

DrawChunk::~DrawChunk()
{
	delete[chunkVertexBufferSize] chunkVertexBuffer;
	delete[chunkIndicieBufferSize] chunkIndicieBuffer;

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

/*	==================================================
*	Z+ | NORTH		Z- | SOUTH
*	X+ | WEST		X- | EAST
*	Y+ | UP			Y- | DOWN
	================================================== */

void DrawChunk::ChunkDataToMesh(glm::vec2 chunkCoord, std::map<std::pair<int, int>, WorldChunkData*> worldDat)
{
	int checkDir[6][3] = {
		//x, y, z
		{ 1, 0, 0 },
		{-1, 0, 0 },
		{ 0, 1, 0 },
		{ 0,-1, 0 },
		{ 0, 0, 1 },
		{ 0, 0,-1 }
	};

	//Add block data and indicies to buffers

	Blocks *blockRef = new Blocks();
	int indicieOffset = 0;

	std::map<std::pair<int, int>, WorldChunkData*>::iterator worldDatIT = worldDat.find(std::pair<int, int>((int)chunkCoord.x, (int)chunkCoord.y));
	WorldChunkData* currentChunk = worldDatIT->second;

	//Data in array is in [x][z][y] format
	for (int x = 0; x < 16; x++)
	{
		for (int z = 0; z < 16; z++)
		{
			for (int y = 0; y < 16; y++)
			{
				//check if the block isn't "air"
				//if (testChunkData[x][z][y] != 0)
				if (currentChunk->chunkData[x][z][y] != 0)
				{
					//Block* currentBlock = blockRef->blockLookup[testChunkData[x][z][y]];
					Block* currentBlock = blockRef->blockLookup[currentChunk->chunkData[x][z][y]];
					float* tempVert = new float[240];
					unsigned int* tempInd = new unsigned int[36];
					int faceCount = 0;

					//Check every block arround to see if there is air
					for (int c = 0; c < 6; c++)
					{
						int checkX = x + checkDir[c][0];
						int checkY = y + checkDir[c][1];
						int checkZ = z + checkDir[c][2];

						if (checkX >= 0 && checkX < 16 && checkX != x)
						{
							//block to check is in the current chunk
							//if (testChunkData[checkX][checkZ][checkY] == 0)
							if (currentChunk->chunkData[checkX][checkZ][checkY] == 0)
							{
								if (checkX > x)
								{
									//Right face
									LoadFaceData(currentBlock->GetBlockRightFace(), tempVert, tempInd, x, y, z, indicieOffset, faceCount);
								}
								else
								{
									//Left face
									LoadFaceData(currentBlock->GetBlockLeftFace(), tempVert, tempInd, x, y, z, indicieOffset, faceCount);
								}
								faceCount++;
							}
						}
						else if (checkX != x && (checkX < 0 || checkX >= 16))
						{
							//block is not in the chunk and east/west chunk needs to be checked
							if (checkX > x)
							{
								//Get west chunk
								worldDatIT = worldDat.find(std::pair<int, int>((int)chunkCoord.x + 1, (int)chunkCoord.y));
								//Safty check that data is there
								//TODO: world data should be generated at the same time chunks are loaded
								//		when chunks are loaded relative to player generate one chunk farther than render distance
								if (worldDatIT != worldDat.end())
								{
									WorldChunkData* westChunk = worldDatIT->second;
									if (westChunk->chunkData[0][z][y] == 0)
									{
										LoadFaceData(currentBlock->GetBlockRightFace(), tempVert, tempInd, x, y, z, indicieOffset, faceCount);
									}
								}
							}
							else
							{
								//Get east chunk
								worldDatIT = worldDat.find(std::pair<int, int>((int)chunkCoord.x - 1, (int)chunkCoord.y));
								if (worldDatIT != worldDat.end())
								{
									WorldChunkData* eastChunk = worldDatIT->second;
									if (eastChunk->chunkData[15][z][y] == 0)
									{
										LoadFaceData(currentBlock->GetBlockLeftFace(), tempVert, tempInd, x, y, z, indicieOffset, faceCount);
									}
								}
							}
						}
						if (checkZ >= 0 && checkZ < 16 && checkZ != z)
						{
							//block to check is in the current chunk
							//if (testChunkData[checkX][checkZ][checkY] == 0)
							if (currentChunk->chunkData[checkX][checkZ][checkY] == 0)
							{
								if (checkZ > z)
								{
									//Front face
									LoadFaceData(currentBlock->GetBlockFrontFace(), tempVert, tempInd, x, y, z, indicieOffset, faceCount);
								}
								else
								{
									//Back face
									LoadFaceData(currentBlock->GetBlockBackFace(), tempVert, tempInd, x, y, z, indicieOffset, faceCount);
								}
								faceCount++;
							}
						}
						else if (checkZ != z && (checkZ < 0 || checkZ >= 16))
						{
							//block is not in the chunk and north/south chunk needs to be checked
							if (checkZ > z)
							{
								//Get north chunk
								worldDatIT = worldDat.find(std::pair<int, int>((int)chunkCoord.x, (int)chunkCoord.y + 1));
								if (worldDatIT != worldDat.end())
								{
									WorldChunkData* northChunk = worldDatIT->second;
									if (northChunk->chunkData[x][0][y] == 0)
									{
										LoadFaceData(currentBlock->GetBlockFrontFace(), tempVert, tempInd, x, y, z, indicieOffset, faceCount);
									}
								}
							}
							else
							{
								//Get south chunk
								worldDatIT = worldDat.find(std::pair<int, int>((int)chunkCoord.x, (int)chunkCoord.y - 1));
								if (worldDatIT != worldDat.end())
								{
									WorldChunkData* southChunk = worldDatIT->second;
									if (southChunk->chunkData[x][15][y] == 0)
									{
										LoadFaceData(currentBlock->GetBlockBackFace(), tempVert, tempInd, x, y, z, indicieOffset, faceCount);
									}
								}
							}
						}
						if (checkY >= 0 && checkY < 16 && checkY != y)
						{
							//block to check is withing the hight bounds
							//if (testChunkData[checkX][checkZ][checkY] == 0)
							if (currentChunk->chunkData[checkX][checkZ][checkY] == 0)
							{
								if (checkY > y)
								{
									//Top face
									LoadFaceData(currentBlock->GetBlockTopFace(), tempVert, tempInd, x, y, z, indicieOffset, faceCount);
								}
								else
								{
									//Bottom face
									LoadFaceData(currentBlock->GetBlockBottomFace(), tempVert, tempInd, x, y, z, indicieOffset, faceCount);
								}
								faceCount++;
							}
						}
						else if (checkY != y && (checkY < 0 || checkY >= 16))
						{
							//block to check is outside hight bounds, draw that face
							
							if (checkY > y)
							{
								//Top face
								LoadFaceData(currentBlock->GetBlockTopFace(), tempVert, tempInd, x, y, z, indicieOffset, faceCount);
							}
							else
							{
								//Bottom face
								LoadFaceData(currentBlock->GetBlockBottomFace(), tempVert, tempInd, x, y, z, indicieOffset, faceCount);
							}
							faceCount++;
						}
					}

					//Add the new face data into the vertex buffer
					int oldVertexBufferSize = chunkVertexBufferSize;
					chunkVertexBufferSize += (faceCount * 40);
					float* newVertBuffer = new float[chunkVertexBufferSize];
					if (chunkVertexBuffer != nullptr)
					{
						memcpy_s(newVertBuffer, sizeof(float) * oldVertexBufferSize, chunkVertexBuffer, sizeof(float) * oldVertexBufferSize);
						delete[oldVertexBufferSize] chunkVertexBuffer;
					}
					memcpy_s(newVertBuffer + oldVertexBufferSize, sizeof(float) * (faceCount * 40), tempVert, sizeof(float) * (faceCount * 40));
					chunkVertexBuffer = newVertBuffer;
					delete[240] tempVert;


					//Add the new indicie data into the indicie buffer
					int oldIndecieBufferSize = chunkIndicieBufferSize;
					chunkIndicieBufferSize += (faceCount * 6);
					unsigned int* newIndBuffer = new unsigned int[chunkIndicieBufferSize];
					if (chunkIndicieBuffer != nullptr)
					{
						memcpy_s(newIndBuffer, sizeof(unsigned int) * oldIndecieBufferSize, chunkIndicieBuffer, sizeof(unsigned int) * oldIndecieBufferSize);
						delete[oldIndecieBufferSize] chunkIndicieBuffer;
					}
					memcpy_s(newIndBuffer + oldIndecieBufferSize, sizeof(unsigned int) * (faceCount * 6), tempInd, sizeof(unsigned int) * (faceCount * 6));
					delete[36] tempInd;
					chunkIndicieBuffer = newIndBuffer;


				}
			}
		}
	}

	delete blockRef;

	int chunkOffsetX = (int)chunkCoord.x * 16;
	int chunkOffsetY = (int)chunkCoord.y * 16;

	//Take chunk data and convert it into a mesh that can be used and drawn to the screen
	//generate buffers
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	//bind buffers
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	//buffer data
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * chunkVertexBufferSize, chunkVertexBuffer, GL_DYNAMIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * chunkIndicieBufferSize, chunkIndicieBuffer, GL_DYNAMIC_DRAW);

	//Interpret vertex data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void *)0);
	//Interpret normal data
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void *)(sizeof(float) * 3));
	//Interpret texture coord data
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void *)(sizeof(float) * 6));
	//Interpret atlas index data
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void *)(sizeof(float) * 8));
	//Enable attributes
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);


	//Get and load texture
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	int width;
	int hight;
	int nrChannels;
	unsigned char* textureData = stbi_load("textures/256Atlas.png", &width, &hight, &nrChannels, 0);
	if (textureData)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, hight, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "ERROR::TEXTURE::FAILED_TO_LOAD\n" << std::endl;
	}
	stbi_image_free(textureData);


	glBindVertexArray(0);

	//Set model transform
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(chunkOffsetX, 0, chunkOffsetY));
}

void DrawChunk::DrawChunkMesh(glm::mat4 view, glm::mat4 proj, Shader chunkShader)
{
	//use shader
	chunkShader.use();

	

	//Send matrix data to shader
	int modelLoc = glGetUniformLocation(chunkShader.ID, "model");
	int viewLoc = glGetUniformLocation(chunkShader.ID, "view");
	int projLoc = glGetUniformLocation(chunkShader.ID, "projection");

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

	//Draw
	glBindTexture(GL_TEXTURE_2D, texture);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glDrawElements(GL_TRIANGLES, chunkIndicieBufferSize, GL_UNSIGNED_INT, 0);

}

float* DrawChunk::GetVertexBuffer()
{
	return chunkVertexBuffer;
}

unsigned int* DrawChunk::GetIndicieBuffer()
{
	return chunkIndicieBuffer;
}

int DrawChunk::GetVertexSize()
{
	return chunkVertexBufferSize;
}

int DrawChunk::GetIndicieSize()
{
	return chunkIndicieBufferSize;
}
