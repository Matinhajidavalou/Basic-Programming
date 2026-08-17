#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define PI 3.14159265358
#define Gravity 0.4

typedef struct
{
    int x;
    int Health;
} Tank;

typedef struct
{
    Tank tank1;
    Tank tank2;
    int currentPlayer;
    int gameRunning;
    int bulletActive;
    int bulletX;
    int bulletY;
    char grid[22][121];
} gameState;
// List of Functions we Need
void initGame(gameState *game);
void gameLoop(gameState *game);
void healthProcess(int *tank1, int *tank2);
int newPosition(Tank *tank, char command, int move, int maxMove, int minMove);
int fireShot(gameState *game);
void checkGameOver(gameState *game);
void screenPrint(gameState *game);
void printStatsBar(gameState *game);
int main()
{
    gameState game;
    initGame(&game);
    gameLoop(&game);
    return 0;
}
void initGame(gameState *game)
{
    // init Game Setting
    srand(time(NULL));
    game->tank1.x = rand() % 25;
    game->tank2.x = (rand() % 27) + 85;
    game->tank1.Health = 100;
    game->tank2.Health = 100;
    game->gameRunning = 1;
    game->currentPlayer = 1;
    // Grid
    strcpy(game->grid[0], "                  ^                                                                                                     ");
    strcpy(game->grid[1], "                 ^^^                                                                            ^                       ");
    strcpy(game->grid[2], "                ^^^^^                                                                          ^^^                      ");
    strcpy(game->grid[3], "                                                                                              ^^^^^                     ");
    strcpy(game->grid[4], "                                                                                                                        ");
    strcpy(game->grid[5], "                                                                                                                        ");
    strcpy(game->grid[6], "                      ^^                                                                                                ");
    strcpy(game->grid[7], "                     ^^^^                                                                                               ");
    strcpy(game->grid[8], "                    ^^^^^^                                                                                    ^         ");
    strcpy(game->grid[9], "                                                                                                             ^^^        ");
    strcpy(game->grid[10], "                                                                                                                        ");
    strcpy(game->grid[11], "                                                                                                                        ");
    strcpy(game->grid[12], "                                                          ^                                                             ");
    strcpy(game->grid[13], "                                                         ^^^         ^^                                                 ");
    strcpy(game->grid[14], "                                                        ^^^^^       ^^^^                                                ");
    strcpy(game->grid[15], "                                               ^       ^^^^^^^^    ^^^^^^                                               ");
    strcpy(game->grid[16], "                                              ^^^     ^^^^^^^^^^  ^^^^^^^^     ^                                        ");
    strcpy(game->grid[17], "                                   ^^        ^^^^^  ^^^^^^^^^^^^^^^^^^^^^^^^  ^^^                                       ");
    strcpy(game->grid[18], "                                  ^^^^     ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^                                      ");
    strcpy(game->grid[19], "                                 ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^                                    ");
    strcpy(game->grid[20], "########################################################################################################################");
    strcpy(game->grid[21], "########################################################################################################################");
}

void screenPrint(gameState *game)
{
    // Tanks Array
    char TanksArray1[3][10] = {
        "   __    ",
        " _|__|_//",
        "|_______|"};
    char TanksArray2[3][10] = {
        "    __   ",
        "\\\\_|__|_ ",
        "|_______|",
    };
    // Frame Line
    char upDownFrame[123] = {"|------------------------------------------------------------------------------------------------------------------------|"};
    printf("%s\n", upDownFrame);
    // Print Process
    for (int i = 0; i < 22; i++)
    {
        printf("|");
        for (int j = 0; j < 120; j++)
        {

            if (game->bulletActive && i == game->bulletY && j == game->bulletX)
            {
                printf("*");
            }
            else if (i > 16 && i < 20 && j >= game->tank1.x && j <= game->tank1.x + 8)
            {
                printf("%c", TanksArray1[i - 17][j - game->tank1.x]);
            }
            else if (i > 16 && i < 20 && j >= game->tank2.x && j <= game->tank2.x + 8)
            {
                printf("%c", TanksArray2[i - 17][j - game->tank2.x]);
            }
            else
                printf("%c", game->grid[i][j]);
        }
        printf("|");
        printf("\n");
    }
    printf("%s\n", upDownFrame);
}

void printStatsBar(gameState *game)
{
    // Status Bar
    char statusBarLine[123] = {
        "=========================================================================================================================="};
    printf("%s\n", statusBarLine);
    printf("|                        [P1] TANK ALPHA  | HEALTH: %3d%%   ||   [P2] TANK BETA  | HEALTH: %3d%%                           |\n", game->tank1.Health, game->tank2.Health);
    printf("%s\n", statusBarLine);
}

