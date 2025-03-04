<h1>GAME DEVELOPMENT: SNAKE GAME</h1>

<h2>COMPANY: CODTECH IT SOLUTIONS

NAME: TARUN SURANA

INTERN ID: CT12KDX

DOMAIN: C++ PROGRAMMING

DURATION: 8 WEEEKS

MENTOR: NEELA SANTOSH</h2>

<h2>DESCRIPTON OF THE TASK</h2>

This code is a Snake Game implemented using the SFML (Simple and Fast Multimedia Library) in C++.

SFML is the most used library of C++ when one wishes to add graphics and sounds into the project.

<h2>Key Components of the Code</h2>

1. Game Window:

The game runs in a window with dimensions SCREEN_WIDTH (750) and SCREEN_HEIGHT (500).

The game area is divided into a grid of size GRID_SIZE (20), which determines the size of the snake and fruit.

2. Snake Movement:

The snake moves in four directions (W, A, S, D) and grows in length when it eats a fruit.

The snake's position is stored in two vectors (snakex and snakey), which track the coordinates of each segment of the snake.

3. Fruit:

A fruit is randomly placed on the grid. When the snake eats the fruit, its length increases, and a new fruit is spawned.

4. Collision Detection:

The game checks for collisions with the walls and the snake's own body. If a collision occurs, the game ends.

5. Score and High Score:

The player's score increases as the snake eats fruits.

The high score is saved to a file (highscore.txt) and loaded when the game starts.

6. Pause Feature:

The game can be paused by pressing the spacebar.

7. Game Over:

When the game ends, the final score and reason for game over (e.g., collision with wall or self) are displayed.

<h2>Workflow of the Program:</h2>

1. The game starts with the snake in the center of the screen and a fruit at a random position.

2. The player controls the snake using the W, A, S, and D keys.

3. If the snake eats the fruit, it grows in length, and a new fruit is spawned.

4. The game ends if the snake collides with the walls or itself.

5. The final score and reason for game over are displayed, and the high score is updated if necessary.

<h2>Key Points to Note:</h2>

1. start():

Initializes the snake's starting position and spawns the first fruit.

2. move():

Updates the snake's position based on the current direction.

Removes the tail segment of the snake unless a fruit has been eaten.

3. fruit():

Spawns a new fruit at a random position, ensuring it doesn't overlap with the snake.

4. oadHighscore() and saveHighscore():

Load and save the high score from/to a file.

5. updateScoreDisplay():

Updates the score and high score displayed on the screen.

<h2>Conclusion</h2>

This code is a simple yet complete implementation of the classic Snake game.

It uses SFML for rendering and input handling, and it includes features like score tracking, high score saving, and collision detection.

The game is easy to understand and can be extended with additional features like levels, obstacles, or power-ups.

<h1>OUTPUT</h1>

![Image](https://github.com/user-attachments/assets/1be15f15-f9d5-4bff-9a12-ced7a82f862e)

![Image](https://github.com/user-attachments/assets/aaa24a5f-3b39-44e4-b726-466b13e66322)

![Image](https://github.com/user-attachments/assets/ea4d5f01-fcc2-410c-a336-867e96402d0d)

![Image](https://github.com/user-attachments/assets/d3f1e077-eda2-4bfc-b18e-cac330f42e59)

![Image](https://github.com/user-attachments/assets/8a68cf09-ed1f-433a-9922-7e6a5453c66d)
