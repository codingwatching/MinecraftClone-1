#include "Chunk.h"

Block* Chunk::getBlock(int x, int y, int z)
{
	//ci::app::console() << ((x+1)*(y+1)*(z+1))-1 << std::endl;
	return &blocks[x][y][z];
}

Block* Chunk::getBlock(ci::ivec3 v)
{
	return &blocks[v.x][v.y][v.z];
}

void Chunk::setTexMap(ci::gl::Texture2dRef tex)
{
	mTex = tex;
}

void Chunk::GenMesh()
{
	mMesh= ci::TriMesh(
		ci::TriMesh::Format()
		.positions()
		.colors(3)
		.texCoords(2)
	);

	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 16; j++) {
			for (int k = 0; k < 16; k++) {
				ci::ivec3 pos=ci::vec3(i, j, k);
				if (getBlock(pos)->GetID() == 1) {
					if (pos.y + 1 < 16) {
						if (getBlock(ci::vec3(pos.x, pos.y + 1, pos.z))->GetID() == 0) {
							addFace(&mMesh, pos+(ChunkPos * ci::ivec3(16)), ypos, getBlock(ci::vec3(pos.x, pos.y + 1, pos.z))->GetID());
						}
					}
					else {
						addFace(&mMesh, pos + (ChunkPos * ci::ivec3(16)), ypos, getBlock(ci::vec3(pos.x, pos.y + 1, pos.z))->GetID());
					}
					if (pos.y - 1 > 0) {
						if (getBlock(ci::vec3(pos.x, pos.y-1, pos.z))->GetID() == 0) {
							addFace(&mMesh, pos + (ChunkPos * ci::ivec3(16)), yneg, getBlock(ci::vec3(pos.x, pos.y - 1, pos.z))->GetID());
						}
					}
					else {
						addFace(&mMesh, pos + (ChunkPos * ci::ivec3(16)), yneg, getBlock(ci::vec3(pos.x, pos.y - 1, pos.z))->GetID());
					}
					if (pos.x + 1 < 16) {
						if (getBlock(ci::vec3(pos.x + 1, pos.y, pos.z))->GetID()==0) {
							addFace(&mMesh, pos + (ChunkPos * ci::ivec3(16)), xpos, getBlock(ci::vec3(pos.x + 1, pos.y, pos.z))->GetID());
						}
					}
					else {
						addFace(&mMesh, pos + (ChunkPos * ci::ivec3(16)), xpos, getBlock(ci::vec3(pos.x + 1, pos.y, pos.z))->GetID());
					}
					if (pos.x - 1 > 0) {
						if (getBlock(ci::vec3(pos.x - 1, pos.y, pos.z))->GetID() == 0) {
							addFace(&mMesh, pos + (ChunkPos * ci::ivec3(16)), xneg, getBlock(ci::vec3(pos.x - 1, pos.y, pos.z))->GetID());
						}
					}
					else {
						addFace(&mMesh, pos + (ChunkPos * ci::ivec3(16)), xneg, getBlock(ci::vec3(pos.x - 1, pos.y, pos.z))->GetID());
					}
					if (pos.z + 1 < 16) {
						if (getBlock(ci::vec3(pos.x, pos.y, pos.z+1))->GetID() == 0) {
							addFace(&mMesh, pos + (ChunkPos * ci::ivec3(16)), zpos, getBlock(ci::vec3(pos.x, pos.y, pos.z + 1))->GetID());
						}
					}
					else {
						addFace(&mMesh, pos + (ChunkPos * ci::ivec3(16)), zpos, getBlock(ci::vec3(pos.x, pos.y, pos.z + 1))->GetID());
					}
					if (pos.z - 1 > 0) {
						if (getBlock(ci::vec3(pos.x, pos.y, pos.z-1))->GetID() == 0) {
							addFace(&mMesh, pos + (ChunkPos * ci::ivec3(16)), zneg, getBlock(ci::vec3(pos.x, pos.y, pos.z - 1))->GetID());
						}
					}
					else {
						addFace(&mMesh, pos + (ChunkPos * ci::ivec3(16)), zneg, getBlock(ci::vec3(pos.x, pos.y, pos.z - 1))->GetID());
					}
					
				}
			}
		}
	}
}

