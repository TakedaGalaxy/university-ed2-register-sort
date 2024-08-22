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
  {
    if (argc < 3 | argc > 5)
    {
      std::cout << "Invalid parameters !";
      return 0;
    }

    std::string path = argv[2];

    std::string quantityRegisters = argc == 4 ? argv[3] : "512000";
    std::string seed = argc == 5 ? argv[4] : "42";

    std::cout << "Generating...\n";

    gerar_array_iv(path.c_str(), atoi(quantityRegisters.c_str()), atoi(seed.c_str()));

    std::cout << "Generated with " << quantityRegisters << " records !";
    return 1;
  }

  if (command == "-s" || command == "sort")
  {
    if (argc < 3 | argc > 4)
    {
      std::cout << "Invalid parameters !";
      return 0;
    }

    return 1;
  }

  std::cout << "Command not found !";

  return 0;
}