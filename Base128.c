//#define ARR_len(x) sizeof(x) / sizeof(x)[0]
#include "Base128Lib.h"



int main(/*const */int argc, char *argv[]) {
    if (argc < 3) {
        printf("%s", "Base128\nCommand [-encode | -decode] [[filePath]] [[DestFilePath]] |\n"
                     "Command [-encode | -decode] [[filePath]]");
        return 'P';
    }
    char dA[strlen(argv[1]) + 1];
    ToUpperCase(dA, argv[1]);
    int d = (!strcmp(dA, "-DECODE")) ? 1 : 0;
    char FileName[strlen(argv[2]) + 1], DestFileName[strlen(argv[argc == 3 ? 2 : 3]) + 1 + ((argc == 3) ? 4 : 0)];
    strcpy(FileName, argv[2]);
    char zFN[strlen(argv[2]) + 1 + ((argc == 3) ? 4 : 0)];
    if (argc == 3) {
        NewFileName(zFN, argv[2]);
        strcpy(DestFileName, zFN);
    } else if (argc == 4) {
        strcpy(DestFileName, argv[3]);
    }
    if (!d) {
        printf("%s", "Encoding...\n");
        eD(FileName, DestFileName);
        /*long long a = fileSize / 7LL;
        int b = (int) (fileSize % 7LL);
        char b1[8] = {0, 0, 0, 0, 0, 'z', 'h', 'c'};
        b1[0] = (char) b;
        fwrite(b1, 8, 1, fpO);
        char r[7] = {""};
        for (long long i = 0; i < a; ++i) {
            fread(r, 7, 1, fp);
            if (i % 374490LL == 0) {
                printf("progress: %f%%\n", (float) 100 * ((float) (7 * (i + 1)) / (float) fileSize));
            }
            static char s0[57] = {""};
            static char itoaR[9] = {""};
            strcpy(s0, "");
            for (int k = 0; k < 7; ++k) {
                itoa(((int) r[k]) & 0xFF, itoaR, 2);
                char len_To_8R[9] = {""};
                NumStr_lenTo(len_To_8R, itoaR, 8);
                strcat(s0, len_To_8R);
            }
            String_56_DivideInto(s0, 7);
            char wR[8] = {""};
            for (int l = 0; l < DivideR_len; ++l) {
                wR[l] = (char) BinToDec(DivideR[l]);
            }
            fwrite(wR, 8, 1, fpO);
        }
        if (b != 0) {
            memset(r, 0, 7);
            fread(r, 7, 1, fp);
            static char s0[57] = {""};
            static char itoaR[9] = {""};
            strcpy(s0, "");
            for (int k = 0; k < 7; ++k) {
                itoa(((int) r[k]) & 0xFF, itoaR, 2);
                char len_To_8R[9] = {""};
                NumStr_lenTo(len_To_8R, itoaR, 8);
                strcat(s0, len_To_8R);
            }
            s0[56] = 0;
            String_56_DivideInto(s0, 7);
            char wR[8] = {""};
            for (int l = 0; l < DivideR_len; ++l) {
                wR[l] = (char) BinToDec(DivideR[l]);
            }
            fwrite(wR, 8, 1, fpO);
        }*/
    } else {
        printf("%s", "Decoding...\n");
        dD(FileName, DestFileName);
    }
    if (argc == 3) {
        remove(argv[2]);
        rename(zFN, argv[2]);
    }
    return 0;
}