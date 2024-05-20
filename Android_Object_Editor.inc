 //
//  Android_Object_Editor by BigSmoke_bb
// Respetar creditos.
// - Discord: BigSmoke_bb
// - First version
//
// Version 1.0
//
//
//Macros/Defines/Funciones
#define AO_EDITOR_VERSION                                   (10000) //a.b.c g+10000*a+100*b+c
#define AO_EDITOR_LIBRARY_NAME                              "OA EDITOR"
#define AO_EDITOR_AUTHOR_NAME                               "BigSmoke_bb"
#define AO_EDITOR_AUTHOR_DISCORD                            "BigSmoke_bb#1888"
#if defined _samp_included
    #if (!defined GetPlayerPoolSize || !defined GetSVarInt)
        #error [OA EDITOR] This include requires SA:MP version 0.3.7
    #endif
    #define AO_EDITOR_PLATFORM_NAME                        "SA:MP"
    #if defined GetPlayerCustomSkin
        #define AO_EDITOR_PLATFORM_VERSION                 "0.3 DL"
    #else
        #define AO_EDITOR_PLATFORM_VERSION                 "0.3.7"
    #endif
    #define AO_EDITOR_PLATFORM_CODE                        AO_EDITOR_PLATFORM_SAMP
#endif
#if !defined AO_EDITOR_PLATFORM_CODE
    #define AO_EDITOR_PLATFORM_CODE                        AO_EDITOR_PLATFORM_PAWN
    #define AO_EDITOR_PLATFORM_NAME                        "Pawn"
    #define AO_EDITOR_PLATFORM_VERSION                     "3.0"
#endif
#define OA_EDITOR::                                        OA_
#define OA_GetVersion(%0)                                  ((%0) / 10000),(((%0) % 10000) / 100),(((%0) % 10000) % 100)

/********************************
 * Definitions                  *
 ********************************/
forward OnEditorAttachVehicleAndroid(playerid, vehicleid, editor_id, response,modelid, Float:oa_POS_X, Float:oa_POS_Y, Float:oa_POS_Z, Float:oa_ROT_X, Float:oa_ROT_Y, Float:oa_ROT_Z);
#define GetDynamicObjectModel(%0) Streamer_GetIntData(STREAMER_TYPE_OBJECT, %0, E_STREAMER_MODEL_ID) // By Crayder (Pottus)
#define ANDROID_EDITOR_RESPONSE_SAVE 0
#define ANDROID_EDITOR_RESPONSE_CANCEL 1
#define ALSS_OPC    0x1
forward EditDynamicAndroidObject(playerid, editorid, objectid, editormode);
#define AO_INVALID_ID -1

#define MAX_OBJECT_PER_VEH_AO 100
/********************************
 * Enums                        *
 ********************************/

new ALSS_CallBacks;

enum
{
    EDITOR_MODE_OBJECT,
    EDITOR_MODE_VEHICLE_OBJECT
}
enum @ao_enum_GLOBAL_TEXTDRAW
{
    Text:ao_TXT_EDITOR_ANDROID[ 19 ]
}
new ao_GLOBAL_TEXTDRAW[ @ao_enum_GLOBAL_TEXTDRAW ];

/********************************
 * Variables                        *
 ********************************/
enum @ao_array_ANDROID_OBJECT
{
    ao_vehicleid,
    bool:ao_valid_object,
    ao_OBJECT_ID

}
new AO_EDITOR[ MAX_VEHICLES ][ @ao_array_ANDROID_OBJECT ][ MAX_OBJECT_PER_VEH_AO ];

enum @ao_enum_PLAYER_TEXTDRAW
{
    PlayerText:ao_TXT_EDITOR_ANDROID[ 8 ],
    bool:ao_EDITTING,
    Float:ao_POSX,
    Float:ao_POSY,
    Float:ao_POSZ,
    Float:ao_POSRX,
    Float:ao_POSRY,
    Float:ao_POSRZ,
    Float:ao_EDITOR_POS[ 3 ],
    Float:ao_EDITOR_ROT[ 3 ],
    ao_EDITOR_ID,
    ao_OBJECT_ID,
    ao_TEMP_OBBJECT_ID,
    oa_EDITOR_MODE,
    Float:oa_SPEED,
    oa_MOVE_MODE,
    oa_FOR_VEHICLE,
    ao_MODEL_ID
}
new ao_PLAYER_SAVE_EDITOR[ MAX_PLAYERS ][ @ao_enum_PLAYER_TEXTDRAW ];
// ===============================================================================================

public OnGameModeInit()
{
    oa_CreateMenus_Android();
    oa_INFO_script();
    return (funcidx("ALSS_OnGameModeInit") != -1 ? CallLocalFunction("ALSS_OnGameModeInit", "") : 1);
}

#if defined _ALS_OnGameModeInit
    #undef OnGameModeInit
#else
    #define _ALS_OnGameModeInit
#endif
#define OnGameModeInit ALSS_OnGameModeInit

forward ALSS_OnGameModeInit();

// ===============================================================================================
// ===============================================================================================
public OnFilterScriptInit()
{
    oa_CreateMenus_Android();
    oa_INFO_script();
    return (funcidx("ALSS_OnFilterScriptInit") != -1 ? CallLocalFunction("ALSS_OnFilterScriptInit", "") : 1);
}

#if defined _ALS_OnFilterScriptInit
    #undef OnFilterScriptInit
#else
    #define _ALS_OnFilterScriptInit
#endif
#define OnFilterScriptInit ALSS_OnFilterScriptInit

forward ALSS_OnFilterScriptInit();
// ===============================================================================================
// ===============================================================================================
// ===============================================================================================
public OnPlayerConnect(playerid)
{
    ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_EDITTING ] = false;
    ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_EDITOR_ID ] = AO_INVALID_ID;
    ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_OBJECT_ID ] = INVALID_OBJECT_ID;
    ao_PLAYER_SAVE_EDITOR[ playerid ][ oa_FOR_VEHICLE ] = INVALID_VEHICLE_ID;

    ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_POSX ] = 0.0;
    ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_POSY ] = 0.0;
    ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_POSZ ] = 0.0;
    ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_POSRX ] = 0.0;
    ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_POSRY ] = 0.0;
    ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_POSRZ ] = 0.0;
    ao_PLAYER_SAVE_EDITOR[ playerid ][ oa_SPEED ] = 0.1;
    ao_PLAYER_SAVE_EDITOR[ playerid ][ oa_MOVE_MODE ] = 0;
    oa_CreateMenuEditor(playerid);
    return CallLocalFunction("Big_OnPlayerc", "i", playerid);
}

#if defined _ALS_OnPlayerConnect
    #undef OnPlayerConnect
#else
    #define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect Big_OnPlayerc

forward Big_OnPlayerc(playerid);
// ===============================================================================================
// ===============================================================================================

public OnPlayerDisconnect(playerid, reason)
{
    ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_EDITTING ] = false;
    ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_EDITOR_ID ] = AO_INVALID_ID;
    ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_OBJECT_ID ] = INVALID_OBJECT_ID;

    ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_POSX ] = 0.0;
    ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_POSY ] = 0.0;
    ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_POSZ ] = 0.0;
    ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_POSRX ] = 0.0;
    ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_POSRY ] = 0.0;
    ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_POSRZ ] = 0.0;
    oa_DestroyMenuEditor(playerid);
    return (ALSS_CallBacks & ALSS_OPC ? CallLocalFunction("ALSS_OnPlayerConnect", "i", playerid) : 1);
}
#if defined _ALS_OnPlayerDisconnect
    #undef OnPlayerDisconnect
