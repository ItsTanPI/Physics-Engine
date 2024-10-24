# Physics Engine

A **Physics Engine** developed using C++ and OpenGL, designed to simulate basic physics. This engine allows users to apply fundamental physics principles, making it suitable for creating simple physics-based games like Flappy Bird.

https://github.com/user-attachments/assets/03804e5a-64b5-462a-bfda-b741ada709b4
### Note
 - The FPS of the device should be locked at 144 to get the exact same result


## Features

- **Verlet Integration**: Efficiently simulates physics by using the Verlet integration method.
- **Rendering**:
  - **Line Renderer**: Renders lines for visual representation of joints or other elements.
  - **Point Renderer**: Renders points, useful for visualizing specific coordinates or particles.
- **Joints**:
  - **Spring Joint**: Simulates spring-like connections between objects.
  - **Distance Joint**: Maintains a fixed distance between connected objects.
- **Collision Detection**: Implements basic collision handling between objects.
- **Movement Control**:
  - **Jump Movement**: Triggered by the `Space` key.
  - **Directional Control**: Use the `Up Arrow` key to control the main square for jumping.

## Getting Started

### Prerequisites

To run this project, ensure you have the following:

- **C++ Compiler**: Supports C++11 or higher.
- **OpenGL**: The project is built using OpenGL, with the following libraries:
  - **GLFW**: For handling window creation and input.
  - **GLEW**: For managing OpenGL extensions.


## Contributing

Feel free to fork the repository, create a branch, and submit pull requests. Contributions are welcome!
