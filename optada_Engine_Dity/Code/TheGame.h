// Created by OPTada // Free for use //
// - - - - - - - - - - - - - - - - - //

#pragma once

#include "Render\OPTada_Render.h"
#include "Window\OPTada_Window.h"
#include "Input\OPTada_Input.h"

#include "Physics\q3.h"

#include "Sound\include\soloud.h"
#include "Sound\include\dr_mp3.h"
#include "Sound\include\dr_wav.h"

#include "OPTadaC_GO_Factory.h"



// enum of game states
enum OPTadaE_GameState
{
	ENUM_GS_Play  = 0, // tested logic
	ENUM_GS_NewGame = 1, // pause logic
	ENUM_GS_GameOver  = 2, // play logic
};



OPTadaC_GO_Car car;


struct  chank_cell {
	OPTadaC_GO_Monolit road_Mass[4];

	chank_cell() {
		for (int i = 0; i < 4; i++) {
			OPTadaC_GO_Factory::Create_Monolit(road_Mass[i], ENUM_GO_Monolit_Road_1);
		}
	}

	void Draw(std::vector<OPTadaC_Obj_Draw*>& draw_opaque_) {
		for (int i = 0; i < 4; i++) {
			road_Mass[i].Draw(draw_opaque_);
		}
	}
};




//
class OPTada_TheGame : public q3ContactListener
{
private:


	OPTadaE_GameState gameState = ENUM_GS_Play;

	std::vector<OPTadaC_Obj_Draw*>* draw_opaque; // draw list

	// game objects

	OPTadaC_Obj_Camera* camera = nullptr;

	OPTadaC_GO_Car Player_Car;

	std::vector<OPTadaC_GO_Car*> carList;
	std::vector<OPTadaC_GO_Car*> carList_save; // for sort delete cars

	chank_cell chank_mass[5];
	int chunkPointer = 1;
	
	OPTadaC_Obj_Draw plan_draw;
	OPTadaS_WorldNavigationData plan;



public:

	void SetupAll(OPTadaC_Obj_Camera* camera_, std::vector<OPTadaC_Obj_Draw*>& draw_opaque_) {
		camera = camera_;
		draw_opaque = &draw_opaque_;
		OPTadaC_GO_Factory::Create_Car(Player_Car, ENUM_GO_CarType_PlayerCar, 0);

		for (int i = 0; i < 5; i++) {
			XMMATRIX position;
			XMMATRIX rotation;
			XMMATRIX scale;

			chank_mass[i].road_Mass[0].navigation.position.Z = i * 20 - 0;
			chank_mass[i].road_Mass[0].navigation.position.X = 25;
			chank_mass[i].road_Mass[0].navigation.position.Y = -0.5;
			
			chank_mass[i].road_Mass[0].navigation.calcPosition(position);
			chank_mass[i].road_Mass[0].navigation.calcRotation(rotation);
			chank_mass[i].road_Mass[0].navigation.calcScaling(scale);
			chank_mass[i].road_Mass[0].navigation.calcMatrix_SRT(scale, rotation, position);

			chank_mass[i].road_Mass[1].navigation.position.Z = i * 20 - 5;
			chank_mass[i].road_Mass[1].navigation.position.X = 25;
			chank_mass[i].road_Mass[1].navigation.position.Y = -0.5;

			chank_mass[i].road_Mass[1].navigation.calcPosition(position);
			chank_mass[i].road_Mass[1].navigation.calcRotation(rotation);
			chank_mass[i].road_Mass[1].navigation.calcScaling(scale);
			chank_mass[i].road_Mass[1].navigation.calcMatrix_SRT(scale, rotation, position);

			chank_mass[i].road_Mass[2].navigation.position.Z = i * 20 - 10;
			chank_mass[i].road_Mass[2].navigation.position.X = 25;
			chank_mass[i].road_Mass[2].navigation.position.Y = -0.5;

			chank_mass[i].road_Mass[2].navigation.calcPosition(position);
			chank_mass[i].road_Mass[2].navigation.calcRotation(rotation);
			chank_mass[i].road_Mass[2].navigation.calcScaling(scale);
			chank_mass[i].road_Mass[2].navigation.calcMatrix_SRT(scale, rotation, position);

			chank_mass[i].road_Mass[3].navigation.position.Z = i * 20 - 15;
			chank_mass[i].road_Mass[3].navigation.position.X = 25;
			chank_mass[i].road_Mass[3].navigation.position.Y = -0.5;

			chank_mass[i].road_Mass[3].navigation.calcPosition(position);
			chank_mass[i].road_Mass[3].navigation.calcRotation(rotation);
			chank_mass[i].road_Mass[3].navigation.calcScaling(scale);
			chank_mass[i].road_Mass[3].navigation.calcMatrix_SRT(scale, rotation, position);
		}

		global_physics_scene.SetContactListener(this);

		Player_Car.fbody->SetTransform({ 13.0f, 0.1, 0.0f });

		// shit
		plan_draw.PS = ENUM_PixelShaderList_PS_Color;
		plan_draw.VS = ENUM_VertexShaderList_VS_Color;
		plan_draw.world = &plan;
		plan_draw.mesh = ENUM_MeshList_Plane;
		plan_draw.texture_mass.push_back(ENUM_TextureList_Text_0); // set texture //TODO add random

		XMMATRIX position;
		XMMATRIX rotation;
		XMMATRIX scale;
		
	}