#else
    #define _ALS_OnPlayerDisconnect
#endif
#define OnPlayerDisconnect ALSS_OnPlayerConnect
forward ALSS_OnPlayerConnect(playerid);
// ===============================================================================================
// ===============================================================================================
//Stocks & Functions
public EditDynamicAndroidObject(playerid, editorid, objectid, editormode)
{
    //SendClientMessage(playerid, -1,sprintf("editando id: %d",objectid));

    if(IsValidDynamicObject(objectid))
    {
        ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_EDITOR_ID ] = editorid;
        ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_OBJECT_ID ] = objectid;
        ao_PLAYER_SAVE_EDITOR[ playerid ][ oa_EDITOR_MODE ] = editormode;
        ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_EDITTING ] = true;


        //
        switch(editormode)
        {
            case EDITOR_MODE_OBJECT:
            {
                new  Float:ao_X, Float:ao_Y, Float:ao_Z, Float: ao_RX, Float:ao_RY, Float:ao_RZ;
                GetDynamicObjectPos(objectid, ao_X,ao_Y,ao_Z);
                GetDynamicObjectRot(objectid, ao_RX,ao_RY,ao_RZ);
             
                if(!IsPlayerInRangeOfPoint(playerid, 8, ao_X,ao_Y,ao_Z)) return SendClientMessage(playerid,-1, "Editor android: El objeto no esta cerca de ti");

                SendClientMessage(playerid, -1, sprintf("Recibidos: %d, %d, %d || %f,%f,%f", editorid, objectid, editormode,ao_X,ao_Y,ao_Z ));

                ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_POSX ] = ao_X;
                ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_POSY ] = ao_Y;
                ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_POSZ ] = ao_Z;
                ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_POSRX ] = ao_RX;
                ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_POSRY ] = ao_RY;
                ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_POSRZ ] = ao_RZ;
                
            }
            case EDITOR_MODE_VEHICLE_OBJECT:
            {

                if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
                {
                    new vehicleid = GetPlayerVehicleID(playerid);
                    if(IsValidVehicle(vehicleid))
                    {
                        ao_PLAYER_SAVE_EDITOR[ playerid ][ oa_FOR_VEHICLE ] = vehicleid;
                        new info[2];
                        Streamer_GetArrayData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_EXTRA_ID, info);
                
                        if(IsValidPlayerObject(playerid, ao_PLAYER_SAVE_EDITOR[playerid][ao_TEMP_OBBJECT_ID])) DestroyPlayerObject(playerid, ao_PLAYER_SAVE_EDITOR[playerid][ao_TEMP_OBBJECT_ID]);
                        //SendClientMessage(playerid, -1, sprintf("Comparar: %d:%d | %d:%d", info[1], vehicleid, info[0],objectid ));

                        if(info[1] != vehicleid) return SendClientMessage(playerid,-1, "Editor android: El objecto que quieres editar no pertence al vehiculo en el que estas");
                        new Float:ao_VehiclePOS[ 3 ];
                        GetVehiclePos(vehicleid, ao_VehiclePOS[ 0 ], ao_VehiclePOS[ 1 ], ao_VehiclePOS[ 2 ]);
                        new Float:pos[3];
                        new Float:ao_OffSetPos[ 3 ], Float:ao_OffSetPos_ROT[ 3 ];
                        
                        Streamer_GetFloatData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_ATTACH_R_X, ao_OffSetPos_ROT[ 0 ]);
                        Streamer_GetFloatData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_ATTACH_R_Y, ao_OffSetPos_ROT[ 1 ]);
                        Streamer_GetFloatData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_ATTACH_R_Z, ao_OffSetPos_ROT[ 2 ]);

                        //new Float:ao_Float_DATA[ 3 ];
                        Streamer_GetFloatData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_ATTACH_OFFSET_X, ao_OffSetPos[ 0 ]);
                        Streamer_GetFloatData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_ATTACH_OFFSET_Y, ao_OffSetPos[ 1 ]);
                        Streamer_GetFloatData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_ATTACH_OFFSET_Z, ao_OffSetPos[ 2 ]);

                        pos[0] = ao_VehiclePOS[ 0 ] + ao_OffSetPos[ 0 ];
                        pos[1] = ao_VehiclePOS[ 1 ] + ao_OffSetPos[ 1 ];
                        pos[2] = ao_VehiclePOS[ 2 ] + ao_OffSetPos[ 2 ];
                        

                        ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_EDITOR_POS ][0] = ao_OffSetPos[ 0 ];
                        ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_EDITOR_POS ][1] = ao_OffSetPos[ 1 ];
                        ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_EDITOR_POS ][2] = ao_OffSetPos[ 2 ];
                        ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_EDITOR_ROT ][0] = ao_OffSetPos_ROT[ 0 ];
                        ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_EDITOR_ROT ][1] = ao_OffSetPos_ROT[ 1 ];
                        ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_EDITOR_ROT ][2] = ao_OffSetPos_ROT[ 2 ];
                        //
                        new ao_modelid,
                            ao_txdname[ 32 ],
                            ao_texturename[ 32 ],
                            ao_materialcolor,
                            oa_materialindex, ao_cant;
                        //
                        for(oa_materialindex = 0; oa_materialindex < 10; oa_materialindex++)
                        {
                            if(IsDynamicObjectMaterialUsed(objectid, oa_materialindex))
                            {
                                GetDynamicObjectMaterial(objectid, oa_materialindex, ao_modelid, ao_txdname, ao_texturename, ao_materialcolor);
                                //SendClientMessage(playerid, -1, sprintf("Datos extraidos del objeto: %d-%d-%d || %s , %s, %d",objectid, oa_materialindex, ao_modelid, ao_txdname, ao_texturename, ao_materialcolor));
                                ao_cant ++;
                            }

                        }

                        /*SendClientMessage(playerid, -1, sprintf("Datos OffSets del objeto: %f,%f,%f | %f,%f,%f",
                            ao_OffSetPos[ 0 ],ao_OffSetPos[ 1 ],ao_OffSetPos[ 2 ], 
                            ao_OffSetPos_ROT[ 0 ], ao_OffSetPos_ROT[ 1 ], ao_OffSetPos_ROT[ 2 ]));*/


                        ao_PLAYER_SAVE_EDITOR[playerid][ao_TEMP_OBBJECT_ID] = CreatePlayerObject(playerid, GetDynamicObjectModel (objectid), pos[0], pos[1], pos[2], 
                            ao_OffSetPos_ROT[ 0 ], 
                            ao_OffSetPos_ROT[ 1 ], 
                            ao_OffSetPos_ROT[ 2 ]);
                        //
                        
                        //
                        AttachPlayerObjectToVehicle(playerid, ao_PLAYER_SAVE_EDITOR[playerid][ao_TEMP_OBBJECT_ID], vehicleid, 
                            ao_OffSetPos[ 0 ],ao_OffSetPos[ 1 ],ao_OffSetPos[ 2 ], 
                            ao_OffSetPos_ROT[ 0 ], ao_OffSetPos_ROT[ 1 ], ao_OffSetPos_ROT[ 2 ]);

                        ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_MODEL_ID ] = GetDynamicObjectModel (objectid);
                        for(ao_cant = 0; ao_cant < 10; ao_cant++)
                        {
                            if(IsDynamicObjectMaterialUsed(objectid, ao_cant))
                            {
                                SetPlayerObjectMaterial(playerid, ao_PLAYER_SAVE_EDITOR[playerid][ao_TEMP_OBBJECT_ID] , ao_cant, ao_modelid, ao_txdname, ao_texturename, ao_materialcolor);
                            }
                        }
                        //
                        new a = 0;
                        new MaterialSaveText_Index[ 10 ],MaterialSave_Text[ 10 ][256],MaterialSave_Size[ 10 ],MaterialSave_FontFace[ 10 ][ 256 ],MaterialSave_Font_Size[ 10 ],MaterialSave_Bold[ 10 ],MaterialSave_FontColor[ 10 ],MaterialSave_BackColor[ 10 ], MaterialSave_TextAligment[ 10 ];

                        for(new i = 0; i < 10; i++)
                        {
                            if(IsDynamicObjectMaterialTextUsed(objectid, i))
                            {
                                new ao_text[256],ao_materialsize,ao_fontface[256],ao_fontsize,ao_bold,ao_fontcolor,ao_backcolor,ao_textalignment;
                                GetDynamicObjectMaterialText(objectid, i,ao_text,ao_materialsize,ao_fontface,ao_fontsize,ao_bold,ao_fontcolor,ao_backcolor,ao_textalignment);

                                MaterialSaveText_Index[ a ]     = i;
                                MaterialSave_Text[ a ]          = ao_text;
                                MaterialSave_Size[ a ]          = ao_materialsize;
                                MaterialSave_FontFace[ a ]      = ao_fontface;
                                MaterialSave_Font_Size[ a ]     = ao_fontsize;
                                MaterialSave_Bold[ a ]          = ao_bold;
                                MaterialSave_FontColor[ a ]     = ao_fontcolor;
                                MaterialSave_BackColor[ a ]     = ao_backcolor;
                                MaterialSave_TextAligment[ a ]  = ao_textalignment;

                                
                                a ++;
                            }

                        }
                        for(new i = 0; i < a; i++)
                        {
                            SetPlayerObjectMaterialText(playerid, 
                            ao_PLAYER_SAVE_EDITOR[playerid][ao_TEMP_OBBJECT_ID] ,
                            MaterialSave_Text[ i ], 
                            MaterialSaveText_Index[ i ], 
                            MaterialSave_Size[ i ],
                            MaterialSave_FontFace[ i ],
                            MaterialSave_Font_Size[ i ],
                            MaterialSave_Bold[ i ],
                            MaterialSave_FontColor[ i ],
                            MaterialSave_BackColor[ i ],
                            MaterialSave_TextAligment[ i ]);
 
                        }
                    }
                }
            }
        }
        oa_StartEditorAndroid(playerid);
        Streamer_Update(playerid);
    }
    return 1;
}

