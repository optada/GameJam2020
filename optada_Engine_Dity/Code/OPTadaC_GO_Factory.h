// Created by OPTada // Free for use //
// - - - - - - - - - - - - - - - - - //

#pragma once

#include "OPTadaC_GO_Template.h"


// factory of game objects 
class OPTadaC_GO_Factory
{
public:

	// for create car with hitbox | AI | Engine parameters
	static void Create_Car(OPTadaC_GO_Car& car_, OPTadaE_GO_Car_TypeList carEnum_, bool rotate_Y_180_) {

		// create car
		switch (carEnum_)
		{

			// ----------  ven
		case OPTadaE_GO_Car_TypeList::ENUM_GO_CarType_Car_1_Ven_1: {

			car_.SetupBase(ENUM_GO_Car);
			car_.drawMass.push_back(OPTadaC_Obj_Draw()); // create one draw object for car (body)

			// get first object and setup it
			OPTadaC_Obj_Draw& object = car_.drawMass[0]; 
			object.PS = ENUM_PixelShaderList_PS_Color;
			object.VS = ENUM_VertexShaderList_VS_Color;
			object.world = &car_.navigation;
			
			object.mesh = ENUM_MeshList_CarBody_1;

			object.texture_mass.push_back(ENUM_TextureList_TextureForCar_1_2); // set texture //TODO add random

			// ----- create physic part 

			q3BodyDef bodyDef2; // global
			bodyDef2.position.Set(0.0f, 0.0f, 0.0f);
			bodyDef2.axis.Set(0.0f, 1.0f, 0.0f);
			bodyDef2.angle        = XMConvertToRadians((rotate_Y_180_)?(180.f):(0)); // rotate y
			bodyDef2.bodyType     = eDynamicBody;
			bodyDef2.gravityScale = 3.0f; // massa 
			car_.fbody = global_physics_scene.CreateBody(bodyDef2);

			q3Transform tx2;
			q3BoxDef boxDef2;
			q3Identity(tx2);

			// setup hitbox
			tx2.position.Set(0.0f, 0.5f, 0.0f); 			
			boxDef2.Set(tx2, q3Vec3(1.45f, 1.0f, 3.0f));
			//boxDef2.SetFriction(0.1f);
			car_.fbody->AddBox(boxDef2);

			// ------ setup car engine settings

			car_.engine_max_Speed = 100.0f;  // engine max speed
			car_.engine_Power     = 60.0f;   // engine power
			car_.max_Speed_limit  = 1000.0f; // MAX speed
			car_.Rotate_Power     = 90.0f;   // rotate power

		} break;

			// ----------  sedan
		case OPTadaE_GO_Car_TypeList::ENUM_GO_CarType_Car_2_Sedan_1: {

			car_.SetupBase(ENUM_GO_Car);
			car_.drawMass.push_back(OPTadaC_Obj_Draw()); // create one draw object for car (body)

			// get first object and setup it
			OPTadaC_Obj_Draw& object = car_.drawMass[0];
			object.PS = ENUM_PixelShaderList_PS_Color;
			object.VS = ENUM_VertexShaderList_VS_Color;
			object.world = &car_.navigation;

			object.mesh = ENUM_MeshList_CarBody_2;

			object.texture_mass.push_back(ENUM_TextureList_TextureForCar_2_1); // set texture //TODO add random

			// ----- create physic part 

			q3BodyDef bodyDef2; // global
			bodyDef2.position.Set(0.0f, 0.0f, 0.0f);
			bodyDef2.axis.Set(0.0f, 1.0f, 0.0f);
			bodyDef2.angle        = XMConvertToRadians((rotate_Y_180_) ? (180.f) : (0)); // rotate y
			bodyDef2.bodyType     = eDynamicBody;
			bodyDef2.gravityScale = 3.0f; // massa 
			car_.fbody = global_physics_scene.CreateBody(bodyDef2);

			q3Transform tx2;
			q3BoxDef boxDef2;
			q3Identity(tx2);

			// setup hitbox
			tx2.position.Set(0.0f, 0.5f, 0.0f);
			boxDef2.Set(tx2, q3Vec3(1.45f, 1.0f, 3.0f));
			//boxDef2.SetFriction(0.1f);
			car_.fbody->AddBox(boxDef2);

			// ------ setup car engine settings

			car_.engine_max_Speed = 100.0f;  // engine max speed
			car_.engine_Power     = 70.0f;   // engine power
			car_.max_Speed_limit  = 1000.0f; // MAX speed
			car_.Rotate_Power     = 90.0f;   // rotate power

		} break;

			// ----------  buss
		case OPTadaE_GO_Car_TypeList::ENUM_GO_CarType_Car_3_Buss_1: {

			car_.SetupBase(ENUM_GO_Car);
			car_.drawMass.push_back(OPTadaC_Obj_Draw()); // create one draw object for car (body)

			// get first object and setup it
			OPTadaC_Obj_Draw& object = car_.drawMass[0];
			object.PS = ENUM_PixelShaderList_PS_Color;
			object.VS = ENUM_VertexShaderList_VS_Color;
			object.world = &car_.navigation;

			object.mesh = ENUM_MeshList_CarBody_3;

			object.texture_mass.push_back(ENUM_TextureList_TextureForCar_3_2); // set texture //TODO add random

			// ----- create physic part 

			q3BodyDef bodyDef2; // global
			bodyDef2.position.Set(0.0f, 0.0f, 0.0f);
			bodyDef2.axis.Set(0.0f, 1.0f, 0.0f);
			bodyDef2.angle        = XMConvertToRadians((rotate_Y_180_) ? (180.f) : (0)); // rotate y
			bodyDef2.bodyType     = eDynamicBody;
			bodyDef2.gravityScale = 7.0f; // massa 
			car_.fbody = global_physics_scene.CreateBody(bodyDef2);

			q3Transform tx2;
			q3BoxDef boxDef2;
			q3Identity(tx2);

			// setup hitbox
			tx2.position.Set(0.0f, 0.65f, 0.0f);
			boxDef2.Set(tx2, q3Vec3(1.5f, 1.3f, 5.0f));
			//boxDef2.SetFriction(0.1f);
			car_.fbody->AddBox(boxDef2);

			// ------ setup car engine settings

			car_.engine_max_Speed = 100.0f;  // engine max speed
			car_.engine_Power = 70.0f;   // engine power
			car_.max_Speed_limit = 1000.0f; // MAX speed
			car_.Rotate_Power = 90.0f;   // rotate power

		} break;

			// ----------  track
		case OPTadaE_GO_Car_TypeList::ENUM_GO_CarType_Car_4_Truck_1: {

			car_.SetupBase(ENUM_GO_Car);
			car_.drawMass.push_back(OPTadaC_Obj_Draw()); // create one draw object for car (body)

			// get first object and setup it
			OPTadaC_Obj_Draw& object = car_.drawMass[0];
			object.PS = ENUM_PixelShaderList_PS_Color;
			object.VS = ENUM_VertexShaderList_VS_Color;
			object.world = &car_.navigation;

			object.mesh = ENUM_MeshList_CarBody_4;

			object.texture_mass.push_back(ENUM_TextureList_TextureForCar_4_1); // set texture //TODO add random

			// ----- create physic part 

			q3BodyDef bodyDef2; // global
			bodyDef2.position.Set(0.0f, 0.0f, 0.0f);
			bodyDef2.axis.Set(0.0f, 1.0f, 0.0f);
			bodyDef2.angle        = XMConvertToRadians((rotate_Y_180_) ? (180.f) : (0)); // rotate y
			bodyDef2.bodyType     = eDynamicBody;
			bodyDef2.gravityScale = 1.0f; // massa 
			car_.fbody = global_physics_scene.CreateBody(bodyDef2);

			q3Transform tx2;
			q3BoxDef boxDef2;
			q3Identity(tx2);

			// setup hitbox
			tx2.position.Set(0.0f, 1.0f, 0.0f);
			boxDef2.Set(tx2, q3Vec3(2.0f, 1.0f, 3.6f));
			//boxDef2.SetFriction(0.1f);
			car_.fbody->AddBox(boxDef2);

			// ------ setup car engine settings

			car_.engine_max_Speed = 80.0f;  // engine max speed
			car_.engine_Power     = 90.0f;   // engine power
			car_.max_Speed_limit  = 1000.0f; // MAX speed
			car_.Rotate_Power     = 90.0f;   // rotate power

		} break;

			// ----------  PLayer car
		case OPTadaE_GO_Car_TypeList::ENUM_GO_CarType_PlayerCar: {

			car_.SetupBase(ENUM_GO_Car);
			car_.drawMass.push_back(OPTadaC_Obj_Draw()); // create one draw object for car (body)

			// get first object and setup it
			OPTadaC_Obj_Draw& object = car_.drawMass[0];
			object.PS = ENUM_PixelShaderList_PS_Color;
			object.VS = ENUM_VertexShaderList_VS_Color;
			object.world = &car_.navigation;

			object.mesh = ENUM_MeshList_Player_Car_Mesh;

			object.texture_mass.push_back(ENUM_TextureList_Test_PlayerCar); // set texture //TODO add random

			// ----- create physic part 

			q3BodyDef bodyDef2; // global
			bodyDef2.position.Set(0.0f, 0.0f, 0.0f);
			bodyDef2.axis.Set(0.0f, 1.0f, 0.0f);
			bodyDef2.angle = XMConvertToRadians((rotate_Y_180_) ? (180.f) : (0)); // rotate y
			bodyDef2.bodyType = eDynamicBody;
			bodyDef2.gravityScale = 6.0f; // massa 
			car_.fbody = global_physics_scene.CreateBody(bodyDef2);

			q3Transform tx2;
			q3BoxDef boxDef2;
			q3Identity(tx2);

			// setup hitbox
			tx2.position.Set(0.0f, 1.0f, 0.0f);
			boxDef2.Set(tx2, q3Vec3(1.5f, 1.0f, 1.75f));
			//boxDef2.SetFriction(0.1f);
			car_.fbody->AddBox(boxDef2);

			// ------ setup car engine settings

			car_.engine_max_Speed = 80.0f;  // engine max speed
			car_.engine_Power = 90.0f;   // engine power
			car_.max_Speed_limit = 1000.0f; // MAX speed
			car_.Rotate_Power = 90.0f;   // rotate power

		} break;


		default: break;
		}

	}

	// for creating monolit objects ofr drawing (like trees of stones), with no hit box effect
	static void Create_Monolit(OPTadaC_GO_Monolit& obj_, OPTadaE_GO_Monolit_TypeList monolitEnum_) {

		// create car
		switch (monolitEnum_) {
		case ENUM_GO_Monolit_Road_1:
		{
			obj_.SetupBase(ENUM_GO_Monolit);
			obj_.drawMass.push_back(OPTadaC_Obj_Draw());
		
			// get first object and setup it
			OPTadaC_Obj_Draw& object = obj_.drawMass[0];
			object.PS = ENUM_PixelShaderList_PS_Color;
			object.VS = ENUM_VertexShaderList_VS_Color;
			object.world = &obj_.navigation;

			object.mesh = ENUM_MeshList_Road_Mesh;

			object.texture_mass.push_back(ENUM_TextureList_Road_1); // set texture //TODO add random

		} break;

		default: break;
		}

	}


};