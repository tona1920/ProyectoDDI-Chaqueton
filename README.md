# ProyectoDDI-P 
'CHAQUETON'
## Objetivo del proyecto
EL chaquetón es un proyecto que ofrece brindarle una experiencia de seguridad al usuario que lo utilice, con distintos tipos de seguridad al transitar en caminos, carreteras entre otros.
El chaquetón permite saber tu ritmo cardiaco en caso de que te sientas mal (mareado, cansado) podrás medir tu ritmo cardiaco para descartar o tener conocimientos si es tu corazón.
El chaquetón permite avisar a los conductores de vehículos a donde vas a girar en caso de hacerlo por medio de leds color amarillo simulando las direccionales de los autos así mismo advierte cuando están demasiado cerca encendiendo leds en color rojo simulando las calaveras de los autos.
La secretaria de Movilidad de la Ciudad de México, señaló que en el primer trimestre del 2022 hubo 582 ciclistas accidentados. El chaquetón busca la prevención y eliminación en medida de lo posible de estos accidentes.

## Integrantes
- Jessy Javier Araiza Cervantes
- Cristian Israel Buclon Pedroza
- Jorge Alejandro Rico Arvizu
- Gerardo Tonathiu Rojas Torres 

## Beneficiario
- Papa del cristian (Ingeniero en traslado y entrega de correspondencia)

## Hardware
| Num. | Componente | Descripción | Imagen | Costo | Cantidad | 
|------|------------|-------------|--------|-------|----------|
| 1 | Raspberry Pi 4 | Microcomputador reciente  |<img src='https://github.com/tona1920/ProyectoDDI-P/assets/88992807/7ec91669-392b-483c-943a-8270fcdaeb79' width="200px"/>| $2500.00 | 1 |
|2|LVGL|Pantalla inteligente|<img src='https://github.com/tona1920/ProyectoDDI-P/assets/97042086/62956cd8-4f82-4beb-a9b5-c7e6aa76097e' width="200px"/>|200.00|1|
|3|GY-NEO6MV3|Sensor GPS|<img src='https://github.com/tona1920/ProyectoDDI-P/assets/97042086/0053050a-98e4-4cb0-a671-4d14cfc2b9e2' width="200px"/>|177.00|1|
|4|Modulo DHT11| Sensor temperatura y humedad|<img src='https://github.com/tona1920/ProyectoDDI-P/assets/97042086/bf8e3d5d-9c6e-4dbe-a56b-0bd0ffae030e' width="200px"/>|77.00|1|
|5|Modulo HC-SR04| Sensor Proximidad |<img src='https://github.com/tona1920/ProyectoDDI-P/assets/97042086/6f98139e-898d-402e-a6cf-43ef3d4571e6' width="200px"/>|60.00|1|
|6|Modulo Pulso Cardiaco| Sensor de pulso cardiaco |<img src='https://github.com/tona1920/ProyectoDDI-P/assets/97042086/1259c34f-25b0-4e0a-aa47-abf83db7b710' width="200px"/>|110.00|1|
|7|Led| Led |<img src='https://github.com/tona1920/ProyectoDDI-P/assets/97042086/3f7b4685-80e4-4b65-8504-1a14e64aaa51' width="200px"/>|10.00|1|
|8|Buzzer| Buzzer |<img src='https://github.com/tona1920/ProyectoDDI-P/assets/97042086/6997eafb-f849-4b54-9c4c-5bbc5f37a5fb' width="200px"/>|40.00|1|


## Tabla de Software utilizado
| Id | Software | Version | Tipo |
|----|----------|---------|------|
|  1  |  Node Red  |  3.0.2   |  Dasboard  |
|  2  |  MicroPyton |   3.11.3   |    Lenguaje de programacion  |
|  3  |  MySQL   |      5.2.1     |   Almacenar datos (Base de datos)   |
| 4  | Raspberry Pi OS |  11   |   Sistema operativvo de Raspberry  |
|  5  | MQTT |  5.0 | Protocolo de comunicacion |

