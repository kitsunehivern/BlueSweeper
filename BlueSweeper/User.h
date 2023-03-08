#ifndef USER_H
#define USER_H

#include <string>

#include "Table.h"

struct User {
private:
	std::string username, password;

public:
	User();
	User(std::string, std::string);
	std::string getUsername();
	std::string getPassword();
	void changePassword(std::string);
};

#endif