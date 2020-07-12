// Created by OPTada // Free for use //
// - - - - - - - - - - - - - - - - - //

#pragma once

#include "Render\OPTada_Render.h"
#include "Physics\q3.h" // Physics lib by RandyGaul https://github.com/RandyGaul/qu3e
static q3Scene global_physics_scene(1.0 / 60.0); // physics scene


// game obhect type list
enum OPTadaE_GO_Type
{
	ENUM_GO_NONE               = 0, // Game object none
	ENUM_GO_Car                = 1, // game object Car
	ENUM_GO_Monolit_WithHitbox = 2, // game object with monolit hitbox 
	ENUM_GO_Monolit            = 3, // game object woth NO hit box (just draw)++
	ENUM_GO_Dinamic            = 4, // game object dinamic with hitbox
	ENUM_GO_Trigger            = 5, // just hitbox
};


// Game object template 
class OPTadaC_GO_Template
{
public:

	OPTadaE_GO_Type objectType = ENUM_GO_NONE; // type of object
	OPTadaS_WorldNavigationData navigation; // coordynates of object and other data

	virtual void Draw(std::vector<OPTadaC_Obj_Draw*>& draw_opaque_) = 0;

	virtual void SetupBase(OPTadaE_GO_Type enumType_) = 0;
};


// -----------------------------------------------------------------------------------------------------------------------

enum OPTadaE_GO_Car_TypeList
{
	ENUM_GO_CarType_Car_1_Ven_1,
	ENUM_GO_CarType_Car_2_Sedan_1,
	ENUM_GO_CarType_Car_3_Buss_1,
	ENUM_GO_CarType_Car_4_Truck_1,
	ENUM_GO_CarType_PlayerCar,
};

// Game object car
class OPTadaC_GO_Car : public OPTadaC_GO_Template
{
public:

	q3Body* fbody = nullptr; // HitBox + phisic
	std::vector<OPTadaC_Obj_Draw> drawMass; // mass with draw objects

	// car engine parameters
	float max_Speed_limit  = 0;
	float engine_max_Speed = 0;
	float engine_Power = 0;
	float Rotate_Power = 0;

	float move_Right = 0;
	float move_Back = 0;

	void SetupBase(OPTadaE_GO_Type enumType_) {
		objectType = enumType_;
		drawMass.clear();
	}

	~OPTadaC_GO_Car() {
		global_physics_scene.RemoveBody(fbody);
		drawMass.clear();
	}

	void Update_ModelPosition() {
		// setup transform parameters

		q3Transform trans; // for take phisic box data
		trans = fbody->GetTransform();

		navigation.position.X = trans.position.x;
		navigation.position.Y = trans.position.y;
		navigation.position.Z = trans.position.z;

		XMMATRIX position;
		XMMATRIX rotation;
		XMMATRIX scale;
		navigation.calcPosition(position);
		navigation.calcRotation(rotation);
		navigation.calcScaling(scale);

		rotation._11 = trans.rotation.ex.x;
		rotation._12 = trans.rotation.ex.y;
		rotation._13 = trans.rotation.ex.z;

		rotation._21 = trans.rotation.ey.x;
		rotation._22 = trans.rotation.ey.y;
		rotation._23 = trans.rotation.ey.z;

		rotation._31 = trans.rotation.ez.x;
		rotation._32 = trans.rotation.ez.y;
		rotation._33 = trans.rotation.ez.z;

		navigation.calcMatrix_SRT(scale, rotation, position);
	}

	void Draw(std::vector<OPTadaC_Obj_Draw*>& draw_opaque_) {
		for (int i = 0; i < drawMass.size(); i++) {
			draw_opaque_.push_back(&drawMass[i]);
		}

		move_Right = 0;
		move_Back = 0;
	}

	// controll

