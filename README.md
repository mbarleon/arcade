# Arcade

> Arcade games with multiple libraries supported

![Platform](https://img.shields.io/badge/platform-Linux%20%7C%20macOS-blue)

## Group leaders

The lead developper of this program is Mathieu BARLEON (@mbarleon). You can contact him at mathieu.barleon@epitech.eu

This arcade is compatible with the one developped by Léo QUINZLER (@Leorevoir). You can contact him at leo.quinzler@epitech.eu

## 📦 Features

- Built with custom modular libraries
- Cross-platform support (Linux/macOS)

## 🚀 Getting Started

### Prerequisites

Make sure you have the following installed:

- `g++` / `clang`
- `make`
- (Optional) `doxygen`, `python3`

### Installation

```bash
git clone git@github.com:EpitechPromo2028/B-OOP-400-STG-4-1-arcade-mathieu.barleon.git
cd project-name
make
```

### Running

./arcade [graphical_lib]

## Example Usage

./arcade lib/arcade_ncurses.so

## Create your own library

To create your own library, run the following command with the appropriate flags (see --help for more informations).

```bash
python3 GenrateTemplate/templateCreator.py
```

After you have typed this command, simply complete the functions in the `.cpp` file created by the script. Feel free to add more private fucntions in your library.

Beware, the functions in the `extern "C"` part must remain unchanged.

## Contact

If you have any question, feel free to conctact the maintainers.

Mathieu BARLEON (@mbarleon): mathieu.barleon@epitech.eu

Jason KOENIG (@OkotEgarim): jason.koenig@epitech.eu

Noé CARABIN (@CorpsB): noe.carabin@epitech.eu

## Project Structure

```
B-OOP-400-STG-4-1-arcade-mathieu.barleon/
├── doc/
│   ├── Doxygen
│   ├── generate.sh
│   └── open.sh
├── GenerateTemplate/
│   ├── TemplateCreator/
│   │   ├── Games/
│   │   │   ├── __Name__Game.cpp
│   │   │   ├── __Name__Game.hpp
│   │   │   └── Makefile
│   │   ├── Graphicals/
│   │   │   ├── __Name__DisplayModule.cpp
│   │   │   ├── __Name__DisplayModule.hpp
│   │   │   └── Makefile
│   │   ├── Menu/
│   │   │   ├── __Name__Game.cpp
│   │   │   ├── __Name__Game.hpp
│   │   │   └── Makefile
│   │   ├── __init__.py
│   │   ├── BuildFiles.py
│   │   ├── Main.py
│   │   ├── ParseArgs.py
│   │   └── ReadFlags.py
│   └── templateCreator.py
├── include/
│   ├── Macro.hpp
│   └── Types.hpp
├── lib/
│   └── .gitkeep
├── Score/
│   └── .gitkeep
├── src/
│   ├── Core/
│   │   ├── Core.cpp
│   │   └── Core.hpp
│   ├── Games/
│   │   ├── Menu/
│   │   │   ├── Makefile
│   │   │   ├── Menu.cpp
│   │   │   └── Menu.hpp
│   │   ├── Pacman/
│   │   │   ├── Assets/
│   │   │   │   ├── map/
│   │   │   │   │   ├── green_bottom.hpp
│   │   │   │   │   ├── orange_bottom.hpp
│   │   │   │   │   ├── pinh_bottom.hpp
│   │   │   │   │   ├── red_bottom.hpp
│   │   │   │   │   └── vulnerable_bottom.hpp
│   │   │   │   ├── map/
│   │   │   │   │   ├── gum.hpp
│   │   │   │   │   ├── map.hpp
│   │   │   │   │   └── pacgum.hpp
│   │   │   │   └── pac/
│   │   │   │       └── pac_bottom_4.hpp
│   │   │   ├── Makefile
│   │   │   ├── PacmanBuilder.cpp
│   │   │   ├── PacmanGame.cpp
│   │   │   ├── PacmanGame.hpp
│   │   │   └── PacmanMove.cpp
│   │   ├── Snake/
│   │   │   ├── Makefile
│   │   │   ├── SnakeGame.cpp
│   │   │   └── SnakeGame.hpp
│   │   ├── AGame.cpp
│   │   ├── AGame.hpp
│   │   ├── IGame.hpp
│   │   └── Makefile
│   ├── Graphicals/
│   │   ├── NCurses/
│   │   │   ├── Makefile
│   │   │   ├── NCursesDisplayModule.cpp
│   │   │   └── NCursesDisplayModule.hpp
│   │   ├── SDL/
│   │   │   ├── Makefile
│   │   │   ├── SDLDisplayModule.cpp
│   │   │   └── SDLDisplayModule.hpp
│   │   ├── SFML/
│   │   │   ├── Makefile
│   │   │   ├── SFMLCharTraitFix.cpp
│   │   │   ├── SFMLDisplayModule.cpp
│   │   │   └── SFMLDisplayModule.hpp
│   │   ├── ADisplayModule.cpp
│   │   ├── ADisplayModule.hpp
│   │   ├── IDisplayModule.hpp
│   │   └── Makefile
│   ├── Main/
│   │   └── main.cpp
│   ├── Utils/
│   │   ├── Error.cpp
│   │   ├── Error.hpp
│   │   ├── GetLib.cpp
│   │   ├── GetLib.hpp
│   │   ├── Logger.cpp
│   │   ├── Logger.hpp
│   │   └── Makefile
├── .gitignore
├── Makefile
├── README.md
└── SFPro.OTF
```
