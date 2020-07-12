// Created by OPTada // Free for use //
// - - - - - - - - - - - - - - - - - //

#pragma once

#include "OPTadaC_GO_Factory.h"

#define OPTADA_GLOBAL_CHUNK_X 10
#define OPTADA_GLOBAL_CHUNK_Y 10


// struct item of chunk
struct OPTadaS_Ñhunc_Cell
{
	short int tile;
	char roadData;
};


struct OPTadaS_Chunc
{
	OPTadaS_Ñhunc_Cell mass[OPTADA_GLOBAL_CHUNK_X][OPTADA_GLOBAL_CHUNK_Y]; // mass of chunk data

	std::vector<OPTadaC_GO_Monolit>            monolit_list;           // monolit objects list
	std::vector<OPTadaC_GO_Monolit_WithHitBox> monolitWithHitBox_List; // monolit objects with hitbox list
	std::vector<OPTadaC_GO_Trigger>            trigger_list;           // trigger objects list


	void clear() {
		// clear mass
		int i = 0, i2 = 0;
		for (; i < OPTADA_GLOBAL_CHUNK_X; i++) {
			for (; i2 < OPTADA_GLOBAL_CHUNK_Y; i2++) {

			}
		}
	}
};