	void Tick(float delatTime_, unsigned char* kb_Mass_, unsigned char* m_Mass_) {
	
		// input

		// test mode
		if (gameState == ENUM_GS_Play) {
			PauseMode(delatTime_, kb_Mass_, m_Mass_);
			return;
		}
		// pause mode
		if (gameState == ENUM_GS_NewGame) {
			PlayMode(delatTime_, kb_Mass_, m_Mass_);
			return;
		}
		//play mode
		if (gameState == ENUM_GS_GameOver) {
			TestMode(delatTime_, kb_Mass_, m_Mass_);
			return;
		}

		// sound (update music)

	}

	void TestMode(float deltaTime_, unsigned char* kb_Mass_, unsigned char* m_Mass_) {

		// ---------- input player 
		if (_B_DOWN(kb_Mass_[DIK_F])) {
			spawnCar(Player_Car.navigation.position.Z, 10);
			//lvl.body->SetAngularVelocity(q3Vec3(0.0f, 0.0f, 1.0f));
			//lvl.body->SetAngularDamping(5.0f);
		}
		if (_B_PRESSED(kb_Mass_[DIK_D])) {
			Player_Car.Turn(0.4f);
		}
		if (_B_PRESSED(kb_Mass_[DIK_A])) {
			Player_Car.Turn(-0.4f);
		}
		if (_B_PRESSED(kb_Mass_[DIK_S])) {
			//Player_Car.MoveBack(-0.5f);
		}
		if (_B_PRESSED(kb_Mass_[DIK_W])) {
			Player_Car.MoveForward();		
		}
		if (_B_PRESSED(kb_Mass_[DIK_Q])) {

		}
		if (_B_PRESSED(kb_Mass_[DIK_E])) {

		}

		// ---------- update player car 

		Player_Car.Update_ModelPosition();
		Player_Car.Draw(*draw_opaque);
		
		// ---------- camera 

		camera->lookAt.X = Player_Car.navigation.position.X;
		camera->lookAt.Y = Player_Car.navigation.position.Y;
		camera->lookAt.Z = Player_Car.navigation.position.Z;

		camera->position.Z = Player_Car.navigation.position.Z - 10;
		camera->position.X = Player_Car.navigation.position.X;
		camera->position.Y = 8;

		camera->Update_ViewMatrix();

		// ---------- update AI cars
		int AIcount = carList.size();
		for (int i = 0; i < AIcount; i++) {
			carList[i]->MoveForward();
		}

		// ---------- check Delete Cars
		carList_save.clear();
		Try_deleteCar(Player_Car.navigation.position.Z);
		carList.clear();

		// ---------- copy saved cars to main mass
		AIcount = carList_save.size();
		for (int i = 0; i < AIcount; i++) {
			carList.push_back(carList_save[i]);
		}

		// ---------- draw cars
		AIcount = carList.size();
		for (int i = 0; i < AIcount; i++) {
			carList[i]->Update_ModelPosition();
			carList[i]->Draw(*draw_opaque);
		}

		// ---------- draw road
		for (int i = 0; i < 5; i++) {
			chank_mass[i].Draw(*draw_opaque);
		}

		// ---------- Check update chunk
		
		if (((int)(Player_Car.navigation.position.Z) / (int)20) > chunkPointer) {
			chunkPointer++; 
			for (int i = 0; i < 5; i++) {
				XMMATRIX position;
				XMMATRIX rotation;
				XMMATRIX scale;

				chank_mass[i].road_Mass[0].navigation.position.Z = i * 20 - 0 + chunkPointer * 20;

				chank_mass[i].road_Mass[0].navigation.calcPosition(position);
				chank_mass[i].road_Mass[0].navigation.calcRotation(rotation);
				chank_mass[i].road_Mass[0].navigation.calcScaling(scale);
				chank_mass[i].road_Mass[0].navigation.calcMatrix_SRT(scale, rotation, position);

				chank_mass[i].road_Mass[1].navigation.position.Z = i * 20 - 5 + chunkPointer * 20;

				chank_mass[i].road_Mass[1].navigation.calcPosition(position);
				chank_mass[i].road_Mass[1].navigation.calcRotation(rotation);
				chank_mass[i].road_Mass[1].navigation.calcScaling(scale);
				chank_mass[i].road_Mass[1].navigation.calcMatrix_SRT(scale, rotation, position);

				chank_mass[i].road_Mass[2].navigation.position.Z = i * 20 - 10 + chunkPointer * 20;

				chank_mass[i].road_Mass[2].navigation.calcPosition(position);
				chank_mass[i].road_Mass[2].navigation.calcRotation(rotation);
				chank_mass[i].road_Mass[2].navigation.calcScaling(scale);
				chank_mass[i].road_Mass[2].navigation.calcMatrix_SRT(scale, rotation, position);

				chank_mass[i].road_Mass[3].navigation.position.Z = i * 20 - 15 + chunkPointer * 20;

				chank_mass[i].road_Mass[3].navigation.calcPosition(position);
				chank_mass[i].road_Mass[3].navigation.calcRotation(rotation);
				chank_mass[i].road_Mass[3].navigation.calcScaling(scale);
				chank_mass[i].road_Mass[3].navigation.calcMatrix_SRT(scale, rotation, position);
			}


			//spawnCar(Player_Car.navigation.position.Z, 0);
			
		}
		



		//q3Transform trans; // for take phisic box data
		//trans = Player_Car.fbody->GetTransform();
		//XMMATRIX rotation;
		//Player_Car.navigation.calcRotation(rotation);
		//rotation._11 = trans.rotation.ex.x;
		//rotation._12 = trans.rotation.ex.y;
		//rotation._13 = trans.rotation.ex.z;
		//rotation._21 = trans.rotation.ey.x;
		//rotation._22 = trans.rotation.ey.y;
		//rotation._23 = trans.rotation.ey.z;
		//rotation._31 = trans.rotation.ez.x;
		//rotation._32 = trans.rotation.ez.y;
		//rotation._33 = trans.rotation.ez.z;

		//XMVECTOR oneDot = XMVectorSet(0.0f, 0.0f, 1.0f, 1.0f);
		//oneDot = XMVector4Transform(oneDot, rotation);


		//lvl.body->ApplyForceAtWorldPoint(q3Vec3(0.0f, 10.0f, 0.0f), q3Vec3(0.0f, 0.0f, -2.0f));
		//lvl.body->ApplyLinearForce(q3Vec3(0.0f, 0.0f, 10.0f));	
		//lvl.body->ApplyTorque(q3Vec3(0.0f, 0.0f, -100.0f));

		// ---------- update physic
		static f32 accumulator = 0;
		accumulator += deltaTime_;
		accumulator = q3Clamp01(accumulator);
		if (accumulator >= (1.0f / 60.0f))
		{
			global_physics_scene.Step();
			accumulator = 0;
		}	

	}

