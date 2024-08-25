#pragma once

#include <iostream>
#include <cstdint>

#include "../file-buffer/file-buffer-in.hpp"
#include "../file-buffer/file-buffer-out.hpp"
#include "../quick-sort/quick-sort.hpp"
#include "../file-generator/big-file.h"

void removeSegments(uint64_t nBlocks);

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

  ReturnGetIndexNextMin returnValue;

  returnValue.index = iMin;
  returnValue.isAllEmpty = isAllEmpty;

  return returnValue;
};

template <typename T>
uint64_t segmentAndSort(std::string path, uint64_t blockSizeBytes)
{
  auto inputFile = fopen(path.c_str(), "rb");

  if (inputFile == NULL)
    return 0;

  uint64_t nRecords = blockSizeBytes / sizeof(T);

  std::cout << "nBlock = " << nRecords << std::endl;

  auto records = new T[nRecords];

  uint64_t i = 0;

  while (1)
  {
    auto nRead = fread(records, sizeof(T), nRecords, inputFile);

    if (nRead <= 0)
      break;

    quickSort<ITEM_VENDA>(records, 0, nRead - 1);

    std::string pathOutFile = "./p" + std::to_string(i) + ".bin";

    auto outFile = fopen(pathOutFile.c_str(), "wb");

    fwrite(records, sizeof(T), nRead, outFile);

    fclose(outFile);

    i++;
  }

  fclose(inputFile);

  return i;
};
