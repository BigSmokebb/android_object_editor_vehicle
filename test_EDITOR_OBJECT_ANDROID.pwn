#include  <a_samp>
 
#include  <zcmd>
//native IsValidVehicle(vehicleid);
#include "streamer"
#include "strlib"
#include "Android_Object_Editor"
#pragma dynamic  10000



#define EDITOR_ID_PRUEBA_1 100
#define DIALOGO_PRUEBA 1
new SELECT_INDEX_OBJECT[ MAX_PLAYERS ];
//new SELECT_INDEX_VEHICLE[ MAX_PLAYERS ];
new VEHICULOS_TUNING[ 4 ], PRUEBA_EDITOR[ MAX_VEHICLES ][ 13 ];
public OnFilterScriptInit()
{
 

    VEHICULOS_TUNING[ 1 ] = CreateVehicle(560,3, 0, 4,180,0,0,-1);


    VEHICULOS_TUNING[ 0 ] = CreateVehicle(444,0, 0, 3,181.4347,0,0,-1);

    PRUEBA_EDITOR[ VEHICULOS_TUNING[ 0 ] ][ 0 ] = CreateDynamicObject(19917,0.0,0.0,-1000.0,0.0,0.0,0.0,-1,-1,-1,300.0,300.0);
    AttachDynamicObjectToVehicle(PRUEBA_EDITOR[ VEHICULOS_TUNING[ 0 ] ][ 0 ], VEHICULOS_TUNING[ 0 ], -0.020, 2.120, 0.649, 0.000, 0.000, 0.000);

    PRUEBA_EDITOR[ VEHICULOS_TUNING[ 0 ] ][ 1 ] = CreateDynamicObject(18693,0.0,0.0,-1000.0,0.0,0.0,0.0,-1,-1,-1,300.0,300.0);
    AttachDynamicObjectToVehicle(PRUEBA_EDITOR[ VEHICULOS_TUNING[ 0 ] ][ 1 ], VEHICULOS_TUNING[ 0 ], -0.020, 2.451, -0.210, 0.000, 0.000, 0.000);

    PRUEBA_EDITOR[ VEHICULOS_TUNING[ 0 ] ][ 2 ] = CreateDynamicObject(1319,0.0,0.0,-1000.0,0.0,0.0,0.0,-1,-1,-1,300.0,300.0);
    SetDynamicObjectMaterial(PRUEBA_EDITOR[ VEHICULOS_TUNING[ 0 ] ][ 2 ], 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0);
    AttachDynamicObjectToVehicle(PRUEBA_EDITOR[ VEHICULOS_TUNING[ 0 ] ][ 2 ], VEHICULOS_TUNING[ 0 ], -0.020, 2.488, 0.972, -34.500, 0.000, 95.399);

    PRUEBA_EDITOR[ VEHICULOS_TUNING[ 0 ] ][ 3 ] = CreateDynamicObject(1319,0.0,0.0,-1000.0,0.0,0.0,0.0,-1,-1,-1,300.0,300.0);
    SetDynamicObjectMaterial(PRUEBA_EDITOR[ VEHICULOS_TUNING[ 0 ] ][ 3 ], 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0);
    AttachDynamicObjectToVehicle(PRUEBA_EDITOR[ VEHICULOS_TUNING[ 0 ] ][ 3 ], VEHICULOS_TUNING[ 0 ], -0.020, 2.432, 0.927, 34.399, 0.000, 93.999);

    PRUEBA_EDITOR[ VEHICULOS_TUNING[ 0 ] ][ 4 ] = CreateDynamicObject(18693,0.0,0.0,-1000.0,0.0,0.0,0.0,-1,-1,-1,300.0,300.0);
    AttachDynamicObjectToVehicle(PRUEBA_EDITOR[ VEHICULOS_TUNING[ 0 ] ][ 4 ], VEHICULOS_TUNING[ 0 ], -0.020, 2.480, -0.130, 0.000, 0.000, 0.000);

    PRUEBA_EDITOR[ VEHICULOS_TUNING[ 0 ] ][ 5 ] = CreateDynamicObject(19314,0.0,0.0,-1000.0,0.0,0.0,0.0,-1,-1,-1,300.0,300.0);
    SetDynamicObjectMaterial(PRUEBA_EDITOR[ VEHICULOS_TUNING[ 0 ] ][ 5 ], 0, 14415, "carter_block_2", "ws_doormat", 0);
    AttachDynamicObjectToVehicle(PRUEBA_EDITOR[ VEHICULOS_TUNING[ 0 ] ][ 5 ], VEHICULOS_TUNING[ 0 ], -0.020, 2.493, 1.175, 90.700, -92.199, -0.200);

    PRUEBA_EDITOR[ VEHICULOS_TUNING[ 0 ] ][ 6 ] = CreateDynamicObject(1736,0.0,0.0,-1000.0,0.0,0.0,0.0,-1,-1,-1,300.0,300.0);
    SetDynamicObjectMaterial(PRUEBA_EDITOR[ VEHICULOS_TUNING[ 0 ] ][ 6 ], 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0);
    AttachDynamicObjectToVehicle(PRUEBA_EDITOR[ VEHICULOS_TUNING[ 0 ] ][ 6 ], VEHICULOS_TUNING[ 0 ], -0.020, 3.099, 0.710, 0.000, 0.000, 178.100);

    PRUEBA_EDITOR[ VEHICULOS_TUNING[ 0 ] ][ 7 ] = CreateDynamicObject(1001,0.0,0.0,-1000.0,0.0,0.0,0.0,-1,-1,-1,300.0,300.0);
    SetDynamicObjectMaterial(PRUEBA_EDITOR[ VEHICULOS_TUNING[ 0 ] ][ 7 ], 0, 19058, "xmasboxes", "silk6-128x128", 0);
    AttachDynamicObjectToVehicle(PRUEBA_EDITOR[ VEHICULOS_TUNING[ 0 ] ][ 7 ], VEHICULOS_TUNING[ 0 ], -0.020, -2.939, 1.020, 0.000, 0.000, 0.000);

    PRUEBA_EDITOR[ VEHICULOS_TUNING[ 0 ] ][ 8 ] = CreateDynamicObject(1113,0.0,0.0,-1000.0,0.0,0.0,0.0,-1,-1,-1,300.0,300.0);
    AttachDynamicObjectToVehicle(PRUEBA_EDITOR[ VEHICULOS_TUNING[ 0 ] ][ 8 ], VEHICULOS_TUNING[ 0 ], -0.020, -2.030, 0.000, 0.000, 0.000, 0.000);

    PRUEBA_EDITOR[ VEHICULOS_TUNING[ 0 ] ][ 9 ] = CreateDynamicObject(18693,0.0,0.0,-1000.0,0.0,0.0,0.0,-1,-1,-1,300.0,300.0);
    AttachDynamicObjectToVehicle(PRUEBA_EDITOR[ VEHICULOS_TUNING[ 0 ] ][ 9 ], VEHICULOS_TUNING[ 0 ], -0.020, -1.832, 0.589, 0.000, -105.699, 112.200);

    PRUEBA_EDITOR[ VEHICULOS_TUNING[ 0 ] ][ 10 ] = CreateDynamicObject(1116,0.0,0.0,-1000.0,0.0,0.0,0.0,-1,-1,-1,300.0,300.0);
    SetDynamicObjectMaterial(PRUEBA_EDITOR[ VEHICULOS_TUNING[ 0 ] ][ 10 ], 0, 9514, "711_sfw", "supasave_wintemp", 0);
    AttachDynamicObjectToVehicle(PRUEBA_EDITOR[ VEHICULOS_TUNING[ 0 ] ][ 10 ], VEHICULOS_TUNING[ 0 ], -0.020, 2.940, -0.000, 0.000, 0.000, 0.000);

    PRUEBA_EDITOR[ VEHICULOS_TUNING[ 0 ] ][ 11 ] = CreateDynamicObject(2715,0.0,0.0,-1000.0,0.0,0.0,0.0,-1,-1,-1,300.0,300.0);
    SetDynamicObjectMaterialText(PRUEBA_EDITOR[ VEHICULOS_TUNING[ 0 ] ][ 11 ], 0, "HOLA MUNDO", 90, "Fixedsys", 50, 0, -65281, 0, 0);
    AttachDynamicObjectToVehicle(PRUEBA_EDITOR[ VEHICULOS_TUNING[ 0 ] ][ 11 ], VEHICULOS_TUNING[ 0 ], -0.020, -0.607, 0.340, 0.000, 0.000, -91.300);

    PRUEBA_EDITOR[ VEHICULOS_TUNING[ 0 ] ][ 12 ] = CreateDynamicObject(1143,0.0,0.0,-1000.0,0.0,0.0,0.0,-1,-1,-1,300.0,300.0);
    SetDynamicObjectMaterial(PRUEBA_EDITOR[ VEHICULOS_TUNING[ 0 ] ][ 12 ], 0, 14584, "ab_abbatoir01", "ab_vent1", 0);
    AttachDynamicObjectToVehicle(PRUEBA_EDITOR[ VEHICULOS_TUNING[ 0 ] ][ 12 ], VEHICULOS_TUNING[ 0 ], -0.020, 0.230, 1.660, 0.000, 0.000, 0.000);
 

    VEHICULOS_TUNING[ 2 ] = CreateVehicle(535,0.4417, 4.7889, 3.6351,180.5625,0,0,-1); //

    PRUEBA_EDITOR[ VEHICULOS_TUNING[ 2 ] ][ 0 ] = CreateDynamicObject(1003,0.0,0.0,-1000.0,0.0,0.0,0.0,-1,-1,-1,300.0,300.0);
    //printf("Objecto id : %d , vehiculo id: %d", PRUEBA_EDITOR[ VEHICULOS_TUNING[ 2 ] ][ 0 ], VEHICULOS_TUNING[ 2 ]);
    SetDynamicObjectMaterial(PRUEBA_EDITOR[ VEHICULOS_TUNING[ 2 ] ][ 0 ], 0, 19058, "xmasboxes", "silk6-128x128", 0);
    AttachDynamicObjectToVehicle(PRUEBA_EDITOR[ VEHICULOS_TUNING[ 2 ] ][ 0 ], VEHICULOS_TUNING[ 2 ], 0.000, -2.461, 0.320, 0.000, 0.000, 0.000);

    PRUEBA_EDITOR[ VEHICULOS_TUNING[ 2 ] ][ 1 ] = CreateDynamicObject(19917,0.0,0.0,-1000.0,0.0,0.0,0.0,-1,-1,-1,300.0,300.0);
    AttachDynamicObjectToVehicle(PRUEBA_EDITOR[ VEHICULOS_TUNING[ 2 ] ][ 1 ], VEHICULOS_TUNING[ 2 ], 0.000, 1.881, 0.000, 0.000, 0.000, -179.000);

    PRUEBA_EDITOR[ VEHICULOS_TUNING[ 2 ] ][ 2 ] = CreateDynamicObject(19314,0.0,0.0,-1000.0,0.0,0.0,0.0,-1,-1,-1,300.0,300.0);
    SetDynamicObjectMaterial(PRUEBA_EDITOR[ VEHICULOS_TUNING[ 2 ] ][ 2 ], 0, 19058, "xmasboxes", "wrappingpaper4-2", 0);
    AttachDynamicObjectToVehicle(PRUEBA_EDITOR[ VEHICULOS_TUNING[ 2 ] ][ 2 ], VEHICULOS_TUNING[ 2 ], 0.011, 2.458, 0.616, 33.499, 87.099, 5.200);

    PRUEBA_EDITOR[ VEHICULOS_TUNING[ 2 ] ][ 3 ] = CreateDynamicObject(1254,0.0,0.0,-1000.0,0.0,0.0,0.0,-1,-1,-1,300.0,300.0);
    SetDynamicObjectMaterial(PRUEBA_EDITOR[ VEHICULOS_TUNING[ 2 ] ][ 3 ], 0, 19115, "sillyhelmets", "sillyhelmet3", 0);
    SetDynamicObjectMaterial(PRUEBA_EDITOR[ VEHICULOS_TUNING[ 2 ] ][ 3 ], 3, 19115, "sillyhelmets", "sillyhelmet2", 0);
    SetDynamicObjectMaterial(PRUEBA_EDITOR[ VEHICULOS_TUNING[ 2 ] ][ 3 ], 4, 19115, "sillyhelmets", "sillyhelmet2", 0);
    AttachDynamicObjectToVehicle(PRUEBA_EDITOR[ VEHICULOS_TUNING[ 2 ] ][ 3 ], VEHICULOS_TUNING[ 2 ], -0.830, 2.442, -0.180, 0.000, 0.000, 0.000);

    PRUEBA_EDITOR[ VEHICULOS_TUNING[ 2 ] ][ 4 ] = CreateDynamicObject(1254,0.0,0.0,-1000.0,0.0,0.0,0.0,-1,-1,-1,300.0,300.0);
    SetDynamicObjectMaterial(PRUEBA_EDITOR[ VEHICULOS_TUNING[ 2 ] ][ 4 ], 0, 19115, "sillyhelmets", "sillyhelmet3", 0);
    SetDynamicObjectMaterial(PRUEBA_EDITOR[ VEHICULOS_TUNING[ 2 ] ][ 4 ], 3, 19115, "sillyhelmets", "sillyhelmet2", 0);
    AttachDynamicObjectToVehicle(PRUEBA_EDITOR[ VEHICULOS_TUNING[ 2 ] ][ 4 ], VEHICULOS_TUNING[ 2 ], 0.820, 2.511, -0.200, 0.000, 0.000, 0.000);

    PRUEBA_EDITOR[ VEHICULOS_TUNING[ 2 ] ][ 5 ] = CreateDynamicObject(2715,0.0,0.0,-1000.0,0.0,0.0,0.0,-1,-1,-1,300.0,300.0);
    SetDynamicObjectMaterialText(PRUEBA_EDITOR[ VEHICULOS_TUNING[ 2 ] ][ 5 ], 0, "PuroDesmadre Freeroam", 90, "Fixedsys", 50, 0, -16776961, 0, 0);
    AttachDynamicObjectToVehicle(PRUEBA_EDITOR[ VEHICULOS_TUNING[ 2 ] ][ 5 ], VEHICULOS_TUNING[ 2 ], 1.261, 0.301, -0.380, 0.000, 0.000, 89.800);

    VEHICULOS_TUNING[ 3 ] = CreateVehicle(411,2.4417, 8.7889, 3.6351,180.5625,0,0,-1); //
    new tmpobjid2;
    tmpobjid2 = CreateDynamicObject(920,0.0,0.0,-1000.0,0.0,0.0,0.0,-1,-1,-1,300.0,300.0);
    SetDynamicObjectMaterial(tmpobjid2, 0, 13659, "8bars", "AH_gbarrier", 0);
    SetDynamicObjectMaterial(tmpobjid2, 1, 16322, "a51_stores", "wtmetal3", 0);
    AttachDynamicObjectToVehicle(tmpobjid2, VEHICULOS_TUNING[ 3 ], 0.000, 1.749, 0.119, 0.000, 0.000, -89.299);
    tmpobjid2 = CreateDynamicObject(1143,0.0,0.0,-1000.0,0.0,0.0,0.0,-1,-1,-1,300.0,300.0);
    SetDynamicObjectMaterial(tmpobjid2, 0, -1, "none", "none", -13421773);
    AttachDynamicObjectToVehicle(tmpobjid2, VEHICULOS_TUNING[ 3 ], 0.008, 2.503, 0.265, 3.900, -90.299, -88.900);
    tmpobjid2 = CreateDynamicObject(1138,0.0,0.0,-1000.0,0.0,0.0,0.0,-1,-1,-1,300.0,300.0);
    SetDynamicObjectMaterial(tmpobjid2, 0, 10101, "2notherbuildsfe", "flatdoor01_law", 0);
    AttachDynamicObjectToVehicle(tmpobjid2, VEHICULOS_TUNING[ 3 ], 0.000, -2.289, 0.310, 0.000, 0.000, 0.000);
    tmpobjid2 = CreateDynamicObject(1113,0.0,0.0,-1000.0,0.0,0.0,0.0,-1,-1,-1,300.0,300.0);
    AttachDynamicObjectToVehicle(tmpobjid2, VEHICULOS_TUNING[ 3 ], 0.839, -0.017, -0.610, -2.099, 0.000, 8.099);
    tmpobjid2 = CreateDynamicObject(1113,0.0,0.0,-1000.0,0.0,0.0,0.0,-1,-1,-1,300.0,300.0);
    AttachDynamicObjectToVehicle(tmpobjid2, VEHICULOS_TUNING[ 3 ], 0.911, 0.288, -0.610, 0.000, 0.000, 5.899);
    tmpobjid2 = CreateDynamicObject(1113,0.0,0.0,-1000.0,0.0,0.0,0.0,-1,-1,-1,300.0,300.0);
    AttachDynamicObjectToVehicle(tmpobjid2, VEHICULOS_TUNING[ 3 ], -0.883, -0.037, -0.640, 0.000, 0.000, -9.799);
    tmpobjid2 = CreateDynamicObject(1113,0.0,0.0,-1000.0,0.0,0.0,0.0,-1,-1,-1,300.0,300.0);
    AttachDynamicObjectToVehicle(tmpobjid2, VEHICULOS_TUNING[ 3 ], -0.918, 0.222, -0.640, 0.000, 0.000, -8.399);
    tmpobjid2 = CreateDynamicObject(1116,0.0,0.0,-1000.0,0.0,0.0,0.0,-1,-1,-1,300.0,300.0);
    SetDynamicObjectMaterial(tmpobjid2, 0, 19058, "xmasboxes", "silk6-128x128", 0);
    AttachDynamicObjectToVehicle(tmpobjid2, VEHICULOS_TUNING[ 3 ], 0.000, 2.770, -0.670, 0.000, 0.000, 0.000);
    tmpobjid2 = CreateDynamicObject(2715,0.0,0.0,-1000.0,0.0,0.0,0.0,-1,-1,-1,300.0,300.0);
    SetDynamicObjectMaterialText(tmpobjid2, 0, "09", 20, "Calibri", 30, 0, -1, 0, 0);
    AttachDynamicObjectToVehicle(tmpobjid2, VEHICULOS_TUNING[ 3 ], -0.492, -0.060, 0.750, 89.599, 4.299, -5.600);
    oa_CreateMenuEditor( 0 );
    ao_PLAYER_SAVE_EDITOR[ 0 ][ oa_SPEED ] = 0.01;

    return 1;
}

