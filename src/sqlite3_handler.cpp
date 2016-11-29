#include "sqlite3_handler.h"
#include <stdio.h>
#include <stdlib.h>

sqlite3_handler::sqlite3_handler(std::string filename){
	/* Open database */
	//int ret = sqlite3_open(filename.c_str(), db);
	int ret = sqlite3_open_v2(filename.c_str(), &db, SQLITE_OPEN_READONLY, NULL);
	if( ret ){
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		exit(-1);
	}else{
		fprintf(stdout, "Opened database %s successfully\n", filename.c_str());
	}
}

sqlite3_handler::~sqlite3_handler(){
	   sqlite3_close(db);
}
