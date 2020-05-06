# SnakesSimulation
## Compile with make
* git clone git@github.com:DENNKA/SnakesSimulation.git
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
* Install libsfml-dev
* Open SnakesSimulation.cbp
* Project - Build options - Linker settings - Other linker options  change -lopengl32 to -lGL
* On the left side switch to debug and delete "-d" in all libs
* build

