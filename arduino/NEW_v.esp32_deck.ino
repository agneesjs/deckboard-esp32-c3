#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>
#include <WiFi.h>      // Potrzebne do wyłączenia WiFi
#include <esp_bt.h>    // Do zarządzania energią Bluetooth

// Unikalne identyfikatory Twojej usługi
#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

// Funkcja wywoływana, gdy telefon wysyła komendę
class MyCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
      std::string value = pCharacteristic->getValue();
      if (value.length() > 0) {
        String cmd = "";
        for (int i = 0; i < value.length(); i++) {
          // Filtrujemy tylko znaki czytelne (ASCII)
          if (value[i] >= 32 && value[i] <= 126) cmd += (char)value[i];
        }
        Serial.println(cmd); 
      }
    }
};

void setup() {
  // 1. Zmniejszenie taktowania procesora do 80MHz (oszczędza energię i chłodzi płytkę)
  setCpuFrequencyMhz(80);
  
  Serial.begin(115200);

  // 2. Całkowite wyłączenie modułu WiFi (ESP32-C3 domyślnie go zasila)
  WiFi.mode(WIFI_OFF);
  btStop(); // Reset BT na start
  delay(100);
  btStart(); // Włącz tylko BT

  // 3. Konfiguracja Bluetooth Low Energy (BLE)
  BLEDevice::init("Agneesjs_Deck");
  
  // Opcjonalnie: Zmniejszenie mocy nadawania (Tx Power), aby jeszcze bardziej ograniczyć ciepło
  // ESP_PWR_LVL_P3 to ok. +3dBm (wystarczy na pokój)
  esp_ble_tx_power_set(ESP_BLE_PWR_TYPE_DEFAULT, ESP_PWR_LVL_P3);

  BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(SERVICE_UUID);
  
  BLECharacteristic *pChar = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_WRITE
                                       );

  pChar->setCallbacks(new MyCallbacks());
  pService->start();

  // Rozpoczęcie rozgłaszania sygnału
  BLEDevice::startAdvertising();
  
  Serial.println(">>> AGNEESJS DECK: GOTOWY I CHŁODNY <<<");
}

void loop() {
  // 4. Bardzo ważne: delay pozwala procesorowi "odpocząć"
  // Przy 100ms opóźnienie w reakcji przycisków jest niezauważalne, 
  // a temperatura spada o kilka/kilkanaście stopni.
  delay(100);
}
