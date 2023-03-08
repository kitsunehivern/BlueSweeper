#include <iostream>
#include <fstream>
#include <filesystem>
#include <cassert>

#include "User.h"
#include "Tile.h"
#include "Table.h"

namespace fs = std::filesystem;

User::User() {
}

User::User(std::string _username, std::string _password) {
	username = _username;
	password = _password;
}

std::string User::getUsername() {
	return username;
}

std::string User::getPassword() {
	return password;
}

void User::changePassword(std::string newPassword) {
	password = newPassword;
}