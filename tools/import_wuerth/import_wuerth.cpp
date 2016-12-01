#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

#include <cmath>
#include <string.h>
#include "sqlite3_handler.h"

int main(int argc, char* argv[]){
    cout << "Import WUERTH reliability data" << endl;
    cout << "\tcompiled @ " << __DATE__ << " " << __TIME__ << " using GCC " << __VERSION__ << endl << endl;

    float table;
    char curve;

    cout << "Table: " << endl;
    cin >> table;

    cout << "Curve: " << endl;
    cin >> curve;

    printf("Will fill %3.1f %c\n", table, curve);

//    sqlite3_handler db("../../wuerth.db");

    std::string filename;

    if(argc > 1){
	filename = std::string(argv[1]);
    }else{
        cout << "Insert filename of table: " << endl;
        cin >> filename;
    }

    ifstream in;
    in.open(filename.c_str());

    std::string line;
    getline(in, line);
    std::cout << line << std::endl;

    float temperature, value;
    char query[1024];

    ofstream out;
    char filen[2014];
    sprintf(filen, "%3.1f_%c.sql", table, curve);
    out.open(filen);

    int column;
    cout << "Which column to use: (temperature = 0): " << endl;
    cin >> column;

    float value1, value2, value3, value4;

    while(true){
	char buffer[4096];
	getline(in, line);
	sprintf(buffer, "%s", line.c_str());
	sscanf(buffer, "%f %f %f %f %f", &temperature, &value1, &value2, &value3, &value4);
//        in >> temperature >> value;

	if(column == 1) value = value1;
	else if(column == 2) value = value2;
	else if(column == 3) value = value3;
	else if(column == 4) value = value4;

        if(!in.good()) break;
        // INSERT INTO reliability_data VALUES (5.1, 'A', 0.003000, 0.751250, date('now') );
        sprintf(query, "INSERT INTO reliability_data VALUES (\"%3.1f\", \"%c\", \"%f\", \"%f\", date('now'));", table, curve, temperature, value);
        printf("%s\n", query);

        out << std::string(query) << endl;

//        db.runSQL(std::string(query));
    }
    out.close();
    return 0;
}
