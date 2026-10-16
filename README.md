# Selection Sort — APS

Projeto acadêmico desenvolvido em C++ para implementar e analisar o desempenho do algoritmo **Selection Sort**, utilizando dados reais do INPE e dados gerados aleatoriamente.

O objetivo é medir o tempo necessário para ordenar grandes quantidades de registros e observar o comportamento do algoritmo em diferentes situações.

## Sobre o algoritmo

O Selection Sort funciona procurando o menor elemento da parte ainda não ordenada e colocando-o na posição correta.

Esse processo é repetido até que todos os registros estejam ordenados.

O algoritmo foi implementado em **C++**, utilizando `vector` para armazenar os registros e `chrono` para medir o tempo de execução.

## Dados utilizados

### Dados reais do INPE

Foram utilizados 500.000 registros extraídos do projeto PRODES — Amazônia Legal, disponibilizado pelo INPE na plataforma TerraBrasilis.

Os registros possuem oito campos:

| Campo | Descrição |
|---|---|
| `area_km` | Área do registro |
| `year` | Ano |
| `image_date` | Data da imagem |
| `satellite` | Satélite |
| `scene_id` | Identificador da cena |
| `state` | Estado |
| `longitude` | Longitude |
| `latitude` | Latitude |

**Campo utilizado na ordenação:** `scene_id`, comparado numericamente.

As coordenadas foram extraídas do primeiro ponto da geometria de cada polígono, não necessariamente do centro da área.

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

O Selection Sort foi testado com **250.000 e 500.000 registros**, considerando três situações:

- **Ordenados:** registros previamente organizados.
- **Semiordenados:** primeira metade embaralhada e segunda metade ordenada.
- **Desordenados:** registros completamente embaralhados.

O tempo foi medido em segundos utilizando a biblioteca `chrono`, com o programa compilado usando `-O2`.

## Resultados — Dados reais do INPE

| Quantidade | Ordenados | Semiordenados | Desordenados |
|---|---:|---:|---:|
| 250.000 | 62,948 s | 60,517 s | 75,612 s |
| 500.000 | 402,032 s | 399,623 s | 449,217 s |

Critério de ordenação: `scene_id` numérico.

## Resultados — Dados aleatórios

| Quantidade | Ordenados | Semiordenados | Desordenados |
|---|---:|---:|---:|
| 250.000 | 26,745 s | 21,504 s | 21,916 s |
| 500.000 | 96,523 s | 105,054 s | 99,175 s |

Critério de ordenação: `tamanho`.

**Os 12 testes foram concluídos e tiveram a ordenação confirmada como correta pelo programa.**

Os tempos podem variar conforme o computador e as condições de execução.

## Amostras dos registros

Foram preparadas amostras dos conjuntos de 500.000 registros, contendo:

- 10 linhas ordenadas.
- 10 linhas semiordenadas (5 da parte desordenada e 5 da parte ordenada).
- 10 linhas desordenadas.

Arquivos:

- `amostras_reais_500000.txt`
- `amostras_aleatorios_500000.txt`

As amostras foram geradas em Python a partir dos mesmos dados utilizados nos testes. A sequência embaralhada pode ser diferente da exibida pelo C++.

## Arquivos do projeto

| Arquivo | Descrição |
|---|---|
| `selection_sort_aps.cpp` | Implementação do Selection Sort e testes |
| `gerar_metadados.cpp` | Gerador de registros aleatórios |
| `extrair_metadados_reais.py` | Extrator dos dados do INPE |
| `salvar_amostras.py` | Geração das amostras |
| `amostras_reais_500000.txt` | Amostras dos dados reais |
| `amostras_aleatorios_500000.txt` | Amostras dos dados aleatórios |

Os arquivos completos de dados não estão incluídos no repositório.

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

Baixe os dados originais do PRODES — Amazônia Legal na plataforma TerraBrasilis.

Instale a biblioteca necessária:

```bash
python -m pip install pyshp
```

Configure o caminho dos arquivos Shapefile no script `extrair_metadados_reais.py` e execute:

```bash
python extrair_metadados_reais.py
```

Será gerado o arquivo `dados_inpe_corrigidos_500000.csv`.

### 3. Executar o Selection Sort

Compile:

```bash
g++ -O2 -std=c++14 selection_sort_aps.cpp -o selection_aps.exe
```

Execute no Windows:

```powershell
.\selection_aps.exe
```

O programa permite escolher:

1. Dados reais ou aleatórios.
2. Quantidade de registros: 250.000 ou 500.000.
3. Situação inicial: ordenados, semiordenados ou desordenados.

Ao finalizar, apresenta o tempo de execução, uma amostra dos registros e a confirmação da ordenação.

### 4. Gerar as amostras

Com os dois arquivos completos de dados na pasta:

```bash
python salvar_amostras.py
```

## Conclusão

O Selection Sort conseguiu ordenar corretamente todos os conjuntos de registros utilizados.

Os resultados demonstraram um aumento significativo no tempo de execução ao passar de 250.000 para 500.000 registros.

Também foi possível observar diferenças de tempo entre os dados reais e os dados aleatórios.

## Referência

Instituto Nacional de Pesquisas Espaciais (INPE) — TerraBrasilis, PRODES Amazônia Legal.

https://terrabrasilis.dpi.inpe.br/downloads/