public OnFilterScriptExit()
{
    oa_DestroyMenuEditor(0);
    oa_DestroyGlobalMenus();

    DestroyVehicle(VEHICULOS_TUNING[ 0 ] );
    DestroyVehicle(VEHICULOS_TUNING[ 1 ] );
    DestroyVehicle(VEHICULOS_TUNING[ 2 ] );
    DestroyPlayerObject(0, ao_PLAYER_SAVE_EDITOR[0][ao_TEMP_OBBJECT_ID]);
    return 1;
}

CMD:editor(playerid)
{
    new string[120],dialog[1200];
    new vehicleid = GetPlayerVehicleID(playerid);
    for(new i = 0; i < MAX_OBJECT_PER_VEH_AO; i ++)
    {
        if(AO_EDITOR[ vehicleid ][ ao_valid_object ][ i ])
        {
            if(AO_EDITOR[ vehicleid ][ ao_vehicleid ][ i ] != vehicleid) return SendClientMessage(playerid, -1, "Error en AO_EDITOR - Vehiculo incorrecto");
            format(string, sizeof(string ), "ID %d | # %d\n",AO_EDITOR[ vehicleid ][ ao_OBJECT_ID ][ i ] , i + 1);//No mover el texto o cambiarlo puede causar errores
            strcat(dialog,string);
            printf(string);
        }
        
    }
    ShowPlayerDialog(playerid, DIALOGO_PRUEBA, DIALOG_STYLE_LIST, "Object list", dialog, "Edit post", "Cancel");
    return 1;
}
 

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    switch(dialogid)
    {
        case DIALOGO_PRUEBA:
        {
            if(response)
            {
                new i = 0, teledid_[256];
                while(inputtext[i+4] != ' ')
                ++i;
                new ManageObjeto;
                strmid(teledid_, inputtext, 3, 4+i, sizeof(teledid_));
                ManageObjeto =  strval(teledid_);
                SELECT_INDEX_OBJECT[ playerid ] = ManageObjeto;
                EditDynamicAndroidObject(playerid, EDITOR_ID_PRUEBA_1, 
                    ManageObjeto, 
                    EDITOR_MODE_VEHICLE_OBJECT);
            }
        }
    }
    
    return 1;
}
public OnEditorAttachVehicleAndroid(playerid, vehicleid, editor_id, response, modelid, Float:oa_POS_X, Float:oa_POS_Y, Float:oa_POS_Z, Float:oa_ROT_X, Float:oa_ROT_Y, Float:oa_ROT_Z)
{
    new inputvehicleid = GetPlayerVehicleID(playerid);
    SendClientMessage(playerid,-1, sprintf("OnEditorAttachVehicleAndroid: %d,%d,%d | %f,%f,%f - %f,%f,%f",
        vehicleid, editor_id, response,oa_POS_X,oa_POS_Y,oa_POS_Z,oa_ROT_X,oa_ROT_Y,oa_ROT_Z));
    switch(editor_id)
    {
        case EDITOR_ID_PRUEBA_1:
        {

            switch(response)
            {
                case ANDROID_EDITOR_RESPONSE_SAVE:
                {
                    if (inputvehicleid != vehicleid) SendClientMessage(playerid,-1,"Error.");
                    new Float:v_size[3];
                    GetVehicleModelInfo(GetVehicleModel( vehicleid ), VEHICLE_MODEL_INFO_SIZE, v_size[0], v_size[1], v_size[2]);
                    
 
                    if  ((oa_POS_X >= v_size[0]) || 
                        (-v_size[0] >=oa_POS_X)  ||
                        (oa_POS_Y >= v_size[1]) || 
                        (-v_size[1] >=oa_POS_Y) ||
                        (oa_POS_Z >= v_size[2]) || 
                        (-v_size[2] >=oa_POS_Z)
                        )
                    {
                        SendClientMessage(playerid, -1, "El objeto esta lejos del vehiculo.");
                        return 1;
                    }
                    //new index = SELECT_INDEX_OBJECT[ playerid ];
                    new objectid = SELECT_INDEX_OBJECT[ playerid ];//PRUEBA_EDITOR[ vehicleid ][ index ];
                    new ao_modelid,ao_txdname[ 32 ],ao_texturename[ 32 ],ao_materialcolor;
                    new SaveMaterialIndex[ 10 ],SaveMaterialModelid[ 10 ],SaveMaterialColor[ 10 ],SaveMaterialTX_Name[ 10 ][ 32 ],SaveMaterialTX_Texture[ 10 ][ 32 ];
                    new total_Creatematerial;
                    for(new i = 0; i < 10; i++)
                    {
                        if(IsDynamicObjectMaterialUsed(objectid, i))
                        {
                            GetDynamicObjectMaterial(objectid, i, ao_modelid, ao_txdname, ao_texturename, ao_materialcolor);
                            SaveMaterialIndex[ total_Creatematerial ] =  i;
                            SaveMaterialModelid[ total_Creatematerial ] = ao_modelid;
                            format(SaveMaterialTX_Name[ total_Creatematerial ], 32, ao_txdname);
                            format(SaveMaterialTX_Texture[ total_Creatematerial ], 32, ao_texturename);
                            SaveMaterialColor[ total_Creatematerial ] = ao_materialcolor;

                            total_Creatematerial++;

                        }
                    }
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
                    if(IsValidDynamicObject(objectid))
                    {
                        DestroyDynamicObject(objectid);
                        for(new i = 0; i < MAX_OBJECT_PER_VEH_AO; i ++)
                        {
                            if(AO_EDITOR[ vehicleid ][ ao_vehicleid ][ i ] == vehicleid)
                            {
                                if(AO_EDITOR[ vehicleid ][ ao_OBJECT_ID ][ i ] == objectid)
                                {
                                    if(AO_EDITOR[ vehicleid ][ ao_valid_object ][ i ])
                                    {
                                        AO_EDITOR[ vehicleid ][ ao_valid_object ][ i ] = false;
                                        AO_EDITOR[ vehicleid ][ ao_vehicleid ][ i ] = INVALID_VEHICLE_ID;
                                        AO_EDITOR[ vehicleid ][ ao_OBJECT_ID ][ i ] = INVALID_OBJECT_ID;
                                        printf("Slot: %d liberado", i);
                                                                
                                    }
                                }
                            }
                        }
                    }
                    //
                    new Float:ao_VehiclePOS[ 3 ];
                    GetVehiclePos(vehicleid, ao_VehiclePOS[ 0 ], ao_VehiclePOS[ 1 ], ao_VehiclePOS[ 2 ]);

                    objectid = CreateDynamicObject(modelid,
                        ao_VehiclePOS[ 0 ], ao_VehiclePOS[ 1 ], ao_VehiclePOS[ 2 ],0.0,0.0,0.0,-1,-1,-1,300.0,300.0);
 
                    for(new i = 0; i < total_Creatematerial; i++)
                    {
                        SetDynamicObjectMaterial(objectid, SaveMaterialIndex[ i ], SaveMaterialModelid[ i ], SaveMaterialTX_Name[ i ], SaveMaterialTX_Texture[ i ], SaveMaterialColor[ i ]);
                    }
                    for(new i = 0; i < a; i++)
                    {
                        SetDynamicObjectMaterialText( objectid, MaterialSaveText_Index[ i ], MaterialSave_Text[ i ], MaterialSave_Size[ i ],MaterialSave_FontFace[ i ],MaterialSave_Font_Size[ i ],MaterialSave_Bold[ i ],MaterialSave_FontColor[ i ],MaterialSave_BackColor[ i ],MaterialSave_TextAligment[ i ]);
                    }
 
                    AttachDynamicObjectToVehicle(objectid, vehicleid,oa_POS_X,oa_POS_Y,oa_POS_Z,oa_ROT_X,oa_ROT_Y,oa_ROT_Z);

                }
            }
            
        }
    }
    Streamer_Update(playerid);
    return 1;
}