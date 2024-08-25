#pragma once

#include <iostream>

struct ReturnGetIndexNextMin
{
  uint64_t index;
  bool isAllEmpty;
};

template <typename T>
ReturnGetIndexNextMin getIndexNextMin(FileBufferIn<T> *buffers, uint64_t n)
{
  uint64_t iMin = 0;
  bool isAllEmpty = true;
  T minItem;

  for (int i = 0; i < n; i++)
  {
    if (buffers[i].isEmpty())
      continue;

    if (isAllEmpty)
    {
      iMin = i;
      minItem = buffers[i].viewNext();
      isAllEmpty = false;
      continue;
    }

    if (minItem <= buffers[i].viewNext())
      continue;

    iMin = i;
    minItem = buffers[i].viewNext();
  }

  return {iMin, isAllEmpty};
};

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
};
