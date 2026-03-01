# deckboard-esp32-c3

# 🚀 Agneesjs Deck
DIY Stream Deck sterowany przez Bluetooth z iPhone'a (Bluefy).

## 📁 Struktura
- `index.html` - Panel sterowania (GitHub Pages).
- `arduino/` - Kod dla ESP32.
- `python/` - Skrypt odbiorczy dla Linux Mint XFCE.

## ⚙️ Instalacja
1. Wgraj kod z folderu `arduino/` na płytkę ESP32.
2. Na laptopie zainstaluj: `pip install pyserial --break-system-packages`.
3. Uruchom skrypt: `python3 python/deck_listener.py --break-system-packages`.
4. Otwórz stronę projektu w Bluefy i połącz się z **Agneesjs_Deck**.

## ⌨️ Funkcje
- **Matrix ON/OFF** - Zielony deszcz znaków.
- **Lock** - Szybka blokada ekranu.
