#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#define PLYRS_COUNT 7
#define NAME_SIZ 25
#define MAX_POINTS_PLYS 5

typedef struct {
    char name[NAME_SIZ];
    unsigned int point;
} Player;

int main() {
    FILE *file = fopen("playersInfo.txt", "w+");
    Player players[PLYRS_COUNT] = {
        {"Armen", 13},
        {"Henry", 14},
        {"Michael", 15},
        {"Yana", 3},
        {"Anahit", 90},
        {"Jasn", 6},
        {"John", 12}
    };

    for (int i = 0; i < PLYRS_COUNT; ++i) {
        fprintf(file, "%s\nPoint: %d\n", players[i].name, players[i].point);
        fprintf(file, "----------\n");
    }
    rewind(file);

    int points[PLYRS_COUNT];
    char tmpBuff[NAME_SIZ];
    int serialCh;

    for (int i = 0; i < PLYRS_COUNT; ++i) {
        fgets(tmpBuff, NAME_SIZ, file);
        while ((serialCh = fgetc(file)) != ' ');
        fscanf(file, "%d", &points[i]);
        fgets(tmpBuff, NAME_SIZ, file);
    }
    rewind(file);

    for (int i = 0; i < PLYRS_COUNT; ++i) {
        for (int j = i + 1; j < PLYRS_COUNT; ++j) {
            if (points[i] < points[j]) {
                points[i] ^= points[j];
                points[j] ^= points[i];
                points[i] ^= points[j];
            }
        }
    }

    FILE *file2 = fopen("greatPointsPlayers.txt", "w");
    int place = 1;

    for (int i = 0; i < MAX_POINTS_PLYS; ++i) {
        for (int j = 0; j < PLYRS_COUNT; ++j) {
            if (players[j].point == points[i]) {
                fprintf(file2, "%d) place is %s with point <%u> ! \n", place++, players[j].name, players[j].point);
            }
        }
    }

    fclose(file);
    fclose(file2);
    return 0;

}
