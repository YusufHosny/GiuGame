
# Features
- Player Features
	- The Player can move with:
		- WASD movement
		- Clicking on target tile
		- GOTO command in the command box
		- PMOV command in the command box
	- The Player is animated with 4 animation states (IDLE, WALK, FIGHT, DIE), some are directional
	- The Player fights enemies and collects health packs by walking onto them
	- The Player dies if health or energy reaches 0
	- The Player's path is drawn behind him
- Enemies
	- Normal Enemy
		- Deals damage to the player when they fight
	- Poison Enemy
		- Deals damage to the player when they fight and adds poison debuff
		- Poison debuff continuously damages player over time until it runs out
	- Blink Enemy
		- Appears and disappears periodically, can only damage the player while its visible
	- All enemies are animated
- Health Packs
	- Give health to the player when collected
	- Animated
- Levels
	- There are 3 levels in the game
	- Levels can be navigated to using the door tiles present (Animated)
- Visualizations
	- 2D
		- Grid based visualization with a grayscale tile grid
	- Text
		- Letters mapped by luminance value to each tile
	- Overlay
		- Similar to 2d, but with an image overlayed instead of the tile grid
	- The views can be changed at runtime with the switch view button
	- Zooming in and out and panning are possible (with mouse wheel and arrow keys respectively)
	- Camera can be reset to player position with R button or CRST command
- Command box input
	- The command box has many commands (PMOV, CMOV, CRST, GOTO), which are auto completed, so "PMOV LEFT" can be shortened to "p l"

# Architecture

Many parts of the architecture were constrained by the requirements of the project, and a lot of compromises were made between what I would have preferred and implemented in a void, versus what was realistic and possible to fit the requirements. Furthermore, in many cases, I had to make a choice between implementing a certain feature from scratch, or doing it the "Qt" way.

- Engine
	-  The code base is roughly divided into two sections, the "Engine" and the "Game".
	-  The engine contains more generic code (with an asterisk) whereas the game contains game logic specific implementation
	- The engine is mainly designed around GameObjects, which are the primitive class containing the bulk of the "Model" and "Controller" sections of the codebase. GameObjects are built around a hierarchy system, and an init(), step() function architecture. The init functions are called on game start, and the step functions are called for every GameObject for each frame update.
	- Furthermore, GameObjectComponents allow for a more modular approach to object logic, allowing the reuse of parts of game logic, such as collision management. Additionally, they can be used to separate and abstract away portions of code that aren't generic but would bloat the GameObject, and would be easier to deal with in a seperate component.
	- The Game Engine also introduces a GameInput class and an InputManager interface, which are used to collect input from the user in an abstract way, ideally these inputs would be global inputs (such as mouse and keyboard inputs), and would be extendable in some form, however due to the structure of the project it made more sense to compromise on the generic-ness of the GameInput system, and introduce game specific inputs (Player Move, Camera Move, Camera Reset, etc)
	- The GameObject hierarchy is designed with a strong and flexible template api, able to retrieve children and components via their rtti, and allows for very flexible hierarchy manipulation to control game logic.
	- Ideally the Engine would contains some primitive form of visualization, for it to function as an actual game engine, however due to the project requiring multiple visualizations, another compromise was made, making the game visualization non-generic, and the responsibility of the game, not the engine.
- Game
	- The Game implementation follows a simple philosophy to the Engine, implementing a GameObject for every part of the game, and using the component system to manage collisions via the ColliderComponent and the CollisionManagerComponent.
	- Player
		- The player uses a path tracer component and an autoplay component to manage the path tracing and the autoplay features in the player
		- The player handles all the collision effect logic, including taking damage and healing on collision with enemies and healthpacks
	- AnimationComponent
		-  A modular component that allows for simple animations and animation state management, used in conjunction with the GameView's to animate the visualizations of the GameObjects
		- Due to the structure of the project requiring multiple visualizations, the visualization was defined as a part of the game not the engine, and as such the animation component wasn't as generic as it could be and was part of the game not the engine as well. Ideally both the gameview and the animation component would have some implementation in the engine portion. 
		- A SpriteLoader helper class is implemented to load sprites for the views
	- Levels
		- The levels are created using 3 main files (data.png, overlay.png, and config.txt)
		- The data.png contains the world model data, indicating the weight of each grid tile via the grayscale value of each pixel
		- The overlay contains the overlay image for this level, ideally this is the same aspect ratio as the data, however its stretched if thats not the case
		- The config.txt contains the configuration data for the level, including the number of enemies and ratio of penemies and benemies, that start and end positions, and the next level
		- This allows levels to be added independently of game compilation, which can be used to customize and add as many levels without tedious recompilation
- Visualization
	- The visualizations are all built around a direct mapping from GameObject to a GameView, which are managed by the top level GameView which draws and updates these GameViews.
	- A basic frustrum culling functionality is implemented, to increase framerates by only drawing relevant objects.
	- The game views are abstracted behind an itemview and an animated item view api, to generify as much as possible
        - A rudimentary 3d view is included, but since the game is designed around 2d functionality, its more of an afterthought, and isn't very detailed. Its designed by transforming the 2d tile in world space into 3d space, then projecting them onto screen space via linear transformations.        

# Credits
Code: Yusuf Hussein
Assets: Legend of Zelda: The Minish Cap
