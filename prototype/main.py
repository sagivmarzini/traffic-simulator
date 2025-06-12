import pygame
import sys
from car import Car
from math import pi

# INIT
pygame.init()
WIDTH, HEIGHT = 1280, 720
FPS = 60

screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Goofy Ahh Pygame Driving")
clock = pygame.time.Clock()


def draw_text(surface, text, pos, color=(255, 255, 255), size=32, bold=False):
    font = pygame.font.SysFont(None, size, bold)
    img = font.render(text, True, color)
    surface.blit(img, pos)


# GAME STATE SETUP
def load_assets():
    # put your image/sound loads here
    global car_image
    car_image = pygame.image.load("./assets/car1.png").convert_alpha()
    global car_brake_image
    car_brake_image = pygame.image.load("./assets/car1-brake.png").convert_alpha()
    pass


def init():
    # init game objects, vars, etc.
    global car
    car = Car(pygame.Vector2(100, HEIGHT / 2), 0, car_image, car_brake_image)

    # pygame.mouse.set_visible(False)

    pass


def handle_input():
    keys = pygame.key.get_pressed()
    # example:
    # if keys[pygame.K_w]: player.move_up()
    return keys


def update(dt: float, keys):
    car.handle_input(keys, dt)
    car.update(dt, pygame.Vector2(WIDTH, HEIGHT))

    pass


def draw():
    screen.fill((20, 20, 20))  # dark background

    car.draw(screen)

    # --- Display speed ---
    raw_speed = car.car_speed  # pixels/second
    # Assume 100 pixels = 1 meter
    speed_mps = raw_speed / 23
    speed_kmh = speed_mps * 3.6

    draw_text(screen, f"Speed: {speed_kmh:.1f} km/h", (20, 20), bold=True)
    draw_text(screen, f"Speed: {raw_speed:.1f} px/s", (20, 60))
    draw_text(screen, car.position.__str__(), (20, 100))

    # screen.blit(...), draw sprites, UI, etc.
    pygame.display.flip()


# MAIN LOOP
def main():
    load_assets()
    init()
    running = True
    while running:
        dt = clock.tick(FPS) / 1000  # seconds, float

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

        keys = handle_input()
        update(dt, keys)
        draw()

    pygame.quit()
    sys.exit()


if __name__ == "__main__":
    main()
