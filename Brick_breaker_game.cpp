#include <graphics.h>
#include <iostream>
#include <fstream>
#include <conio.h>
#include <cstdio>

using namespace std;

#define ORANGE 9
#define MAROON 10
#define PURPLE 11
#define GREEN 12
#define BLUE 13

void testRebound(int &x, int &y);
void move();
void readMaxScore(int &maxScore);
void writeMaxScore(int maxScore);
void resetMaxScore(int &maxScore);
void displayEndGame(int score, int maxScore);

struct coordinates {
    int x;
    int y;
};

struct dabbe {
    int lx;
    int ly;
    int rx;
    int ry;
    int hitCounter;
    int color;
};

dabbe platform;
coordinates ball;
int score = 0;
int size = 0;
int balls = 7;
int testX = 1, testY = 0;
char ch;
int diff = 13;
const int len = 21;
int endGame = len;
char mode[10];
int maxScore = 0;
int lives = 0;
dabbe b[len] = {
    {0, 0, 124, 20, 2,  MAROON },
    {124, 0, 248, 20, 2, PURPLE},
    {248, 0, 392, 20, 2, BLUE},
    {392, 0, 516, 20, 2,  PURPLE},
    {516, 0, 640, 20, 2, MAROON},
    {124, 40, 248, 60, 2, BLUE},
    {248, 60, 392, 80, 2,  MAROON},
    {392, 40, 516, 60, 2, BLUE},
    {0, 60, 124, 80, 2, PURPLE},
    {124, 80, 248, 100, 2, PURPLE},
    {248, 100, 392, 120, 2,PURPLE},
    {392, 80, 516, 100, 2, PURPLE},
    {516, 60, 640, 80, 2, PURPLE},
    {0, 120, 124, 140, 2, MAROON},
    {124, 140, 248, 160, 2, PURPLE},
    {248, 160, 392, 180, 2, MAROON},
    {392, 140, 516, 160, 2,PURPLE},
    {516, 120, 640, 140, 2, MAROON},
    {124, 60, 248, 80, 2, BLUE},
    {248, 80, 392, 100, 2, BLUE},
    {392, 60, 516, 80, 2,  BLUE},


};

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "c://turboc3/bgi");
    cleardevice();
    char maxScoreText[50];
