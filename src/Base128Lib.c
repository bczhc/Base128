//jnilo
// Created by root on 19-7-3.
//

#include "Base128Lib.h"

char e_table_l[] = {1, 3, 7, 15, 31, 63, 127};

void e1(char *Dest, const char buf[7]) {
    Dest[0] = (char) ((buf[0] & 255) >> 1);
    /*Dest[1] = (char) (((buf[0] & 1) << 6) | ((buf[1] & 255) >> 2));
    Dest[2] = (char) (((buf[1] & 3) << 5) | ((buf[2] & 255) >> 3));
    Dest[3] = (char) (((buf[2] & 7) << 4) | ((buf[3] & 255) >> 4));
    Dest[4] = (char) (((buf[3] & 15) << 3) | ((buf[4] & 255) >> 5));
    Dest[5] = (char) (((buf[4] & 31) << 2) | ((buf[5] & 255) >> 6));
    Dest[6] = (char) (((buf[5] & 63) << 1) | ((buf[6] & 255) >> 7));*/
    for (int i = 1; i < 7; ++i) {
        Dest[i] = (char) (((buf[i - 1] & e_table_l[i - 1]) << (7 - i)) | ((buf[i] & 255) >> (i + 1)));
    }
    Dest[7] = (char) (buf[6] & 127);
}

void d1(char *Dest, const char buf[8]) {
    /*Dest[0] = (char) (((buf[0] & 255) << 1) | ((buf[1] & 255) >> 6));
    Dest[1] = (char) (((buf[1] & 255) << 2) | ((buf[2] & 255) >> 5));
    Dest[2] = (char) (((buf[2] & 255) << 3) | ((buf[3] & 255) >> 4));
    Dest[3] = (char) (((buf[3] & 255) << 4) | ((buf[4] & 255) >> 3));
    Dest[4] = (char) (((buf[4] & 255) << 5) | ((buf[5] & 255) >> 2));
    Dest[5] = (char) (((buf[5] & 255) << 6) | ((buf[6] & 255) >> 1));
    Dest[6] = (char) (((buf[6] & 255) << 7) | (buf[7] & 255));*/
    for (int i = 0; i < 7; ++i) {
        Dest[i] = (char) (((buf[i] & 255) << (i + 1)) | ((buf[i + 1] & 255) >> (6 - i)));
    }
}

int e_1029P(char *Dest, const char buf[ERS], int readSize) {
    int a = readSize / 7, b = readSize % 7, g = b ? a + 1 : a, rL = g * 8;
    for (int i = 0; i < g; ++i) {
        e1(Dest + 8 * i, buf + 7 * i);
    }
    return rL;
}

int d_1176P(char *Dest, const char buf[DRS], int readSize) {
    int a = readSize / 8, b = readSize % 8, g = b ? a + 1 : a, rL = g * 7;
    for (int i = 0; i < g; ++i) {
        d1(Dest + 7 * i, buf + 8 * i);
    }
    return rL;
}

//char t_b[4][1029] = {{0}};
//char t_e_r[4][DRS] = {{0}};

/*
void *T_fun(void *arg) {
    int i = *((int *) arg);//????
    e_1029P(t_e_r[i], t_b[i], 1029);
    return NULL;
}

int i_t[4] = {0};
*/

/*
int e_4116_TP(char buf[4116], int readSize) {
    pthread_t t[4];
    for (int i = 0; i < 3; ++i) {
        substr2(t_b[i], buf, 1029 * i, 1029);
        i_t[i] = i;
        pthread_create(&(t[i]), NULL, T_fun, &(i_t[i]));
    }
    for (int j = 0; j < 4; ++j) {
        pthread_join(t[j], NULL);
    }
}

*/
int eD(const char *fN, const char *D_fN) {
    FILE *fp, *fpO;
    if ((fp = fopen(fN, "rb")) == NULL) {
        printf("fopen error. \n");
        return EOF;
    }
    if ((fpO = fopen(D_fN, "wb")) == NULL) {
        printf("fopen error. \n");
        return EOF;
    }
    dl fS = getFileSize(fp), a = fS / ERS;
    printf("size: %lld\n", fS);
    clock_t c1 = clock();
    int b = (int) (fS % ERS);
    char r[ERS] = {0};
    char R[DRS] = {0};
    char b1[8] = {0, 0, 0, 0, 0, 'z', 'h', 'c'};
    b1[0] = (char) (fS % 7);
    fwrite(b1, 8, 1, fpO);
    for (int i = 0; i < a; ++i) {
        fread(r, ERS, 1, fp);
        e_1029P(R, r, 1029);
        fwrite(R, DRS, 1, fpO);
        if (!(i % 20000)) printf("progress: %f%%\n", (double) i / (double) a * 100);
    }
    if (b) {
        memset(r, 0, ERS);
        fread(r, b, 1, fp);
        int rL = e_1029P(R, r, b);
        fwrite(R, rL, 1, fpO);
    }
    clock_t c2 = clock();
    fclose(fp);
    fclose(fpO);
    printf("progress: 100.000000%%\n"
           "speed: %fMB/s", (fS / (c2 - c1 + .1)) / 1048.576);
    return 0;
}

int dD(const char *fN, const char *D_fN) {
    FILE *fp, *fpO;
    if ((fp = fopen(fN, "rb")) == NULL) {
        printf("fopen error. \n");
        return EOF;
    }
    dl fS = getFileSize(fp) - 8, a = fS / DRS;
    printf("size: %lld\n", fS + 8);
    int b = fS % DRS;
    char r[DRS] = {0};
    char R[ERS] = {0};
    int fC = 0;
    fread(r, 8, 1, fp);
    char b1[8] = {0, 0, 0, 0, 0, 'z', 'h', 'c'};
    int f_ck = 0;
    for (int j = 1; j < 8; ++j) {
        f_ck += (r[j] != b1[j]);
    }
    if (f_ck > 0) {
        printf("not Base128 encoded\n");
        return -2;
    }
    if ((fpO = fopen(D_fN, "wb")) == NULL) {
        printf("fopen error. \n");
        return EOF;
    }
    clock_t c1 = clock();
    fC = r[0] & 255;
    for (int i = 0; i < a; ++i) {
        if (!(i % 20000)) printf("progress: %f%%\n", (double) i / (double) a * 100);
        fread(r, DRS, 1, fp);
        d_1176P(R, r, DRS);
        fwrite(R, ERS, 1, fpO);
    }
    if (b) {
        fread(r, b, 1, fp);
        int rL = d_1176P(R, r, b);
        fwrite(R, rL + fC - 7, 1, fpO);
    }
    clock_t c2 = clock();
    fclose(fp);
    fclose(fpO);
    printf("progress: 100.000000%%\n"
           "speed: %fMB/s", ((fS + 8) / (c2 - c1 + .1)) / 1048.576);
    return 0;
}

void NewFileName(char **Dest, const char *filePath) {
    int x = 2;
    while (1) {
        char *xS = NULL;
//        itoa(x, xS, 10);
        m_itoa(&xS, x);
        strcpyAndCat_auto(Dest, filePath, -1, " ", -1);
        strcpyAndCat_auto(Dest, *Dest, -1, "(", -1);
        strcpyAndCat_auto(Dest, *Dest, -1, xS, -1);
        strcpyAndCat_auto(Dest, *Dest, -1, ")", -1);
        if (access(*Dest, F_OK) == EOF) break;
        ++x;
        free(xS);
    }
}