void gameLoop(gameState *game)
{
    while (game->gameRunning)
    {
        system("cls");
        printStatsBar(game);
        screenPrint(game);
        Tank *currentTank;
        char input[50];
        char command;
        int move;
        int maxPos;
        int minPos;
        int scanResult;
        printf("\n Player %d: Enter Command - L=Left, R=Right, S=Skip, Q=Quit, N=New Game:", game->currentPlayer);
        fgets(input, sizeof(input), stdin);
        scanResult = sscanf(input, " %c %d", &command, &move);

        if (scanResult == 2)
        {
            if (game->currentPlayer == 1)
            {
                currentTank = &game->tank1;
                maxPos = 24;
                minPos = 0;
            }
            else if (game->currentPlayer == 2)
            {
                currentTank = &game->tank2;
                maxPos = 111;
                minPos = 85;
            }
            if (command == 'L' || command == 'R')
            {
                if (newPosition(currentTank, command, move, maxPos, minPos) == 0)
                {
                    printf("Illegal Move - Your Turn Is Lost!");
                    Sleep(3000);
                    game->currentPlayer = (game->currentPlayer == 1) ? 2 : 1;
                    continue;
                }
            }
            else
            {
                printf("\nInvalid Command - Your Turn Is Lost!");
                game->currentPlayer = (game->currentPlayer == 1) ? 2 : 1;
                Sleep(3000);
                continue;
            }
            fireShot(game);
            checkGameOver(game);
            if (!game->gameRunning)
                break;
            game->currentPlayer = game->currentPlayer == 1 ? 2 : 1;
            continue;
        }

        if (scanResult == 1)
        {
            if (command == 'S')
            {
                game->currentPlayer = (game->currentPlayer == 1) ? 2 : 1;
            }
            else if (command == 'N')
            {
                initGame(game);
            }
            else if (command == 'Q')
            {
                game->gameRunning = 0;
            }
            else
            {
                printf("Invalid Command - Your Turn Is Lost!");
                game->currentPlayer = (game->currentPlayer == 1) ? 2 : 1;
                Sleep(3000);
            }
        }
    }
}

int newPosition(Tank *tank, char command, int move, int maxPos, int minPos)
{
    int newPos = tank->x;
    if (command == 'L')
    {
        newPos -= move;
        if (newPos < minPos)
        {
            newPos += move;
            tank->x = newPos;
            return 0;
        }
        tank->x = newPos;
        return 1;
    }
    if (command == 'R')
    {
        newPos += move;
        if (newPos > maxPos)
        {
            newPos -= move;
            tank->x = newPos;
            return 0;
        }
        tank->x = newPos;
        return 1;
    }
    return 0;
}
int fireShot(gameState *game)
{
    Tank *shooter;
    Tank *enemy;
    int startY = 17;
    int startX;
    int direction;
    // Declare Shooter & Enemy Tanks
    if (game->currentPlayer == 1)
    {
        shooter = &game->tank1;
        enemy = &game->tank2;
        startX = game->tank1.x + 9;
        direction = 1;
    }
    else
    {
        shooter = &game->tank2;
        enemy = &game->tank1;
        startX = game->tank2.x - 1;
        direction = -1;
    }
    //  Input Bullet Variables
    double angle, powerInput;
    system("cls");
    printStatsBar(game);
    screenPrint(game);
    printf("\nPlayer %d: Enter Firing Angle [0-180]: ", game->currentPlayer);
    scanf("%lf", &angle);
    //  False Data From Player
    if (angle < 0 || angle > 180)
    {
        printf("\nAngle Out Of Range - Your Turn Is Lost!");
        Sleep(3000);
        return 0;
    }
    printf("Player %d: Enter Shot Power [1-100]: ", game->currentPlayer);
    scanf("%lf", &powerInput);
    //  False Data From Player
    if (powerInput < 1 || powerInput > 100)
    {
        printf("\nPower Out Of Range - Your Turn Is Lost!");
        Sleep(3000);
        return 0;
    }
    // Bullet Settings
    game->bulletActive = 1;
    double power = 2 + (7 * (pow(powerInput / 100, 1.5)));
    double rad = (angle * PI) / 180.0;
    // initalization for display bullet
    int lastX = startX;
    int lastY = startY;
    // Gameplay
    for (double t = 0.0; t < 50.0; t += 0.1)
    { //  x , y , velocity equations
        double velocityX = direction * (power * cos(rad));
        double velocityY = (power * sin(rad));
        double x = (startX + (velocityX * t));
        double y = (startY - ((velocityY * t) - (0.5 * Gravity * t * t)));
        int nextX = round(x);
        int nextY = round(y);
        // Collision with Game Frame
        if (nextX < 0 || nextX >= 120 ||
            nextY < 0 || nextY >= 20)
        {
            Sleep(750);
            printf("Shot Terminated!\n");
            break;
        }
        // Collision with Stones
        else if (game->grid[nextY][nextX] == '^')
        {
            Sleep(750);
            printf("Shot Terminated!\n");
            break;
        }
        // Collision with Enemy Tank
        else if (nextY >= 17 && nextY <= 19 && nextX >= enemy->x && nextX <= enemy->x + 8)
        {
            game->bulletX = lastX;
            game->bulletY = lastY;
            system("cls");
            screenPrint(game);
            Sleep(750);
            enemy->Health -= 20;
            printf("BOOM!!! Clean Hit On The Enemy\n");
            break;
        }
        // Collision with own Tank
        else if (nextY >= 17 && nextY <= 19 && nextX >= shooter->x && nextX <= shooter->x + 8)
        {
            game->bulletX = lastX;
            game->bulletY = lastY;
            system("cls");
            screenPrint(game);
            Sleep(750);
            shooter->Health -= 20;
            printf("BOOM!!! Friendly Fire\n");
            break;
        }
        // Using ( a^2 + b^2 = c^2 ) to apply (dx = 6)
        else if (pow((nextX - lastX), 2) + pow((nextY - lastY), 2) >= 36)
        {
            lastX = nextX;
            lastY = nextY;
            game->bulletX = lastX;
            game->bulletY = lastY;
            system("cls");
            screenPrint(game);
            Sleep(750);
        }
    }
    Sleep(3000);
    game->bulletActive = 0;
    return 1;
}

void checkGameOver(gameState *game)
{
    if (game->tank1.Health <= 0)
    {
        printf("--------------------------------------------------------PLAYER 2 WINS-----------------------------------------------------");
        Sleep(3000);
        game->gameRunning = 0;
    }
    if (game->tank2.Health <= 0)
    {
        printf("--------------------------------------------------------PLAYER 1 WINS-----------------------------------------------------");
        Sleep(3000);
        game->gameRunning = 0;
    }
}
