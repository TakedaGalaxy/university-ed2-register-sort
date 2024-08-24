#include "main.hpp"

// Função auxiliar para trocar dois elementos
template <typename T>
void swap(T* a, T* b)
{
    T temp = *a;
    *a = *b;
    *b = temp;
}

// Função que realiza a partição e retorna o índice do pivô
template <typename T>
int partition(T arr[], int low, int high)
{
    T pivot = arr[high];  // Escolhe o último elemento como pivô
    int i = (low - 1);    // Índice do menor elemento

    for (int j = low; j < high; j++)
    {
        // Se o elemento atual é menor ou igual ao pivô
        if (arr[j] <= pivot)
        {
            i++;  // Incrementa o índice do menor elemento
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

// Função principal do Quick Sort
template <typename T>
void quickSort(T arr[], int low, int high)
{
    if (low < high)
    {
        // Índice de partição
        int pi = partition(arr, low, high);

        // Ordena os elementos antes e depois da partição
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}


template <typename T>
uint64_t segmentAndSort(std::string path, uint64_t blockSizeBytes)
{
  auto inputFile = fopen(path.c_str(), "rb");

  uint64_t nRecords = blockSizeBytes / sizeof(T);

  std::cout << "n = " << nRecords << std::endl;

  auto records = new T[nRecords];

  uint64_t i = 0;

  while (1)
  {
    auto nRead = fread(records, sizeof(T), nRecords, inputFile);

    if (nRead <= 0)
      break;

    quickSort<ITEM_VENDA>(records, 0, nRead);

    std::string pathOutFile = "./p" + std::to_string(i) + ".bin";

    auto outFile = fopen(pathOutFile.c_str(), "wb");

    fwrite(records, sizeof(T), nRead, outFile);

    fclose(outFile);

    i++;
  }

  fclose(inputFile);

  return i;
}

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
    if (argc < 3 || argc > 5)
    {
      std::cout << "Invalid parameters !";
      return 0;
    }

    std::string path = argv[2];

    std::string bytesToUse = argv[3];
    std::string outputBuzzerSize = argv[4];

    auto nBlocks = segmentAndSort<ITEM_VENDA>(path, atoll(bytesToUse.c_str()));

    std::cout << "nBLOCKS = " << nBlocks << std::endl;

    return 1;
  }

  std::cout << "Command not found !";

  return 0;
}
