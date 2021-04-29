#include "TextureManager.h"

void TextureManager::LoadTextures()
{
	//grass
	CBitmap* pGrassBitmap = new CBitmap();
	pGrassBitmap->LoadFromFile("grass.png");

	glGenTextures(1, &grassTexture);
	glBindTexture(GL_TEXTURE_2D, grassTexture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, pGrassBitmap->m_nWidth, pGrassBitmap->m_nHeight, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, pGrassBitmap->m_pBytes);

	delete(pGrassBitmap);


	//dirt
	CBitmap* pDirtBitmap = new CBitmap();
	pDirtBitmap->LoadFromFile("dirt.jpg");

	glGenTextures(1, &dirtTexture);
	glBindTexture(GL_TEXTURE_2D, dirtTexture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, pDirtBitmap->m_nWidth, pDirtBitmap->m_nHeight, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, pDirtBitmap->m_pBytes);

	delete(pDirtBitmap);


	//stone
	CBitmap* pStoneBitmap = new CBitmap();
	pStoneBitmap->LoadFromFile("stone.png");

	glGenTextures(1, &stoneTexture);
	glBindTexture(GL_TEXTURE_2D, stoneTexture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, pStoneBitmap->m_nWidth, pStoneBitmap->m_nHeight, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, pStoneBitmap->m_pBytes);

	delete(pStoneBitmap);


	//cloud
	CBitmap* pCloudBitmap = new CBitmap();
	pCloudBitmap->LoadFromFile("Cloud.png");

	glGenTextures(1, &cloudTexture);
	glBindTexture(GL_TEXTURE_2D, cloudTexture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, pCloudBitmap->m_nWidth, pCloudBitmap->m_nHeight, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, pCloudBitmap->m_pBytes);

	delete(pCloudBitmap);
	CBitmap* pSkyboxBitmap = new CBitmap();
	//cloud
	pSkyboxBitmap->LoadFromFile("skybox.jpg");

	glGenTextures(1, &skyboxTexture);
	glBindTexture(GL_TEXTURE_2D, skyboxTexture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, pSkyboxBitmap->m_nWidth, pSkyboxBitmap->m_nHeight, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, pSkyboxBitmap->m_pBytes);

	delete(pSkyboxBitmap);


	// water
	CBitmap* pWaterBitmap = new CBitmap();
	pWaterBitmap->LoadFromFile("blending_transparent_window.png");

	glGenTextures(1, &waterTexture);
	glBindTexture(GL_TEXTURE_2D, waterTexture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pWaterBitmap->m_nWidth, pWaterBitmap->m_nHeight, 0, GL_BGRA, GL_UNSIGNED_BYTE, pWaterBitmap->m_pBytes);

	delete(pWaterBitmap);
}

void TextureManager::BindTexture(GLuint texture)
{
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_TEXTURE);
	glBindTexture(GL_TEXTURE_2D, texture);
}
