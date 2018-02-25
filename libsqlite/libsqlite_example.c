#include <stdio.h>
#include <sqlite3.h>

int callback(void* user_data, int argc, char* argv[], char* field[]) {
    int i;
    int* counter = (int*)user_data;

    printf("callback(%d) : ", ++(*counter));
    for (int i=0; i<argc; i++) {
        printf("%s(%s), ", field[i], argv[i]);
    }
    printf("\n");

    return 0;
}

int main(int argc, char* argv[]) {
    sqlite3* db;
    char* err_msg = NULL;
    int rc;
    int counter = 0;

    if ((rc = sqlite3_open_v2(argv[1], &db, SQLITE_OPEN_READONLY, NULL)) != SQLITE_OK)
        return 1;

    if ((rc = sqlite3_exec(db, argv[2], callback, &counter, &err_msg)) != SQLITE_OK) {
        puts(err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 1;
    }

    printf("%d callbacks called\n", counter);
    sqlite3_close(db);
    return 0;
}
