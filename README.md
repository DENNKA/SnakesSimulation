# SnakesSimulation
## Used libs
* opengl
* sfml
## Compile with make on Linux
* git clone git@github.com:DENNKA/SnakesSimulation.git
* Install libsfml-dev and mesa-utils (opengl) from package manager
* cd SnakesSimulation
* make (make debug)
* ./SnakesSimulation
## Compile with code::blocks
### Win
* git clone git@github.com:DENNKA/SnakesSimulation.git
* Download sfml
* Open SnakesSimulation.cbp
* Set your path to sfml (Project - Build options - Search directories - Compiler */sfml/include and Linker */sfml/lib)
* Build
### Linux
* git clone git@github.com:DENNKA/SnakesSimulation.git
* Install libsfml-dev and mesa-utils (opengl) from package manager
* Open SnakesSimulation.cbp
* Project - Build options - Linker settings - Other linker options  change -lopengl32 to -lGL
* On the left side switch to debug and delete "-d" in all libs
* build

