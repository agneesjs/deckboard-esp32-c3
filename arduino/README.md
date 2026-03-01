# ⚙️ Kody dla ESP32-C3

W tym folderze znajdują się dwie wersje oprogramowania:

1. **v1_basic.ino** – Podstawowa wersja kodu (może powodować nagrzewanie się płytki).
2. **v2_optimized.ino** – Wersja zoptymalizowana:
   - Obniżone taktowanie procesora (80MHz).
   - Wyłączone moduły WiFi (mniejszy pobór prądu).
   - Dodane opóźnienia `delay()`, które chłodzą układ.

⚠️ **Uwaga:** Przy wgrywaniu wersji v2 wybierz w Arduino IDE: 
`Tools` -> `Partition Scheme` -> `Huge APP (3MB No OTA)`.
