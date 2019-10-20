This is a basic implementation of the AStar and Jump Point Search (JPS) alghoritm.
When the demo is booted, the player will be able to place obstacles on the grid as well as the start and target point.
Changing from EDIT_MODE to PATHFINDING (in the Imgui), it is possible to run the search and see the 
2 characters (the 2 white boxes) move towards the target following the path found.
In this view, when in debug mode, is also possible to debug the path AStar and JPS have found, which nodes have been expanded
and what the costs associated with them are.
The characters can be paused by pressing P.
Moreover, by pressing 1 or 2 the player can switch between a FPS camera style or a top down perspective camera.
The demo can be quit by pressing ESC