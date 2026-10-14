# 🕹️ AVR Breakout Controller — Hardware & Software Engine

A full-stack embedded game project featuring a hardware physics engine running on an **8-bit AVR ATmega32** microcontroller, interfaced with a desktop renderer written in **Python (Pygame)** via a custom **UART telemetry protocol**.

---

## 🏛️ System Architecture

The core philosophy of this project is a strict separation of concerns: **the microcontroller is the "brain" of the game, while the PC acts purely as a display unit and controller interface.**

```
               DESKTOP PC
     ┌───────────────────────────┐
     │      Python / Pygame      │
     │                           │
     │   - Graphical Rendering   │
     │   - Keyboard Event Listen │
     │   - UI State Overlays     │
     └─────────────┬─────────────┘
                   │
              UART (USB-TTL)
             115200 baud, 8N1
                   │
                   ▼
     ┌───────────────────────────┐
     │      AVR ATmega32         │
     │                           │
     │   - Hardware Timer (CTC)  │
     │   - Finite State Machine  │
     │   - Ball & Paddle Physics │
     │   - Block Collision Engine│
     │   - Telemetry Streamer    │
     └───────────────────────────┘
```

---

## ✨ Key Features

* **Real-Time Embedded Engine:** Non-blocking event loop driven by Hardware **Timer 1** CTC interrupts running at a precise tick rate.
* **Hardware Physics & Collision Detection:**
  * Sub-pixel boundary checks for paddle and wall bounces.
  * Directional edge-detection for block collisions (determines horizontal vs. vertical bounce vectors).
  * Variable ball trajectory and bounding box calculation.
* **Custom Serial Telemetry Protocol:** Real-time data streaming over UART (115200 baud) conveying ball coordinates (`BALL:x,y`), paddle position (`PADDLE:x`), block matrix state (`BLOCKS:1010...`), and system state changes (`STATE:n`).
* **Finite State Machine (FSM):** Complete game life-cycle managed entirely in C on the MCU (`GAME_MENU`, `GAME_RUNNING`, `GAME_PAUSED`, `GAME_OVER`, `GAME_WIN`).
* **Pygame Visualizer:** Python frontend that decodes serial telemetry on a dedicated non-blocking buffer thread and maps virtual 100x100 MCU coordinates to a 600x600 px desktop screen.

---

## 🛠️ Hardware & Tools

* **Microcontroller:** Atmel ATmega32 (8-bit AVR, 11.0592 MHz external crystal for **0% UART error rate**)
* **Programmer:** USBasp
* **Toolchain:** `avr-gcc`, `avr-libc`, `make`
* **IDE / Workspace:** Eclipse IDE for AVR Developers
* **PC Requirements:** Python 3.x, `pygame`, `pyserial`

---

## 📁 Project Structure

```text
AVR_BREAKOUT/
├── ball.c / ball.h          # Ball physics, movement & collision triggers
├── blocks.c / blocks.h      # Block matrix state & directional collision algorithms
├── paddle.c / paddle.h      # Paddle movement & bounds validation
├── game.c / game.h          # Finite State Machine & game reset logic
├── timer.c / timer.h        # Timer1 CTC mode setup & interrupt handling (100 Hz tick)
├── uart.c / uart.h          # Hardware USART driver & string streaming functions
├── main.c                   # Main non-blocking system loop
└── pc/
    └── controller.py        # Pygame renderer & UART telemetry receiver
```

---

## 📡 Serial Protocol Specifications

Data is transmitted bidirectionally via standard ASCII frames over UART at **115200 baud**:

### AVR $\rightarrow$ PC (Telemetry)
| Frame Format | Description |
| :--- | :--- |
| `PADDLE:<x>` | Current horizontal position of the paddle ($0 \dots 80$) |
| `BALL:<x>,<y>` | Current coordinates of the ball ($0 \dots 100$) |
| `STATE:<n>` | Current state ID (`0`=MENU, `1`=RUNNING, `2`=PAUSED, `3`=OVER, `4`=WIN) |
| `BLOCKS:<string>` | 28-character binary string representing active (`1`) / destroyed (`0`) blocks |

### PC $\rightarrow$ AVR (Commands)
| Command | Action |
| :---: | :--- |
| `a` / `d` | Move paddle Left / Right |
| `s` | Start / Resume game |
| `p` | Pause game |
| `r` | Reset game to Menu |

---

## 🚀 Getting Started

### 1. Flash the Microcontroller
Ensure you have `avr-gcc` and `avrdude` installed, then compile and flash the HEX file to your ATmega32:

```bash
cd AVR_BREAKOUT
make all
avrdude -c usbasp -p m32 -U flash:w:AVR_BREAKOUT.hex:i
```

### 2. Run the PC Visualizer
Install dependencies and run the Pygame script (update the `PORT` variable in `controller.py` to match your COM / ttyUSB port):

```bash
pip install pygame pyserial
python pc/controller.py
```

---

## 👨‍💻 Author

**Dawid Cichy** — [GitHub Profile](https://github.com/dawidcichy141)