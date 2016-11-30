#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

#include <cmath>
#include <string.h>
#include "sqlite3_handler.h"

int main(){
    cout << "Import WUERTH reliability data" << endl;
    cout << "\tcompiled @ " << __DATE__ << " " << __TIME__ << " using GCC " << __VERSION__ << endl << endl;

    float table;
    char curve;

    cout << "Table: " << endl;
    cin >> table;

    cout << "Curve: " << endl;
    cin >> curve;

    printf("Will fill %3.1f %c\n", table, curve);

    sqlite3_handler db("../../wuerth.db");

    std::string filename;
    cout << "Insert filename of table: " << endl;
    cin >> filename;

    ifstream in;
    in.open(filename.c_str());

    float temperature, value;
    char query[1024];
    while(true){
        in >> temperature >> value;
        if(!in.good()) break;
        sprintf(query, "INSERT INTO reliability_data ('table', 'curve', 'temperature', 'FIT') VALUES ('%3.1f', '%c', '%f', '%f')", table, curve, temperature, value);
        printf("%s\n", query);

        db.runSQL(std::string(query));
    }
    // INSERT INTO reliability_data ('table', 'curve', 'temperature', 'FIT') VALUES ('5.7', 'f', '40', '0.05')


    return 0;
}
