# Dune

A game based on Frank Herbert's novel Dune

A  modification of the classic Snake game from CppND-Capstone-Snake-Game.

Dependencies:

    cmake >= 3.16
    make >= 4.2.1
    SDL2 >= 2.0
    gcc/g++ >= 9.3.0
        Windows: recommend using MinGW 


Build Instructions:

    Clone this repo.
    Make a build directory in the top level directory: mkdir build && cd build
    Compile: cmake .. && make
    Run it: ./DuneGame.
    

Game Description:

Your ornithopter has crash-landed in the desserts of Arrakis. You must make it to the safety of a Fremen stronghold before you run out of water. Somewhere beneath the sands, a hungry sandworm is prowling. The sandworms are attracted to motion, so as soon as you step onto the dessert it will appear and come for you.Scattered around the dessert are rocky outcrops (marked in grey). If you stand on one of these, the sandworm will disappear under the sand again and stop looking for you. The sandworm will move about randomly, so the longer you stay on the rock, the further away it is likely to be. However, time is ticking and you must make it to safety before you run out of water. You have a single thumper, which you can use at any time (by pressing the spacebar). A thumper is a device that is planted in the sand and makes a noise to distract the worm. If you plant it, the sandworm will be attracted to it instead of you. However, as soon as it has consumed the thumper, it will come after you again.


Game Instructions:

- The crash site, where you begin, is on the top left edge of the map.

- The Fremen stroghold, where you can find safety and win the game, is on the bottom right corner of the map.

- The rocky outcrops are marked in grey.

- Deploy your thumper by pressing the spacebar.

- You control your movement using the arrow keys.

- To stop moving (eg if you want to stop on a rocky outcrop), simply press the opposite direction key to your direction of movement. E.g. if you are moving         right and you want to stop, simply press the left arrow key once.


Overview of Code Structure

The game code consists of five main classes: Game, SandWorm, Player, Controller, and Renderer. There is also a helper file named Helper.

To start, main creates a Renderer, a Controller, and a Game object. The Game object stores a Snadworm and Player oject as part of the state. The game loop is   started by main calling Game::Run to start the game loop.

To begin the game, main creates a Controller, a Game, and a Renderer object. Game stores SandWorm and Player objects as part of the state. Game also defines positions on the game grid that are defined as rocks. The Player may cross these, but the sandWorm may not. main calls Game::Run to start the game loop.

main.cpp

This is the entry point for the program. The main function sets the window size, and the frames per second. Main also creates Renderer, Controller and Game objects and calls the Game::Run method to start the game loop.

sandworm.h and sandWorm.cpp

These files define the sandWorm class which contains attributes to keep track of the sandWorm speed and location. Just as in the CppND-Capstone-Snake-Game project, there are methods to update the sandWorm state, which are called from the Game::Update method. The sandWorm head and body are treated separately; the head is stored using float coordinates, and the body is stored using a vector of int cell coordinates. The snadWorm::UpdateHead method updates the head location using the sandWorm's speed. If the head has passed into a new cell, then the body is updated with sandWorm::UpdateBody.


