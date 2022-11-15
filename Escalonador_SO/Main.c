/*
    Como Compilar:
    gcc main.c -o main
    ./main Entrada.txt
 */

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int P, R;

int *All_R = NULL, *Available_R = NULL;

int **In_Use_R, **Required_R;

bool allocateResources() {
    int *Rn = (int *)malloc(R * sizeof(int));

    for (int i = 0; i < P; i++) {
        for (int u = 0; u < R; u++) {
            Rn[u] = Available_R[u];
        }

        int DoNothing = 0;
        for (int j = 0; j < R; j++) {
            DoNothing += Required_R[i][j];
        }

        int CanAllocate = 1;
        for (int j = 0; j < R; j++) {
            if (Rn[j] < Required_R[i][j]) {
                CanAllocate = 0;
            }
        }

        if (DoNothing == 0) {
            // Do Nothing
        } else if (CanAllocate) {
            for (int j = 0; j < R; j++) {
                In_Use_R[i][j] += Rn[j];
                Required_R[i][j] = 0;
                Available_R[j] = 0;
            }
            return true;
        }
    }
    return false;
}

void runProcess() {
    for (int i = 0; i < P; i++) {
        int DoNothing = 0;
        for (int j = 0; j < R; j++) {
            DoNothing += In_Use_R[i][j];
        }

        int CanProcess = 0;
        for (int j = 0; j < R; j++) {
            CanProcess += Required_R[i][j];
        }

        if (DoNothing == 0) {
            // Do Nothing
        } else if (CanProcess == 0) {
            for (int j = 0; j < R; j++) {
                Available_R[j] += In_Use_R[i][j];
                In_Use_R[i][j] = 0;
            }
            printf("\n\t| PROCESS %d FINISHED  ^u^ |\n", i + 1);
        }
    }
}

void checkDeadLock() {
    int *ActiveProcess = (int *)malloc(P * sizeof(int));
    for (int i = 0; i < P; i++) {
        ActiveProcess[i] = 1;
    }

    for (int i = 0; i < P; i++) {
        int sum = 0;
        for (int j = 0; j < R; j++) {
            sum += In_Use_R[i][j] + Required_R[i][j];
        }
        if (sum == 0)
            ActiveProcess[i] = 0;
    }

    for (int i = 0; i < P; i++) {
        if (ActiveProcess[i]) {
            for (int j = 0; j < R; j++) {
                if (Required_R[i][j] != 0) {
                    int WaitingResource = Required_R[i][j] - Available_R[j];
                    if (WaitingResource > 0) {
                        if (All_R[j] >= Required_R[i][j])
                            printf("\n\t| PROCESS %d IN DEADLOCK MISSING %d INSTANCES OF R%d  >:c |\n", i + 1, WaitingResource, j + 1);
                        if(All_R[j] < Required_R[i][j])
                            printf("\n\t| PROCESS %d WAITING FOR %d INSTANCES OF R%d  ^~^ |\n", i + 1, WaitingResource, j + 1);
                    }
                }
            }
            printf("\n");
        }
    }
}

void FillVec(int **Vector, FILE *fp) {
    free(*Vector);

    int *tmp = (int *)malloc(R * sizeof(int));

    for (int i = 0; i < R; i++) {
        fscanf(fp, "%d", &tmp[i]);
    }

    *Vector = tmp;
}

void FillMat(int ***Matriz, FILE *fp) {
    free(*Matriz);

    int **line = (int **)malloc(P * sizeof(int *));

    for (int i = 0; i < P; i++) {
        int *column = NULL;
        FillVec(&column, fp);
        line[i] = column;
    }

    *Matriz = line;
}

/*  Manipula ações do arquivo, com a leitura do mesmo preenche as matrizes   */
void FileHandling(char const *File_Name, char *mode) {
    FILE *fp;
    fp = fopen(File_Name, mode);

    bool checkData[6] = {false, false, false, false, false, false};
    while (1) {
        if (feof(stdin))
            break;
        if (!checkData[0]) {
            fscanf(fp, "%d", &P);
            checkData[0] = true;
        } else if (!checkData[1]) {
            fscanf(fp, "%d", &R);
            checkData[1] = true;
        } else if (!checkData[2]) {
            FillVec(&All_R, fp);
            checkData[2] = true;
        } else if (!checkData[3]) {
            FillVec(&Available_R, fp);
            checkData[3] = true;
        } else if (!checkData[4]) {
            FillMat(&In_Use_R, fp);
            checkData[4] = true;
        } else if (!checkData[5]) {
            FillMat(&Required_R, fp);
            checkData[5] = true;
        } else {
            break;
        }
    }
    fclose(fp);
}

void ShowData() {
    printf("\n %d", P);

    printf(" %d\n\n", R);

    for (int i = 0; i < R; i++) {
        printf(" %d", All_R[i]);
    }
    printf("\n\n");
    for (int i = 0; i < R; i++) {
        printf(" %d", Available_R[i]);
    }
    printf("\n\n");
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            printf(" %d", In_Use_R[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            printf(" %d", Required_R[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main(int argc, char const *argv[]) {
    FileHandling(argv[1], "r");

    /*  Enquanto pudermos alocar recursos e rodar os processos não teremos DeadLock. */
    ShowData();
    while (allocateResources()) {
        runProcess();
    }

    checkDeadLock();

    ShowData();

    return 0;
}
