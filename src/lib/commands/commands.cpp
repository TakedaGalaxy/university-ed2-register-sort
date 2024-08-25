#include "./commands.hpp"

int commandGenerateFile(int argc, char **argv)
{
  if (argc < 3 || argc > 5)
  {
    std::cout << "Invalid parameters !";
    return 1;
  }

  std::string path = argv[2];
  std::string quantityRegisters = argc >= 4 ? argv[3] : "512000";
  std::string seed = argc == 5 ? argv[4] : "42";

  std::cout << "Generating...\n";

  gerar_array_iv(path.c_str(), atoi(quantityRegisters.c_str()), atoi(seed.c_str()));

  std::cout << "Generated with " << quantityRegisters << " records !" << std::endl;
  return 0;
}

int commandConvertFileToTxt(int argc, char **argv)
{
  if (argc < 3 || argc > 4)
  {
    std::cout << "Invalid parameters !";
    return 1;
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

  return 0;
}

int commandSortFile(int argc, char **argv)
{
  if (argc < 3 || argc > 5)
  {
    std::cout << "Invalid parameters !";
    return 1;
  }

  std::string path = argv[2];

  std::string bytesToUse = argv[3];
  std::string outputBuzzerSize = argv[4];

  auto nBlocks = segmentAndSort<ITEM_VENDA>(path, atoll(bytesToUse.c_str()));

  void *memory = operator new[](sizeof(FileBufferIn<ITEM_VENDA>) * nBlocks);

  FileBufferIn<ITEM_VENDA> *bufffers = static_cast<FileBufferIn<ITEM_VENDA> *>(memory);

  uint64_t sizeBuffer = atoll(bytesToUse.c_str()) / nBlocks;

  for (int i = 0; i < nBlocks; i++)
  {
    std::string path = "./p" + std::to_string(i) + ".bin";

    new (&bufffers[i]) FileBufferIn<ITEM_VENDA>(path, sizeBuffer);

    std::cout << i << " " << bufffers[i].getNext().id << std::endl;
  }

  auto bufferOut = FileBufferOut<ITEM_VENDA>("text.bin", atoll(outputBuzzerSize.c_str()));

  while (true)
  {
    auto result = getIndexNextMin<ITEM_VENDA>(bufffers, nBlocks);

    if (result.isAllEmpty)
      break;

    auto item = bufffers[result.index].getNext();

    bufferOut.add(item);
  }

  bufferOut.save();

  for (int i = 0; i < nBlocks; i++)
  {
    bufffers[i].~FileBufferIn();
  }

  bufferOut.~FileBufferOut();

  return 0;
}