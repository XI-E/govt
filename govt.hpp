#ifndef GOVT_HPP
#define GOVT_HPP

#include <iostream>
#include <string>
#include "society.hpp"
#include "sqlite3.h"
#include "rlutil.h"

#define CURRENCY (char) 167

typedef unsigned long long ull;

namespace govt{
	human matchhuman(ull id){
		sqlite3 *ppdb;
		human temp;

		if(sqlite3_open("govt.db", &ppdb) != SQLITE_OK){
			std::cout << "Database open error!" << std::endl;
			std::cout << sqlite3_errmsg(ppdb);
		}	

		sqlite3_stmt *cmpld_stmt;
		char stmt[] = "SELECT * FROM human WHERE UID = ?1";
		const char *end = stmt + strlen(stmt);

		if(sqlite3_prepare_v2(ppdb, stmt, strlen(stmt), &cmpld_stmt, &end) != SQLITE_OK){
			std::cout << "SQL statement compile error!" << std::endl;
			std::cout << sqlite3_errmsg(ppdb);
		}

		sqlite3_bind_int(cmpld_stmt, 1, id);
	
		auto flag = sqlite3_step(x);		

		if(flag == SQLITE_DONE || flag == SQLITE_ROW){
			std::cout << std::endl << "SQL execution error" << std::endl;
			std::cout << sqlite3_errmsg(ppdb);
		}

		/*
			SQL Column return order
				
				1. UID[INT]
				2. Name[CHAR *]
				3. Age[INT]
				4. Year of birth[INT]
				5. Residence ID (HID)[INT]
				6. Parent 1 UID[INT]
				7. Parent 2 UID[INT]
				8. Sex (0 for male, 1 for female)[INT]
				9. Cash on hand[INT]
				10. Adult (0 for false, 1 for true)[INT]
				11. Bank Account number[INT]
				12. Loan ID (LID), if any, else 0[INT]
				13. Spouse UID, if any, else 0[INT]
				14. Prez Candidate (0/1 false/true)[INT]
				15. Vote (candidate number)[INT]

		*/

		temp.UID = sql_column_int(cmpld_stmt, 0);
		temp.name = string (sql_column_text(cmpld_stmt, 1));
		temp.age = sql_column_int(cmpld_stmt, 2);
		temp.year = sql_column_int(cmpld_stmt, 3);
		temp.residence = sql_column_int(cmpld_stmt, 4);
		temp.parent_UID[0] = sql_column_int(cmpld_stmt, 5);
		temp.parent_UID[1] = sql_column_int(cmpld_stmt, 6);
		temp.sex = sql_column_int(cmpld_stmt, 7);
		temp.cash = sql_column_int(cmpld_stmt, 8);
		temp.adult = sql_column_int(cmpld_stmt, 9);
		temp.acc = sql_column_int(cmpld_stmt, 10);
		temp.loan = sql_column_int(cmpld_stmt, 11);
		temp.spouse = sql_column_int(cmpld_stmt, 12);
		temp.prez_cand = sql_column_int(cmpld_stmt, 13);
		temp.vote = sql_column_int(cmpld_stmt, 14);

		return temp;
	}

	namespace bank{
		;
	}
}


#endif
