#include "KeeperException.h"
#include <iostream>
#include <cstring>

using namespace std;

KeeperException::KeeperException(const char* msg) : exception(msg) {}