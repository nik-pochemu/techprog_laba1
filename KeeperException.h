#pragma once
#include <stdexcept>
#include <iostream>
using namespace std;
class KeeperException : public exception {
public:
	KeeperException(const char* msg);
};