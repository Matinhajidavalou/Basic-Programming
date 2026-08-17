#include <stdio.h>
#define cellLength 100

void process(int, int, int, int, int, char *);
int getLength(char[]);           // طول مسیر
int getEnergyCost(int, char);    // انرژی مصرفی هر حرکت
int getNewPosition(int, char);   // محاسبه موقعیت جدید بعد هر حرکت
int getNewLivesValue(int, char); // مقدار جدید جان تارزان

int main()
{
    char cell[cellLength];
    int lives, energy, status = 1, pos = 0; /* گرفتن ورودی ها از کاربر */

    scanf("%99s", cell);
    scanf("%d", &lives);
    scanf("%d", &energy);
    int rootLength = getLength(cell);

    process(status, pos, rootLength, energy, lives, cell);
    return 0;
}
void process(int status, int pos, int rootLength, int energy, int lives, char *cell)
{
    
    for (int i = 0; i < rootLength; i++)
    {
        if (cell[i] == 'S')
        {
            pos = i;
        }
    }
    

    while (status != 0)
    {
        char move;
        scanf(" %c", &move); 
        if (move != 'R' && move != 'T' && move != 'L' && move != 'K' && move != 'Q')
            continue;
        // بررسی خروج از برنامه
        if (move == 'Q')
        {break;}

        energy = getEnergyCost(energy, move);
        pos = getNewPosition(pos, move);

        // حالات گم شدن تارزان در جنگل
        if (pos < 0 || pos > rootLength - 1)
        {
            printf("TARZAN GOT LOST IN THE JUNGLE!\n");
            status = 0;
            break;
        }

        if (energy == -1) // استثنا در طول مسیر : اگه انرژی 1 باشد و دو خانه حرکت انجام شود
        {
            energy = 0;
            if (move == 'T')
            {
                pos -= 1;
            }
            else if (move == 'K')
            {
                pos += 1;
            }
        }
        
        lives = getNewLivesValue(lives, cell[pos]); //  محاسبه جان تارزان اگر در تله یا چاله بیفتد

        printf("Moved to position %d, Energy left: %d, Lives left: %d\n", pos + 1, energy, lives); // چاپ وضعیت فعلی

        if (cell[pos] == 'F')
        {
            printf("TARZAN REACHED HIS FRIEND!\n");
            status = 0;
            break;
        }
        if (lives <= 0)
        {
            printf("TARZAN HAS NO LIFE LEFT!\n");
            status = 0;
            break;
        }

        if (energy <= 0)
        {
            printf("TARZAN RAN OUT OF ENERGY!\n");
            status = 0;
            break;
        }
    }
}

int getLength(char arr[]) // محاسبه طول مسیر
{

    int i = 0, length = 0;
    while (arr[i] != '\0')
    {
        length += 1;
        i++;
    }
    return length;
}

int getEnergyCost(int energy, char move)
{

    switch (move)
    {
    case 'R': energy -= 1; break;
    case 'L': energy -= 1; break;
    case 'T': energy -= 2; break;
    case 'K': energy -= 2; break;
    case 'Q': break;
    default: break;
    }

    return energy;
}

int getNewPosition(int pos, char move)
{
    switch (move)
    {
    case 'R': pos += 1; break;
    case 'L': pos -= 1; break;
    case 'T': pos += 2; break;
    case 'K': pos -= 2; break;
    default: break;
    }

    return pos;
}

int getNewLivesValue(int lives, char cell)
{

    switch (cell)
    {
    case 'T':
        printf("TARZAN STEPPED ON A TRAP, LOSE 1 LIFE\n");
        lives -= 1;
        break;

    case 'H':
        printf("TARZAN STEPPED INTO A HOLE, LOSE 1 LIFE\n");
        lives -= 1;
        break;

    default:
        break;
    }
    return lives;
}