ci::TriMesh * Chunk::GetMesh()
{
	return &mMesh;
}

void Chunk::addFace(ci::TriMesh* mesh, ci::vec3 pos, Face face,int blockID)
{
	ci::vec3 YPosface[4] = {
	ci::vec3(0 + pos.x, 1 + pos.y, 1 + pos.z),
	ci::vec3(1 + pos.x, 1 + pos.y, 1 + pos.z),
	ci::vec3(1 + pos.x, 1 + pos.y, 0 + pos.z),
	ci::vec3(0 + pos.x, 1 + pos.y, 0 + pos.z)
	};
	ci::vec3 YNegface[4] = {
	ci::vec3(0 + pos.x, 0 + pos.y, 1 + pos.z),
	ci::vec3(1 + pos.x, 0 + pos.y, 1 + pos.z),
	ci::vec3(1 + pos.x, 0 + pos.y, 0 + pos.z),
	ci::vec3(0 + pos.x, 0 + pos.y, 0 + pos.z)
	};
	ci::vec3 XPosface[4] = {
	ci::vec3(1 + pos.x, 0 + pos.y, 1 + pos.z),
	ci::vec3(1 + pos.x, 1 + pos.y, 1 + pos.z),
	ci::vec3(1 + pos.x, 1 + pos.y, 0 + pos.z),
	ci::vec3(1 + pos.x, 0 + pos.y, 0 + pos.z)
	};
	ci::vec3 XNegface[4] = {
	ci::vec3(0 + pos.x, 0 + pos.y, 1 + pos.z),
	ci::vec3(0 + pos.x, 1 + pos.y, 1 + pos.z),
	ci::vec3(0 + pos.x, 1 + pos.y, 0 + pos.z),
	ci::vec3(0 + pos.x, 0 + pos.y, 0 + pos.z)
	};
	ci::vec3 ZPosface[4] = {
	ci::vec3(0 + pos.x, 0 + pos.y, 1 + pos.z),
	ci::vec3(0 + pos.x, 1 + pos.y, 1 + pos.z),
	ci::vec3(1 + pos.x, 1 + pos.y, 1 + pos.z),
	ci::vec3(1 + pos.x, 0 + pos.y, 1 + pos.z)
	};
	ci::vec3 ZNegface[4] = {
	ci::vec3(0 + pos.x, 0 + pos.y, 0 + pos.z),
	ci::vec3(0 + pos.x, 1 + pos.y, 0 + pos.z),
	ci::vec3(1 + pos.x, 1 + pos.y, 0 + pos.z),
	ci::vec3(1 + pos.x, 0 + pos.y, 0 + pos.z)
	};
	switch (face)
	{
	case Chunk::ypos:
		for (int i = 0; i < 4; i++) {
			mesh->appendPosition(YPosface[i]);
			appendTex(i, mesh, blockID);
		}
		break;
	case Chunk::yneg:
		
		for (int i = 0; i < 4; i++) {
			mesh->appendPosition(YNegface[i]);
			appendTex(i, mesh, blockID);
		}
		break;
	case Chunk::xpos:
			for (int i = 0; i < 4; i++) {
				mesh->appendPosition(XPosface[i]);
				appendTex(i, mesh, blockID);
			}

		break;
	case Chunk::xneg:
		for (int i = 0; i < 4; i++) {
			mesh->appendPosition(XNegface[i]);
			appendTex(i, mesh, blockID);
		}
		break;
	case Chunk::zpos:
		for (int i = 0; i < 4; i++) {
			mesh->appendPosition(ZPosface[i]);
			appendTex(i, mesh, blockID);
		}
		break;
	case Chunk::zneg:
		for (int i = 0; i < 4; i++) {
			mesh->appendPosition(ZNegface[i]);
			appendTex(i, mesh, blockID);
		}
		break;
	default:
		break;
	}



	int vert0 = mesh->getNumVertices() - 4;
	int vert1 = mesh->getNumVertices() - 1;
	int vert2 = mesh->getNumVertices() - 2;
	int vert3 = mesh->getNumVertices() - 3;
	mesh->appendTriangle(vert0, vert1, vert3);
	mesh->appendTriangle(vert3, vert1, vert2);

}

