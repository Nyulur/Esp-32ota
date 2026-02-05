# ESP32 Web OTA + GitHub Actions

Ez a projekt egy ESP32-alapú firmware fejlesztési és frissítési környezetet valósít meg,
amely **PC nélkül**, kizárólag **böngészőből (pl. iPad)** használható.

A cél egy letisztult, megbízható OTA (Over-The-Air) frissítési folyamat kialakítása,
GitHub Actions alapú automatikus firmware buildeléssel.

---

## Fő funkciók

- 🌐 ESP32 Web OTA frissítés böngészőn keresztül
- 🔁 Automatikus firmware fordítás GitHub Actions segítségével
- 📦 Letölthető `firmware.bin` minden commit után
- 📱 Teljes fejlesztési workflow iPadről / táblagépről
- ⚙️ PlatformIO + Arduino framework

---

## Könyvtárstruktúra
Esp-32ota
├─ .github/workflows
│  └─ build.yml          # GitHub Actions firmware build
├─ src
│  └─ main.cpp           # ESP32 firmware (Web OTA)
├─ platformio.ini        # PlatformIO konfiguráció
└─ README.md
---

## OTA frissítés menete (ESP32 oldalon)

1. ESP32 elindul
2. WiFi-re csatlakozik (vagy AP módba lép)
3. Böngészőben megnyitható:
4. http://<ESP_IP>/update
5. 4. `firmware.bin` feltöltése
5. Automatikus újraindítás

---

## Firmware build (GitHub Actions)

Minden `main` ágra történő commit esetén:

1. GitHub Actions lefut
2. PlatformIO lefordítja a projektet
3. Elkészül a `firmware.bin`
4. A bin fájl letölthető az **Actions → Artifacts** részből

Ez a fájl közvetlenül használható az ESP32 OTA felületén.

---

## Követelmények

- ESP32 (Arduino framework)
- GitHub fiók
- Böngésző (Safari / Chrome)
- PlatformIO (csak a buildhez, GitHub Actions intézi)

---

## Megjegyzések / Tervek

- Jelszavas OTA védelem
- Verziószám megjelenítése a webes felületen
- Több ESP32 kezelése
- RC / iBUS / FOC ESC integráció

---

## Licenc

Szabadon felhasználható, módosítható, saját projektekhez 
