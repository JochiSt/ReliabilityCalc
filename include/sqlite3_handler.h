#ifndef SQLITE3_HANDLER_H
#define SQLITE3_HANDLER_H

#include <sqlite3.h>
#include <string>

class sqlite3_handler {
	public:
		sqlite3_handler(std::string filename);
		virtual ~sqlite3_handler();

	protected:

	private:
		sqlite3 *db;

};

#endif
