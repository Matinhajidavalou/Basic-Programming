#include <stdio.h>
#define dayLengthMin 1440

void processNight(int, int, int *, int *, int *);
void printProcess(int, int, int, int);
int convertToMin(int);
int calculateSleepMinutes(int, int);
int isLowSleep(int);
int isIrregular(int, int);

int main()
{
    int n, sleep, wakeUp;
    int totalSleepMinutes = 0, low = 0, irreg = 0;
    

    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        scanf("%4d-%4d", &sleep, &wakeUp);
        processNight(sleep, wakeUp, &totalSleepMinutes, &low, &irreg);
    }

    printProcess(totalSleepMinutes, low, irreg, n);
    return 0;
}

void processNight(int sleep, int wakeUp, int *totalSleepMinutes, int *low, int *irreg)
{
    *totalSleepMinutes += calculateSleepMinutes(sleep, wakeUp);
    if (isLowSleep(calculateSleepMinutes(sleep, wakeUp)))
    {
        (*low) += 1;
    }

    if (isIrregular(sleep, wakeUp))
    {
        (*irreg) += 1;
    }
}
void printProcess(int totalSleepMinutes, int low, int irreg, int n)
{
    float avreageSleep = (totalSleepMinutes * 1.00) / n;
    printf("Total Sleep: %d minutes\n", totalSleepMinutes);
    printf("Average Sleep: %.2f minutes \n", avreageSleep);
    printf("Low Sleep Nights: %d \n", low);
    printf("Irregular Nights: %d", irreg);
}
int convertToMin(int HHMM) //نبدیل فرمت به دقیقه
{
    int minutes = 0;
    minutes += HHMM % 100;
    minutes += (HHMM / 100) * 60;
    return minutes;
}
int calculateSleepMinutes(int sleepTime, int wakeTime) // محاسبه مجموع دقایق خواب
{
    int sleepMinutes;
    sleepTime = convertToMin(sleepTime);
    wakeTime = convertToMin(wakeTime);

    if (sleepTime > wakeTime)  // ساعت خواب قبل از 00:00
    {
        sleepMinutes = (dayLengthMin - sleepTime) + wakeTime;
    }
    else // ساعت خواب بعد از 00:00
    {
        sleepMinutes = wakeTime - sleepTime;
    }

    return sleepMinutes;
}
int isLowSleep(int sumSleep)
{
    if (sumSleep < 360)
        return 1;

    else
    {
        return 0;
    }
}
int isIrregular(int sleepTime, int wakeTime)
{

    if (convertToMin(sleepTime) < 300 || convertToMin(wakeTime) > 600)
        return 1;

    else
        return 0;
}