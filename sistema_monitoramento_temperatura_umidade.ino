#include <WiFi.h>
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define WIFI_SSID "rede_wifi"
#define WIFI_PASS "senha_wifi"

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883
#define AIO_USERNAME    "usuário_adafruit"
#define AIO_KEY         "chave_adafruit"

#define DHTPIN 26   
#define RELAYPIN 23 

#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);
Adafruit_MQTT_Publish temperaturaPub = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/temperatura");
Adafruit_MQTT_Publish umidadePub = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/umidade");
Adafruit_MQTT_Subscribe relayControl = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/relaycontrol");

void setup() {
  Serial.begin(115200);
  
  Serial.print("Conectando ao WiFi...");
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Conectado!");

  dht.begin();
  
  pinMode(RELAYPIN, OUTPUT);
  
  mqtt.subscribe(&relayControl);

}

void loop() {
  MQTT_connect();
  
  float temperatura = dht.readTemperature();
  float umidade = dht.readHumidity();
  
  if (isnan(temperatura) || isnan(umidade)) {
    Serial.println("Falha na leitura do sensor DHT!");
    return;
  }
  
  if (!temperaturaPub.publish(temperatura)) {
    Serial.println("Falha ao publicar a temperatura.");
  }
  if (!umidadePub.publish(umidade)) {
    Serial.println("Falha ao publicar a umidade.");
  }

  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.println(" °C");
  
  Serial.print("Umidade: ");
  Serial.print(umidade);
  Serial.println(" %");
  
  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(5000))) {
    if (subscription == &relayControl) {
      if (strcmp((char *)relayControl.lastread, "ON") == 0) {
        digitalWrite(RELAYPIN, LOW);
        Serial.println("Relé ligado.");
      } else if (strcmp((char *)relayControl.lastread, "OFF") == 0) {
        digitalWrite(RELAYPIN, HIGH);
        Serial.println("Relé desligado.");
      }
    }
  }

  if (temperatura > 30) {
    digitalWrite(RELAYPIN, LOW);
    Serial.println("Temperatura alta! Relé ativado.");
  } else {
    digitalWrite(RELAYPIN, HIGH);
  }

  delay(3000);
}

void MQTT_connect() {
  int8_t ret;

  if (mqtt.connected()) {
    return;
  }

  Serial.print("Conectando ao MQTT... ");
  while ((ret = mqtt.connect()) != 0) {
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Tentando reconectar ao MQTT em 5 segundos...");
    delay(5000);
  }
  Serial.println("Conectado ao MQTT!");
}