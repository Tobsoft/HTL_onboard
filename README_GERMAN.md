# HTL_onboard-Bibliothek
Die HTL_onboard Bibliothek bietet Funktionen zur Steuerung der onboard Hardwarekomponenten der HTL Uno Entwicklungsplatine, einschließlich HEX Display, LED Streifen, RGB LED, Schalter und Potentiometer.

[English Version](README.md)

## Installation
### Installation über den Arduino Library Manager
1. Öffne die Arduino IDE.
2. Navigiere zu **Sketch > Include Library > Manage Libraries...** Dies öffnet den Library Manager.
3. Gebe in der Suchleiste "HTL_onboard" ein und drücke die Enter.
4. Suchen Sie in den Suchergebnissen nach der Bibliothek "HTL_onboard".
5. Klicke auf die Schaltfläche "Installieren", um die Bibliothek zu installieren.
6. Schließe nach Abschluss der Installation den Bibliotheksmanager.
7. Du kannst nun die HTL_onboard-Bibliothek in deine Programme einbinden, indem du oben "#include <HTL_onboard.h>" eingiebst.

### Installation per .zip-Datei
1. Lade die HTL_onboard-Bibliothek (.zip) aus dem [HTL_onboard github repository](https://github.com/Tobsoft/HTL_onboard) herunter.
2. Füge die Bibliothek zu deiner Arduino IDE hinzu, indem du zu Sketch > Include Library > Add .ZIP Library... navigierst und die heruntergeladene ZIP-Datei auswählst.

## Verwendung
## Initialisierung
```cpp
#include <HTL_onboard.h>

HTL_onboard onboard;

void setup() {
    onboard.begin();
}
```
## Beispiel-Programme

*Für weitere Beispiele siehe Datei > Beispiele > Beispiele aus benutzerdefinierten Bibliotheken > HTL_onboard in der Arduino IDE*

### Binäres Zählen auf LED-Streifen
```cpp
#include <HTL_onboard.h>

HTL_onboard ledStripe;

void setup() {
    // Initialisieren des LED-Streifens
    ledStripe.begin();
}

void loop() {
    // Zählen in Binärform von 0 bis 1023
    for (int i = 0; i < 1024; i++) {
        ledStripe.writeBinary(i);
        delay(50); // Verzögerung für 0,05 Sekunden (50ms)
    }
}
```

### Dezimaler und hexadezimaler Zähler auf dem HEX-Feld
```cpp
#include <HTL_onboard.h>

HTL_onboard hexPanel;

void setup() {
    // Initialisieren des Hex-Feldes
    hexPanel.begin();
}

void loop() {
    // Anzeige der Hexadezimalzahlen von -F bis F
    for (int i = -15; i <= 15; i++) {
        hexPanel.writeHex(i);
        delay(500); // Verzögerung für 0,5 Sekunden
    }

    // Ganzzahlige Werte von -19 bis 19 anzeigen
    for (int i = -19; i <= 19; i++) {
      hexPanel.writeInt(i);
      delay(500);
    }
}
```

### Schalterzustände lesen
```cpp
#include <HTL_onboard.h>

HTL_onboard switchReader;

void setup() {
    Serial.begin(9600);
    switchReader.begin();
}

void loop() {
    // Den Zustand der Schalter auslesen
    int switchState = switchReader.readSwitchState();

    // Ausgeben des Schalterstatus über den Seriellen Monitor
    if (switchState == 3) {
        Serial.println("Schalter 3 ist aktiv");
    } else if (switchState == 2) {
        Serial.println("Schalter 2 ist aktiv");
    } else if (switchState == 1) {
        Serial.println("Beide Schalter sind aktiv");
    } else {
        Serial.println("Keine Schalter sind aktiv");
    }

    Serial.println(analogRead(A1));

    delay(1000); // Verzögerung für 1 Sekunde
}
```

## Multiplexen

Die Bibliothek HTL_onboard unterstützt Multiplexing, so dass du in regelmäßigen Abständen verschiedene Anzeigemodi (HEX-Anzeige, LED-Streifen, RGB-LED) durchlaufen kannst. In diesem Abschnitt erfährst du, wie du die von der Bibliothek bereitgestellten Multiplexing-Methoden nutzen kannst.

### Multiplexing einrichten

Gehe folgendermaßen vor, um Multiplexing zu verwenden:

1. **Initialisieren Sie die Bibliothek**: Beginne mit der Initialisierung der HTL_onboard-Bibliothek mit der Methode `begin()`.

    ```cpp
    onboard.begin();
    ```

2. **Definieren Sie die aktiven Modi**: Definieren Sie eine Reihe von aktiven Modi, die du während des Multiplexens durchlaufen willst. Jeder Modus wird durch einen Integer-Wert dargestellt: 0 für HEX-Anzeige, 1 für LED-Streifen und 2 für RGB-LED. Du kannst auch die vordefinierten Makros MODE_HEX, MODE_RGB und MODE_STRIPE verwenden.

    ```cpp
    int activeModes[] = {MODE_HEX, MODE_RGB, MODE_STRIPE};
    ```

3. **Multiplexing-Modi einstellen**: Verwende die Methode `setModesMultiplex()`, um die aktiven Modi für das Multiplexing zu setzen.

    ```cpp
    onboard.setModesMultiplex(activeModes, 3);
    ```

4. **Multiplex-Intervall festlegen**: Gebe mit der Methode `setMultiplexInterval()` das Intervall in Millisekunden an, in dem das System die verschiedenen aktiven Anzeigemodi durchläuft. Das angegebene Intervall muss eine nicht-negative Ganzzahl sein.

    ```cpp
    onboard.setMultiplexInterval(5); // Intervall auf 5ms setzen
    ```

### Multiplexing aktualisieren

Nachdem du das Multiplexing eingerichtet hast, musst du regelmäßig die Methode `updateMultiplex()` innerhalb der Funktion `loop()` aufrufen, um die aktiven Anzeigemodi zu durchlaufen. Dies gewährleistet einen reibungslosen Übergang zwischen den verschiedenen Modi.

```cpp
void loop() {
    onboard.updateMultiplex();
}
```

**Hinweis:** Um Werte im Multiplex-Modus zu ändern, wird empfohlen, **die von der Bibliothek bereitgestellten Setter** zu verwenden, z. B. setHexNumber() anstelle von writeHex(). Dadurch wird sichergestellt, dass die Werte innerhalb des Multiplexing-Frameworks korrekt aktualisiert und angezeigt werden.
```cpp
// Korrekter Weg zum Setzen der HEX-Zahl im Multiplex-Modus
onboard.setHexNumber(10);

// Korrekter Weg, um den Wert der LED-Streifen im Multiplex-Modus zu setzen
onboard.setLedStripeValue(512);

// Korrekte Einstellung der RGB-Werte im Multiplex-Modus
onboard.setRed(255);
onboard.setGreen(255);
onboard.setBlue(255);

// Oder Benutze "setRGB_Multiplex"
onboard.setRGB_Multiplex(255, 255, 255);
```


## Dokumentation

### HTL_onboard Klasse

Die Klasse "HTL_onboard" ermöglicht die Steuerung verschiedener Onboard-Hardwarekomponenten der HTL Uno, einschließlich eines HEX-Displays, eines LED-Streifens und einer RGB-LED. Sie bietet Methoden zur Anzeige von Werten, zur Steuerung von LEDs, zur Einstellung von Farben, zum Auslesen von Schaltern und Potentiometerwerten und zur Verwaltung von Anzeigemodi. Die Klasse unterstützt den Multiplex-Betrieb.

#### Öffentliche Methoden

- HTL_onboard()`
  - Konstruktor für die Initialisierung der HTL_onboard-Bibliothek.

- `void begin()`
  - Initialisiert die Bibliothek und richtet Pin-Modi für alle notwendigen Pins ein.

- `void writeHex(int8_t hexNumber)`
  - Schreibt eine hexadezimale Zahl (-15 bis 15) in die HEX-Anzeige.

- `void writeInt(int8_t intZahl)`
  - Schreibt eine Ganzzahl (-19 bis 19) in die HEX-Anzeige.

- `void writeChar(char c)`
  - Zeigt ein Zeichen auf der 7-Segment-Anzeige an.

- `void writeBinary(int binValue)`
  - Schreibt einen Binärwert (0 bis 1023) auf den LED-Streifen.

- `void setLED(int pin)`
  - Setzt eine bestimmte LED (0 bis 9) auf dem LED-Streifen.

- `void clearLED(int pin)`
  - Löscht eine bestimmte LED (0 bis 9) auf dem LED-Streifen.

- `void clearStripe()`
  - Löscht alle LEDs auf dem LED-Streifen.

- `void setRGB(uint8_t rot, uint8_t grün, uint8_t blau)`
  - Setzt die RGB-LED auf die angegebene Farbe (0 bis 255 für jede Komponente).

- `int readSwitchState()`
  - Liest den Zustand der Schalter und gibt zurück:
    - `2`, wenn Schalter 2 gedrückt ist,
    - `3`, wenn Schalter 3 gedrückt ist,
    - `1`, wenn beide Schalter gedrückt sind,
    - `0`, wenn kein Schalter gedrückt ist.

- `int readPot()`
  - Liest den Wert des Potentiometers ein (0-1023).

- `void setMode(int mode, bool state)`
  - Setzt den Modus der HTL_onboard Klasse (0 für HEX, 1 für LED-Streifen, 2 für RGB).

- `void cfgSwitches(int switch1Threshold, int switchNoneThreshold, int switch12Threshold)`
  - Konfiguriert die Schwellenwerte für die Schalterzustände.

- `void updateMultiplex()`
  - Aktualisiert alle Anzeigen. Sollte in der Funktion `loop()` aufgerufen werden.

- `void setModesMultiplex(const int modes[], int size)`
  - Setzt die im Multiplexbetrieb verwendeten Modi (0 für HEX, 1 für LED-Streifen, 2 für RGB).

- `void setMultiplexInterval(int multiplexInterval)`
  - Legt das Intervall (in Millisekunden) für das Multiplexen zwischen verschiedenen Anzeigemodi fest.

- `void setHexMode(int mode)`
  - Setzt den Anzeigemodus der HEX-Anzeige (0 für HEX, 1 für Dezimal, 2 für Character).

- `int getHexMode()`
  - Ruft den aktuellen Anzeigemodus der HEX-Anzeige ab.

- `void setHexNumber(int number)`
  - Setzt die Zahl, die auf dem HEX-Display angezeigt werden soll (-15 bis 15 im HEX-Modus, -19 bis 19 im Dezimal-Modus).

- `int getHexNumber()`
  - Ruft die aktuell auf dem HEX-Display angezeigte Zahl/Zeichen ab.

- `void setChar(char c)`
  - Setzt das Zeichen, das auf dem HEX-Display angezeigt werden soll.

- `void setString(String str)`
  - Legt die auf der HEX-Anzeige anzuzeigende Zeichenkette fest.

- `String getString()`
  - Ruft die aktuell auf dem HEX-Display angezeigte Zeichenkette ab.

- `void setRGB_Multiplex(uint8_t red, uint8_t green, uint8_t blue)`
  - Setzt die im Multiplex Modus verwendete Farbe der RGB-LED (0 bis 255 für jede Komponente).

- `void setRed(uint8_t r)`
  - Setzt die Intensität der roten Komponente der RGB-LED (0 bis 255).

- `void setGreen(uint8_t g)`
  - Legt die Intensität der grünen Komponente der RGB-LED fest (0 bis 255).

- `void setBlue(uint8_t b)`
  - Setzt die Intensität der blauen Komponente der RGB-LED (0 bis 255).

- `uint8_t getRed()`
  - Liefert die Intensität der roten Komponente der RGB-LED.

- uint8_t getGreen()`
  - Liefert die Intensität der grünen Komponente der RGB-LED.

- uint8_t getBlue()`
  - Liefert die Intensität der Blaukomponente der RGB-LED.

- `void setStringDelay(int stringDelay)`
  - Setzt die Verzögerung (in Millisekunden) für die Anzeige jedes Zeichens im String-Anzeigemodus.

- `int getStringDelay()`
  - Ermittelt die aktuelle Verzögerung (in Millisekunden) für die Anzeige jedes Zeichens im String-Anzeigemodus.

- `void setLedStripeValue(int value)`
  - Setzt den Wert (0 bis 1023) des LED-Streifens.

- `int getLedStripeValue()`
  - Ruft den aktuellen Wert (0 bis 1023) des LED-Streifens ab.

## Autor
Tobias Weich, 2024