void displayEndGame(int score, int &maxScore);
    readMaxScore(maxScore);

    int check1 = 0, check2 = 0, check1_ball = 0, check2_ball = 0, diff_time,
        diff_ball_time, check1_bar = 0, check2_bar = 0, diff_bar_time, speed = 0;
    time_t start_t, end_t, start_ball_t, end_ball_t, start_bar_t, end_bar_t;
    char scoreBoard[50];
    int maxX = getmaxx();
    int maxY = getmaxy();
    int x = 0;

    for (;;) {
            readimagefile("background2.bmp", 0, 0, getmaxx(), getmaxy());
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 5);
        setcolor(YELLOW);
        outtextxy((maxX / 2) - 250, (maxY / 2 - 180), "BRICK BREAKER");
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
        setcolor(RED);
    setbkcolor(LIGHTBLUE);
        outtextxy((maxX / 2) - 230, (maxY / 2 + 35), (" Please Press 'Enter' to start "));
        outtextxy((maxX / 2) - 230, (maxY / 2 + 95), ("'A' for left & 'L' for right move"));
        outtextxy((maxX / 2) - 270, (maxY / 2 + 65), ("'E' for Easy,'M' for Medium,'H' for Hard"));
        outtextxy((maxX / 2) - 230, (maxY / 2 + 155), ("press esc to exit the game"));
        outtextxy((maxX / 2) - 230, (maxY / 2 + 125), ("'T' to reset Max Score to 0"));

        settextstyle(DEFAULT_FONT, VERT_DIR, 3);
        setcolor(RED);
        setbkcolor(CYAN);
        outtextxy(1, 500, ("  roisul  &&  rahad  "));
        settextstyle(DEFAULT_FONT, VERT_DIR, 3);
        setcolor(RED);
        outtextxy(620, 500, ("  roisul  &&  rahad "));
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
        setcolor(RED);
        outtextxy(1, 1, ("  roisul     &&    rahad   "));
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
        setcolor(RED);
        outtextxy(27, 460, (" roisul    &&      rahad "));
        for (;;) {
        ch = getch();
        if (ch == 'e' || ch == 'E') {
            diff = 25;
            size = 20;
            lives = 3;
            strcpy(mode, "EASY");
            break;
        } else if (ch == 'm' || ch == 'M') {
            diff = 13;
            size = 0;
            lives = 2;
            strcpy(mode, "MEDIUM");
            break;
        } else if (ch == 'h' || ch == 'H') {
            diff = 7;
            size = -10;
            lives = 2;
            strcpy(mode, "HARD");
            break;
        }
    }


        ch = getch();
        if (ch == 13)
            break;
    }


    for (ball.x = x, ball.y = maxY - 150, platform.lx = (maxX / 2) - (50),
         platform.ly = maxY - 20, platform.rx = (maxX / 2) + (50),
         platform.ry = maxY - 10;;) {
        ch = 'o';
        move();

        setfillstyle(SOLID_FILL, BLUE);
        fillellipse(ball.x, ball.y, balls, balls);

        testRebound(maxX, maxY);
        if (ball.y >= maxY - 15) {
            lives--;}
        delay(diff);
        cleardevice();
        setcolor(BLUE);
        setfillstyle(SOLID_FILL, RED);

        bar(platform.lx - size, platform.ly, platform.rx + size, platform.ry);
        setcolor(RED);
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
        sprintf(scoreBoard, "Score : %d", score);
        outtextxy(maxX - 300, maxY - 150, scoreBoard);

        // Display mode
        setcolor(WHITE);
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
        char modeText[50];
        sprintf(modeText, "Mode : %s", mode);
        outtextxy(10, maxY - 150, modeText);

        sprintf(scoreBoard, "  Lives: %d", lives);

       outtextxy(10, maxY - 180, scoreBoard);

        setcolor(WHITE);
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
        sprintf(maxScoreText, "Max Score : %d", maxScore);
        outtextxy(10, maxY - 120, maxScoreText);

        for (int i = 0; i < len; i++) {
            setfillstyle(SOLID_FILL, b[i].color);
            if (b[i].hitCounter > 0)
                bar(b[i].lx, b[i].ly, b[i].rx, b[i].ry);
        }

        if (ball.x <= platform.rx + balls + size &&
            ball.x >= platform.lx - balls - size && ball.y >= maxY - (20 + balls))
            testX = 1;

        if (ball.y >= maxY - 15) {
            //lives--;
            for(;;){

                    if (lives == 0)
                break;
                 ball.x = (platform.lx + platform.rx) / 2; // ball position middle when lives--
                ball.y = platform.ly - balls;
                testX = 1;
                     setfillstyle(SOLID_FILL, BLUE);
             fillellipse(ball.x, ball.y, balls, balls);
                char q;
                q=getch();
            if (lives == 0)
                break;
                if(q==13)break;
            }
            if (lives == 0)
                break;
            else {
                ball.x = (platform.lx + platform.rx) / 2; // ball position middle when lives--
                ball.y = platform.ly - balls;
                testX = 1;
            }
        }

        if (kbhit())
            ch = getch();
        if (ch == 27)
            break;

        else if (ch == 108) { // move right press L
            if (platform.rx + (12 + speed) <= maxX) { // Check if dont exceed screen width
                platform.lx += (12 + speed);
                platform.rx += (12 + speed);
            }
        } else if (ch == 97) {
            if (platform.lx - (12 + speed) >= 0) {
                platform.lx -= (12 + speed);
                platform.rx -= (12 + speed);
            }
        } else if (ch == 116 || ch == 84) {
            resetMaxScore(maxScore);
        }
    }

    displayEndGame(score, maxScore);

    getch();
    cleardevice();
    closegraph();
    return 0;
}

