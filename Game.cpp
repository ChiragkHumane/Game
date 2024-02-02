#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int MAP_SIZE = 5;
const int MAX_ENEMIES = 3;

class Player {
public:
    int x, y;
    int health;

    Player(int startX, int startY) : x(startX), y(startY), health(100) {}

    void move(int dx, int dy) {
        x += dx;
        y += dy;
    }
};

class Enemy {
public:
    int x, y;
    int health;

    Enemy(int startX, int startY) : x(startX), y(startY), health(20) {}

    void moveTowards(int playerX, int playerY) {
        if (x < playerX) x++;
        else if (x > playerX) x--;
        if (y < playerY) y++;
        else if (y > playerY) y--;
    }
};

class Treasure {
public:
    int x, y;

    Treasure(int startX, int startY) : x(startX), y(startY) {}
};

class Game {
private:
    Player player;
    Enemy enemies[MAX_ENEMIES];
    Treasure treasure;

    void printMap() {
        for (int i = 0; i < MAP_SIZE; ++i) {
            for (int j = 0; j < MAP_SIZE; ++j) {
                if (player.x == j && player.y == i) cout << "P ";
                else if (treasure.x == j && treasure.y == i) cout << "T ";
                else {
                    bool enemyPresent = false;
                    for (int k = 0; k < MAX_ENEMIES; ++k) {
                        if (enemies[k].x == j && enemies[k].y == i) {
                            enemyPresent = true;
                            break;
                        }
                    }
                    if (enemyPresent) cout << "E ";
                    else cout << ". ";
                }
            }
            cout << endl;
        }
    }

public:
    Game() : player(0, 0), treasure(MAP_SIZE - 1, MAP_SIZE - 1) {
        // Initialize enemies at random positions
        srand(time(nullptr));
        for (int i = 0; i < MAX_ENEMIES; ++i) {
            int x = rand() % MAP_SIZE;
            int y = rand() % MAP_SIZE;
            enemies[i] = Enemy(x, y);
        }
    }

    void play() {
        char move;
        while (player.health > 0) {
            printMap();
            cout << "Enter move (W/A/S/D): ";
            cin >> move;

            int dx = 0, dy = 0;
            switch (move) {
                case 'w':
                case 'W':
                    dy = -1;
                    break;
                case 'a':
                case 'A':
                    dx = -1;
                    break;
                case 's':
                case 'S':
                    dy = 1;
                    break;
                case 'd':
                case 'D':
                    dx = 1;
                    break;
                default:
                    cout << "Invalid move!" << endl;
                    continue;
            }

            player.move(dx, dy);

            // Move enemies towards the player
            for (int i = 0; i < MAX_ENEMIES; ++i) {
                enemies[i].moveTowards(player.x, player.y);
            }

            // Check for encounters with enemies
            for (int i = 0; i < MAX_ENEMIES; ++i) {
                if (player.x == enemies[i].x && player.y == enemies[i].y) {
                    player.health -= 10;
                    cout << "You encountered an enemy! Your health: " << player.health << endl;
                }
            }

            // Check for treasure
            if (player.x == treasure.x && player.y == treasure.y) {
                cout << "You found the treasure! You win!" << endl;
                return;
            }
        }
        cout << "Game over! You died." << endl;
    }
};

int main() {
    Game game;
    game.play();
    return 0;
}
