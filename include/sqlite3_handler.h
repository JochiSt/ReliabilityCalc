#ifndef SQLITE3_HANDLER_H
#define SQLITE3_HANDLER_H

#include <sqlite3.h>
#include <string>

/**
 * \brief SQLite3 handler
 * \author Jochen Steinmann
 * \date 2016-11-29
 * \version 1.0
 *
 * Connect to a database via the SQLite3 API
 */

class sqlite3_handler {
	public:
		/**
		 * constructor of sqlite3 handler
		 * \param[in] filename path to database file
		 * \param[in] flags options for opening the database. 
		 * 			When records in database should be created use SQLITE_OPEN_READWRITE
		 */
		sqlite3_handler(std::string filename, int flags = SQLITE_OPEN_READONLY);

		virtual ~sqlite3_handler();

		/**
 		 * perfrom SQL query without return
 		 * \param sql sql statement
 		 */
		void runSQL(std::string sql);

		/**
 		 * perfrom SQL query with a single return
 		 * \param[in]	sql	sql statement
 		 * \param[out]	ret1	first return statement
 		 */
		void runSQL(std::string sql, std::string &ret1);

		/**
 		 * perfrom SQL query with a single return
 		 * \param[in]	sql	sql statement
 		 * \param[out]	ret1,ret2	return statements
 		 */
		void runSQL(std::string sql, std::string &ret1, std::string &ret2);

		/**
 		 * perfrom SQL query with a single return
 		 * \param[in]	sql	sql statement
 		 * \param[out]	ret1,ret2,ret3	return statements
 		 */
		void runSQL(std::string sql, std::string &ret1, std::string &ret2, std::string &ret3);

		/**
 		 * perfrom SQL query with a single return
 		 * \param[in]	sql	sql statement
 		 * \param[out]	ret1,ret2,ret3,ret4	return statementments
 		 */
		void runSQL(std::string sql, std::string &ret1, std::string &ret2, std::string &ret3, std::string &ret4);

		/**
		 * does the table exist?
		 */
		bool existsTable(std::string tablename);

	protected:

	private:
		sqlite3 *db;

};

#endif