void testRebound(int &x, int &y) {
    //right wall
    if (ball.x >= x) {
        testY = 1;
    }
    // left wall
    else if (ball.x <= balls) {
        testY = 0;
    }
    // top wall
    if (ball.y <= balls) {
        testX = 0;
    }


    for (int i = 0; i < len; i++) {
        if (b[i].hitCounter > 0) {
            // left side of brick
            if ((ball.x == b[i].lx - balls || ball.x == b[i].lx - (balls + 1) || ball.x == b[i].lx - (balls - 1)) &&
                (ball.y >= b[i].ly - balls) && (ball.y <= b[i].ry + balls)) {
                testY = 1;
                b[i].hitCounter--;
                if (b[i].hitCounter == 0) {
                    score += 50;
                    endGame--;
                    b[i].color = RED;
                } else {
                    b[i].color = GREEN;
                }
            }
            //  bottom side of  brick
            if ((ball.y == b[i].ry + balls || ball.y == b[i].ry + (balls + 1) || ball.y == b[i].ry + (balls - 1)) &&
                (ball.x >= b[i].lx - balls) && (ball.x <= b[i].rx + balls)) {
                testX = 0;
                b[i].hitCounter--;
                if (b[i].hitCounter == 0) {
                    score += 50;
                    endGame--;
                    b[i].color = RED;
                } else {
                    b[i].color = GREEN;
                }
            }
            //  right side of  brick
            if ((ball.x == b[i].rx + balls || ball.x == b[i].rx + balls + 1 || ball.x == b[i].rx + balls - 1) &&
                (ball.y >= b[i].ly - balls) && (ball.y <= b[i].ry + balls)) {
                testY = 0;
                b[i].hitCounter--;
                if (b[i].hitCounter == 0) {
                    score += 50;
                    endGame--;
                    b[i].color = RED;
                } else {
                    b[i].color = GREEN;
                }
            }
            // top side of  brick
            if ((ball.y == b[i].ly - balls || ball.y == b[i].ly - (balls + 1) || ball.y == b[i].ly - (balls - 1)) &&
                (ball.x >= b[i].lx - balls) && (ball.x <= b[i].rx + balls)) {
                testX = 1;
                b[i].hitCounter--;
                if (b[i].hitCounter == 0) {
                    score += 50;
                    endGame--;
                    b[i].color = RED;
                } else {
                    b[i].color = GREEN;
                }
            }
        }
    }
}

void move() {
    if (testX == 0) // top
        ball.y += 3;
    else if (testX == 1) //paddle
        ball.y -= 3;
    if (testY == 0) // left
        ball.x += 3;
    else if (testY == 1) // right
        ball.x -= 3;
}

void readMaxScore(int &maxScore) {
    ifstream infile("maxscore.txt");
    if (infile.is_open()) {
        infile >> maxScore;
        infile.close();
    } else {
        maxScore = 0;
    }
}



void resetMaxScore(int &maxScore) {
    maxScore = 0;
}



void writeMaxScore(int maxScore) {
    std::ofstream outfile("maxscore.txt");
    if (outfile.is_open()) {
        outfile << maxScore;
        outfile.close();
    }
}

void displayEndGame(int score, int &maxScore) {
    cleardevice();
    readimagefile("background.bmp", 0, 0, getmaxx(), getmaxy());

    int maxX = getmaxx();
    int maxY = getmaxy();
    char scoreText[50];
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
     setcolor(RED);

    sprintf(scoreText, "Your Score: %d", score);
    outtextxy((maxX / 2) - 250, (maxY / 2) -100, scoreText);
    if (score > maxScore) {
        maxScore = score;
        writeMaxScore(maxScore);
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
        outtextxy((maxX / 2) - 310, (maxY / 2) - 50, "This is a new high score!");

        delay(3000); //delay 2 sec
        readimagefile("background1.bmp", 0, 0, getmaxx(), getmaxy());
    } else {
        char maxScoreText[50];
        sprintf(maxScoreText, "Max Score : %d", maxScore);
        outtextxy((maxX / 2) - 250, (maxY / 2)-150, maxScoreText);
    }
}