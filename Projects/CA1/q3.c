#include <stdio.h>

void process(int , int , int, int , int , int) ;


int main()
{
    int n;
    int runTime , successExercise , difficulty;
    int tempRun , tempSuccess ;

    int runTimeImprove = 1, successExerciseImprove = 1;
    int runTimeDecline = 1, successExerciseDecline = 1;
    int difficultySum = 0;

    scanf("%d", &n);
    scanf("%d %d %d", &difficulty, &successExercise, &runTime);
    tempRun = runTime;
    tempSuccess = successExercise;
    difficultySum += difficulty;

    for (int i = 1; i < n; i++)
    {
        scanf("%d %d %d", &difficulty, &successExercise, &runTime);
        if (runTime < tempRun)
        {
            runTimeImprove = 0;
        }
        if (runTime > tempRun)
        {
            runTimeDecline= 0;
        }
        
        tempRun = runTime;

        if (successExercise < tempSuccess)
        {
            successExerciseImprove = 0;
        }
        if(successExercise > tempSuccess)
        {
            successExerciseDecline = 0;
        }
        tempSuccess = successExercise;

        difficultySum += difficulty;
    }
    process(difficultySum , n , successExerciseImprove , runTimeImprove , runTimeDecline , successExerciseDecline);
return 0;
}

void process(int difficultySum , int n , int successExerciseImprove , int runTimeImprove , int runTimeDecline , int successExerciseDecline)
{
    int averageDifficulty = difficultySum / n;

    if (averageDifficulty >= 5 && successExerciseImprove == 1 && runTimeImprove == 1)
    {
        printf("Athlete Status: Improving");
    }

    else if (averageDifficulty < 5 && successExerciseDecline == 1 && runTimeDecline == 1)
    {
        printf("Athlete Status: Declining");
    }
    else
    {
        printf("Athlete Status: Stable");
    }
}