## Tabla de historias de usuario
| Id | Historia de usuario | Prioridad | Estimación | Como probarlo | Responsable |
|----|---------------------|-----------|------------|---------------|-------------|
|  HU01  |  Yo como ciclista quiero que el dispositivo me proporcione la frecuencia cardiaca IPM. Para tener conocimiento de estas mientras estoy realizando mis actividades.   |  Debe Hacerse | 4 | El ciclista debe colocarse la prenda inteligente (chaquetón) y presionar un botón,en la pantalla inteligente, para que este le muestre por medio del display de la pantalla inteligente su IPM | Jessy |
|  HU02  |  Yo como ciclista quiero que el dispositivo me proporcione mi ubicación en tiempo real. Para tener nocion de donde me situo. | Debe Hacerse |  4  |  El ciclista debe colocarse la prenda inteligente (chaquetón) y presionar un botón en la pantalla inteligente, para que este le muestre por medio del display de la pantalla inteligente sus coordenadas  | Cristian |
|  HU03  | Yo como ciclista quiero que el dispositivo me proporcione la humedad y temperatura a la que se encuetra el ambiente. Para tener conocimiento sobre que vestimenta puedo usar y que rutas puedo tomar. | Debe Hacerse | 4 |  El ciclista debe colocarse la prenda inteligente (chaquetón) y presionar un botón en la pantalla inteligente, para que este le muestre por medio del display de la pantalla inteligente la temperatura y humedad actual  |   Jorge     |
|  HU04  | Yo como ciclista quiero avisar a los autos que se encuentren atrás de mí. Para que mientras yo tránsito en mi bicicleta,  se pueda ser apreciado a donde me dirijo con luces intermitentes, que cuyo acceso sea sencillo. | Debe Hacerce  |   4    |  El ciclista debe colocarse la prenda inteligente (chaquetón) para despues precionar un boton que salga de la manga o algun acceso facil, este debera dejarse precionado asta que se desee dejar de dar la señal.    |  Tona    |
|  HU05  |  Yo como ciclista me gustaria que de alguna manera las mismas luces, enciendan de color rojo en dado caso que un auto se acercace demaciado a mi.                  |  Podria Hacerse       |    6    |  Yo como ciclista quiero que otras luces enciendan de color rojo. Para en dado caso que un auto se acercace demaciado a mi.            |       Cristian      |
|  HU06  |  Yo como ciclista requiero en caso de estar en una situación de peligro mandar mi ubicación a un contacto de emergencia. Para que mis familiares me puedan auxiliar más fácil en caso de necesitar ayuda.  | Podría Hacerse  |   8    |  El ciclista debe colocarse la prenda inteligente (chaquetón) para después presionar un botón que salga de la manga o algún acceso fácil, este deberá presionar un botón para mandar un mensaje con la ubicación del ciclista a algún contacto de emergencia.  |   Jorge   |
|  HU07  | Yo como ciclista quiero que el dispositivo me muestre la temperatura corporal que tengo. Para tener conocimiento de mi estado de salud y evitar el riesgo de deshidratación, insolación o un golpe de calor. |Podría Hacerce  |   4    |  El ciclista debe colocarse la prenda inteligente (chaquetón) y presionar un botón en la pantalla inteligente, para que este le muestre por medio del display de la pantalla inteligente la temperatura corporal actual.  | Tona   |
|  HU08  | Yo como ciclista quiero que el dispositivo me muestre la hora real. Para poder planificar mis rutas a tomar, descansos y parada, sin que afecte mis tiempos estimados | Podría hacerse| 5 | El ciclista debe colocarse la prenda inteligente (chaquetón) para después presionar un botón, este deberá presionar un botón para mandar un mensaje con la hora en tiempo real |Jessy|
## Prototipo en dibujo
![image](https://github.com/tona1920/ProyectoDDI-P/assets/97042086/7e276b2f-d920-4681-b061-3b69453b720d)

## Prototipo en Fitzing
![image](https://github.com/tona1920/ProyectoDDI-P/assets/97042086/c9466974-e3c4-44bc-824b-075609255ab0)

## Placa PCB
![image](https://github.com/tona1920/ProyectoDDI-P/assets/97042086/bfb91e7a-367d-4f06-aa8c-03aebb169db6)

## Modelado 3D
https://www.tinkercad.com/things/8LRIvwNC0sq-frantic-albar/edit?sharecode=_havVZ2Vmezt7P5Z318VvKj5t1hMpyFZkGJieAYW2w0

![image](https://github.com/tona1920/ProyectoDDI-P/assets/90641445/68293f99-57f4-436b-a7f4-b81e9e4188d6)

![image](https://github.com/tona1920/ProyectoDDI-P/assets/90641445/f5e1c3d5-d21b-4154-ae04-e0807d225320)
