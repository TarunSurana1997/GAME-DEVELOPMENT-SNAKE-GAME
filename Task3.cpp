#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>

using namespace std;

// Screen dimensions
const int SCREEN_WIDTH = 750;
const int SCREEN_HEIGHT = 500;
const int GRID_SIZE = 20;
const int SCORE_AREA_HEIGHT = 100;  // Space for score display

// Game state variables
bool playing = true;
bool paused = false;
string gameOverReason = "";

// Snake and game variables
int length = 1;
int lengthmax = 1;
int snake_x = (SCREEN_WIDTH / 2) / GRID_SIZE * GRID_SIZE;
int snake_y = (SCORE_AREA_HEIGHT + (SCREEN_HEIGHT/2)) / GRID_SIZE * GRID_SIZE;
char direc = '-';
char last = '-';
int fruitx, fruity;
bool eaten = false;
vector<int> snakex;
vector<int> snakey;
int score1 = 0;
int highscore = 0;

// Font and text objects
sf::Font font;
sf::Text scoreText;
sf::Text highscoreText;
sf::Text gameOverText;
sf::Text pauseText;

// Function declarations
void fruit();
void move();
void start();
void loadHighscore();
void saveHighscore();
void initText();
void updateScoreDisplay();

void loadHighscore() {
    ifstream file("highscore.txt");
    if (file.is_open()) {
        file >> highscore;
        file.close();
    }
}

void saveHighscore() {
    ofstream file("highscore.txt");
    if (file.is_open()) {
        file << highscore;
        file.close();
    }
}

void initText() {
    if (!font.loadFromFile("Montserrat.ttf")) {
        cerr << "Error loading font!" << endl;
    }

    // Score background
    scoreText.setFont(font);
    scoreText.setCharacterSize(30);
    scoreText.setFillColor(sf::Color::Black);
    scoreText.setPosition(SCREEN_WIDTH - 300, 20);

    highscoreText.setFont(font);
    highscoreText.setCharacterSize(30);
    highscoreText.setFillColor(sf::Color::Black);
    highscoreText.setPosition(SCREEN_WIDTH - 300, 60);

    // Game Over text
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(30);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setStyle(sf::Text::Bold);
    gameOverText.setPosition(SCREEN_WIDTH/2 - 300, SCREEN_HEIGHT/2 - 100);

    // Pause text
    pauseText.setFont(font);
    pauseText.setCharacterSize(40);
    pauseText.setFillColor(sf::Color::Yellow);
    pauseText.setString("PAUSED");
    pauseText.setPosition(SCREEN_WIDTH/2 - 80, SCREEN_HEIGHT/2 - 50);
}

void updateScoreDisplay() {
    stringstream ss;
    ss << "Score: " << score1;
    scoreText.setString(ss.str());

    ss.str("");
    ss << "High Score: " << highscore;
    highscoreText.setString(ss.str());
}

