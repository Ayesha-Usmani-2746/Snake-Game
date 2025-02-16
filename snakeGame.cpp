#include <iostream>
#include <iomanip>
#include <conio.h>
#include <cstdlib>
#include <windows.h>
#include<fstream>
using namespace std;
const int width = 40;
const int height = 20;
int x, y, fruitx, fruity,score,highscore;
int tailX[100];
int tailY[100];
int taillength;
bool pause = false;
enum direction
{
    STOP = 0,
    RIGHT,
    LEFT,
    UP,
    DOWN
};
direction dir;
bool game;
void setup()
{
    x = width / 2;
    y = height / 2;
    fruitx = rand() % width;
    fruity = rand() % height;
    game = false;
    dir = STOP;
    score=0;
    ifstream myFile("highscore.txt");
    myFile>>highscore;
}
void display()
{

    system("cls");
    for (int i = 0; i < width + 2; i++)
    {
        cout << "#";
    }
    cout << endl;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)
            {
                cout << "#";
            }
            if (j == x && i == y)
            {
                cout << "O";
            }

            else if (j == fruitx && i == fruity)
            {
                cout << "F";
            }
            else
            {
                bool print = false;
                for (int k = 0; k < taillength; k++)
                {
                    if (j == tailX[k] && i == tailY[k])
                    {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print)
                {
                    cout << " ";
                }
            }
            if (j == width - 1)
            {
                cout << "#";
            }
        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++)
    {
        cout << "#";
    }
    cout<<endl;
    cout<<"Score:"<<score<<"\t High Score : "<<highscore<<endl;
}
void input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
        {
            if (!pause)
            {
                dir = LEFT;
                break;
            }
        }
        case 'w':
        {
            if (!pause)
            {
                dir = UP;
                break;
            }
        }
        case 'd':
        {
            if (!pause)
            {
                dir = RIGHT;
                break;
            }
        }
        case 's':
        {
            if (!pause)
            {
                dir = DOWN;
                break;
            }
        }
        case 'p':
        {
            pause = !pause;
            break;
        }
        default:
        {
            game = true;
            break;
        }
        }
    }
}
void logic()
{
    if(pause)
    {
        return;
    }
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < taillength; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (dir)
    {
    case LEFT:
    {
        x--;
        break;
    }
    case RIGHT:
    {
        x++;
        break;
    }
    case UP:
    {
        y--;
        break;
    }
    case DOWN:
    {
        y++;
        break;
    }
    }
    if (x >= width)
    {
        x = 0;
    }
    else if (x < 0)
    {
        x = width - 1;
    }
    if (y >= height)
    {
        y = 0;
    }
    else if (y < 0)
    {
        y = height - 1;
    }
    for (int i = 0; i < taillength; i++)
    {
        if (tailX[i] == x && tailY[i] == y)

        {
            game = true;
        }
    }
    if (x == fruitx && y == fruity)
    {
        fruitx = rand() % width;
        fruity = rand() % height;
        taillength++;
        score=score+10;
        if(score>=highscore)
        {
            highscore=score;
        }
        ofstream myFile("highscore.txt");
        myFile<<score;
        myFile.close();
    }
}
int main()
{

    setup();
    while (!game)
    {
        display();
        input();
        logic();
        Sleep(200);
    }

    return 0;
}