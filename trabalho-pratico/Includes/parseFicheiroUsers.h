#pragma once
#include "users.h"

userInfo* parseUsersCsvLine(char* linha);

void separateWordsUsers(Catalog* catalogo, char *ficheiro);
