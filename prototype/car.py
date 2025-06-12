from pygame.math import Vector2
import pygame
from math import cos, sin, atan2, pi, radians, degrees


class Car:
    def __init__(
        self,
        position: Vector2,
        car_heading: float,
        car_sprite: pygame.Surface | None = None,
        car_braking_sprite: pygame.Surface | None = None,
    ):
        self.position = position
        self.car_heading = car_heading
        self.car_sprite = car_sprite
        self.car_braking_sprite = car_braking_sprite

        self.car_speed: float = 0
        self.steer_angle: float = 0
        self.wheel_base: float = 100

        # === PHYSICS PROPERTIES ===
        self.max_speed = 5000  # pixels per second
        self.acceleration_rate = 2000  # how fast we accelerate
        self.deceleration_rate = 1000  # how fast we slow down
        self.drag_coefficient = 0.96  # how much speed we lose each frame

        self.__max_steer_angle = radians(40)

        self.is_braking = False

    def update(self, dt: float):
        # === STEP 1: Handle acceleration/deceleration ===

        # Apply drag (speed naturally decreases over time)
        self.car_speed *= self.drag_coefficient

        # Stop very slow movement (prevents jittering)
        if abs(self.car_speed) < 5:
            self.car_speed = 0

        # === STEP 2: Use the bicycle model for movement ===
        if self.car_speed != 0:  # Only move if we have speed
            # Calculate where the wheels are RIGHT NOW
            back_wheel, front_wheel = self._face_wheels_to_car_heading()

            # Move the back wheel straight forward
            forward_dir = Vector2(cos(self.car_heading), sin(self.car_heading))
            back_wheel += self.car_speed * dt * forward_dir

            # Move the front wheel in the steered direction
            steer_dir = Vector2(
                cos(self.car_heading + self.steer_angle),
                sin(self.car_heading + self.steer_angle),
            )
            front_wheel += self.car_speed * dt * steer_dir

            # Now update the car's position and heading based on new wheel positions
            self.position = (back_wheel + front_wheel) / 2
            self.car_heading = atan2(
                front_wheel.y - back_wheel.y, front_wheel.x - back_wheel.x
            )

    def _face_wheels_to_car_heading(self) -> tuple[Vector2, Vector2]:
        forward_direction = Vector2(cos(self.car_heading), sin(self.car_heading))
        offset = (self.wheel_base / 2) * forward_direction

        back_wheel = self.position - offset
        front_wheel = self.position + offset
        return back_wheel, front_wheel

    def draw(self, surface: pygame.Surface):
        car_length = self.wheel_base * 1.2
        car_width = self.wheel_base / 2
        if self.car_sprite is None:
            car_surf = pygame.Surface((car_length, car_width), pygame.SRCALPHA)
            car_surf.fill((255, 0, 50))

            rotated = pygame.transform.rotate(car_surf, -degrees(self.car_heading))
            rect = rotated.get_rect(center=self.position)
            surface.blit(rotated, rect.topleft)
        else:
            if self.car_braking_sprite:
                sprite = self.car_braking_sprite if self.is_braking else self.car_sprite
            else:
                sprite = self.car_sprite

            # Scale sprite to have a width of car_length, maintaining aspect ratio
            sprite_width, sprite_height = sprite.get_size()
            aspect_ratio = sprite_height / sprite_width
            scaled_height = int(car_length * aspect_ratio)

            sprite = pygame.transform.scale(sprite, (int(car_length), scaled_height))
            rotated = pygame.transform.rotate(sprite, -degrees(self.car_heading))
            rect = rotated.get_rect(center=self.position)
            surface.blit(rotated, rect.topleft)

    def handle_input(self, keys, dt: float):
        # === ACCELERATION/DECELERATION ===
        if keys[pygame.K_w]:
            self.accelerate(dt)

        elif keys[pygame.K_s]:
            self.decelerate(dt)

        # === STEERING ===
        dynamic_steer = self._get_dynamic_steer_angle()
        if keys[pygame.K_d]:
            self.steer_angle = dynamic_steer
        elif keys[pygame.K_a]:
            self.steer_angle = -dynamic_steer
        else:
            self.steer_angle = 0

    def accelerate(self, dt: float):
        """Simulates pressing the gas pedal"""
        self.car_speed += self.acceleration_rate * dt
        self.car_speed = min(self.car_speed, self.max_speed)  # Cap max speed

        # Activate the brake light as long as we're reducing speed
        if self.car_speed < 0:
            self.is_braking = True
        else:
            self.is_braking = False

    def decelerate(self, dt: float):
        """Simulates pressing the brake pedal"""
        # Decelerate or reverse
        self.car_speed -= self.deceleration_rate * dt
        self.car_speed = max(self.car_speed, -self.max_speed / 2)  # Reverse is slower
        if self.car_speed > 0:
            self.is_braking = True
        else:
            self.is_braking = False

    def _get_dynamic_steer_angle(self) -> float:
        # At 0 speed = full steer. At max_speed = half or less.
        speed_factor = max(0.3, 1 - (abs(self.car_speed) * 2 / self.max_speed))
        return self.__max_steer_angle * speed_factor