	void PauseMode(float delatTime_, unsigned char* kb_Mass_, unsigned char* m_Mass_) {


		gameState = ENUM_GS_NewGame;

	}

	void PlayMode(float delatTime_, unsigned char* kb_Mass_, unsigned char* m_Mass_) {

		gameState = ENUM_GS_GameOver;

	}


	// -----------------------------------------------------------------------------------------------------------


	void Try_deleteCar(int zPlayer) {
		int CarsCount = carList.size();
		for (int i = 0; i < CarsCount; i++) {
			if (carList[i]->navigation.position.Z < zPlayer - 40 || carList[i]->navigation.position.Z > zPlayer + 250) {
				//carList[i]->~OPTadaC_GO_Car();
				//delete(&carList[i]);
			}
			else {
				carList_save.push_back(carList[i]);
			}
		}
	}

	void spawnCar(int z, int randCoef) {
		srand(time(NULL));
		int enginePWR;
		bool forward;
		int zKoordinate;
		int xKoordinate;
		int currentCar;
		OPTadaE_GO_Car_TypeList carType;
		for (int i = 1; i < 24; i += 3)
		{
			for (int j = z + 45; j < z + 56; j += 10)
			{
				if (rand() % 100 + 1 + randCoef > 25) {

					int currentCar = rand() % 100 + 1;
					if (currentCar < 40)
					{
						carType = ENUM_GO_CarType_Car_1_Ven_1;
					}
					else if (currentCar < 80 && currentCar>40)
					{
						carType = ENUM_GO_CarType_Car_2_Sedan_1;
					}
					else if (currentCar < 90)
					{
						carType = ENUM_GO_CarType_Car_3_Buss_1;
					}
					else
					{
						carType = ENUM_GO_CarType_Car_4_Truck_1;
					}

					enginePWR = rand() % 15 + 10;
					zKoordinate = j;
					xKoordinate = i;
					if (i < 12)
					{
						forward = true;
					}
					else
					{
						forward = false;
					}
					OPTadaC_GO_Car* memoryLeak = new OPTadaC_GO_Car();
					carList.push_back(memoryLeak); // Memory leak XD
					OPTadaC_GO_Car& car = *carList.back();
					OPTadaC_GO_Factory::Create_Car(car, carType, forward);
					car.engine_Power = enginePWR;
					car.fbody->SetTransform(q3Vec3(xKoordinate + 0.5f, 0.1f, zKoordinate));
					//cout << "z" << zKoordinate << endl << "x" << xKoordinate << endl << "dvizhok" << enginePWR << endl << "car " << carType << endl << "polosa " << forward << endl;
				}
			}
		}
	}


	// -----------------------------------------------------------------------------------------------------------


	void BeginContact(const q3ContactConstraint* contact) {
		
	};

	void EndContact(const q3ContactConstraint* contact) {

	};
};