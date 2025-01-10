# From the subject

__Summary:__  
This project is inspired by the world-famous Wolfenstein 3D game, which
was the first FPS ever.  
It will enable you to explore ray-casting. Your goal will be to
make a dynamic view inside a maze, in which you’ll have to find your way.  
Version: 10  

The constraints are as follows:  
• Display different wall textures (the choice is yours) that vary depending on which
side the wall is facing (North, South, East, West).  
• Your program must be able to set the floor and ceiling colors to two different ones.  
• Your program must take as a first argument a scene description file with the .cub
extension.  
◦ The map must be composed of only 6 possible characters: 0 for an empty space,
1 for a wall, and N,S,E or W for the player’s start position and spawning
orientation.  
◦ The map must be parsed as it looks in the file. Spaces are a valid part of the
map and are up to you to handle. You must be able to parse any kind of map,
as long as it respects the rules of the map. (yes only 6 possible characters but also space)  
◦ Each element (except the map) firsts information is the type identifier (composed by one or two character(s)), followed by all specific informations for each
object in a strict order such as :  
∗ North texture:  
`NO ./path_to_the_north_texture`  
· identifier: NO  
· path to the north texure  
∗ Floor color:  
`F 220,100,0`  
· identifier: F  
· R,G,B colors in range [0,255]: 0, 255, 255  
◦ If any misconfiguration of any kind is encountered in the file, the program
must exit properly and return "Error\n" followed by an explicit error message
of your choice.  

__Bonus__  
Bonus list:  
• Wall collisions.  
• A minimap system.  
• Doors which can open and close.  
• animated sprite.  
• Rotate the point of view with the mouse.  

Additional bonuses:  
• Looking up/down  
• Changing player height  
• Floor texture  
• Skybox (sort of)  
• Half blocks (doors, glass, half-height blocks)  
• "Gun" to destroy blocks  

# Usage
Texture identifiers are :  
· `NO`, north texture  
· `SO`, south texture  
· `WE`, west texture  
· `EA`, east texture  
· `F`, floor color or texture  
· `C`, skybox color or texture  
· `TB`, half-height blocks texture (has default if missing)  
· `GL`, glass texture (has default if missing)  
· `DO`, door texture (has default if missing)  

Map characters are:  
· `0`, nothing (inside of walls)  
· `1`, walls  
· ` `, nothing (outside of walls)  
· `N`/`S`/`W`/`E`, player (different orientations)  
· `G`, glass  
· `T`/`B`, half-height block (different heights)  
· `D`, door  

Controls:  
· WASD to move  
· ctrl to crouch  
· shift to run  
· space to jump  
· LMB to destroy blocks  
· mouse to look around  

`make bonus`, `make img` for textures, then `./cub3D [map].cub`.  