int main() {
    srand(time(NULL));
    loadHighscore();

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SnakeGame");
    initText();
    start();

    sf::Clock clock;
    float timer = 0, delay = 0.1;

    // Score background rectangle
    sf::RectangleShape scoreBackground(sf::Vector2f(SCREEN_WIDTH, SCORE_AREA_HEIGHT));
    scoreBackground.setFillColor(sf::Color::White);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                    case sf::Keyboard::W: if (last != 's') direc = 'w'; break;
                    case sf::Keyboard::S: if (last != 'w') direc = 's'; break;
                    case sf::Keyboard::A: if (last != 'd') direc = 'a'; break;
                    case sf::Keyboard::D: if (last != 'a') direc = 'd'; break;
                    case sf::Keyboard::Space: paused = !paused; break;
                }
            }
        }

        if (!paused && playing) {
            float time = clock.getElapsedTime().asSeconds();
            clock.restart();
            timer += time;

            if (timer > delay) {
                timer = 0;
                move();
                fruit();
            }
        }

        // Collision detection
        if (snake_x >= SCREEN_WIDTH || snake_x < 0 || 
            snake_y >= SCREEN_HEIGHT || snake_y < SCORE_AREA_HEIGHT) {
            playing = false;
            gameOverReason = "Collision with wall!";
        }

        for (int i = 0; i < snakex.size() - 1; i++) {
            if (snake_x == snakex[i] && snake_y == snakey[i]) {
                playing = false;
                gameOverReason = "Collision with self!";
            }
        }

        window.clear(sf::Color::Black);

        // Draw score area
        window.draw(scoreBackground);
        updateScoreDisplay();
        window.draw(scoreText);
        window.draw(highscoreText);

        // Draw game elements
        sf::RectangleShape line(sf::Vector2f(SCREEN_WIDTH, 1));
        line.setFillColor(sf::Color(50, 50, 50));
        for (int y = SCORE_AREA_HEIGHT; y < SCREEN_HEIGHT; y += GRID_SIZE) {
            line.setPosition(0, y);
            window.draw(line);
        }
        line.setSize(sf::Vector2f(1, SCREEN_HEIGHT - SCORE_AREA_HEIGHT));
        for (int x = 0; x < SCREEN_WIDTH; x += GRID_SIZE) {
            line.setPosition(x, SCORE_AREA_HEIGHT);
            window.draw(line);
        }

        // Draw fruit
        sf::RectangleShape fruitShape(sf::Vector2f(GRID_SIZE, GRID_SIZE));
        fruitShape.setFillColor(sf::Color::Red);
        fruitShape.setPosition(fruitx, fruity);
        window.draw(fruitShape);

        // Draw snake
        sf::RectangleShape snakeSegment(sf::Vector2f(GRID_SIZE, GRID_SIZE));
        snakeSegment.setFillColor(sf::Color::Green);
        for (int i = 0; i < snakex.size(); i++) {
            snakeSegment.setPosition(snakex[i], snakey[i]);
            window.draw(snakeSegment);
        }

        // Draw game over/pause text
        if (!playing) {
            stringstream gameOverSS;
            gameOverSS << "Game Over! Final Score: " << score1 << "\n" << gameOverReason;
            gameOverText.setString(gameOverSS.str());
            window.draw(gameOverText);
            
            if (score1 > highscore) {
                highscore = score1;
                saveHighscore();
            }
        }
        
        if (paused && playing) {
            window.draw(pauseText);
        }

        window.display();
    }
    return 0;
}

void start() {
    snakex.push_back(snake_x);
    snakey.push_back(snake_y);

    fruitx = (rand() % (SCREEN_WIDTH / GRID_SIZE)) * GRID_SIZE;
    fruity = SCORE_AREA_HEIGHT + (rand() % ((SCREEN_HEIGHT - SCORE_AREA_HEIGHT) / GRID_SIZE)) * GRID_SIZE;

    // Ensure fruit stays within game area
    fruitx = max(0, min(fruitx, SCREEN_WIDTH - GRID_SIZE));
    fruity = max(SCORE_AREA_HEIGHT, min(fruity, SCREEN_HEIGHT - GRID_SIZE));
}

void move() {
    last = direc;
    if (direc == 's') snake_y += GRID_SIZE;
    else if (direc == 'a') snake_x -= GRID_SIZE;
    else if (direc == 'w') snake_y -= GRID_SIZE;
    else if (direc == 'd') snake_x += GRID_SIZE;

    snakex.push_back(snake_x);
    snakey.push_back(snake_y);

    if (!eaten) {
        if (snakex.size() > lengthmax) {
            snakex.erase(snakex.begin());
            snakey.erase(snakey.begin());
        }
    } else {
        eaten = false;
    }
}

void fruit() {
    if (snake_x == fruitx && snake_y == fruity) {
        eaten = true;
        lengthmax++;
        score1++;

        bool onSnake;
        do {
            onSnake = false;
            fruitx = (rand() % (SCREEN_WIDTH / GRID_SIZE)) * GRID_SIZE;
            fruity = SCORE_AREA_HEIGHT + (rand() % ((SCREEN_HEIGHT - SCORE_AREA_HEIGHT) / GRID_SIZE)) * GRID_SIZE;

            for (int i = 0; i < snakex.size(); i++) {
                if (fruitx == snakex[i] && fruity == snakey[i]) {
                    onSnake = true;
                    break;
                }
            }
        } while (onSnake);

        fruitx = max(0, min(fruitx, SCREEN_WIDTH - GRID_SIZE));
        fruity = max(SCORE_AREA_HEIGHT, min(fruity, SCREEN_HEIGHT - GRID_SIZE));
    }
}
