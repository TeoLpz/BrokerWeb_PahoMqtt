#include <WiFi.h>
#include <PubSubClient.h>

// Update these with values suitable for your network.
const char* ssid = "KBLEX.3.169";  // Tu red     
const char* password = "58894217";  // Clave de tu red
const char *mqtt_broker = "broker.emqx.io";  
//const char *mqtt_broker = "test.mosquitto.org";  
const int mqttPort = 1884;
const char *topic = "UTP"; // Tu topico de conexión
int led = 2;  

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
   delay(100);
  // Conexion a la red desde el esp32
    Serial.print("Conectando a ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) 
    {
      delay(500);
      Serial.print(".");
    }
  randomSeed(micros());
  Serial.println("");
  Serial.println("WiFi conectado!");
  Serial.println("Direccion IP: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) 
{
  Serial.print("Topico tomado desde MQTT : [");
  Serial.print(topic);
  Serial.print("]");
  int p =(char)payload[0]-'0';
  // Si MQTT retorna un 0, entonces APAGUE EL LED
  if(p==0) 
  {
     digitalWrite(led, LOW); 
    Serial.println(" LED Apagado! " );
  } 
  // Si MQTT retorna un 1, entonces ENCIENDA EL LED
  if(p==1)
  {
     digitalWrite(led, HIGH);
    Serial.println(" LED Encendido! " );
  }
  Serial.println();
} //end callback

void reconnect() {
  // En caso de perder conexion wifi este reintenta reconectar
  while (!client.connected()) 
  {
    Serial.print("Preparando la conexión MQTT ...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    //if you MQTT broker has clientID,username and password
    //please change following line to    if (client.connect(clientId,userName,passWord))
    if (client.connect(clientId.c_str()))
    {
      Serial.println(" Ya estas conectado!");
     // Si mqtt se conecta, imprime el mensaje, sino, imprime el fallo
      client.subscribe("UTP"); // Tu topico de conexión
       client.publish(topic, "Hola desde ESP32"); 
    } else {
      Serial.print("Fallo la conexión, rc=");
      Serial.print(client.state());
      Serial.println(" Reintentando conectar...");
      // En caso de perder conexion, reintentar cada 6 segundos la reconexion
      delay(6000);
    }
  }
} //end reconnect()

// Conexion del puerto broker de mqtt
void setup() {
  Serial.begin(9600);
  setup_wifi();
  client.setServer(mqtt_broker, 1883);
  client.setCallback(callback);
  pinMode(led, OUTPUT);
 digitalWrite(led, LOW); 
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

}
