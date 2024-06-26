## This project involved collaboration, and my teammate was https://github.com/Luzog78


https://github.com/fZpHr/cub3d_42/assets/92046611/eca88560-edbe-43c4-9f0a-d648ca9117e4




## Cub3D

Cub3D is a 42 project where you create a simple 3D game using the raycasting technique. The goal is to build a small game engine capable of rendering a 3D environment from a 2D map, allowing the player to navigate through it in a first-person perspective. This project helps reinforce your understanding of graphics programming and computational geometry concepts.

*For more information, please refer to the subject in the git.*

## Installation

To install Cub3D, clone the project and download the minilibx

```bash
git clone git@github.com:fZpHr/cub3d_42.git
cd cub3d_42
  
```
```Downloading the minilibx
wget https://cdn.intra.42.fr/document/document/22379/minilibx-linux.tgz
tar -xf minilibx-linux
```
Then compile the executable using (make for the mandatory part or make bonus for the bonus)
```bash
make
```
Finally, launch the game with

```bash
./cub3D <path_of_ur_map>
```

    
## Play

You can play the game using the keys **W**, **A**, **S**, **D**.  
Use your **mouse** / **left_arrow / right arrow** to rotate the point of view.  
By using **M**, you can enable and disable the minimap.  
By using **I**, you can enable and disable info.  

## Map Requirement
Here is an example of a working map for mandatory :
```
NO ./textures/bricks-blue-00.xpm
SO ./textures/bricks-blue-00.xpm
WE ./textures/bricks-blue-00.xpm
EA ./textures/bricks-blue-00.xpm

F 255,100,0
C 225,30,0

        1111111111111111111111111
        1000000000110000000000001
        1011000001110000000000001
        1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111
```
Here is an example of a working map for bonus :
```
NO [<id>] <path_to_the_xpm_file>  // Required for id 1
SO [<id>] <path_to_the_xpm_file>  // There can be multiple definition:
WE [<id>] <path_to_the_xpm_file>  //    the images will be the frames of the animation.
EA [<id>] <path_to_the_xpm_file>  // def_text id=1
                                  // def_text texture=NULL (transparent)

MP <id> (<R>,<G>,<B>)             // def_text 1=238,238,238; 2=0,0,0; others=transparent
TY <id> <type>                    // 0=no collision; 1=collision
                                  // def_text for '0'    >> 0 (void)
                                  // def_text for others >> 1 (wall)
SP <id> <amim_delay_in_frames>    // def_text delay=30

// Map rules:
// 1. ' ' = void
// 2. '1' = wall
// 3. '0' = empty
// 4. 'N', 'S', 'W', 'E' = player
// 5. Void should not be accessible by the player
        (it should be a wall preventing the player from going there)
// 6. There should be at least one player
// 7. Any char is accepted BUT the texture MUST BE DECLARED in the .cub file

// Adds:
// - 'X' = Closed Door >> Should be able to open
// - 'O' = Opened Door >> Should be able to close
// - '-' = Opening Door >> Automatically becomes 'O' once fully opened

F (<R>,<G>,<B>)          // Required & Always end by C or F
C (<R>,<G>,<B>)          // Required & Always end by C or F

        1111111111111111111111111
        1000000000100000000000001
        1011000001110000000000001
        100100000000000000X000001
111111111011000001110000000000001
10000000000011000001110112311111111
11110111111111011100000010001
11110111111111011101010010001
110000001101010111001 1010001
1000000000000001100010010001
1000E000000000001101010000001
1100000111010101111101111000111
11110111 1110101 10111101000011
11111111 1111111 111111111111

// After the map, there must be nothing (either empty lines, comments or EOF)
```
