# SnakesSimulation

[![](https://tokei.rs/b1/github/DENNKA/SnakesSimulation)](https://github.com/XAMPPRocky/tokei)
[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)

Original makefile https://github.com/mbcrawfo/GenericMakefile
## Used libs
* opengl
* sfml
## Compile with make on Linux
* git clone git@github.com:DENNKA/SnakesSimulation.git
* Install sfml (libsfml-dev) from package manager
* cd SnakesSimulation
* make (make debug)
* ./SnakesSimulation
## Compile with code::blocks
### Win
* git clone git@github.com:DENNKA/SnakesSimulation.git
* Download sfml https://www.sfml-dev.org/download.php
* Open SnakesSimulation.cbp
* Set your path to sfml (Project - Build options - Search directories - Compiler */sfml/include and Linker */sfml/lib)
* Build
### Linux
* git clone git@github.com:DENNKA/SnakesSimulation.git
* Install sfml (libsfml-dev) from package manager
* Open SnakesSimulation.cbp
* Project - Build options - Linker settings - Other linker options  change -lopengl32 to -lGL
* On the left side switch to debug and delete "-d" in all libs
* build

