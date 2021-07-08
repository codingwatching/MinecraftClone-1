#include "World.h"

World::World()
{
	auto image = ci::loadImage(ci::app::loadAsset("../resources/textures/block/0ALL.png"));
	mTex = ci::gl::Texture2d::create(image);
}

Chunk* World::getChunk(int x, int y, int z)
{
	for (int i = 0; i < chunks.size(); i++) {
		if (chunks[i].getChunkPos() == ci::vec3(x, y, z)) {
			return &chunks[i];
		}
	}
	return NULL;
}

Chunk* World::getChunk(ci::vec3 v)
{
	return getChunk(v.x,v.y,v.z);
}

int World::getNumChunk()
{
	return chunks.size();
}

void World::LoadChunk(int x, int y, int z)
{
	if (!isChunkLoaded(x, y, z)) {
		Chunk tmp(&gen, scale, ci::ivec3(x, y, z));
		tmp.setTexMap(mTex);
		chunks.push_back(tmp);
	}
}

void World::LoadChunk(ci::vec3 v)
{
	LoadChunk(v.x, v.y, v.z);
}

void World::UnLoadChunk(int x, int y, int z)
{
	if (isChunkLoaded(x, y, z)) {
		for (int i = 0; i < chunks.size(); i++) {
			if (chunks[i].getChunkPos() == ci::vec3(x, y, z)) {
				chunks.erase(chunks.begin() + i);
			}
		}
	}
}

void World::UnLoadChunk(ci::vec3 v)
{
	UnLoadChunk(v.x, v.y, v.z);
}

bool World::isChunkLoaded(int x, int y, int z)
{
	for (int i = 0; i < chunks.size(); i++) {
		if (chunks[i].getChunkPos() == ci::vec3(x, y, z)) {
			return true;
		}
	}
	return false;
}

bool World::isChunkLoaded(ci::vec3 v)
{
	return isChunkLoaded(v.x, v.y, v.z);
}

void World::Draw()
{
	for (int i = 0; i < chunks.size(); i++)
	{
		chunks[i].Draw();
	}
}

ci::TriMesh* World::getChunkMesh(int x, int y, int z)
{
	return getChunk(x,y,z)->GetMesh();
}
