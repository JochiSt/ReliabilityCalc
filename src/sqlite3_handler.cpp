#include "sqlite3_handler.h"
#include <stdio.h>
#include <stdlib.h>

sqlite3_handler::sqlite3_handler(std::string filename){
	/* Open database */
	int ret = sqlite3_open_v2(filename.c_str(), &db, SQLITE_OPEN_READONLY, NULL);
	if( ret ){
		fprintf(stderr, "Can't open database: %s\n\t\t%s\n", filename.c_str(), sqlite3_errmsg(db));
		exit(-1);
	}else{
		fprintf(stdout, "Opened database %s successfully\n", filename.c_str());
	}
}

sqlite3_handler::~sqlite3_handler(){
	   sqlite3_close(db);
}

void sqlite3_handler::runSQL(std::string sql){
	int row = 0;
        sqlite3_stmt *selectStmt;
        sqlite3_prepare(db, sql.c_str(), sql.length()+1, &selectStmt, NULL);
        while (1) {
            int s;
            printf("in select while\n");
            s = sqlite3_step (selectStmt);
            if (s == SQLITE_ROW) {
                printf ("%s: %s\n", sqlite3_column_text(selectStmt, 0), sqlite3_column_text(selectStmt, 1));
                row++;
            }
            else if (s == SQLITE_DONE) {
                break;
            }
            else {
                fprintf (stderr, "Failed.\n");
                exit (1);
            }
        }
        sqlite3_finalize(selectStmt);
}

void sqlite3_handler::runSQL(std::string sql, std::string &ret1){
	sqlite3_stmt *selectStmt;
	sqlite3_prepare(db, sql.c_str(), sql.length()+1, &selectStmt, NULL);
	int s = sqlite3_step (selectStmt);
	ret1 = "-";
	if (s == SQLITE_ROW) {
		ret1 = std::string((const char*) sqlite3_column_text(selectStmt, 0));
	}
	sqlite3_finalize(selectStmt);
}
void sqlite3_handler::runSQL(std::string sql, std::string &ret1, std::string &ret2){
	sqlite3_stmt *selectStmt;
	sqlite3_prepare(db, sql.c_str(), sql.length()+1, &selectStmt, NULL);
	int s = sqlite3_step (selectStmt);
	ret1 = "-";
	ret2 = "-";
	if (s == SQLITE_ROW) {
		ret1 = std::string((const char*) sqlite3_column_text(selectStmt, 0));
		ret2 = std::string((const char*) sqlite3_column_text(selectStmt, 1));
	}
	sqlite3_finalize(selectStmt);
}
void sqlite3_handler::runSQL(std::string sql, std::string &ret1, std::string &ret2, std::string &ret3){
	sqlite3_stmt *selectStmt;
	sqlite3_prepare(db, sql.c_str(), sql.length()+1, &selectStmt, NULL);
	int s = sqlite3_step (selectStmt);
	ret1 = "-";
	ret2 = "-";
	ret3 = "-";
	if (s == SQLITE_ROW) {
		ret1 = std::string((const char*) sqlite3_column_text(selectStmt, 0));
		ret2 = std::string((const char*) sqlite3_column_text(selectStmt, 1));
		ret3 = std::string((const char*) sqlite3_column_text(selectStmt, 2));
	}
	sqlite3_finalize(selectStmt);
}
void sqlite3_handler::runSQL(std::string sql, std::string &ret1, std::string &ret2, std::string &ret3, std::string &ret4){
	sqlite3_stmt *selectStmt;
	sqlite3_prepare(db, sql.c_str(), sql.length()+1, &selectStmt, NULL);
	int s = sqlite3_step (selectStmt);
	ret1 = "-";
	ret2 = "-";
	ret3 = "-";
	ret4 = "-";
	if (s == SQLITE_ROW) {
		ret1 = std::string((const char*) sqlite3_column_text(selectStmt, 0));
		ret2 = std::string((const char*) sqlite3_column_text(selectStmt, 1));
		ret3 = std::string((const char*) sqlite3_column_text(selectStmt, 2));
		ret4 = std::string((const char*) sqlite3_column_text(selectStmt, 3));
	}
	sqlite3_finalize(selectStmt);
}
