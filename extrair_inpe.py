
import csv
from pathlib import Path
from dbfread import DBF

# Procura o arquivo DBF na mesma pasta do programa
arquivos = list(Path(".").glob("*.dbf"))

if not arquivos:
    print("Nenhum arquivo DBF encontrado!")
    exit()

arquivo_dbf = arquivos[0]

campos = [
    "uuid",
    "area_km",
    "year",
    "image_date",
    "satellite",
    "scene_id",
    "state"
]

print("Lendo:", arquivo_dbf.name)

tabela = DBF(
    str(arquivo_dbf),
    encoding="latin1",
    char_decode_errors="ignore",
    load=False
)

print("Total de registros:", len(tabela))
print("Campos disponíveis:", tabela.field_names)

# Verifica se todos os campos existem
faltando = [
    campo for campo in campos
    if campo not in tabela.field_names
]

if faltando:
    print("Campos não encontrados:", faltando)
    print("Confira os nomes antes de extrair.")
    exit()

quantidade = 0

with open("dados_inpe_50000.csv", "w",
          newline="", encoding="utf-8-sig") as arquivo:

    escritor = csv.writer(arquivo, delimiter=";")
    escritor.writerow(campos)

    for registro in tabela:
        escritor.writerow([
            registro[campo] for campo in campos
        ])

        quantidade += 1

        if quantidade >= 50000:
            break

print("Extração concluída!")
print("Registros salvos:", quantidade)
print("Arquivo: dados_inpe_50000.csv")
