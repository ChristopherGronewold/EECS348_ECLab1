#include <stdio.h>

int main() {
    int dep[5][5];
    int prog[5][5];
    int assigned_deps[5] = {-1, -1, -1, -1, -1};
    int assign_count = 0;
    int assigned, p, i, j, k, dep_rank, prog_rank;
    int dep_sorted[5] = {};

    FILE *fp = fopen("matching-data.txt", "r");

    for (i = 0; i < 10; i++) {
        for (j = 0; j < 5; j++) {
            fscanf(fp, "%d", i < 5 ? &dep[j][i] : &prog[j][i - 5]);
        }
    }
    fclose(fp);

    for (p = 1; p < 6; p++) {
        int prog_stats[5][3];
        int top_dep[3] = {-1, -1, -1};
        for (i = 0; i < 5; i++) {
            dep_rank = 0;
            assigned = 0;
            for (j = 0; j < 5; j++) {
                if (dep[i][j] >= p) {
                    if (dep[i][j] == p) {
                        prog_rank = 0;
                        for (k = 0; k < 5; k++) {
                            if (prog[p-1][k] == i + 1) {
                                prog_rank = k;
                            }
                            if (assigned_deps[k] == i) {
                                assigned = 1;
                            }
                        }
                        if (assigned == 0 && (top_dep[0] == -1 || (top_dep[1] > dep_rank) || (top_dep[1] == dep_rank && top_dep[2] > prog_rank))) {
                            top_dep[0] = i;
                            top_dep[1] = dep_rank;
                            top_dep[2] = prog_rank;
                        }
                    }
                    dep_rank++;
                }
            }
        }
        assigned_deps[assign_count] = top_dep[0];
        assign_count++;
        dep_sorted[top_dep[0]] = p;
    }
    for (i = 0; i < 5; i++) {
        printf("Department #%d will get Programmer #%d\n", i+1, dep_sorted[i]);
    }
    return 0;
}
