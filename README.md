# Selection Sort — APS

Projeto acadêmico desenvolvido em C++ para implementar e analisar o desempenho do algoritmo **Selection Sort**, utilizando dados reais do INPE e dados gerados aleatoriamente.

O objetivo é medir o tempo necessário para ordenar diferentes quantidades de registros e observar o comportamento do algoritmo em diferentes situações.

## Sobre o algoritmo

O Selection Sort funciona procurando o menor elemento da parte ainda não ordenada e colocando-o na posição correta.

Esse processo é repetido até que todos os registros estejam ordenados.

O algoritmo foi implementado em **C++**, utilizando `vector` para armazenar os registros e `chrono` para medir o tempo de execução.

## Dados utilizados

### Dados reais do INPE

Foram utilizados 500.000 registros extraídos do projeto PRODES — Amazônia Legal, disponibilizado pelo INPE na plataforma TerraBrasilis.

Os registros possuem sete campos:

| Campo | Descrição |
|---|---|
| `scene_id` | Identificador numérico da cena |
| `uuid` | Identificador único do registro |
| `area_km` | Área do registro |
| `year` | Ano |
| `image_date` | Data da imagem |
| `satellite` | Satélite |
| `state` | Estado |

**Campo utilizado na ordenação:** `scene_id`, comparado numericamente.

Os dados são armazenados no arquivo `dados_inpe_500000_sla.csv`, utilizando ponto e vírgula como separador.

### Dados aleatórios

Foram gerados 500.000 registros em C++, contendo seis campos:

| Campo | Descrição |
|---|---|
| `id` | Identificador |
| `latitude` | Latitude simulada |
| `longitude` | Longitude simulada |
| `altitude` | Altitude simulada |
| `nuvens` | Valor simulado de nuvens |
| `tamanho` | Tamanho utilizado na ordenação |

**Campo utilizado na ordenação:** `tamanho`.

## Testes realizados

O Selection Sort foi testado com **10.000, 250.000 e 500.000 registros**, considerando três situações principais:

- **Ordenados:** registros previamente organizados em ordem crescente.
- **Semiordenados:** primeira metade embaralhada e segunda metade ordenada.
- **Desordenados:** registros completamente embaralhados.

Também foi adicionada uma quarta opção:

- **Ordem inversa:** registros inicialmente organizados em ordem decrescente, que depois são ordenados em ordem crescente pelo Selection Sort.

O tempo de ordenação é medido em segundos utilizando a biblioteca `chrono`.

## Resultados — Dados reais do INPE

| Quantidade | Ordenados | Semiordenados | Desordenados |
|---|---:|---:|---:|
| 10.000 | 0,166 s | 0,176 s | 0,188 s |
| 250.000 | 150,868 s | 152,994 s | 116,819 s |
| 500.000 | 645,138 s | 649,357 s | 752,700 s |

Critério de ordenação: `scene_id` numérico.

## Resultados — Dados aleatórios

| Quantidade | Ordenados | Semiordenados | Desordenados |
|---|---:|---:|---:|
| 10.000 | 0,161 s | 0,177 s | 0,164 s |
| 250.000 | 26,745 s | 21,504 s | 21,916 s |
| 500.000 | 96,523 s | 105,054 s | 99,175 s |

Critério de ordenação: `tamanho`.

**Todos os 18 testes apresentados nas duas tabelas tiveram a ordenação confirmada como correta pelo programa.**

Os tempos podem variar conforme o computador, a compilação e as condições de execução.

## Testes em ordem inversa

Também foram iniciados testes com os registros organizados inicialmente em ordem decrescente.

| Quantidade | Dados reais | Dados aleatórios |
|---|---:|---:|
| 10.000 | Pendente | Pendente |
| 250.000 | 116,914 s | Pendente |
| 500.000 | Pendente | Pendente |

O Selection Sort continua organizando os registros em ordem crescente. A ordem inversa é utilizada apenas como situação inicial para o teste.

## Amostras dos registros

Foram preparadas amostras dos conjuntos de 500.000 registros, contendo:

- 10 linhas ordenadas.
- 10 linhas semiordenadas (5 da parte desordenada e 5 da parte ordenada).
- 10 linhas desordenadas.

Arquivos:

- `amostras_reais_500000.txt`
- `amostras_aleatorios_500000.txt`

As amostras foram geradas em Python a partir dos mesmos arquivos de dados utilizados nos testes. A sequência embaralhada pode ser diferente da exibida pelo C++.

## Arquivos do projeto

| Arquivo | Descrição |
|---|---|
| `selection_sort_aps.cpp` | Implementação do Selection Sort e execução dos testes |
| `gerar_metadados.cpp` | Gerador de registros aleatórios |
| `extrair_metadados_reais.py` | Extrator dos dados reais do INPE |
| `salvar_amostras.py` | Geração das amostras |
| `dados_inpe_500000_sla.csv` | Conjunto de 500.000 registros reais do INPE |
| `amostras_reais_500000.txt` | Amostras dos dados reais |
| `amostras_aleatorios_500000.txt` | Amostras dos dados aleatórios |

O CSV completo dos dados reais está disponível no repositório. O arquivo `metadados.txt`, utilizado para os dados aleatórios, pode ser produzido pelo gerador em C++.

## Como executar

### 1. Gerar os dados aleatórios

Compile o gerador:

```bash
g++ -O2 gerar_metadados.cpp -o gerar_metadados.exe
```

Execute no Windows:

```powershell
.\gerar_metadados.exe
```

Será criado o arquivo `metadados.txt` com 500.000 registros.

### 2. Preparar os dados reais

O arquivo `dados_inpe_500000_sla.csv` já está disponível no repositório.

Caso seja necessário realizar novamente a extração, baixe os dados originais do PRODES — Amazônia Legal na plataforma TerraBrasilis.

Instale a biblioteca necessária:

```bash
python -m pip install pyshp
```

Configure o caminho dos arquivos Shapefile no script `extrair_metadados_reais.py` e execute:

```bash
python extrair_metadados_reais.py
```

Será gerado o arquivo `dados_inpe_500000_sla.csv`.

### 3. Executar o Selection Sort

Compile:

```bash
g++ -O2 -std=c++14 selection_sort_aps.cpp -o selection_sort_aps.exe
```

Execute no Windows:

```powershell
.\selection_sort_aps.exe
```

O programa permite escolher:

1. Tipo de dados: reais do INPE ou aleatórios.
2. Quantidade de registros: 10.000, 250.000 ou 500.000.
3. Situação inicial: ordenados, semiordenados, desordenados ou ordem inversa.

Ao finalizar, apresenta o tempo de execução, uma amostra dos registros e a confirmação da ordenação.

### 4. Gerar as amostras

Com os dois arquivos completos de dados na pasta:

```bash
python salvar_amostras.py
```

## Conclusão

O Selection Sort conseguiu ordenar corretamente todos os conjuntos de registros apresentados nos testes concluídos.

Os resultados demonstraram um aumento significativo no tempo de execução ao passar de 10.000 para 250.000 e 500.000 registros.

Também foi possível observar diferenças de tempo entre os dados reais do INPE e os dados gerados aleatoriamente.

Os testes em ordem inversa e a comparação de desempenho entre computadores complementam a análise do algoritmo.

## Referência

Instituto Nacional de Pesquisas Espaciais (INPE) — TerraBrasilis, PRODES Amazônia Legal.

https://terrabrasilis.dpi.inpe.br/downloads/