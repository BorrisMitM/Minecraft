#include "TextureManager.h"

void TextureManager::LoadTextures()
{
	CBitmap* pGrassBitmap = new CBitmap();
	//dirt
	pGrassBitmap->LoadFromFile("grass.png");

	glGenTextures(1, &grassTexture);
	glBindTexture(GL_TEXTURE_2D, grassTexture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, pGrassBitmap->m_nWidth, pGrassBitmap->m_nHeight, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, pGrassBitmap->m_pBytes);

	delete(pGrassBitmap);
	CBitmap* pDirtBitmap = new CBitmap();
	//dirt
	pDirtBitmap->LoadFromFile("dirt.jpg");

	glGenTextures(1, &dirtTexture);
	glBindTexture(GL_TEXTURE_2D, dirtTexture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, pDirtBitmap->m_nWidth, pDirtBitmap->m_nHeight, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, pDirtBitmap->m_pBytes);

	delete(pDirtBitmap);
	CBitmap* pStoneBitmap = new CBitmap();
	//dirt
	pStoneBitmap->LoadFromFile("stone.png");

	glGenTextures(1, &stoneTexture);
	glBindTexture(GL_TEXTURE_2D, stoneTexture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, pStoneBitmap->m_nWidth, pStoneBitmap->m_nHeight, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, pStoneBitmap->m_pBytes);

	delete(pStoneBitmap);

	CBitmap* pCloudBitmap = new CBitmap();
	//cloud
	pCloudBitmap->LoadFromFile("Cloud.png");

	glGenTextures(1, &cloudTexture);
	glBindTexture(GL_TEXTURE_2D, cloudTexture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, pCloudBitmap->m_nWidth, pCloudBitmap->m_nHeight, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, pCloudBitmap->m_pBytes);

	delete(pCloudBitmap);
}

void TextureManager::BindTexture(GLuint texture)
{
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, texture);

}
