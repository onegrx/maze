#include <iostream>
#include <vector>

using namespace std;

bool canPlace(int x, int y);

char getField(int x, int y);

void solveMirrors(int x, int y, int mirrorsLeft);

int getCrystals();

bool simulateLaser();

void printSolution();

void darkenCrystals();

struct Crystal {
    int x;
    int y;
    bool light;
};
enum Direction {
    UP, DOWN, RIGHT, LEFT
};

vector<string> maze;
vector<Crystal> crystals;
int height, width, mirrors;

const char MIRROR1 = '/',
        MIRROR2 = '\\',
        EMPTY = ' ',
        BLOCK = '#',
        CRYSTAL = '*';

int main() {

    cin >> height >> width;
    cin >> mirrors;

    cin.ignore();

    for (int i = 0; i < height; ++i) {
        string temp;
        getline(cin, temp);
        maze.push_back(temp);
    }

    getCrystals();
    solveMirrors(0, 0, mirrors);

    cout << "No solution found" << endl;
    return 1;
}

void solveMirrors(int x, int y, int mirrorsLeft) {

    if (mirrorsLeft <= 0) {
        if (simulateLaser()) {
            printSolution();
            exit(0);
        }
    } else {
        for (int row = x; row < height; ++row) {
            for (int col = y; col < width; ++col) {
                if (canPlace(col, row)) {
                    solveMirrors(x, y, mirrorsLeft - 1);

                    maze[row][col] = MIRROR1;
                    solveMirrors(x, y, mirrorsLeft - 1);
                    maze[row][col] = MIRROR2;
                    solveMirrors(x, y, mirrorsLeft - 1);

                    maze[row][col] = EMPTY;

                }
            }
        }
    }


}

bool canPlace(int x, int y) {
    return maze[y][x] == EMPTY;
}

int getCrystals() {
    int counter = 0;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (maze[i][j] == CRYSTAL) {
                Crystal crystal = {j, i, false};
                crystals.push_back(crystal);
                counter++;
            }
        }
    }
    return counter;
}

bool simulateLaser() {
    Direction direction = RIGHT;
    int x = 0, y = 1;

    while (x < width && y < height) {

        if (x < 0 || y < 0 || getField(x, y) == BLOCK) {
            darkenCrystals();
            return false;
        }

        if (getField(x, y) == MIRROR1) {
            switch (direction) {
                case UP:
                    direction = RIGHT;
                    x++;
                    break;
                case DOWN:
                    direction = LEFT;
                    x--;
                    break;
                case LEFT:
                    direction = DOWN;
                    y++;
                    break;
                case RIGHT:
                    direction = UP;
                    y--;
                    break;
            }
        } else if (getField(x, y) == MIRROR2) {
            switch (direction) {
                case UP:
                    direction = LEFT;
                    x--;
                    break;
                case DOWN:
                    direction = RIGHT;
                    x++;
                    break;
                case LEFT:
                    direction = UP;
                    y--;
                    break;
                case RIGHT:
                    direction = DOWN;
                    y++;
                    break;
            }
        } else {

            if (getField(x, y) == CRYSTAL) {
                for (auto& c : crystals) {
                    if(c.x == x && c.y == y) {
                        c.light = true;
                    }
                }
                bool allLight = true;
                for (auto& c : crystals) {
                    if(!c.light) {
                        allLight = false;
                    }
                }
                if (allLight) return true;
            }

            // Normal way
            switch (direction) {
                case UP:
                    y--;
                    break;
                case DOWN:
                    y++;
                    break;
                case RIGHT:
                    x++;
                    break;
                case LEFT:
                    x--;
                    break;
            }

        }

    }
    darkenCrystals();

    return false;
}

char getField(int x, int y) {
    return maze[y][x];
}

void printSolution() {
    cout << height << " " << width << endl;
    cout << mirrors << endl;
    for (int i = 0; i < maze.size(); ++i) {
        cout << maze[i] << endl;
    }
}

void darkenCrystals() {
    for (auto& c : crystals) {
        c.light = false;
    }
}
