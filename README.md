

# Boids 🪽

This project is an implementation of an artificial life program: The Boids algorithm, which models the flocking behavior of birds, fish, and other swarming creatures. The simulation is built using **C++** and **SFML** to create an interactive and visually appealing (in my humble opinion) flocking system.

## Demo 📸

*Mind The Artifacts From The Sliders* 

<p align="center">
    <img src="assets/gifs/boids.gif" width="700" alt="Demo">
</p>

## How It Works ⚙️

I will not subject you to a poor man's explanation of this algorithm works, instead I will refer you to the explanations linked in the Contributions section. 
With that said, here is the TL;DR: While this flocking behavior may seem complex at first, it is deceptively simple and emerges from just three basic rules:

1. **Separation** – Boids steer away from nearby flockmates to avoid collisions.
2. **Alignment** – Boids adjust their velocity to match the average direction of neighbors.
3. **Cohesion** – Boids move toward the average position of nearby flockmates.

By combining these rules, realistic swarm-like behavior emerges. Additionally, I’ve introduced the mouse position as a sort of "Predator." The Boids will actively avoid the mouse as they fly around, adding another layer of interaction to the simulation.

## Features

- Real-time visualization of Boids movement
- Configurable parameters for tuning flocking behavior
- Object-oriented architecture for modularity and scalability
- Smooth animations with SFML's graphics rendering


# Contributions

- [Boids](https://people.ece.cornell.edu/land/courses/ece4760/labs/s2021/Boids/Boids.html)
- [Ben Eater](https://eater.net/boids)
- [N4G1/Slider-SFML: Simple slider made in SFML](https://github.com/N4G1/Slider-SFML)
