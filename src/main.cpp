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
    if (argc < 3 || argc > 5)
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

  if (command == "-r" || command == "read")
  {
    if (argc < 3 || argc > 4)
    {
      std::cout << "Invalid parameters !";
      return 0;
    }

    std::string path = argv[2];
    std::string pathToSave = argc == 4 ? argv[3] : "out.txt";

    auto file = fopen(path.c_str(), "rb");

    if (file == nullptr)
    {
      std::cout << "Failed to open file !";
      return 0;
    }

    auto outFile = fopen(pathToSave.c_str(), "w");

    std::cout << "Start reading..." << std::endl;

    ITEM_VENDA item;
    while (fread(&item, sizeof(ITEM_VENDA), 1, file) == 1)
    {
      fprintf(outFile, ">id:%lu,id_venda:%lu,data:%lu,desconto:%.2f,desc:%s\n",
              item.id, item.id_venda, item.data, item.desconto, item.desc);
    }

    std::cout << "Completed !" << std::endl;

    fclose(file);
    fclose(outFile);

    return 1;
  }

  if (command == "-s" || command == "sort")
  {
    if (argc < 3 || argc > 4)
    {
      std::cout << "Invalid parameters !";
      return 0;
    }

    std::string path = argv[2];

    ITEM_VENDA *item = new ITEM_VENDA;

    std::cout << "Reading !" << std::endl;

    auto file = fopen(path.c_str(), "rb");

    if (file == nullptr)
    {
      std::cout << "Failed to open file !";
      return 0;
    }

    while (fread(item, sizeof(ITEM_VENDA), 1, file) == 1)
    {
      std::cout << "ITEM:" << std::endl;
      std::cout << item->id << std::endl;
      std::cout << item->desc << std::endl;
      std::cout << "END" << std::endl;
    }

    fclose(file);

    return 1;
  }

  std::cout << "Command not found !";

  return 0;
}