oa_StartEditorAndroid(playerid)
{
    PlayerTextDrawSetString(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][ 7 ], sprintf("%.2f",ao_PLAYER_SAVE_EDITOR[ playerid ][ oa_SPEED ]));
    switch(ao_PLAYER_SAVE_EDITOR[ playerid ][ oa_MOVE_MODE ])
    {
        case 0:PlayerTextDrawSetString(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][ 3 ], "Modo Posicion");
        case 1:PlayerTextDrawSetString(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][ 3 ], "Modo Rotacion");
    }
    
    for(new i; i < 8; i++) PlayerTextDrawShow(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][ i ]);
    for(new i; i < 19; i++) TextDrawShowForPlayer(playerid, ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][ i ]);
    SelectTextDraw(playerid, 0xFFFFFF30);
    return 1;
}
oa_HideEditorAndroid(playerid)
{
    if(IsValidPlayerObject(playerid, ao_PLAYER_SAVE_EDITOR[playerid][ao_TEMP_OBBJECT_ID])) DestroyPlayerObject(playerid, ao_PLAYER_SAVE_EDITOR[playerid][ao_TEMP_OBBJECT_ID]);

    ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_EDITTING ] = false;
    ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_EDITOR_ID ] = -1;
    ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_OBJECT_ID ] = -1;
    ao_PLAYER_SAVE_EDITOR[ playerid ][ oa_EDITOR_MODE ] = 0;

    for(new i; i < 8; i++) PlayerTextDrawHide(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][ i ]);
    for(new i; i < 19; i++) TextDrawHideForPlayer(playerid, ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][ i ]);
    return 1;
}
//====================================================================
//====================================================================
forward AttachDynamicObjectToVehicleEx(objectid, vehicleid, Float:offsetx, Float:offsety, Float:offsetz, Float:rx, Float:ry, Float:rz);
public AttachDynamicObjectToVehicleEx(objectid, vehicleid, Float:offsetx, Float:offsety, Float:offsetz, Float:rx, Float:ry, Float:rz)
{
 
    new info[2];
    info[0] = objectid;
    info[1] = vehicleid;
    Streamer_SetArrayData(STREAMER_TYPE_OBJECT, objectid , E_STREAMER_EXTRA_ID, info);

    new Float:ao_OffSetPos[ 3 ];
    ao_OffSetPos[ 0 ] = offsetx;
    ao_OffSetPos[ 1 ] = offsety;
    ao_OffSetPos[ 2 ] = offsetz;

    Streamer_GetFloatData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_ATTACH_OFFSET_X, ao_OffSetPos[ 0 ]);
    Streamer_GetFloatData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_ATTACH_OFFSET_Y, ao_OffSetPos[ 1 ]);
    Streamer_GetFloatData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_ATTACH_OFFSET_Z, ao_OffSetPos[ 2 ]);

    new Float:ao_OffSetPos_ROT[ 3 ];
    ao_OffSetPos_ROT[ 0 ] = rx;
    ao_OffSetPos_ROT[ 1 ] = ry;
    ao_OffSetPos_ROT[ 2 ] = rz;
    Streamer_SetFloatData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_ATTACH_R_X, ao_OffSetPos_ROT[ 0 ]);
    Streamer_SetFloatData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_ATTACH_R_Y, ao_OffSetPos_ROT[ 1 ]);
    Streamer_SetFloatData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_ATTACH_R_Z, ao_OffSetPos_ROT[ 2 ]);

    AttachDynamicObjectToVehicle(objectid, vehicleid, offsetx, offsety, offsetz, rx, ry, rz);
    //
   /* enum @ao_array_ANDROID_OBJECT
{
    ao_vehicleid,
    bool:ao_valid_object,
    ao_OBJECT_ID

}*/
    new id = GetFreeSlotAO_VEH_OBJECT(vehicleid);
    if(id == -1 ) return printf("Error al seleccionar un id AO_EDITOR (Maximo objetos alcanzados o hay un error)");
    AO_EDITOR[ vehicleid ][ ao_vehicleid ][ id ] = vehicleid;
    AO_EDITOR[ vehicleid ][ ao_OBJECT_ID ][ id ] = objectid;

    printf("id en uso : %d",id);
    return 1;
}
#if defined _ALS_AttachbjectToVehicle
    #undef AttachDynamicObjectToVehicle
