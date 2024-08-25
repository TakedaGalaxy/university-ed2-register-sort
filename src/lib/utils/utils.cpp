#include "./utils.hpp"

void removeSegments(uint64_t nBlocks)
{
  for (uint64_t i = 0; i < nBlocks; i++)
  {
    std::string path = "./p" + std::to_string(i) + ".bin";

    FILE *file = fopen(path.c_str(), "r");

    if (!file)
      continue;

    fclose(file);

    remove(path.c_str());
  }
}