void Chunk::appendTex(int i,ci::TriMesh * mesh,int BlockID)
{
	float scalerX = 0.00143472022955523672883787661406;
	float scalerY = 0.015625;
	ci::vec2 offset = ci::vec2(1, 1);
	if (i == 0) {
		mesh->appendTexCoord(ci::vec2(0+(GetOffset(BlockID).x*scalerX), 1 + (GetOffset(BlockID).y * scalerY)));
		//mesh->appendColorRgb(ci::Color(0, 0, 0));
	}
	if (i == 1) {
		mesh->appendTexCoord(ci::vec2(0 + (GetOffset(BlockID).x * scalerX), (1-scalerY) + (GetOffset(BlockID).y * scalerY)));
		//mesh->appendColorRgb(ci::Color(1, 0, 0));
	}
	if (i == 2) {
		mesh->appendTexCoord(ci::vec2(scalerX + (GetOffset(BlockID).x * scalerX), (1-scalerY) + (GetOffset(BlockID).y * scalerY)));
		//mesh->appendColorRgb(ci::Color(1, 1, 0));
	}
	if (i == 3) {
		mesh->appendTexCoord(ci::vec2(scalerX + (GetOffset(BlockID).x * scalerX), 1 + (GetOffset(BlockID).y * scalerY)));
		//mesh->appendColorRgb(ci::Color(0, 1, 0));
	}
}

void Chunk::Draw()
{
	ci::gl::ScopedGlslProg glslScope{ ci::gl::getStockShader(ci::gl::ShaderDef().texture()) };
	ci::gl::ScopedTextureBind texScope{ mTex };
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	ci::gl::draw(mMesh);
	//for (int i = 0; i < 16; i++) {
	//	for (int j = 0; j < 16; j++) {
	//		for (int k = 0; k < 16; k++) {
	//			if (getBlock(i, j, k)->GetID() == 1) {
	//				ci::gl::color(ci::Color(1, 1, 1));
	//				ci::gl::drawCube(ci::vec3(i,j,k),ci::vec3(1));
	//			}
	//		}
	//	}
	//}
}

ci::vec3 Chunk::getChunkPos()
{
	return ChunkPos;
}

ci::vec2 Chunk::GetOffset(int BID)
{
	switch (BID)
	{
	case 0:
		return ci::vec2(425,0);
		break;
	case 1:
		return ci::vec2(425,0);
		break;
	default:
		return ci::vec2(0, 0);
		break;
	}
}

void Chunk::setChunkPos(ci::vec3 pos)
{
	ChunkPos = pos;
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 16; j++) {
			for (int k = 0; k < 16; k++) {
				float tmp = gen->fBm((i + (ChunkPos * ci::ivec3(16)).x) * scale, (j + (ChunkPos * ci::ivec3(16)).y) * scale, (k + (ChunkPos * ci::ivec3(16)).z) * scale);
				if (tmp > 0) {
					getBlock(i, j, k)->SetID(1);
				}
			}
		}
	}
	GenMesh();
}

Chunk::Chunk(ci::Perlin* _gen, float _scale)
{
	//for (int i = 0; i < 4096; i++) {
	//	blocks[i].ID = RandRange<int>(BlockMap.size()-1,0);
	//	blocks[i].MetaData = "";
	//}
	gen = _gen;
	scale = _scale;
	setChunkPos(ci::vec3(0, 0, 0));
}
Chunk::Chunk(ci::Perlin* _gen, float _scale,ci::ivec3 pos)
{
	//for (int i = 0; i < 4096; i++) {
	//	blocks[i].ID = RandRange<int>(BlockMap.size()-1,0);
	//	blocks[i].MetaData = "";
	//}

	gen = _gen;
	scale = _scale;
	setChunkPos(pos);
}

Chunk::Chunk()
{
	gen = nullptr;
	scale = 0;
}

Chunk::~Chunk()
{
}
