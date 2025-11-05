# External Merge Sort — Projeto

## Descrição

Implementação didática de Ordenação Externa (external merge sort) em C. O projeto traz dois programas principais:

- `gerador` — gera um arquivo de números inteiros (texto) que servirá de entrada.
- `ordenacao` — realiza a ordenação externa: divide o arquivo em blocos que cabem na memória, ordena cada bloco e intercala os blocos para produzir o arquivo final ordenado.

## Requisitos

- gcc (compilador C) e make
- No Windows, recomenda-se MSYS2/MinGW, Git Bash ou WSL para obter `make` e utilitários POSIX.
- Espaço em disco suficiente: o gerador pode criar arquivos muito grandes por padrão — ver seção "Avisos importantes".


## Compilação

Abra um terminal na pasta `Projeto` e execute:

```powershell
cd "C:\Users\<você>\...\external-mergesort\external-mergesort\Projeto"
make
```

Isso gera os executáveis `gerador` e `ordenacao` (no Windows podem aparecer como `gerador.exe` e `ordenacao.exe`).

Para limpar artefatos de compilação:

```powershell
make clean
```

## Uso rápido

1) Gerar dados de teste (arquivo `../Dados/dados.txt`):

```powershell
.\gerador.exe
# ou ./gerador (em ambientes Unix)
```

2) Ordenar os dados gerados (arquivo de saída `../Dados/dados_ordenados.txt`):

```powershell
.\ordenacao.exe
# ou ./ordenacao
```

## Detalhes da execução

- `gerador` grava os números em `../Dados/dados.txt`.
- `ordenacao`:
  - lê `../Dados/dados.txt`;
  - divide em blocos de tamanho configurado no código;
  - ordena cada bloco em memória e grava como `../Dados/bloco_*.txt`;
  - intercala todos os blocos gerando `../Dados/dados_ordenados.txt`;
  - remove os arquivos temporários `../Dados/bloco_*.txt`.

Os arquivos temporários são usados para manter a memória sob controle durante a ordenação de grandes volumes.


## Avisos importantes

- Espaço em disco: o valor padrão em `gerador.c` pode gerar arquivos muito grandes. Antes de rodar, ajuste `totalNumeros` e `tamBloco` se necessário.
- Tempo: gerar/ordenar grandes volumes pode levar muito tempo.
- Permissões: verifique se `../Dados` existe e está gravável.


## Estrutura do repositório

- `Dados/` — arquivos de entrada/saída e temporários (`dados.txt`, `dados_ordenados.txt`, `bloco_*.txt`).
- `Projeto/` — código-fonte e `Makefile`:
  - `Gerador/gerador.c`
  - `Ordenacao/ordenacao.c`, `Ordenacao/ordenacaoArquivo.c`, `Ordenacao/ordenacao.h`


## Autores

- [Carlos Eduardo Pereira dos Santos](https://github.com/pereira-devcarlos)
- [Marcos Felipe dos Reis Bento](https://github.com/MarcosBento06)
- [Guilherme de Oliveira Aredes](https://github.com/aredesog)