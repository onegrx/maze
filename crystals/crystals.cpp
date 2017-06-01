#include <iostream>
#include <vector>

using namespace std;

bool canPlace(int x, int y);
char getField(int x, int y);
void solveMirrors(int x, int y, int mirrorsLeft, int height, int width);
int getCrystals(int height, int width);
bool simulateLaser(int height, int width);

vector<string> maze;
struct Crystal {
    int x;
    int y;
    bool light;
};
enum Direction {
    UP, DOWN, RIGHT, LEFT
};
const char MIRROR1 = '/',
        MIRROR2 = '\\',
        EMPTY = ' ',
        BLOCK = '#',
        CRYSTAL = '*';

int main() {

    int height, width, mirrors;
    cin >> height >> width;
    cin >> mirrors;

    cin.ignore();

    for (int i = 0; i < height; ++i) {
        string temp;
        getline(cin, temp);
        maze.push_back(temp);
    }

    int crystalCounter = getCrystals(height, width);

    solveMirrors(0, 0, mirrors, height, width);

    for (int i = 0; i < height; ++i) {
        cout << maze[i] << endl;
    }


    return 0;
}

void solveMirrors(int x, int y, int mirrorsLeft, int height, int width) {

    if (mirrorsLeft <= 0) {
        simulateLaser(height, width);
    } else {
        for (int row = x; row < height; ++row) {
            for (int col = y; col < width; ++col) {
                if (canPlace(col, row)) {
                    solveMirrors(x, y, mirrorsLeft - 1, height, width);

                    maze[row, col] = MIRROR1;
                    solveMirrors(x, y, mirrorsLeft - 1, height, width);
                    maze[row, col] = MIRROR2;
                    solveMirrors(x, y, mirrorsLeft - 1, height, width);

                    maze[row, col] = EMPTY;

                }
            }
        }
    }


}

bool canPlace(int x, int y) {
    return maze[y][x] == EMPTY;
}

int getCrystals(int height, int width) {
    int counter = 0;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (maze[i][j] == CRYSTAL) {
                counter++;
            }
        }
    }
    return counter;
}

bool simulateLaser(int height, int width) {
    Direction direction = RIGHT;
    int x = 0, y = 1;

    while (x < width  && y < height) {
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
                    y--;
                    break;
                case RIGHT:
                    direction = UP;
                    y++;
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
                    y++;
                    break;
                case RIGHT:
                    direction = DOWN;
                    y--;
                    break;
            }
        } else {

            // Normal way
            switch (direction) {
                case UP:
                    y++;
                    break;
                case DOWN:
                    y--;
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

}

char getField(int x, int y) {
    return maze[y][x];
}