
import csv
import random

QUANTIDADE = 500000

def ler_dados_reais():
    dados = []

    with open("dados_inpe_500000_sla.csv",
              "r", encoding="utf-8-sig", newline="") as arquivo:

        leitor = csv.DictReader(arquivo, delimiter=";")

        for linha in leitor:
            linha["scene_id"] = int(linha["scene_id"])
            dados.append(linha)

    return dados


def ler_dados_aleatorios():
    dados = []

    with open("metadados.txt", "r", encoding="utf-8") as arquivo:
        for linha in arquivo:
            campos = linha.strip().split()

            if len(campos) != 6:
                raise ValueError("Registro aleatorio com formato incorreto")

            dados.append({
                "id": campos[0],
                "latitude": campos[1],
                "longitude": campos[2],
                "altitude": campos[3],
                "nuvens": campos[4],
                "tamanho": int(campos[5])
            })

    return dados


def formatar(dado, campos):
    return " ; ".join(str(dado[campo]) for campo in campos)


def salvar_amostras(nome, dados, campo_ordenacao, campos):
    if len(dados) != QUANTIDADE:
        raise ValueError(
            f"{nome}: esperado {QUANTIDADE}, encontrado {len(dados)}"
        )

    # Prepara os dados ordenados
    ordenados = sorted(dados, key=lambda d: d[campo_ordenacao])

    # Reproduz as situacoes de entrada dos testes
    gerador = random.Random(42)

    semiordenados = ordenados.copy()
    metade = len(semiordenados) // 2
    primeira_metade = semiordenados[:metade]
    gerador.shuffle(primeira_metade)
    semiordenados[:metade] = primeira_metade

    desordenados = ordenados.copy()
    gerador = random.Random(42)
    gerador.shuffle(desordenados)

    nome_arquivo = f"amostras_{nome}_500000.txt"

    with open(nome_arquivo, "w", encoding="utf-8") as arquivo:

        arquivo.write(f"SELECTION SORT - {nome.upper()}\n")
        arquivo.write("Quantidade: 500000 registros\n")
        arquivo.write(f"Campo de ordenacao: {campo_ordenacao}\n")
        arquivo.write("Campos: " + " ; ".join(campos) + "\n\n")

        arquivo.write("10 LINHAS ORDENADAS\n")
        for dado in ordenados[:10]:
            arquivo.write(formatar(dado, campos) + "\n")

        arquivo.write("\n10 LINHAS SEMIORDENADAS\n")
        arquivo.write("5 linhas desordenadas:\n")
        for dado in semiordenados[:5]:
            arquivo.write(formatar(dado, campos) + "\n")

        arquivo.write("\n5 linhas ordenadas:\n")
        for dado in semiordenados[metade:metade + 5]:
            arquivo.write(formatar(dado, campos) + "\n")

        arquivo.write("\n10 LINHAS DESORDENADAS\n")
        for dado in desordenados[:10]:
            arquivo.write(formatar(dado, campos) + "\n")

    print(f"Arquivo criado: {nome_arquivo}")


reais = ler_dados_reais()

salvar_amostras(
    "reais",
    reais,
    "scene_id",
    [
        "scene_id", "uuid", "area_km", "year",
        "image_date", "satellite", "state"
    ]
)

aleatorios = ler_dados_aleatorios()

salvar_amostras(
    "aleatorios",
    aleatorios,
    "tamanho",
    [
        "id", "latitude", "longitude",
        "altitude", "nuvens", "tamanho"
    ]
)

print("\nTodas as amostras foram salvas!")