#else
    #define _ALS_AttacObjectToVehicle
#endif

#define AttachDynamicObjectToVehicle AttachDynamicObjectToVehicleEx
//====================================================================
stock GetFreeSlotAO_VEH_OBJECT(vehicleid)
{
    for(new i = 0; i < MAX_OBJECT_PER_VEH_AO; i++)
    {
        if(!AO_EDITOR[ vehicleid ][ ao_valid_object ][ i ])
        {
            AO_EDITOR[ vehicleid ][ ao_valid_object ][ i ] = true;
            return i;
        }
    }
    return -1;

}
//====================================================================
public OnPlayerClickPlayerTextDraw(playerid, PlayerText:playertextid)
{
    if(ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_EDITTING ] == true)
    {
        if(playertextid == ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][ 3 ])
        {
            if(ao_PLAYER_SAVE_EDITOR[ playerid ][ oa_MOVE_MODE ] == 0) ao_PLAYER_SAVE_EDITOR[ playerid ][ oa_MOVE_MODE ] = 1; else ao_PLAYER_SAVE_EDITOR[ playerid ][ oa_MOVE_MODE ] = 0;
            switch(ao_PLAYER_SAVE_EDITOR[ playerid ][ oa_MOVE_MODE ])
            {
                case 0:PlayerTextDrawSetString(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][ 3 ], "Modo Posicion");
                case 1:PlayerTextDrawSetString(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][ 3 ], "Modo Rotacion");
            }
        }
    }

    return CallLocalFunction("oa_OnPlayerClickPlayerTextDraw", "i", playerid);
}
#if defined _ALS_Oa_PlayerCPlayerTextdraw
    #undef OnPlayerClickPlayerTextDraw
#else
    #define _ALS_Oa_PlayerCPlayerTextdraw
#endif

#define OnPlayerClickPlayerTextDraw oa_OnPlayerClickPlayerTextDraw
//====================================================================
//====================================================================
public OnPlayerClickTextDraw(playerid, Text:clickedid)
{
    if(clickedid == Text:INVALID_TEXT_DRAW)
    {
        if(ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_EDITTING ] == true)
        {
            oa_HideEditorAndroid(playerid);
            CancelSelectTextDraw(playerid);

            ao_PLAYER_SAVE_EDITOR[ playerid ][ oa_FOR_VEHICLE ] = INVALID_VEHICLE_ID;
        }
    }
    if(ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_EDITTING ] == true)
    {
        switch(ao_PLAYER_SAVE_EDITOR[ playerid ][ oa_MOVE_MODE ])
        {
            case 0:
            {
                if(clickedid == ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][ 13 ]) // Z ++
                {
                    //ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_EDITOR_POS ][0]
                    //ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_EDITOR_POS ][1]
                    ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_EDITOR_POS ][2] += ao_PLAYER_SAVE_EDITOR[ playerid ][ oa_SPEED ];

                    //ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_EDITOR_ROT ][0]
                    //ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_EDITOR_ROT ][1]
                    //ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_EDITOR_ROT ][2]

                    
                    oa_UpdateEditor(playerid);
                }
                if(clickedid == ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][ 14 ]) // Z --
                {
                    ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_EDITOR_POS ][2] -= ao_PLAYER_SAVE_EDITOR[ playerid ][ oa_SPEED ];
                    oa_UpdateEditor(playerid);
                }
                if(clickedid == ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][ 15 ]) // Y ++
                {
                    ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_EDITOR_POS ][ 0 ] += ao_PLAYER_SAVE_EDITOR[ playerid ][ oa_SPEED ];
                    oa_UpdateEditor(playerid);
                }
                if(clickedid == ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][ 16 ]) // Y --
                {
                    ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_EDITOR_POS ][ 0 ] -= ao_PLAYER_SAVE_EDITOR[ playerid ][ oa_SPEED ];
                    oa_UpdateEditor(playerid);
                }

                if(clickedid == ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][ 17 ]) // X ++
                {
                    ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_EDITOR_POS ][ 1 ] += ao_PLAYER_SAVE_EDITOR[ playerid ][ oa_SPEED ];
                    oa_UpdateEditor(playerid);
                }
                if(clickedid == ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][ 18 ]) // X --
                {
                    ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_EDITOR_POS ][ 1 ] -= ao_PLAYER_SAVE_EDITOR[ playerid ][ oa_SPEED ];
                    oa_UpdateEditor(playerid);
                }
            }
            case 1:
            {
                if(clickedid == ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][ 13 ]) // Z ++
                {
                    ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_EDITOR_ROT ][2] += ao_PLAYER_SAVE_EDITOR[ playerid ][ oa_SPEED ] + 5.0;
                    oa_UpdateEditor(playerid);
                }
                if(clickedid == ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][ 14 ]) // Z --
                {
                    ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_EDITOR_ROT ][2] -= ao_PLAYER_SAVE_EDITOR[ playerid ][ oa_SPEED ] + 5.0;
                    oa_UpdateEditor(playerid);
                }
                if(clickedid == ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][ 15 ]) // Y ++
                {
                    ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_EDITOR_ROT ][ 0 ] += ao_PLAYER_SAVE_EDITOR[ playerid ][ oa_SPEED ] + 5.0;
                    oa_UpdateEditor(playerid);
                }
                if(clickedid == ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][ 16 ]) // Y --
                {
                    ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_EDITOR_ROT ][ 0 ] -= ao_PLAYER_SAVE_EDITOR[ playerid ][ oa_SPEED ] + 5.0;
                    oa_UpdateEditor(playerid);
                }

                if(clickedid == ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][ 17 ]) // X ++
                {
                    ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_EDITOR_ROT ][ 1 ] += ao_PLAYER_SAVE_EDITOR[ playerid ][ oa_SPEED ] + 5.0;
                    oa_UpdateEditor(playerid);
                }
                if(clickedid == ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][ 18 ]) // X --
                {
                    ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_EDITOR_ROT ][ 1 ] -= ao_PLAYER_SAVE_EDITOR[ playerid ][ oa_SPEED ] + 5.0;
                    oa_UpdateEditor(playerid);
                }
            }
        }
        
        if(clickedid == ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][8])
        {
            if(ao_PLAYER_SAVE_EDITOR[ playerid ][ oa_SPEED ] < 0.3) ao_PLAYER_SAVE_EDITOR[ playerid ][ oa_SPEED ] += 0.01;
            PlayerTextDrawSetString(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][ 7 ], sprintf("%.2f",ao_PLAYER_SAVE_EDITOR[ playerid ][ oa_SPEED ]));
        }
        if(clickedid == ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][9])
        {
            if(ao_PLAYER_SAVE_EDITOR[ playerid ][ oa_SPEED ] > 0) ao_PLAYER_SAVE_EDITOR[ playerid ][ oa_SPEED ] -= 0.01;
            PlayerTextDrawSetString(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][ 7 ], sprintf("%.2f",ao_PLAYER_SAVE_EDITOR[ playerid ][ oa_SPEED ]));
        }
        if(clickedid == ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][10])
        {
            
            new vehicleid = GetPlayerVehicleID(playerid);
            OnEditorAttachVehicleAndroid(playerid, vehicleid,
            ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_EDITOR_ID ], 
            ANDROID_EDITOR_RESPONSE_SAVE,
            ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_MODEL_ID ], 
            ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_EDITOR_POS ][0],
            ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_EDITOR_POS ][1],
            ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_EDITOR_POS ][2],
            ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_EDITOR_ROT ][0],
            ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_EDITOR_ROT ][1],
            ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_EDITOR_ROT ][2]);
            //
            oa_HideEditorAndroid(playerid);
            CancelSelectTextDraw(playerid);
            //
            ao_PLAYER_SAVE_EDITOR[ playerid ][ oa_FOR_VEHICLE ] = INVALID_VEHICLE_ID;

        }
        if(clickedid == ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][ 11 ])
        {
            oa_HideEditorAndroid(playerid);
            CancelSelectTextDraw(playerid);

            ao_PLAYER_SAVE_EDITOR[ playerid ][ oa_FOR_VEHICLE ] = INVALID_VEHICLE_ID;

        }
    }
    return CallLocalFunction("oa_OnPlayerClickTextDraw", "i", playerid);

}
#if defined _ALS_Oa_ClicTextdraw
    #undef OnPlayerClickTextDraw
