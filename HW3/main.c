#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
// 定義樂透記錄結構
typedef struct lotto_record {
    int receipt_id;
    int receipt_price;
    char receipt_time[32];
    int lotto_set[5][7];
} lotto_record_t;


void buy_lotto(int n) {
    //宣告變數
    time_t curtime;
    lotto_record_t record;
    //樂透記錄結構
    int num;
    char filename[17];
    FILE* fout;
    FILE* frecord;
    FILE* frecord_check;
    
    //設定時間
    time(&curtime);
    strcpy(record.receipt_time, ctime(&curtime));
    record.receipt_time[24] = '\0';
    
    //判斷record.bin 在不在
    frecord_check = fopen("record.bin", "r");
    frecord = fopen("record.bin", "ab+");
    //在，讀取record.receipt_id 到num再加1
    if (frecord_check != NULL) {
        fseek(frecord, -sizeof(lotto_record_t), SEEK_END);
        fread(&num, sizeof(int), 1, frecord);
        num++;
        fclose(frecord_check);
    }
    //不在，record.receipt_id為1
    else {
        num = 1;
    }
    sprintf(filename, "lotto[%05d].txt", num);
    //將lotto[%05d].txt列印到字串filename中
    fout = fopen(filename, "a+");
    //a+ 附加 
    record.receipt_id = num;
    record.receipt_price = n*100;
    
    
    srand(curtime);
    int x = 0, y = 0, tmp;
    int generated[69];
    while (x < n) {
        tmp = rand() % 69 + 1;
        if (!generated[tmp]) {
            record.lotto_set[x][y] = tmp;
            generated[tmp] = 1;
            y++;
        }
        if (y == 7) {
            x++;
            y = 0;
            for (int i = 0; i < 69; i++) {
                generated[i] = 0;
            }
        }
    }
    
    //輸出結果
    fprintf(fout, "========= lotto649 =========\n");
    fprintf(fout, "========+ NO.%05d +========\n", num);
    fprintf(fout, "= %s =\n", record.receipt_time);
    for (int i = 0; i < 5; i++) {
        fprintf(fout, "[%d]: ", i + 1);
        if (i < n) {
            for (int j = 0; j < 7; j++) {
                fprintf(fout, "%02d ", record.lotto_set[i][j]);
            }
        }
        else {
            for (int j = 0; j < 7; j++) {
                fprintf(fout, "__ ");
            }
        }
        fprintf(fout, "\n");
    }
    fprintf(fout, "========= csie@CGU =========");
    fclose(fout);
    fwrite(&record, sizeof(lotto_record_t), 1, frecord);
    fclose(frecord);
}

void check_lotto(int prize_number[], int count) {
    //宣告變數
    lotto_record_t record;
    int n, num = 0;
    FILE* fp = fopen("record.bin", "rb");
    
    //紀錄有幾組樂透
    fseek(fp, 0, SEEK_SET);
    fseek(fp, -sizeof(lotto_record_t), SEEK_END);
    fread(&n, sizeof(int), 1, fp);
    
    //比較
    while(num < n) {
        fseek(fp, num*sizeof(lotto_record_t), SEEK_SET);
        fread(&record, sizeof(lotto_record_t), 1, fp);
        for(int i = 0; i < 5; i++) {
            for(int j = 0; j < 7; j++) {
                for(int k = 0; k <= count; k++) {
                    if (record.lotto_set[i][j] == prize_number[k]) {
                        printf("彩券 No. %d\n", record.receipt_id);
                        printf("售出時間：%s\n", record.receipt_time);
                        printf("號碼：");
                        for(int s = 0; s < 7; s++) {
                            printf("%02d ", record.lotto_set[i][s]);
                        }
                        printf("\n");
                        j = 7;
                        k = count + 1;
                    }    
                }
            }
        }
        num++;
    }
    fclose(fp);
}

int main() {
    int n;
    
    printf("請問你要買幾組樂透：");
    scanf("%d", &n);
    
    if(n == 0) {
        int count = 0;
        int prize_number[3];
        printf("請輸入中獎號碼(最多三個)：");
        while (count < 3) {
            scanf("%d", &prize_number[count]);
            if (getchar() =='\n' || count == 2) {
                break;
            }
            count++;
        }
        printf("輸入中獎號碼為：");
        for (int i = 0; i <= count; i++) {
            printf("%02d ", prize_number[i]);
        }
        printf("\n以下為中獎彩券：\n");
        check_lotto(prize_number, count);
    }
    else {
        buy_lotto(n);
    }

    return 0;
}
