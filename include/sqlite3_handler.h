#ifndef SQLITE3_HANDLER_H
#define SQLITE3_HANDLER_H

#include <sqlite3.h>
#include <string>

class sqlite3_handler {
	public:
		sqlite3_handler(std::string filename);
		virtual ~sqlite3_handler();

		void runSQL(std::string sql);
		void runSQL_r1(std::string sql, std::string &ret1);
		void runSQL_r2(std::string sql, std::string &ret1, std::string &ret2);
		void runSQL_r3(std::string sql, std::string &ret1, std::string &ret2, std::string &ret3);

	protected:

	private:
		sqlite3 *db;

};

#endif