#else
    #define _ALS_Oa_ClicTextdraw
#endif

#define OnPlayerClickTextDraw oa_OnPlayerClickTextDraw
//====================================================================
//====================================================================
oa_UpdateEditor(playerid)
{
    //
    if(IsValidPlayerObject(playerid, ao_PLAYER_SAVE_EDITOR[playerid][ao_TEMP_OBBJECT_ID]))
    {
     
        if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
        {
            
            if(IsValidVehicle(ao_PLAYER_SAVE_EDITOR[ playerid ][ oa_FOR_VEHICLE ]))
            {
                /*SendClientMessage(playerid, -1, sprintf("Datos: %f,%f,%f | %f,%f,%f",
                    ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_EDITOR_POS ][0],
                    ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_EDITOR_POS ][1],
                    ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_EDITOR_POS ][2],
                    ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_EDITOR_ROT ][0],
                    ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_EDITOR_ROT ][1],
                    ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_EDITOR_ROT ][2]));*/
                new Float:ao_VehiclePOS[ 3 ],Float:pos[3];
                GetVehiclePos(ao_PLAYER_SAVE_EDITOR[ playerid ][ oa_FOR_VEHICLE ], ao_VehiclePOS[ 0 ], ao_VehiclePOS[ 1 ], ao_VehiclePOS[ 2 ]);

                pos[0] = ao_VehiclePOS[ 0 ] + ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_EDITOR_POS ][0];
                pos[1] = ao_VehiclePOS[ 1 ] + ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_EDITOR_POS ][1];
                pos[2] = ao_VehiclePOS[ 2 ] + ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_EDITOR_POS ][2];

                DestroyPlayerObject(playerid, ao_PLAYER_SAVE_EDITOR[playerid][ao_TEMP_OBBJECT_ID]);
                new ao_modelid,
                ao_txdname[ 32 ],
                ao_texturename[ 32 ],
                ao_materialcolor,
                oa_materialindex, ao_cant;
                //
                for(oa_materialindex = 0; oa_materialindex < 10; oa_materialindex++)
                {
                    if(IsDynamicObjectMaterialUsed(ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_OBJECT_ID ], oa_materialindex))
                    {
                        GetDynamicObjectMaterial(ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_OBJECT_ID ], oa_materialindex, ao_modelid, ao_txdname, ao_texturename, ao_materialcolor);
                        ao_cant ++;
                    }
                }

                ao_PLAYER_SAVE_EDITOR[playerid][ao_TEMP_OBBJECT_ID] = CreatePlayerObject(playerid, GetDynamicObjectModel (ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_OBJECT_ID ]), pos[0], pos[1], pos[2], 
                    ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_EDITOR_ROT ][0], 
                    ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_EDITOR_ROT ][1], 
                    ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_EDITOR_ROT ][2]);

                AttachPlayerObjectToVehicle(playerid, ao_PLAYER_SAVE_EDITOR[playerid][ao_TEMP_OBBJECT_ID], ao_PLAYER_SAVE_EDITOR[ playerid ][ oa_FOR_VEHICLE ], 
                    ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_EDITOR_POS ][0],
                    ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_EDITOR_POS ][1],
                    ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_EDITOR_POS ][2], 

                    ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_EDITOR_ROT ][0],
                    ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_EDITOR_ROT ][1],
                    ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_EDITOR_ROT ][2]);


                for(ao_cant = 0; ao_cant < 10; ao_cant++)
                {
                    if(IsDynamicObjectMaterialUsed(ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_OBJECT_ID ], ao_cant))
                    {
                        SetPlayerObjectMaterial(playerid, ao_PLAYER_SAVE_EDITOR[playerid][ao_TEMP_OBBJECT_ID] , ao_cant, ao_modelid, ao_txdname, ao_texturename, ao_materialcolor);
                    }
                }

                new a = 0;
                new MaterialSaveText_Index[ 10 ],MaterialSave_Text[ 10 ][256],MaterialSave_Size[ 10 ],MaterialSave_FontFace[ 10 ][ 256 ],MaterialSave_Font_Size[ 10 ],MaterialSave_Bold[ 10 ],MaterialSave_FontColor[ 10 ],MaterialSave_BackColor[ 10 ], MaterialSave_TextAligment[ 10 ];

                for(new i = 0; i < 10; i++)
                {
                    if(IsDynamicObjectMaterialTextUsed(ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_OBJECT_ID ], i))
                    {
                        new ao_text[256],ao_materialsize,ao_fontface[256],ao_fontsize,ao_bold,ao_fontcolor,ao_backcolor,ao_textalignment;
                        GetDynamicObjectMaterialText(ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_OBJECT_ID ], i,ao_text,ao_materialsize,ao_fontface,ao_fontsize,ao_bold,ao_fontcolor,ao_backcolor,ao_textalignment);

                        MaterialSaveText_Index[ a ]     = i;
                        MaterialSave_Text[ a ]          = ao_text;
                        MaterialSave_Size[ a ]          = ao_materialsize;
                        MaterialSave_FontFace[ a ]      = ao_fontface;
                        MaterialSave_Font_Size[ a ]     = ao_fontsize;
                        MaterialSave_Bold[ a ]          = ao_bold;
                        MaterialSave_FontColor[ a ]     = ao_fontcolor;
                        MaterialSave_BackColor[ a ]     = ao_backcolor;
                        MaterialSave_TextAligment[ a ]  = ao_textalignment;

                        
                        a ++;
                    }

                }
                for(new i = 0; i < a; i++)
                {
                    SetPlayerObjectMaterialText(playerid, 
                    ao_PLAYER_SAVE_EDITOR[playerid][ao_TEMP_OBBJECT_ID], 
                    MaterialSave_Text[ i ], 
                    MaterialSaveText_Index[ i ], 
                    MaterialSave_Size[ i ],
                    MaterialSave_FontFace[ i ],
                    MaterialSave_Font_Size[ i ],
                    MaterialSave_Bold[ i ],
                    MaterialSave_FontColor[ i ],
                    MaterialSave_BackColor[ i ],
                    MaterialSave_TextAligment[ i ]);
                            
 
                }

            }
        }
    }

    return 1;
}
//forward ao_CreateDynamicObject(modelid, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz, worldid = -1, interiorid = -1, playerid = -1, Float:streamdistance = STREAMER_OBJECT_SD, Float:drawdistance = STREAMER_OBJECT_DD, STREAMER_TAG_AREA:areaid = STREAMER_TAG_AREA:-1, priority = 0);
oa_CreateMenuEditor(playerid)
{
    ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][0] = CreatePlayerTextDraw(playerid, 527.916564, 227.592590, "ld_beat:up");
    PlayerTextDrawLetterSize(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][0], 0.000000, 0.000000);
    PlayerTextDrawTextSize(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][0], 30.000000, 23.000000);
    PlayerTextDrawAlignment(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][0], 1);
    PlayerTextDrawColor(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][0], 16711935);
    PlayerTextDrawSetShadow(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][0], 0);
    PlayerTextDrawSetOutline(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][0], 0);
    PlayerTextDrawBackgroundColor(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][0], 255);
    PlayerTextDrawFont(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][0], 4);
    PlayerTextDrawSetProportional(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][0], 0);
    PlayerTextDrawSetShadow(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][0], 0);
    PlayerTextDrawSetSelectable(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][0], false);

    ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][1] = CreatePlayerTextDraw(playerid, 528.333190, 409.074127, "ld_beat:up");
    PlayerTextDrawLetterSize(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][1], 0.000000, 0.000000);
    PlayerTextDrawTextSize(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][1], 29.000000, -26.000000);
    PlayerTextDrawAlignment(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][1], 1);
    PlayerTextDrawColor(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][1], 16711935);
    PlayerTextDrawSetShadow(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][1], 0);
    PlayerTextDrawSetOutline(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][1], 0);
    PlayerTextDrawBackgroundColor(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][1], 255);
    PlayerTextDrawFont(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][1], 4);
    PlayerTextDrawSetProportional(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][1], 0);
    PlayerTextDrawSetShadow(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][1], 0);
    PlayerTextDrawSetSelectable(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][1], false);

    ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][2] = CreatePlayerTextDraw(playerid, 452.916412, 290.851745, "ld_beat:upl");
    PlayerTextDrawLetterSize(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][2], 0.000000, 0.000000);
    PlayerTextDrawTextSize(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][2], 29.000000, 24.000000);
    PlayerTextDrawAlignment(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][2], 1);
    PlayerTextDrawColor(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][2], 16711935);
    PlayerTextDrawSetShadow(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][2], 0);
    PlayerTextDrawSetOutline(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][2], 0);
    PlayerTextDrawBackgroundColor(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][2], 255);
    PlayerTextDrawFont(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][2], 4);
    PlayerTextDrawSetProportional(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][2], 0);
    PlayerTextDrawSetShadow(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][2], 0);
    PlayerTextDrawSetSelectable(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][2], false);

    ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][3] = CreatePlayerTextDraw(playerid, 541.666503, 341.926025, "Modo Posicion");
    PlayerTextDrawLetterSize(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][3], 0.233333, 1.314815);
    PlayerTextDrawTextSize(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][3], 15.000000, 74.000000);
    PlayerTextDrawAlignment(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][3], 2);
    PlayerTextDrawColor(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][3], -1);
    PlayerTextDrawUseBox(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][3], 1);
    PlayerTextDrawBoxColor(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][3], 255);
    PlayerTextDrawSetShadow(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][3], 0);
    PlayerTextDrawSetOutline(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][3], 0);
    PlayerTextDrawBackgroundColor(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][3], 255);
    PlayerTextDrawFont(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][3], 1);
    PlayerTextDrawSetProportional(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][3], 1);
    PlayerTextDrawSetShadow(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][3], 0);
    PlayerTextDrawSetSelectable(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][3], true);

    ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][4] = CreatePlayerTextDraw(playerid, 452.499877, 344.777648, "ld_beat:upl");
    PlayerTextDrawLetterSize(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][4], 0.000000, 0.000000);
    PlayerTextDrawTextSize(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][4], 28.000000, -26.000000);
    PlayerTextDrawAlignment(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][4], 1);
    PlayerTextDrawColor(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][4], 16711935);
    PlayerTextDrawSetShadow(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][4], 0);
    PlayerTextDrawSetOutline(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][4], 0);
    PlayerTextDrawBackgroundColor(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][4], 255);
    PlayerTextDrawFont(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][4], 4);
    PlayerTextDrawSetProportional(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][4], 0);
    PlayerTextDrawSetShadow(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][4], 0);
    PlayerTextDrawSetSelectable(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][4], false);

    ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][5] = CreatePlayerTextDraw(playerid, 634.166503, 292.925689, "ld_beat:upl");
    PlayerTextDrawLetterSize(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][5], 0.000000, 0.000000);
    PlayerTextDrawTextSize(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][5], -30.000000, 24.000000);
    PlayerTextDrawAlignment(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][5], 1);
    PlayerTextDrawColor(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][5], 16711935);
    PlayerTextDrawSetShadow(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][5], 0);
    PlayerTextDrawSetOutline(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][5], 0);
    PlayerTextDrawBackgroundColor(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][5], 255);
    PlayerTextDrawFont(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][5], 4);
    PlayerTextDrawSetProportional(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][5], 0);
    PlayerTextDrawSetShadow(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][5], 0);
    PlayerTextDrawSetSelectable(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][5], false);

    ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][6] = CreatePlayerTextDraw(playerid, 635.416503, 344.259155, "ld_beat:upl");
    PlayerTextDrawLetterSize(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][6], 0.000000, 0.000000);
    PlayerTextDrawTextSize(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][6], -32.000000, -25.000000);
    PlayerTextDrawAlignment(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][6], 1);
    PlayerTextDrawColor(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][6], 16711935);
    PlayerTextDrawSetShadow(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][6], 0);
    PlayerTextDrawSetOutline(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][6], 0);
    PlayerTextDrawBackgroundColor(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][6], 255);
    PlayerTextDrawFont(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][6], 4);
    PlayerTextDrawSetProportional(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][6], 0);
    PlayerTextDrawSetShadow(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][6], 0);
    PlayerTextDrawSetSelectable(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][6], false);

    ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][7] = CreatePlayerTextDraw(playerid, 541.666137, 311.333251, "0.5");
    PlayerTextDrawLetterSize(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][7], 0.181666, 1.273334);
    PlayerTextDrawTextSize(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][7], 0.000000, 35.000000);
    PlayerTextDrawAlignment(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][7], 2);
    PlayerTextDrawColor(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][7], -1);
    PlayerTextDrawUseBox(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][7], 1);
    PlayerTextDrawBoxColor(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][7], 255);
    PlayerTextDrawSetShadow(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][7], 0);
    PlayerTextDrawSetOutline(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][7], 0);
    PlayerTextDrawBackgroundColor(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][7], 255);
    PlayerTextDrawFont(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][7], 2);
    PlayerTextDrawSetProportional(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][7], 1);
    PlayerTextDrawSetShadow(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][7], 0);
    return 1;
}
oa_DestroyMenuEditor(playerid)
{
    for(new i; i < 8; i++)
    {
        PlayerTextDrawDestroy(playerid, ao_PLAYER_SAVE_EDITOR[ playerid ][ ao_TXT_EDITOR_ANDROID ][ i ]);
    }
    return 1;
}
oa_CreateMenus_Android()
{
    ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][0] = TextDrawCreate(541.032409, 251.648300, "box");
    TextDrawLetterSize(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][0], 0.000000, 14.583333);
    TextDrawTextSize(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][0], 544.000000, 0.000000);
    TextDrawAlignment(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][0], 1);
    TextDrawColor(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][0], 16711935);
    TextDrawUseBox(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][0], 1);
    TextDrawBoxColor(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][0], 16777215);
    TextDrawSetShadow(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][0], 0);
    TextDrawSetOutline(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][0], 0);
    TextDrawBackgroundColor(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][0], 255);
    TextDrawFont(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][0], 1);
    TextDrawSetProportional(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][0], 1);
    TextDrawSetShadow(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][0], 0);

    ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][1] = TextDrawCreate(475.231323, 317.081420, "box");
    TextDrawLetterSize(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][1], 0.000000, 0.291664);
    TextDrawTextSize(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][1], 609.000000, 0.000000);
    TextDrawAlignment(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][1], 1);
    TextDrawColor(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][1], -16776961);
    TextDrawUseBox(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][1], 1);
    TextDrawBoxColor(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][1], 16777215);
    TextDrawSetShadow(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][1], 0);
    TextDrawSetOutline(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][1], 0);
    TextDrawBackgroundColor(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][1], 255);
    TextDrawFont(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][1], 1);
    TextDrawSetProportional(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][1], 1);
    TextDrawSetShadow(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][1], 0);

    ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][2] = TextDrawCreate(484.166625, 256.629394, "");
    TextDrawLetterSize(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][2], 0.000000, 0.000000);
    TextDrawTextSize(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][2], 115.000000, 123.000000);
    TextDrawAlignment(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][2], 1);
    TextDrawColor(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][2], 16711935);
    TextDrawSetShadow(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][2], 0);
    TextDrawSetOutline(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][2], 0);
    TextDrawBackgroundColor(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][2], -16777216);
    TextDrawFont(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][2], 5);
    TextDrawSetProportional(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][2], 0);
    TextDrawSetShadow(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][2], 0);
    TextDrawSetPreviewModel(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][2], 18997);
    TextDrawSetPreviewRot(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][2], 90.000000, 0.000000, 0.000000, 1.000000);

    ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][3] = TextDrawCreate(535.416687, 216.962951, "Z+");
    TextDrawLetterSize(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][3], 0.311250, 1.366665);
    TextDrawAlignment(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][3], 1);
    TextDrawColor(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][3], -1);
    TextDrawSetShadow(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][3], 0);
    TextDrawSetOutline(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][3], 1);
    TextDrawBackgroundColor(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][3], 255);
    TextDrawFont(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][3], 1);
    TextDrawSetProportional(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][3], 1);
    TextDrawSetShadow(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][3], 0);

    ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][4] = TextDrawCreate(537.083190, 407.777740, "Z-");
    TextDrawLetterSize(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][4], 0.311250, 1.366665);
    TextDrawAlignment(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][4], 1);
    TextDrawColor(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][4], -1);
    TextDrawSetShadow(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][4], 0);
    TextDrawSetOutline(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][4], 1);
    TextDrawBackgroundColor(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][4], 255);
    TextDrawFont(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][4], 1);
    TextDrawSetProportional(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][4], 1);
    TextDrawSetShadow(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][4], 0);

    ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][5] = TextDrawCreate(454.583374, 279.703704, "Y+");
    TextDrawLetterSize(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][5], 0.311250, 1.366665);
    TextDrawAlignment(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][5], 1);
    TextDrawColor(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][5], -1);
    TextDrawSetShadow(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][5], 0);
    TextDrawSetOutline(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][5], 1);
    TextDrawBackgroundColor(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][5], 255);
    TextDrawFont(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][5], 1);
    TextDrawSetProportional(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][5], 1);
    TextDrawSetShadow(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][5], 0);

    ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][6] = TextDrawCreate(455.000000, 341.925964, "Y-");
    TextDrawLetterSize(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][6], 0.311250, 1.366665);
    TextDrawAlignment(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][6], 1);
    TextDrawColor(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][6], -1);
    TextDrawSetShadow(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][6], 0);
    TextDrawSetOutline(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][6], 1);
    TextDrawBackgroundColor(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][6], 255);
    TextDrawFont(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][6], 1);
    TextDrawSetProportional(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][6], 1);
    TextDrawSetShadow(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][6], 0);

    ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][7] = TextDrawCreate(620.416564, 282.814880, "X+");
    TextDrawLetterSize(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][7], 0.311250, 1.366665);
    TextDrawAlignment(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][7], 1);
    TextDrawColor(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][7], -1);
    TextDrawSetShadow(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][7], 0);
    TextDrawSetOutline(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][7], 1);
    TextDrawBackgroundColor(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][7], 255);
    TextDrawFont(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][7], 1);
    TextDrawSetProportional(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][7], 1);
    TextDrawSetShadow(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][7], 0);

    ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][8] = TextDrawCreate(506.249450, 311.333251, "+");
    TextDrawLetterSize(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][8], 0.348749, 1.252593);
    TextDrawTextSize(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][8], 519.000000, 10.000000);
    TextDrawAlignment(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][8], 1);
    TextDrawColor(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][8], -1);
    TextDrawUseBox(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][8], 1);
    TextDrawBoxColor(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][8], 255);
    TextDrawSetShadow(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][8], 0);
    TextDrawSetOutline(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][8], 0);
    TextDrawBackgroundColor(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][8], 255);
    TextDrawFont(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][8], 1);
    TextDrawSetProportional(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][8], 1);
    TextDrawSetShadow(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][8], 0);
    TextDrawSetSelectable(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][8], true);

    ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][9] = TextDrawCreate(564.999084, 311.851898, "-");
    TextDrawLetterSize(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][9], 0.647499, 1.226667);
    TextDrawTextSize(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][9], 577.000000, 10.000000);
    TextDrawAlignment(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][9], 1);
    TextDrawColor(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][9], -1);
    TextDrawUseBox(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][9], 1);
    TextDrawBoxColor(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][9], 255);
    TextDrawSetShadow(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][9], 0);
    TextDrawSetOutline(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][9], 0);
    TextDrawBackgroundColor(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][9], 255);
    TextDrawFont(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][9], 1);
    TextDrawSetProportional(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][9], 1);
    TextDrawSetShadow(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][9], 0);
    TextDrawSetSelectable(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][9], true);

    ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][10] = TextDrawCreate(467.916717, 390.925872, "ld_chat:thumbup");
    TextDrawLetterSize(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][10], 0.000000, 0.000000);
    TextDrawTextSize(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][10], 27.000000, 28.000000);
    TextDrawAlignment(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][10], 1);
    TextDrawColor(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][10], -1378294017);
    TextDrawSetShadow(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][10], 0);
    TextDrawSetOutline(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][10], 0);
    TextDrawBackgroundColor(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][10], 255);
    TextDrawFont(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][10], 4);
    TextDrawSetProportional(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][10], 0);
    TextDrawSetShadow(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][10], 0);
    TextDrawSetSelectable(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][10], true);

    ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][11] = TextDrawCreate(585.000061, 388.851776, "ld_chat:thumbdn");
    TextDrawLetterSize(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][11], 0.000000, 0.000000);
    TextDrawTextSize(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][11], 27.000000, 28.000000);
    TextDrawAlignment(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][11], 1);
    TextDrawColor(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][11], -1);
    TextDrawSetShadow(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][11], 0);
    TextDrawSetOutline(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][11], 0);
    TextDrawBackgroundColor(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][11], 255);
    TextDrawFont(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][11], 4);
    TextDrawSetProportional(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][11], 0);
    TextDrawSetShadow(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][11], 0);
    TextDrawSetSelectable(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][11], true);

    ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][12] = TextDrawCreate(621.250122, 340.370391, "X-");
    TextDrawLetterSize(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][12], 0.311250, 1.366665);
    TextDrawAlignment(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][12], 1);
    TextDrawColor(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][12], -1);
    TextDrawSetShadow(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][12], 0);
    TextDrawSetOutline(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][12], 1);
    TextDrawBackgroundColor(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][12], 255);
    TextDrawFont(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][12], 1);
    TextDrawSetProportional(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][12], 1);
    TextDrawSetShadow(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][12], 0);

    ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][13] = TextDrawCreate(532.916870, 230.963073, "_");
    TextDrawLetterSize(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][13], 0.407083, 1.641481);
    TextDrawTextSize(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][13], 552.000000, 12.000000);
    TextDrawAlignment(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][13], 1);
    TextDrawColor(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][13], -1);
    TextDrawUseBox(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][13], 1);
    TextDrawBoxColor(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][13], 0xFFFFFF00);
    TextDrawSetShadow(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][13], 0);
    TextDrawSetOutline(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][13], 0);
    TextDrawBackgroundColor(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][13], 255);
    TextDrawFont(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][13], 1);
    TextDrawSetProportional(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][13], 1);
    TextDrawSetShadow(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][13], 0);
    TextDrawSetSelectable(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][13], true);

    ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][14] = TextDrawCreate(532.083618, 390.148345, "_");
    TextDrawLetterSize(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][14], 0.407083, 1.641481);
    TextDrawTextSize(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][14], 553.000000, 12.000000);
    TextDrawAlignment(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][14], 1);
    TextDrawColor(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][14], -1);
    TextDrawUseBox(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][14], 1);
    TextDrawBoxColor(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][14], 0xFFFFFF00);
    TextDrawSetShadow(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][14], 0);
    TextDrawSetOutline(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][14], 0);
    TextDrawBackgroundColor(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][14], 255);
    TextDrawFont(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][14], 1);
    TextDrawSetProportional(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][14], 1);
    TextDrawSetShadow(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][14], 0);
    TextDrawSetSelectable(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][14], true);

    ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][15] = TextDrawCreate(450.417053, 293.703857, "_");
    TextDrawLetterSize(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][15], 0.407083, 1.641481);
    TextDrawTextSize(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][15], 480.000000, 12.000000);
    TextDrawAlignment(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][15], 1);
    TextDrawColor(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][15], -1);
    TextDrawUseBox(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][15], 1);
    TextDrawBoxColor(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][15], 0xFFFFFF00);
    TextDrawSetShadow(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][15], 0);
    TextDrawSetOutline(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][15], 0);
    TextDrawBackgroundColor(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][15], 255);
    TextDrawFont(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][15], 1);
    TextDrawSetProportional(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][15], 1);
    TextDrawSetShadow(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][15], 0);
    TextDrawSetSelectable(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][15], true);

    ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][16] = TextDrawCreate(450.000427, 324.296478, "_");
    TextDrawLetterSize(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][16], 0.407083, 1.641481);
    TextDrawTextSize(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][16], 475.000000, 12.000000);
    TextDrawAlignment(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][16], 1);
    TextDrawColor(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][16], -1);
    TextDrawUseBox(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][16], 1);
    TextDrawBoxColor(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][16], 0xFFFFFF00);
    TextDrawSetShadow(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][16], 0);
    TextDrawSetOutline(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][16], 0);
    TextDrawBackgroundColor(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][16], 255);
    TextDrawFont(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][16], 1);
    TextDrawSetProportional(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][16], 1);
    TextDrawSetShadow(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][16], 0);
    TextDrawSetSelectable(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][16], true);

    ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][17] = TextDrawCreate(610.000488, 297.333496, "_");
    TextDrawLetterSize(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][17], 0.407083, 1.641481);
    TextDrawTextSize(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][17], 634.000000, 12.000000);
    TextDrawAlignment(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][17], 1);
    TextDrawColor(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][17], -1);
    TextDrawUseBox(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][17], 1);
    TextDrawBoxColor(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][17], 0xFFFFFF00);
    TextDrawSetShadow(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][17], 0);
    TextDrawSetOutline(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][17], 0);
    TextDrawBackgroundColor(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][17], 255);
    TextDrawFont(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][17], 1);
    TextDrawSetProportional(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][17], 1);
    TextDrawSetShadow(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][17], 0);
    TextDrawSetSelectable(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][17], true);

    ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][18] = TextDrawCreate(610.000427, 323.259368, "_");
    TextDrawLetterSize(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][18], 0.407083, 1.641481);
    TextDrawTextSize(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][18], 635.000000, 12.000000);
    TextDrawAlignment(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][18], 1);
    TextDrawColor(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][18], -1);
    TextDrawUseBox(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][18], 1);
    TextDrawBoxColor(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][18], 0xFFFFFF00);
    TextDrawSetShadow(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][18], 0);
    TextDrawSetOutline(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][18], 0);
    TextDrawBackgroundColor(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][18], 255);
    TextDrawFont(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][18], 1);
    TextDrawSetProportional(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][18], 1);
    TextDrawSetShadow(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][18], 0);
    TextDrawSetSelectable(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][18], true);
    return 1;
}

oa_DestroyGlobalMenus()
{
    for(new i; i < 19; i++)
    {
        TextDrawDestroy(ao_GLOBAL_TEXTDRAW[ ao_TXT_EDITOR_ANDROID ][ i ]);
    }
    return 1;
}


oa_INFO_script()
{
    print(" ");
    print(" ======================== OA EDITOR ==============================================");
    new ver_name[16];
    format(ver_name,sizeof(ver_name),"%d.%d.%d",OA_EDITOR::GetVersion(AO_EDITOR_VERSION));
    printf("[OA EDITOR] Info: LOADED. %s Generation 1. v%s for %s %s by %s\n\nDiscord: %s\n",
        AO_EDITOR_LIBRARY_NAME,
        ver_name,
        AO_EDITOR_PLATFORM_NAME,
        AO_EDITOR_PLATFORM_VERSION,
        AO_EDITOR_AUTHOR_NAME,
        AO_EDITOR_AUTHOR_DISCORD);
    print(" ======================== OA EDITOR ==============================================");
    print(" ");

    return 1;
}