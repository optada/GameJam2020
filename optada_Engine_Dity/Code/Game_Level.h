// Created by OPTada // Free for use //
// - - - - - - - - - - - - - - - - - //

#pragma once

#include "Render\OPTada_Render.h"
#include "Input\OPTada_Input.h"

// physic
#ifdef _DEBUG
    #pragma comment (lib, "dqu3e.lib")
#else
    #pragma comment (lib, "qu3e.lib")
#endif
#include "Physics\q3.h" // Physics lib by RandyGaul https://github.com/RandyGaul/qu3e
//static q3Scene global_physics_scene(1.0 / 60.0); // physics scene

// sound
#include "Sound\include\soloud.h" // Sound lib by jarikomppa https://github.com/jarikomppa/soloud
#include "Sound\include\soloud_wav.h"
#include "Sound\include\soloud_misc.h"

SoLoud::Soloud gSoloud; // SoLoud engine
SoLoud::Wav gWave;      // One wave file

#include "TheGame.h"


class GameLevel
{
public:

    OPTada_TheGame Game;

    OPTadaC_Obj_Camera PrimaryCamera;

    std::vector<OPTadaC_Obj_Draw*> draw_opaque; // draw list
    std::vector<OPTadaC_Obj_Draw*> draw_clip;   // draw clip list
    std::vector<OPTadaC_Obj_Draw*> draw_blend;  // draw blend list

    std::vector<OPTadaC_Obj_Light*> draw_light; // draw light objects

    q3Body* fbody; // floor
    q3Body* body; // box

public:

    GameLevel() {};
	
