import pygame
import serial
import sys
import time

# --- KONFIGURACJA PORTU SZEREGOWEGO ---
PORT = 'COM3'  
BAUDRATE = 115200

try:
    ser = serial.Serial(PORT, BAUDRATE, timeout=0)
    time.sleep(1)
    print(f"Połączono z AVR Breakout na porcie {PORT}!")
except Exception as e:
    print(f"Błąd otwarcia portu szeregowego: {e}")
    sys.exit(1)

# --- INICJALIZACJA PYGAME ---
pygame.init()
pygame.font.init()

SCALE = 6  # Plansza 100x100 -> Okno 600x600 px
SCREEN_SIZE = 100 * SCALE
screen = pygame.display.set_mode((SCREEN_SIZE, SCREEN_SIZE))
pygame.display.set_caption("AVR Breakout Controller")
clock = pygame.time.Clock()

font_large = pygame.font.SysFont("Consolas", 36, bold=True)
font_small = pygame.font.SysFont("Consolas", 20)

# --- STANY I GEOMETRIA GRY ---
current_state = 0  # 0: GAME_MENU, 1: GAME_RUNNING, 2: GAME_PAUSED, 3: GAME_OVER, 4: GAME_WIN

paddle_x = 40
PADDLE_WIDTH = 20 * SCALE
PADDLE_HEIGHT = 2 * SCALE
PADDLE_Y = 5

ball_x = 48
ball_y = 48
BALL_SIZE = 4 * SCALE

# Geometria klocków (zgodna z blocks.h)
BLOCK_ROWS = 4
BLOCK_COLS = 7
BLOCK_WIDTH = 12 * SCALE
BLOCK_HEIGHT = 4 * SCALE
BLOCK_BOTTOM_HEIGHT = 70
BLOCK_BOTTOM_WIDTH = 8

# Macierz klocków odbierana prosto z AVR (1 = żyje, 0 = zniszczony)
blocks_grid = [[1 for _ in range(BLOCK_COLS)] for _ in range(BLOCK_ROWS)]

running = True
buffer = ""

while running:
    # 1. OBSŁUGA KLAWIATURY
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
        elif event.type == pygame.KEYDOWN:
            if event.key == pygame.K_s:
                ser.write(b's')
            elif event.key == pygame.K_p:
                ser.write(b'p')
            elif event.key == pygame.K_r:
                ser.write(b'r')

    keys = pygame.key.get_pressed()
    if keys[pygame.K_LEFT] or keys[pygame.K_a]:
        ser.write(b'a')
    elif keys[pygame.K_RIGHT] or keys[pygame.K_d]:
        ser.write(b'd')

    # 2. ODBIÓR DANYCH Z AVR (PARSER UART)
    if ser.in_waiting > 0:
        try:
            raw_data = ser.read(ser.in_waiting).decode('utf-8', errors='ignore')
            buffer += raw_data
            
            lines = buffer.split('\r\n')
            buffer = lines.pop()  # Niedokończoną ramkę zostawiamy w buforze

            for line in lines:
                line = line.strip()

                if line.startswith("PADDLE:"):
                    paddle_x = int(line.split(":")[1])

                elif line.startswith("BALL:"):
                    coords = line.split(":")[1].split(",")
                    ball_x = int(coords[0])
                    ball_y = int(coords[1])

                elif line.startswith("STATE:"):
                    current_state = int(line.split(":")[1])

                elif line.startswith("BLOCKS:"):
                    # Odbiór ciagu 28 znaków ('0' i '1') przesyłanego z blocks_send_uart()
                    matrix_str = line.split(":")[1]
                    if len(matrix_str) >= BLOCK_ROWS * BLOCK_COLS:
                        for r in range(BLOCK_ROWS):
                            for c in range(BLOCK_COLS):
                                blocks_grid[r][c] = int(matrix_str[r * BLOCK_COLS + c])
        except (ValueError, IndexError):
            pass

    # 3. RENDEROWANIE GRAFIKI
    screen.fill((15, 15, 22))

    if current_state == 0:  # GAME_MENU
        txt_title = font_large.render("AVR BREAKOUT", True, (0, 255, 200))
        txt_sub = font_small.render("Nacisnij 'S' aby rozpoczac", True, (200, 200, 200))
        screen.blit(txt_title, (SCREEN_SIZE // 2 - txt_title.get_width() // 2, 200))
        screen.blit(txt_sub, (SCREEN_SIZE // 2 - txt_sub.get_width() // 2, 280))

    elif current_state in (1, 2):  # GAME_RUNNING lub GAME_PAUSED
        # --- Rysowanie Klocków z Macierzy AVR ---
        for r in range(BLOCK_ROWS):
            for c in range(BLOCK_COLS):
                if blocks_grid[r][c] == 1:
                    x = (BLOCK_BOTTOM_WIDTH + c * 12) * SCALE
                    y = (100 - (BLOCK_BOTTOM_HEIGHT + (r + 1) * 4)) * SCALE
                    color = (255, 80 + r * 40, 50)
                    pygame.draw.rect(screen, color, (x, y, BLOCK_WIDTH - 2, BLOCK_HEIGHT - 2), border_radius=3)

        # --- Rysowanie Paletki ---
        px = paddle_x * SCALE
        py = (100 - PADDLE_Y - 2) * SCALE
        pygame.draw.rect(screen, (0, 255, 200), (px, py, PADDLE_WIDTH, PADDLE_HEIGHT), border_radius=4)

        # --- Rysowanie Piłki ---
        bx = ball_x * SCALE
        by = (100 - ball_y) * SCALE
        pygame.draw.rect(screen, (255, 255, 255), (bx, by - BALL_SIZE, BALL_SIZE, BALL_SIZE), border_radius=2)

        if current_state == 2:  # PAUSED overlay
            txt_pause = font_large.render("PAUZA ('S' - wznow)", True, (255, 255, 0))
            screen.blit(txt_pause, (SCREEN_SIZE // 2 - txt_pause.get_width() // 2, 280))

    elif current_state == 3:  # GAME_OVER
        txt_over = font_large.render("GAME OVER!", True, (255, 50, 50))
        txt_sub = font_small.render("Nacisnij 'R' aby zresetowac", True, (200, 200, 200))
        screen.blit(txt_over, (SCREEN_SIZE // 2 - txt_over.get_width() // 2, 200))
        screen.blit(txt_sub, (SCREEN_SIZE // 2 - txt_sub.get_width() // 2, 280))

    elif current_state == 4:  # GAME_WIN
        txt_win = font_large.render("WYGRANA!", True, (50, 255, 50))
        txt_sub = font_small.render("Nacisnij 'R' aby zrestartowac", True, (200, 200, 200))
        screen.blit(txt_win, (SCREEN_SIZE // 2 - txt_win.get_width() // 2, 200))
        screen.blit(txt_sub, (SCREEN_SIZE // 2 - txt_sub.get_width() // 2, 280))

    pygame.display.flip()
    clock.tick(60)

ser.close()
pygame.quit()