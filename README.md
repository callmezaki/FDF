# FDF

## Description

FDF is a project that involves creating a wireframe representation of a 3D landscape from a 2D map. This project is part of the 42 curriculum and aims to enhance understanding of computer graphics, specifically 3D projections, and wireframe rendering techniques.

## Features

- 3D wireframe rendering
- Support for multiple projections (e.g., isometric)
- Keyboard controls for rotation, translation, and scaling
- Customizable colors and grid sizes

## Getting Started

### Prerequisites

- GCC or any C compiler
- Make
- MinilibX (provided by the 42 curriculum)

### Installation

1. Clone the repository:

   ```bash
   git clone https://github.com/callmezaki/FDF.git
   cd FDF
   ```

2. Compile the project:

   ```bash
   make
   ```

### Usage

Run the program with the following command:

```bash
./fdf <map_file>
```

- `map_file`: Path to the map file that defines the 3D landscape.

Example:

```bash
./fdf maps/42.fdf
```

## Project Structure

- `src/`: Contains the source files.
- `maps/`: Contains example map files.
- `Makefile`: Defines the build process for the project.
- `README.md`: Project documentation.

## Contributing

Contributions are welcome! Please open an issue or submit a pull request for any changes.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- [42 School](https://42.fr/en/homepage/) for providing the project framework.
- The 42 community for their support and collaboration.