	// use it for initialize level and level's resourses
	bool Init()
	{
        assert(global_Render.g_Device_d3d11);


        // -------------------------- Load the compiled vertex shaders -----------------------------

        LPCWSTR compiledVertexShaderObject;
        OPTadaE_VertexShaderList_ForResourceManager verEnum;

        // Create the input layout for the vertex shader.
        D3D11_INPUT_ELEMENT_DESC vertexLayoutDesc[] =
        {
            { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offsetof(Vertex_F3Coord_F3Normal_F2TextCoord, position),     D3D11_INPUT_PER_VERTEX_DATA, 0 },
            { "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offsetof(Vertex_F3Coord_F3Normal_F2TextCoord, normal),       D3D11_INPUT_PER_VERTEX_DATA, 0 },
            { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, offsetof(Vertex_F3Coord_F3Normal_F2TextCoord, textureCoord), D3D11_INPUT_PER_VERTEX_DATA, 0 },
        };
        
        verEnum = ENUM_VertexShaderList_VS_Color;
        compiledVertexShaderObject = L"VS_Color.cso";
        global_Render.resourceManager.Create_VertexShader_FromBinaryFile(verEnum, compiledVertexShaderObject, global_Render.g_Device_d3d11, vertexLayoutDesc, _countof(vertexLayoutDesc));   

        verEnum = ENUM_VertexShaderList_VS_Shadow;
        compiledVertexShaderObject = L"VS_Shadow.cso";
        global_Render.resourceManager.Create_VertexShader_FromBinaryFile(verEnum, compiledVertexShaderObject, global_Render.g_Device_d3d11, vertexLayoutDesc, _countof(vertexLayoutDesc));


        // ---------------------------- Load the compiled pixel shaders ---------------------------

        LPCWSTR compiledPixelShaderObject;
        OPTadaE_PixelShaderList_ForResourceManager pixEnum;

        pixEnum = ENUM_PixelShaderList_PS_Color;
        compiledPixelShaderObject = L"PS_Color.cso";
        global_Render.resourceManager.Create_PixelShader_FromBinaryFile(pixEnum, compiledPixelShaderObject, global_Render.g_Device_d3d11, { ENUM_SamplerStateList_Linear_16 } );

        pixEnum = ENUM_PixelShaderList_PS_Shadow;
        compiledPixelShaderObject = L"PS_Shadow.cso";
        global_Render.resourceManager.Create_PixelShader_FromBinaryFile(pixEnum, compiledPixelShaderObject, global_Render.g_Device_d3d11, { ENUM_SamplerStateList_Linear_Depth_Clamp, ENUM_SamplerStateList_Linear_Depth_Wrap });


        // -------------------------------- Load Meshes -------------------------------------------

        OPTadaE_MeshList_ForResourceManager meshEnum;

        meshEnum = ENUM_MeshList_Road_Mesh;
        if (!global_Render.resourceManager.Create_Mesh_FromFileToMem(meshEnum, "Mesh/Road.obj", global_Render.g_Device_d3d11, sizeof(Vertex_F3Coord_F3Normal_F2TextCoord), 0, DXGI_FORMAT_R32_UINT)) {
            MessageBox(NULL, L"Create mesh failed", L"Game level", NULL);
        }
        global_Render.resourceManager.Load_ToGPU_Mesh(meshEnum, global_Render.g_Device_d3d11);

        meshEnum = ENUM_MeshList_CarBody_1;
        if (!global_Render.resourceManager.Create_Mesh_FromFileToMem(meshEnum, "Mesh/Car_1.obj", global_Render.g_Device_d3d11, sizeof(Vertex_F3Coord_F3Normal_F2TextCoord), 0, DXGI_FORMAT_R32_UINT)) {
            MessageBox(NULL, L"Create mesh failed", L"Game level", NULL);
        }
        global_Render.resourceManager.Load_ToGPU_Mesh(meshEnum, global_Render.g_Device_d3d11);

        meshEnum = ENUM_MeshList_CarBody_2;
        if (!global_Render.resourceManager.Create_Mesh_FromFileToMem(meshEnum, "Mesh/Car_2.obj", global_Render.g_Device_d3d11, sizeof(Vertex_F3Coord_F3Normal_F2TextCoord), 0, DXGI_FORMAT_R32_UINT)) {
            MessageBox(NULL, L"Create mesh failed", L"Game level", NULL);
        }
        global_Render.resourceManager.Load_ToGPU_Mesh(meshEnum, global_Render.g_Device_d3d11);

        meshEnum = ENUM_MeshList_CarBody_3;
        if (!global_Render.resourceManager.Create_Mesh_FromFileToMem(meshEnum, "Mesh/Car_3.obj", global_Render.g_Device_d3d11, sizeof(Vertex_F3Coord_F3Normal_F2TextCoord), 0, DXGI_FORMAT_R32_UINT)) {
            MessageBox(NULL, L"Create mesh failed", L"Game level", NULL);
        }
        global_Render.resourceManager.Load_ToGPU_Mesh(meshEnum, global_Render.g_Device_d3d11);

        meshEnum = ENUM_MeshList_CarBody_4;
        if (!global_Render.resourceManager.Create_Mesh_FromFileToMem(meshEnum, "Mesh/Car_4.obj", global_Render.g_Device_d3d11, sizeof(Vertex_F3Coord_F3Normal_F2TextCoord), 0, DXGI_FORMAT_R32_UINT)) {
            MessageBox(NULL, L"Create mesh failed", L"Game level", NULL);
        }
        global_Render.resourceManager.Load_ToGPU_Mesh(meshEnum, global_Render.g_Device_d3d11);

        meshEnum = ENUM_MeshList_Player_Car_Mesh;
        if (!global_Render.resourceManager.Create_Mesh_FromFileToMem(meshEnum, "Mesh/Car_Player.obj", global_Render.g_Device_d3d11, sizeof(Vertex_F3Coord_F3Normal_F2TextCoord), 0, DXGI_FORMAT_R32_UINT)) {
            MessageBox(NULL, L"Create mesh failed", L"Game level", NULL);
        }
        global_Render.resourceManager.Load_ToGPU_Mesh(meshEnum, global_Render.g_Device_d3d11);

        meshEnum = ENUM_MeshList_Plane;
        if (!global_Render.resourceManager.Create_Mesh_FromFileToMem(meshEnum, "Mesh/Plane_2x2.obj", global_Render.g_Device_d3d11, sizeof(Vertex_F3Coord_F3Normal_F2TextCoord), 0, DXGI_FORMAT_R32_UINT)) {
            MessageBox(NULL, L"Create mesh failed", L"Game level", NULL);
        }
        global_Render.resourceManager.Load_ToGPU_Mesh(meshEnum, global_Render.g_Device_d3d11);


        // -------------------------------- Load Textures -------------------------------------------

        OPTadaE_TextureList_ForResourceManager textureEnum;

        textureEnum = ENUM_TextureList_Road_1;
        if (!global_Render.resourceManager.Create_Texture_LoadFromFile(textureEnum, L"Textures/Road_Tex.png", global_Render.g_Device_d3d11)) {
            MessageBox(NULL, L"Create texture failed", L"Game level", NULL);
        }

        textureEnum = ENUM_TextureList_TextureForCar_1_1;
        if (!global_Render.resourceManager.Create_Texture_LoadFromFile(textureEnum, L"Textures/Car_1_tex1.png", global_Render.g_Device_d3d11)) {
            MessageBox(NULL, L"Create texture failed", L"Game level", NULL);
        }

        textureEnum = ENUM_TextureList_TextureForCar_1_2;
        if (!global_Render.resourceManager.Create_Texture_LoadFromFile(textureEnum, L"Textures/Car_1_tex2.png", global_Render.g_Device_d3d11)) {
            MessageBox(NULL, L"Create texture failed", L"Game level", NULL);
        }

        textureEnum = ENUM_TextureList_TextureForCar_1_3;
        if (!global_Render.resourceManager.Create_Texture_LoadFromFile(textureEnum, L"Textures/Car_1_tex3.png", global_Render.g_Device_d3d11)) {
            MessageBox(NULL, L"Create texture failed", L"Game level", NULL);
        }

        textureEnum = ENUM_TextureList_TextureForCar_2_1;
        if (!global_Render.resourceManager.Create_Texture_LoadFromFile(textureEnum, L"Textures/Car_2_tex1.png", global_Render.g_Device_d3d11)) {
            MessageBox(NULL, L"Create texture failed", L"Game level", NULL);
        }

        textureEnum = ENUM_TextureList_TextureForCar_2_2;
        if (!global_Render.resourceManager.Create_Texture_LoadFromFile(textureEnum, L"Textures/Car_2_tex2.png", global_Render.g_Device_d3d11)) {
            MessageBox(NULL, L"Create texture failed", L"Game level", NULL);
        }

        textureEnum = ENUM_TextureList_TextureForCar_2_3;
        if (!global_Render.resourceManager.Create_Texture_LoadFromFile(textureEnum, L"Textures/Car_2_tex3.png", global_Render.g_Device_d3d11)) {
            MessageBox(NULL, L"Create texture failed", L"Game level", NULL);
        }

        textureEnum = ENUM_TextureList_TextureForCar_3_1;
        if (!global_Render.resourceManager.Create_Texture_LoadFromFile(textureEnum, L"Textures/Car_3_tex1.png", global_Render.g_Device_d3d11)) {
            MessageBox(NULL, L"Create texture failed", L"Game level", NULL);
        }

        textureEnum = ENUM_TextureList_TextureForCar_3_2;
        if (!global_Render.resourceManager.Create_Texture_LoadFromFile(textureEnum, L"Textures/Car_3_tex2.png", global_Render.g_Device_d3d11)) {
            MessageBox(NULL, L"Create texture failed", L"Game level", NULL);
        }

        textureEnum = ENUM_TextureList_TextureForCar_3_3;
        if (!global_Render.resourceManager.Create_Texture_LoadFromFile(textureEnum, L"Textures/Car_3_tex3.png", global_Render.g_Device_d3d11)) {
            MessageBox(NULL, L"Create texture failed", L"Game level", NULL);
        }

        textureEnum = ENUM_TextureList_TextureForCar_4_1;
        if (!global_Render.resourceManager.Create_Texture_LoadFromFile(textureEnum, L"Textures/Car_4_tex1.png", global_Render.g_Device_d3d11)) {
            MessageBox(NULL, L"Create texture failed", L"Game level", NULL);
        }

        textureEnum = ENUM_TextureList_TextureForCar_4_2;
        if (!global_Render.resourceManager.Create_Texture_LoadFromFile(textureEnum, L"Textures/Car_4_tex2.png", global_Render.g_Device_d3d11)) {
            MessageBox(NULL, L"Create texture failed", L"Game level", NULL);
        }

        textureEnum = ENUM_TextureList_TextureForCar_4_3;
        if (!global_Render.resourceManager.Create_Texture_LoadFromFile(textureEnum, L"Textures/Car_4_tex3.png", global_Render.g_Device_d3d11)) {
            MessageBox(NULL, L"Create texture failed", L"Game level", NULL);
        }
       
        textureEnum = ENUM_TextureList_Test_PlayerCar;
        if (!global_Render.resourceManager.Create_Texture_LoadFromFile(textureEnum, L"Textures/Car_Player_Tex.png", global_Render.g_Device_d3d11)) {
            MessageBox(NULL, L"Create texture failed", L"Game level", NULL);
        }

        textureEnum = ENUM_TextureList_Text_0;
        if (!global_Render.resourceManager.Create_Texture_LoadFromFile(textureEnum, L"Textures/0.png", global_Render.g_Device_d3d11)) {
            MessageBox(NULL, L"Create texture failed", L"Game level", NULL);
        }

        textureEnum = ENUM_TextureList_Text_1;
        if (!global_Render.resourceManager.Create_Texture_LoadFromFile(textureEnum, L"Textures/1.png", global_Render.g_Device_d3d11)) {
            MessageBox(NULL, L"Create texture failed", L"Game level", NULL);
        }

        // -------------------------------- setup main camera ------------------------------------

        OPTadaS_Window_Size workspaceSize;
        global_Window.Get_WorkplaceSize(workspaceSize);
        PrimaryCamera.Setup_ProjectionMatrix(workspaceSize.width, workspaceSize.height, 45.0f);

        // update camera
        PrimaryCamera.position.X = 12.5f;
        PrimaryCamera.position.Y = 5;
        PrimaryCamera.position.Z = -25;

        global_Render.resourceManager.UpdateSubresource(ENUM_ConstantBufferList_Application, &cb_ObjectData, global_Render.g_DeviceContext_d3d11);


        // -------------------------------- setup physic -------------------------------------------

        // Create the floor
        q3BodyDef bodyDef; 
        fbody = global_physics_scene.CreateBody(bodyDef);

        q3BoxDef boxDef;
        boxDef.SetRestitution(0);
        q3Transform tx;
        q3Identity(tx);
        tx.position.Set(0, 0, 0);
        boxDef.Set(tx, q3Vec3(100.0f, 0.0f, 200000.0f));
        boxDef.SetFriction(1.0f);
        fbody->AddBox(boxDef);
        tx.position.Set(0.0f, 0, 0);
        boxDef.Set(tx, q3Vec3(0.0f, 1000.0f, 2000.0f));
        boxDef.SetFriction(1.0f);
        fbody->AddBox(boxDef);
        tx.position.Set(25.0, 0, 0);
        boxDef.Set(tx, q3Vec3(0.0f, 1000.0f, 2000.0f));
        boxDef.SetFriction(1.0f);
        fbody->AddBox(boxDef);


        // -------------------------------- setup sound -------------------------------------------

        gSoloud.init(); // Initialize SoLoud
        gWave.load("Sound/ch6_32bit.wav"); // Load a wave
        SoLoud::handle voiseH = gSoloud.play3d(gWave, 20, 0, 0);
        gSoloud.set3dListenerPosition(0, 0, 0);
        gSoloud.set3dListenerUp(0, 1, 0);
        gSoloud.set3dListenerAt(0, 0, 1); 
        //gSoloud.set3dSourcePosition(voiseH, 10, 0, 0);
        gSoloud.update3dAudio();

        
        Game.SetupAll(&PrimaryCamera, draw_opaque); // setup game

        return true;

	}

	// use it for free all level's resourses
	void Free()
	{

	}


	// Tick function
	// [in] float deltaTime_ // delta time
    // [in] unsigned char* kb_Mass_
    // [in] unsigned char* m_Mass_
    // retur true - done | false - error
	bool Tick(float deltaTime_, unsigned char* kb_Mass_, unsigned char* m_Mass_)
	{

        // update camera
        if (PrimaryCamera.position.Z > 6) {
            PrimaryCamera.position.Z = -6;
        }

        //PrimaryCamera.position.X = 5;
        PrimaryCamera.position.X += 0.0 * deltaTime_;
        //PrimaryCamera.position.Z = 0;

        //PrimaryCamera.Update_ViewMatrix();


        // update light

        static OPTadaC_Obj_Light light1;
        draw_light.clear();
        draw_light.push_back(&light1);


        light1.type = ENUM_Obj_Light_Global;
        light1.Light.dir     = XMFLOAT3(0.0f, 0.0f, -1.0f); // invert coordinate direction
        light1.Light.ambient = XMFLOAT4(0.15f, 0.15f, 0.15f, 1.0f);
        light1.Light.diffuse = XMFLOAT4(0.4f, 0.4f, 0.4f, 1.0f);


        global_Render.resourceManager.UpdateSubresource(ENUM_ConstantBufferList_Frame, &cb_FrameData, global_Render.g_DeviceContext_d3d11);
        
        Game.Tick(deltaTime_, kb_Mass_, m_Mass_); // game tick


        return true;
	}


};
