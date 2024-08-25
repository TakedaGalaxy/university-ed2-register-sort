#pragma once

#include <iostream>

#include "../file-generator/big-file.h"
#include "../file-buffer/file-buffer-in.hpp"
#include "../file-buffer/file-buffer-out.hpp"
#include "../quick-sort/quick-sort.hpp"
#include "../utils/utils.hpp"
#include "../commands/commands.hpp"

// Usado para gerar arquivo via linha de comando
int commandGenerateFile(int argc, char **argv);

// Usado para converter lista de dados em texto
int commandConvertFileToTxt(int argc, char **argv);

// Usado para ordenar o arquivo
int commandSortFile(int argc, char **argv);
