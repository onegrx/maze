#include <iostream>
#include <vector>

using namespace std;

bool canPlace(int x, int y);
vector<string> maze;

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

   for (int i = 0; i < height; ++i) {
       cout << maze[i] << endl;
   }


    int c = 10;
    while (c--) {
        int a = 0, b = 0;

        cin >> a >> b;
        cout << a << " " << b;
        //cout << canPlace(a, b) ? "TAK" : "NIE";
    }

    return 0;
}

bool canPlace(int x, int y) {
    return maze[y][x] == ' ';
}