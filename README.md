# Dune

A game based on Frank Herbert's Dune


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

Your ornithopter has crash-landed in the desserts of Arrakis. You must make it to the safety of a Fremen stronghold before you run out of water. Somewhere beneath the sands, a hungry sandworm is prowling. The sandworms are attracted to motion, so as soon as you step onto the dessert it will appear and come for you. Scattered around the dessert are rocky outcrops (marked in grey). If you stand on one of these, the sandworm will disappear under the sand again and stop looking for you. The sandworm will move about randomly, so the longer you stay on the rock, the further away it is likely to be. However, time is ticking and you must make it to safety before you run out of water. You have a single thumper, which you can use at any time (by pressing the spacebar). A thumper is a device that is planted in the sand and makes a noise to distract the worm. If you plant it, the sandworm will be attracted to it instead of you. However, as soon as it has consumed the thumper, it will come after you again.


Game Instructions:

- The crash site, where you begin, is on the top left edge of the map.

- The Fremen stroghold, where you can find safety and win the game, is on the bottom right corner of the map.

- The rocky outcrops are marked in grey.

- Deploy your thumper by pressing the spacebar.

- You control your movement using the arrow keys.

- To stop moving (eg if you want to stop on a rocky outcrop), simply press the opposite direction key to your direction of movement. E.g. if you are moving right and you want to stop, simply press the left arrow key once.


