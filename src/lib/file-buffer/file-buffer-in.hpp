#pragma once

template <typename T>
class FileBufferIn
{
private:
  FILE *file;
  uint64_t bufferSize;
  uint64_t nItens;
  uint64_t currentIndex;
  T *buffer;
  bool empty = false;

  void storeNextBlock()
  {
    if (this->isEmpty())
      return;

    this->nItens = fread(this->buffer, sizeof(T), this->bufferSize, this->file);
    this->currentIndex = 0;

    if (this->nItens <= 0)
    {
      this->empty = true;
      return;
    }
  }

public:
  FileBufferIn(std::string path, uint64_t bufferSize)
  {
    this->file = fopen(path.c_str(), "rb");

    if (this->file == NULL)
      throw "Error on open file";

    this->bufferSize = bufferSize / sizeof(T);
    this->buffer = new T[this->bufferSize];

    this->storeNextBlock();
  }

  T viewNext()
  {
    // Pode estar vazio
    return this->buffer[this->currentIndex];
  }

  T getNext()
  {
    T item = this->buffer[this->currentIndex];
    this->currentIndex += 1;

    if (this->currentIndex >= this->nItens)
      this->storeNextBlock();

    return item;
  }

  bool isEmpty()
  {
    return this->empty;
  }

  ~FileBufferIn()
  {
    fclose(this->file);
    delete[] this->buffer;
  }
};