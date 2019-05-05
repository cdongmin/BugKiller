#include <conio.h>
#include <windows.h>
#include <iostream>
using namespace std;

bool gameOver;
const int frameWidth = 25;
const int frameHeight = 25;
struct character {
	int x;
	int y;
	int bodyx[100];
	int bodyy[100];
	int size;
};
character player;
character smallEnemy;
character mediumEnemy;
character largeEnemy;

int score;
enum direction {STOP, LEFT, RIGHT, UP, DOWN};
direction dir;

void setup() {
	gameOver = false;
	dir = STOP;
	player.x = rand() % frameWidth;
	player.y = rand() % frameHeight;
	player.size = 1;
	smallEnemy.x = rand() % frameWidth;
	smallEnemy.y = rand() % frameHeight;
	smallEnemy.size = 0;
	mediumEnemy.x = rand() % frameWidth;
	mediumEnemy.y = rand() % frameHeight;
	mediumEnemy.size = 1;
	largeEnemy.x = rand() % (frameWidth-2);
	largeEnemy.y = rand() % frameHeight;
	largeEnemy.size = 2;
}

void draw() {
	system("cls");
	for (int i = 0; i < frameWidth; i++) {
		cout << "#";
		if (i == frameWidth - 1)
			cout << endl;
	}

	for (int j = 0; j < frameHeight; j++) {
		for (int i = 0; i < frameWidth; i++) {
			if (i == 0 || i == frameWidth - 1)
				cout << "#";
			else if ((i == smallEnemy.x && j == smallEnemy.y) || (i == mediumEnemy.x && j == mediumEnemy.y) || (i == largeEnemy.x && j == largeEnemy.y)) {
				if (i == smallEnemy.x && j == smallEnemy.y) {
					for (int l = 0; l < smallEnemy.size; l++) {
						if (l == 0)
							cout << "X";
						else
							cout << "x";
						i++;
					}
					cout << " ";
				}
				else if (i == mediumEnemy.x && j == mediumEnemy.y) {
					for (int l = 0; l < mediumEnemy.size; l++) {
						if (l == 0)
							cout << "X";
						else
							cout << "x";
						i++;
					}
					cout << " ";
				}
				else {
					for (int l = 0; l < largeEnemy.size; l++) {
						if (l == 0)
							cout << "X";
						else
							cout << "x";
						i++;
					}
					cout << " ";
				}

			}
			else if (i == player.x && j == player.y) {
				for (int l = 0; l < player.size; l++) {
					cout << "O";
					i++;
				}
				cout << " ";
			}
			else
				cout << " ";
			if (i == frameWidth - 1)
				cout << endl;
		}
	}

	for (int i = 0; i < frameWidth; i++) {
		cout << "#";
		if (i == frameWidth - 1)
			cout << endl;
	}

	cout << "Score: " << score << endl;
}

void input() {
	if (_kbhit()) {
		switch (_getch()) {
		case 'w': 
			dir = UP;
			break;
		case 'a':
			dir = LEFT;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'x':
			gameOver = true;
			break;
		default:
			break;
		}
	}
}

void logic() {
	for (int i = 0; i < player.size; i++) {
		if (i == 0) 
			player.bodyx[0] = player.x;
		else 
			player.bodyx[i] = player.x + i;
	}
	switch (dir) {
	case UP:
		player.y--;
		break;
	case DOWN:
		player.y++;
		break;
	case LEFT:
		player.x--;
		break;
	case RIGHT:
		player.x++;
		break;
	default:
		break;
	}
	if (player.x < 0 || player.x > frameWidth || player.y < 0 || player.y > frameHeight)
		gameOver = true;
	if (player.x == largeEnemy.x && player.y == largeEnemy.y)
		gameOver = true;
	for (int i = 0; i < 100; i++) {
		if (player.bodyx[i] == smallEnemy.x && player.y == smallEnemy.y) {
			score += smallEnemy.size;
			player.size += smallEnemy.size;
			smallEnemy.size = player.size - 1;
			mediumEnemy.size = player.size;
			largeEnemy.size = player.size + 1;
			smallEnemy.x = rand() % frameWidth;
			smallEnemy.y = rand() % frameHeight;
			mediumEnemy.x = rand() % frameWidth;
			mediumEnemy.y = rand() % frameHeight;
			largeEnemy.x = rand() % frameWidth;
			largeEnemy.y = rand() % frameHeight;
		}
		else if (player.bodyx[i] == mediumEnemy.x && player.y == mediumEnemy.y) {
			score += mediumEnemy.size;
			player.size += mediumEnemy.size;
			smallEnemy.size = player.size - 1;
			mediumEnemy.size = player.size;
			largeEnemy.size = player.size + 1;
			smallEnemy.x = rand() % frameWidth;
			smallEnemy.y = rand() % frameHeight;
			mediumEnemy.x = rand() % frameWidth;
			mediumEnemy.y = rand() % frameHeight;
			largeEnemy.x = rand() % frameWidth;
			largeEnemy.y = rand() % frameHeight;
		}
	}
}

int main() {
	setup();
	while (!gameOver) {
		draw();
		input();
		logic();
		if (dir == UP || dir == DOWN)
			Sleep(75);
		else
			Sleep(42);
	}
	system("cls");
	cout << "GAME OVER" << endl;
	cout << "Your score is " << score << endl;
	cin.get();
	return 0;
}