#pragma once
#include <string>
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Perlin.h"
#include <map>
#include "Block.h"


class Chunk
{
public:
	enum Face {
		ypos,
		yneg,
		zpos,
		zneg,
		xneg,
		xpos
	};

	Block * getBlock(int x,int y,int z);
	Block * getBlock(ci::ivec3 v);

	void setTexMap(ci::gl::Texture2dRef tex);

	void GenMesh();
	ci::TriMesh * GetMesh();
	
	void addFace(ci::TriMesh* mesh, ci::vec3 pos, Face face,int BlockID);
	void appendTex(int i, ci::TriMesh * mesh, int BlockID);

	void Draw();
	ci::vec3 getChunkPos();
	ci::vec2 GetOffset(int BID);
	void setChunkPos(ci::vec3 pos);
	Chunk(ci::Perlin* _gen,	float _scale);
	Chunk(ci::Perlin* _gen, float _scale,ci::ivec3 pos);
	Chunk();
	~Chunk();
private:
	ci::Perlin* gen;
	float scale;
	ci::TriMesh  mMesh;
	ci::ivec3 ChunkPos;
	ci::gl::Texture2dRef mTex;
	Block blocks[16][16][16];
};

