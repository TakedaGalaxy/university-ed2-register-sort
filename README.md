# Projeto de Ordenação de Arquivos Binários

Este projeto implementa um algoritmo para ordenar arquivos com registros randomizados em formato binário, utilizando memória limitada. A solução envolve dividir o arquivo em blocos, ordená-los individualmente com o algoritmo quicksort, e depois combinar os blocos ordenados utilizando buffers e o algoritmo de intercalação k-way merge para produzir um arquivo final ordenado.

## Estrutura do Projeto

- **lib/utils**: Funções utilitárias para operações auxiliares.
- **lib/quick-sort**: Implementação do algoritmo quicksort.
- **lib/file-generator**: Gerador de arquivos binários com registros aleatórios.
- **lib/file-buffer**: Implementação dos buffers de entrada e saída.
- **lib/commands**: Comandos disponíveis para gerar, converter, e ordenar arquivos.

## Pré-requisitos

- **Compilador C++**: Para compilar o código-fonte.
- **PowerShell**: Para medir o tempo de execução, se necessário.
- **Windows OS** (Recomendado): O código foi testado em uma máquina Windows.

## Compilação
Utilizando a ferramenta makefile.

```bash
make
```
## Comandos

O executavel pode realizar 3 comandos.

### Gerar dados aleatorios
```bash
./out/main.exe -g <caminho do arquivo+nome> <quantidade de registros> <seed>
```

### Organizar dados
```bash
./out/main.exe -s <caminho+nome do arquivo de entrada> <quantidade de bytes para usar> <quantidade de bytes para buffer de saída> <caminho+nome do arquivo de saída>
```

### Converter para txt legível
```bash
./out/main.exe -r <caminho+nome do arquivo bin> <caminho+nome do arquivo de saída txt>
```