// Created by OPTada // Free for use //
// - - - - - - - - - - - - - - - - - //

#pragma once


// enum - contains Texture names
enum OPTadaE_TextureList_ForResourceManager
{
	ENUM_TextureList_NONE = 0,


	ENUM_TextureList_Road_1,
	ENUM_TextureList_Test_PlayerCar,

	ENUM_TextureList_TextureForCar_1_1,
	ENUM_TextureList_TextureForCar_1_2,
	ENUM_TextureList_TextureForCar_1_3,

	ENUM_TextureList_TextureForCar_2_1,
	ENUM_TextureList_TextureForCar_2_2,
	ENUM_TextureList_TextureForCar_2_3,

	ENUM_TextureList_TextureForCar_3_1,
	ENUM_TextureList_TextureForCar_3_2,
	ENUM_TextureList_TextureForCar_3_3,

	ENUM_TextureList_TextureForCar_4_1,
	ENUM_TextureList_TextureForCar_4_2,
	ENUM_TextureList_TextureForCar_4_3,

	ENUM_TextureList_Text_0,
	ENUM_TextureList_Text_1,

	ENUM_TextureList_ForResourceManager_MaxCount,
};


// structure - cell of texture
struct OPTadaS_TextureStructure
{
	OPTadaE_TextureList_ForResourceManager textureEnum = ENUM_TextureList_NONE; // texture type (Enum)

	bool isInGPUMemory = false; // true - we have this in GPU memory, and can draw | false - only CPU memory 

	ID3D11ShaderResourceView* texture = nullptr;

	// function will free all GPU resources and set all other on default
	void Free_GPU()
	{
		SafeRelease(texture);
		isInGPUMemory = false;
	}
};

