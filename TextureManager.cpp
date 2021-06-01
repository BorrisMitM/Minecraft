#include "TextureManager.h"

void TextureManager::LoadTextures()
{


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
	//Skybox
	pSkyboxBitmap->LoadFromFile("skyboxNew.png");

	glGenTextures(1, &skyboxTexture);
	glBindTexture(GL_TEXTURE_2D, skyboxTexture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, pSkyboxBitmap->m_nWidth, pSkyboxBitmap->m_nHeight, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, pSkyboxBitmap->m_pBytes);

	delete(pSkyboxBitmap);


	//// water
	//CBitmap* pWaterBitmap = new CBitmap();
	//pWaterBitmap->LoadFromFile("blending_transparent_window.png");

	//glGenTextures(1, &waterTexture);
	//glBindTexture(GL_TEXTURE_2D, waterTexture);

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pWaterBitmap->m_nWidth, pWaterBitmap->m_nHeight, 0, GL_BGRA, GL_UNSIGNED_BYTE, pWaterBitmap->m_pBytes);

	//delete(pWaterBitmap);
	// water
	CBitmap* pChunkBitmap = new CBitmap();
	pChunkBitmap->LoadFromFile("MinecraftAtlas.png");

	glGenTextures(1, &chunkAtlas);
	glBindTexture(GL_TEXTURE_2D, chunkAtlas);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pChunkBitmap->m_nWidth, pChunkBitmap->m_nHeight, 0, GL_BGRA, GL_UNSIGNED_BYTE, pChunkBitmap->m_pBytes);

	delete(pChunkBitmap);
}

void TextureManager::BindTexture(GLuint texture)
{
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_TEXTURE);
	glBindTexture(GL_TEXTURE_2D, texture);
}
