# TurtleEngine

Este es mi proyecto para la clase de "ARQUITECTURA DE MOTORES GRAFICOS".
Este proyecto tiene como objetivo de crear un motor gráfico usando DirectX. 
El cual pueda renderizar modelos y objetos 3D en tiempo real.

![image](https://github.com/user-attachments/assets/49763516-526d-4dc5-bc3a-528d877a41b5)

# Actualización

Se optimizó el código mudando el Main a BaseApp, entre otros cambios. Además ahora los usuarios pueden controlar el 
cubo con el teclado al igual que pueden controlar la cámara con el mouse.

De la misma forma se agregó un IMGUI proporcionado por el video tutorial de: “ROBERTO CHARRETON KAPLÚN”

# Actualización Final
Esta es la actualización final de nuestro proyecto en donde ahora usted usuario… podrá interactuar con un modelo 3d sino 
que también puede exportarlo.

Para comenzar en esta actualización se eliminó el cubo antes utilizado en viejas versiones por nuevos y bonitos modelos 
3d(en formato fbx y obj. Además que estos se pueden seguir manipulando con la ventana de transform. Del mismo modo este 
programa te permite exportar los modelos 3D que tu desees permitiendo manipularlo en el programa. 

Sigue los pasos y las fotos:

Para usarlo solo debe descargar o ingresar sus modelos en las carpetas de Modelo y textura. Estos están ubicados 
en bin/x64/RESPECTIVA CARPETA (Se recomienda que uses solo fbx y obj): 

![Captura de pantalla 2025-04-28 225529](https://github.com/user-attachments/assets/4a3e4e4d-50e9-4100-8906-9253c6b85a8d)
![Captura de pantalla 2025-04-28 225610](https://github.com/user-attachments/assets/c691a17e-f684-4c42-bc42-46abd45ac124)

Para iniciar el código seleccione “TurtleEngine_2010.sln” para abrir el código. Una vez abierto vaya y seleccione 
el “BaseApp.cpp” que se ubica en su esquina derecha el la carpeta Source. Al Abrir el código deberá buscar la 
siguiente parte:

![image](https://github.com/user-attachments/assets/f8ca4a96-adb4-4ef7-8cc1-ca927583f894)
![image](https://github.com/user-attachments/assets/20db9c7e-8a40-4e96-80e1-a7f1f86db065)

Estas líneas de código son las que te permitirán exportar tus modelos. 
(Atención esta linea solo sirve con fbx en un momento explicamos en donde se abren los obj)
Solo agrega el la ubicación de tanto del modelo y de las texturas respectivas como se muestran en las imágenes:

![image](https://github.com/user-attachments/assets/235598b8-2d62-460e-8ef8-58e0e5d603a0)

En este primer ejemplo podras ver como se ve estos modelos y como puedes interactuar con ellos:

![image](https://github.com/user-attachments/assets/4a1b6c16-f420-4c49-9d01-04a9e0a82dd9)

-Adevertencia no todos los fbx saldran bien muchas de ellos tendran texturas distorcinadas-

![image](https://github.com/user-attachments/assets/6576ae14-315d-468f-be19-71e9554129b5)

Por último en las siguientes líneas comentadas están los que se encargan de cargar lo que serían los obj. 
Solo debes comentar las líneas fbx para que no afecten el funcionamiento de este (otra nota es que los obj 
suelen ser más tediosos por lo que puedes agregarlo en la misma carpeta del modelo para más facilidad. 
Otra cosa es abrir el modelo y ver que sus texturas tengan el nombre correcto y el formato que debe ser 
obligatoriamente png.)

![Captura de pantalla 2025-04-28 232306](https://github.com/user-attachments/assets/b01a0e5b-309d-411a-8b07-4ee22feffcb4)

 Y eso es todo disfrute del programa.

