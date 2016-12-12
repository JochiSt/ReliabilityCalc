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
 		 * constructor
 		 * \param filename filename (incl. path) of the databasefile
 		 */
		sqlite3_handler(std::string filename);
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

	protected:

	private:
		sqlite3 *db;

};

#endif
