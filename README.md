https://prnt.sc/1NuUkGFV3HAR

<img width="540" alt="Screenshot_2" src="https://github.com/BigSmokebb/android_object_editor_vehicle/assets/104103838/377997ca-d8da-42ca-bcf9-ae6153e752f9">
<img width="952" alt="Screenshot_3" src="https://github.com/BigSmokebb/android_object_editor_vehicle/assets/104103838/2c156e51-31ca-4e9d-9a03-c40be13ae70f">
# android_object_editor_vehicle
Editor de objetos para el vehiculo en android.

descripción de las funciones y bloques del código:

1. **Función `EditDynamicAndroidObject`:** Esta función permite a un jugador editar un objeto dinámico en el juego. Toma como parámetros el ID del jugador, el ID del vehiculo, el ID del editor, el ID del objeto y el modo de edición. Dependiendo del modo de edición, la función recupera la posición y la rotación del objeto o del vehículo y las guarda en `ao_PLAYER_SAVE_EDITOR`. Luego, si el jugador está en un vehículo, se crea un nuevo objeto en la posición calculada y se adjunta al vehículo. Finalmente, se copian los materiales y textos del objeto original al nuevo objeto.

2. **Función `oa_StartEditorAndroid`:** Esta función muestra el editor al jugador. Configura y muestra varios `PlayerTextDraws` y `TextDraws` para proporcionar una interfaz de usuario en el juego para la edición de objetos.

3. **Función `oa_HideEditorAndroid`:** Esta función oculta el editor del jugador. Destruye el objeto temporal del jugador y oculta todos los `PlayerTextDraws` y `TextDraws` del editor.

4. **Función `AttachDynamicObjectToVehicleEx`:** Esta función es una versión extendida de la función `AttachDynamicObjectToVehicle` de SA-MP. Permite adjuntar un objeto dinámico a un vehículo con una rotación especificada. También guarda el ID del objeto y del vehículo en el array `Streamer`.

5. **Comando `editor`:** Este comando muestra al jugador una lista de objetos adjuntos a su vehículo actual. Itera sobre todos los objetos posibles y comprueba si están adjuntos al vehículo del jugador. Si es así, añade el objeto a una lista de diálogo que luego se muestra al jugador.

6. **Función `OnDialogResponse`:** Esta función se invoca cuando un jugador responde a un diálogo. Si el diálogo es el diálogo de la lista de objetos (DIALOGO_PRUEBA), la función inicia el editor para el objeto seleccionado.

7. **Función `OnEditorAttachVehicleAndroid`:** Esta función se invoca cuando un jugador termina de editar un objeto. Dependiendo de la respuesta del jugador, la función puede actualizar la posición y la rotación del objeto en el vehículo.

- Por favor si vas a usar este sistema agregar los respectivos creditos de su creador.

El sistema no ha sido testeado en su totalidad con jugadores en android, por favor contactarme por discord "bigsmoke_bb" si ves un bug y poder arreglarlo.

Nota:
El editor de objetos para vehículos está diseñado para funcionar con cualquier vehículo que tenga objetos adjuntos. Esto significa que no importa si los objetos fueron añadidos por un jugador o si el vehículo con objetos es parte del servidor, el editor puede seleccionar y permitir la edición de todos los objetos que estén adjuntos al vehículo.

Sin embargo, si tienes vehículos en el servidor que ya tienen objetos adjuntos, tendrás que gestionar esa parte por tu cuenta. Esto es para evitar que los jugadores editen los objetos que no deberían ser editables. En otras palabras, tendrás que implementar medidas adicionales para proteger los objetos de los vehículos del servidor de ser editados por los jugadores.
