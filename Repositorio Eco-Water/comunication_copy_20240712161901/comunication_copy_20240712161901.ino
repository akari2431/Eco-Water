#include <ESP8266WiFi.h>

const char* ssid = "HackatonUTNA"; // Nombre de tu red WiFi
const char* password = "HackatonUTNA"; // Contraseña de tu red WiFi

void setup() {
    Serial.begin(9600);
    delay(1000);

    // Conéctate a la red WiFi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Conectando a WiFi...");
    }
    Serial.println("Conexión WiFi establecida");
}

void loop() {
    // Leer datos del sensor HW-080 (por ejemplo, humedad del suelo)
    int valorHumedad = analogRead(A0);

    // Enviar datos al servidor
    String url = ": http://127.0.0.1:4943/?canisterId=bw4dl-smaaa-aaaaa-qaacq-cai&id=br5f7-7uaaa-aaaaa-qaaca-cai" + String(valorHumedad);
    Serial.print("Enviando datos a: ");
    Serial.println(url);

    // Realiza una solicitud HTTP GET
    WiFiClient client;
    if (client.connect("127.0.0.1", 4943)) {
        client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                     "Host: 127.0.0.1\r\n" +
                     "Connection: close\r\n\r\n");
        while (client.connected()) {
            if (client.available()) {
                String line = client.readStringUntil('\r');
                Serial.println(line);
            }
        }
        client.stop();
    } else {
        Serial.println("Error al conectar al servidor");
    }

    delay(10000); // Esperar 10 segundos antes de enviar más datos
}