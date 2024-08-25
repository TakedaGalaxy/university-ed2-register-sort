#include "main.hpp"

int main(int argc, char **argv)
{

  std::string rootPath = argv[0];

  if (argc <= 1)
  {
    std::cout << "Missing parameters !";
    return 0;
  }

  std::string command = argv[1];

  if (command == "-g" || command == "generate")
    return commandGenerateFile(argc, argv);

  if (command == "-r" || command == "read")
    return commandConvertFileToTxt(argc, argv);

  if (command == "-s" || command == "sort")
    return commandSortFile(argc, argv);

  std::cout << "Command not found !";

  return 1;
}
