from pygame.math import Vector2
import pygame
from math import cos, sin, atan2, pi, radians, degrees


class Car:
    def __init__(
        self,
        position: Vector2,
        car_heading: float,
    ):
        self.position = position
        self.car_heading = car_heading

        self.car_speed: float = 0
        self.steer_angle: float = 0
        self.wheel_base: float = 50

        # === PHYSICS PROPERTIES ===
        self.max_speed = 3000  # pixels per second
        self.acceleration_rate = 2000  # how fast we accelerate
        self.deceleration_rate = 500  # how fast we slow down
        self.drag_coefficient = (
            0.95  # how much speed we lose each frame (0.95 = lose 5%)
        )

        self.__max_steer_angle = radians(15)  # Convert to radians for consistency

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

        car_surf = pygame.Surface((car_length, car_width), pygame.SRCALPHA)
        car_surf.fill((255, 0, 50))

        rotated = pygame.transform.rotate(car_surf, -degrees(self.car_heading))
        rect = rotated.get_rect(center=self.position)
        surface.blit(rotated, rect.topleft)

    def handle_input(self, keys, dt: float):
        # === ACCELERATION/DECELERATION ===
        if keys[pygame.K_w]:
            # Accelerate forward
            self.car_speed += self.acceleration_rate * dt
            self.car_speed = min(self.car_speed, self.max_speed)  # Cap max speed

        elif keys[pygame.K_s]:
            # Decelerate or reverse
            self.car_speed -= self.deceleration_rate * dt
            self.car_speed = max(
                self.car_speed, -self.max_speed / 2
            )  # Reverse is slower

        # === STEERING ===
        if keys[pygame.K_d]:
            self.steer_angle = self.__max_steer_angle
        elif keys[pygame.K_a]:
            self.steer_angle = -self.__max_steer_angle
        else:
            self.steer_angle = 0
