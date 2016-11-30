#include <iostream>
#include <string>
#include <sqlite3.h>

// for usage of SQlite and C/C++ have a look at
// https://www.tutorialspoint.com/sqlite/sqlite_c_cpp.htm

using namespace std;
 
int main(){
	// create database pointer
	sqlite3* Database;
	string Path;

	cout << "Please enter path to database file ";
	cin >> Path;

	// open database
	if(sqlite3_open(Path.c_str(), &Database) != SQLITE_OK){
		cout << "Error while opening " << sqlite3_errmsg(Database) << endl;
		// exit program
		return 1;
	}

	


	sqlite3_close(Database);
	return 0;   
}
