# Self-Driving-Car
Project is arduino code for a collision avoiding rc car. Uses Ultrasonic sensor

## Current State of Project
The car uses extended pulsues during PWM oscillations in order to maintain a constant speed.
The ultrasonic sensor takes the distance away from an object/wall in centimeters and tells
the car to stop using the brake() function by applying a power in the reverse direction for
a small amount of time. Because of this, the car now avoids collisions perfectly with a wall
when going at a comfortable speed.

## Next Steps
The end goal for this project is to have the car stop, readjust its path, and look for a
different way to getting around an object. Now that the braking is in good shape, we can
accomplish this by enhancing our steering system using a more sturdy metal 3d print. We aim
to complete this project within the next 2 weeks (as of 4/27/2022).
