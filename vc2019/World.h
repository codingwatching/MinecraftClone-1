#pragma once
#include "../vc2019/Chunk.h"
#include <vector>

//globals
static ci::Perlin gen;
static float scale = .04;

//end globals
class World
{
	std::vector<Chunk> chunks;
	ci::gl::Texture2dRef mTex;
public:
	World();
	Chunk* getChunk(int x,int y,int z);
	Chunk* getChunk(ci::vec3 v);
	int getNumChunk();
	void LoadChunk(int x, int y, int z);
	void LoadChunk(ci::vec3 v);
	void UnLoadChunk(int x, int y, int z);
	void UnLoadChunk(ci::vec3 v);
	bool isChunkLoaded(int x, int y, int z);
	bool isChunkLoaded(ci::vec3 v);
	void Draw();
	ci::TriMesh* getChunkMesh(int x, int y, int z);
};

