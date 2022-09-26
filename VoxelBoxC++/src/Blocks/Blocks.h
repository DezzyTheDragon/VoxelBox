#ifndef BLOCKS
#define BLOCKS

//							// Block ID
//		  Air block			// 0
#include "VoidBlock.h"		// 1
#include "GrassBlock.h"		// 2
#include "DirtBlock.h"		// 3
#include "StoneBlock.h"		// 4

class Blocks
{
private:
	Block* vb = new VoidBlock();
	Block* gb = new GrassBlock();
	Block* db = new DirtBlock();
	Block* sb = new StoneBlock();
public:
	//Block array for block lookup
	//TODO: look into other maybe better solutions for block lookup that is more memory efficent
	Block* blockLookup[5] = { NULL, vb, gb, db, sb };
	~Blocks() 
	{ 
		delete vb;
		delete gb;
		delete db;
		delete sb;
	};
};
#endif // !BLOCKS