	void MoveForward() {	

		if (engine_Power == 0) {
			return;
		}

		//fbody->SetLinearDamping(0);

		q3Transform trans; // for take phisic box data
		trans = fbody->GetTransform();	
		
		XMMATRIX rotation;
		navigation.calcRotation(rotation);
		rotation._11 = trans.rotation.ex.x;
		rotation._12 = trans.rotation.ex.y;
		rotation._13 = trans.rotation.ex.z;
		rotation._21 = trans.rotation.ey.x;
		rotation._22 = trans.rotation.ey.y;
		rotation._23 = trans.rotation.ey.z;
		rotation._31 = trans.rotation.ez.x;
		rotation._32 = trans.rotation.ez.y;
		rotation._33 = trans.rotation.ez.z;

		XMVECTOR oneDot = XMVectorSet(move_Right, 0.0f, (move_Right >= 0)?(1.0f - move_Right):(1.0f + move_Right) , 1.0f);
		oneDot = XMVector4Transform(oneDot, rotation);

		
		if (move_Back == 0) {
			// ------------------------------------------- X ----------------- Y ------------------ Z
			fbody->ApplyLinearForce(q3Vec3(oneDot.m128_f32[0] * engine_Power, 0.2f, oneDot.m128_f32[2] * engine_Power));
		}
		else {
			// ------------------------------------------- X ------------------------------- Y ------------------ Z
			fbody->ApplyLinearForce(q3Vec3(oneDot.m128_f32[0] * (engine_Power * move_Back), 0.2f, oneDot.m128_f32[2] * (engine_Power * move_Back)));
		}

		q3Vec3 vel;
		//vel = fbody->GetAngularVelocity();
		//fbody->SetAngularVelocity(-vel);

		//fbody->SetLinearVelocity({ 0.0f, 0.0f, 0.0f });

		move_Right = 0;
		move_Back = 0;
	}

	void MoveBack(float Back_) {

		move_Back = Back_;
		MoveForward();
	}

	void Turn(float Right_) {
		move_Right += Right_;
	}
};


// -----------------------------------------------------------------------------------------------------------------------

enum OPTadaE_GO_MonolitWithHitBox_TypeList
{

};

// game object monolit_WithHitBox (road, barier)
class OPTadaC_GO_Monolit_WithHitBox : public OPTadaC_GO_Template
{
public:

	q3Body* fbody = nullptr; // HitBox + phisic
	std::vector<OPTadaC_Obj_Draw> drawMass; // mass with draw objects
};


// -----------------------------------------------------------------------------------------------------------------------

enum OPTadaE_GO_Monolit_TypeList
{
	ENUM_GO_Monolit_Road_1,

};

// game object monilit (tree, some stones, other objects for drawing, without phisics)
class OPTadaC_GO_Monolit : public OPTadaC_GO_Template
{
public:

	std::vector<OPTadaC_Obj_Draw> drawMass; // mass with draw objects

	void Draw(std::vector<OPTadaC_Obj_Draw*>& draw_opaque_) {
		for (int i = 0; i < drawMass.size(); i++) {
			draw_opaque_.push_back(&drawMass[i]);
		}
	}

	void SetupBase(OPTadaE_GO_Type enumType_) {
		objectType = enumType_;
		drawMass.clear();
	}

};


// -----------------------------------------------------------------------------------------------------------------------

enum OPTadaE_GO_Dinamic_TypeList
{
	//ENUM_GO_Dinamic_Conus_1, // road conus
};

// game object dinamic with hitbox(conus, barier with phisic, attention boars, other)
class OPTadaC_GO_Dinamic : public OPTadaC_GO_Template
{
public:

	q3Body* fbody = nullptr; // HitBox + phisic
	std::vector<OPTadaC_Obj_Draw> drawMass; // mass with draw objects

};


// -----------------------------------------------------------------------------------------------------------------------

enum OPTadaE_GO_Trigger_TypeList
{
	//ENUM_GO_Trigger_TriigerBox, // box for triggering somesing
};

// game object hitbox trigger (for trigger actions)
class OPTadaC_GO_Trigger : public OPTadaC_GO_Template
{
public:

	q3Body* fbody = nullptr; // HitBox + phisic

};
