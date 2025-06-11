import pygame
import sys

# INIT
pygame.init()
WIDTH, HEIGHT = 1280, 720
FPS = 60

screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Goofy Ahh Pygame Driving")
clock = pygame.time.Clock()

# GAME STATE SETUP
def load_assets():
    # put your image/sound loads here
    pass

def init():
    # init game objects, vars, etc.
    pass

def handle_input():
    keys = pygame.key.get_pressed()
    # example:
    # if keys[pygame.K_w]: player.move_up()
    return keys

def update(dt: float, keys):
    # update all your shit here
    pass

def draw():
    screen.fill((20, 20, 20))  # dark background

    rect = pygame.Rect(WIDTH/4, HEIGHT/4, WIDTH/2, HEIGHT/2)
    pygame.draw.rect(screen, (200, 0, 0), rect)

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
