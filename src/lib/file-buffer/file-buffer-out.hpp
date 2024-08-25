#pragma once

template <typename T>
class FileBufferOut
{
private:
  FILE *file;
  uint64_t bufferSize;
  uint64_t nItens = 0;
  T *buffer;

public:
  FileBufferOut(std::string path, uint64_t bufferSize)
  {
    this->file = fopen(path.c_str(), "wb");
    this->bufferSize = bufferSize / sizeof(T);
    this->buffer = new T[this->bufferSize];
  }

  ~FileBufferOut()
  {
    fclose(this->file);
    delete[] this->buffer;
  }

  void add(T item)
  {
    if (this->nItens >= this->bufferSize)
    {
      fwrite(this->buffer, sizeof(T), this->nItens, file);
      this->nItens = 0;
    }

    this->buffer[this->nItens] = item;
    this->nItens++;
  }

  void save()
  {
    if (this->nItens > 0)
    {
      fwrite(this->buffer, sizeof(T), this->nItens, file);
      this->nItens = 0;
    }
  }
};