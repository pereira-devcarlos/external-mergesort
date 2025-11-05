# External Merge Sort — Projeto

Este repositório contém uma implementação didática de Ordenação Externa (external merge sort) em C, composta por dois programas principais:

- `gerador` — gera um arquivo de dados com números inteiros (texto) para serem ordenados.
- `ordenacao` — implementa a ordenação externa em arquivo texto: divide em blocos, ordena cada bloco em memória e intercalas os blocos para produzir o arquivo final ordenado.

Estrutura do repositório

- `Dados/` — local destinado aos arquivos de entrada/saída (`dados.txt`, `dados_ordenados.txt`) e blocos temporários gerados pelo processo.
- `Projeto/` — código-fonte e makefile.
  - `Gerador/gerador.c` — gerador de dados.
  - `Ordenacao/ordenacao.c`, `Ordenacao/ordenacaoArquivo.c`, `Ordenacao/ordenacao.h` — implementação da ordenação em memória (quicksort) e lógica de I/O e merge em arquivos.

Requisitos

- gcc (compilador C) e make
- No Windows é recomendado usar MSYS2/MinGW, Git Bash ou WSL para ter `make` e utilitários POSIX; o `Makefile` foi testado com gcc/make.
- Espaço em disco suficiente: o gerador pode criar arquivos muito grandes por padrão — ver seção "Avisos" abaixo.

Compilação

Abra um terminal na pasta `Projeto` e execute:

```powershell
cd "C:\Users\<você>\...\external-mergesort\external-mergesort\Projeto"
make
```

Isso deverá gerar os executáveis `gerador` e `ordenacao` (em Windows podem aparecer como `gerador.exe` e `ordenacao.exe`).

Limpeza

Para remover arquivos objeto e executáveis:

```powershell
make clean
```

Uso / Execução

1. Gerar os dados (arquivo `../Dados/dados.txt`):

```powershell
.\gerador.exe
# ou ./gerador (em ambientes Unix)
```

Por padrão o gerador grava em `../Dados/dados.txt` (caminho relativo ao diretório `Projeto`).

2. Ordenar o arquivo gerado (arquivo de saída `../Dados/dados_ordenados.txt`):

```powershell
.\ordenacao.exe
# ou ./ordenacao
```

O programa `ordenacao` realiza:
- leitura de `../Dados/dados.txt`;
- divisão em blocos (tamanho configurado no código); cada bloco é ordenado em memória e salvo como `../Dados/bloco_*.txt`;
- intercalação (merge) dos blocos ordenados gerando `../Dados/dados_ordenados.txt`;
- remoção dos arquivos temporários `../Dados/bloco_*.txt`.

Parâmetros e alteração do comportamento

- O tamanho dos blocos, número de linhas e paths estão definidos como constantes no código-fonte; para usar valores diferentes edite os arquivos fonte (`gerador.c` e `ordenacaoArquivo.c`) e recompile.
- Recomenda-se tornar os paths e tamanhos parâmetros via linha de comando se desejar flexibilidade — posso ajudar a parametrizar se quiser.

Avisos importantes

- Espaço em disco: o valor padrão no `gerador.c` gera uma quantidade massiva de números (a configuração inicial pode criar arquivos gigantescos — ver constantes no arquivo). Ajuste `totalNumeros` e `tamBloco` antes de gerar se não tiver espaço suficiente.
- Tempo de execução: gerar e ordenar grandes arquivos pode levar muito tempo.
- Permissões: certifique-se que `../Dados` existe e está gravável pelo usuário que executa os programas.

Sobre a técnica (por que usar Ordenação Externa)

A Ordenação Externa é usada quando o tamanho dos dados excede a memória RAM disponível. O procedimento básico:

1. Divide o arquivo grande em blocos que cabem na memória.
2. Ordena cada bloco na memória e grava cada bloco ordenado em disco (arquivos temporários).
3. Intercala (merge) todos os blocos ordenados para produzir o arquivo final ordenado.

Essa estratégia reduz o uso de memória e usa operações sequenciais de disco (mais eficientes) em vez de carregar todo o arquivo em RAM.

Arquivos gerados / temporários

- `../Dados/dados.txt` — arquivo de entrada (gerado pelo `gerador`).
- `../Dados/bloco_1.txt`, `../Dados/bloco_2.txt`, ... — blocos temporários ordenados.
- `../Dados/dados_ordenados.txt` — arquivo final ordenado.

Controle de versão

Este repositório contém um `.gitignore` que já ignora arquivos de build e configurações de editor (por exemplo, `*.exe`, `*.o`, `.vscode/`).

Autores / Créditos

- Carlos Eduardo, Guilherme Aredes, Marcos Felipe
