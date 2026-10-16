
import shapefile
import csv
import os
import math

# Pasta onde estao os arquivos originais do INPE
pasta = r"C:\Users\karlo\OneDrive\Desktop\yearly_deforestation_amazonia_legal_v20260717"

# Procura o arquivo SHP
arquivos = [a for a in os.listdir(pasta) if a.lower().endswith(".shp")]

if not arquivos:
    print("Arquivo SHP nao encontrado!")
    raise SystemExit

caminho = os.path.join(pasta, arquivos[0])

# Abre os dados e as geometrias do INPE
dados = shapefile.Reader(caminho, encoding="latin1")

# Verifica o sistema de coordenadas
prj = os.path.splitext(caminho)[0] + ".prj"

if not os.path.exists(prj):
    print("Arquivo PRJ nao encontrado!")
    dados.close()
    raise SystemExit

with open(prj, "r", encoding="utf-8-sig") as arquivo:
    sistema = arquivo.read().upper()

if "SIRGAS_2000" not in sistema or "GEOGCS" not in sistema:
    print("Sistema de coordenadas diferente do esperado.")
    dados.close()
    raise SystemExit

# Identifica os campos existentes no INPE
campos = [campo[0] for campo in dados.fields[1:]]

print("Campos encontrados:", campos)

necessarios = [
    "area_km",
    "year",
    "image_date",
    "satellite",
    "scene_id",
    "state"
]

# Confere se todos os campos existem
mapa = {}

for nome in necessarios:
    encontrado = None

    for campo in campos:
        if campo.lower() == nome.lower():
            encontrado = campo
            break

    if encontrado is None:
        print("Campo nao encontrado:", nome)
        dados.close()
        raise SystemExit

    mapa[nome] = encontrado

# Cria o CSV corrigido na pasta do script
pasta_saida = os.path.dirname(os.path.abspath(__file__))
saida = os.path.join(pasta_saida, "dados_inpe_corrigidos_500000.csv")

quantidade = 0

with open(saida, "w", newline="", encoding="utf-8-sig") as arquivo:

    escritor = csv.writer(arquivo, delimiter=";")

    # Ordem dos campos definida pelo grupo
    escritor.writerow([
        "area_km",
        "year",
        "image_date",
        "satellite",
        "scene_id",
        "state",
        "longitude",
        "latitude"
    ])

    # Le os atributos junto com a geometria
    for registro in dados.iterShapeRecords():

        if quantidade >= 500000:
            break

        valores = registro.record.as_dict()
        pontos = registro.shape.points

        if not pontos:
            continue

        # Primeiro ponto da geometria
        longitude = pontos[0][0]
        latitude = pontos[0][1]

        # Confere as coordenadas
        if not math.isfinite(longitude) or not math.isfinite(latitude):
            continue

        if not (-180 <= longitude <= 180 and -90 <= latitude <= 90):
            continue

        if valores.get(mapa["scene_id"]) is None:
            continue

        escritor.writerow([
            valores.get(mapa["area_km"], ""),
            valores.get(mapa["year"], ""),
            valores.get(mapa["image_date"], ""),
            valores.get(mapa["satellite"], ""),
            valores.get(mapa["scene_id"], ""),
            valores.get(mapa["state"], ""),
            f"{longitude:.6f}",
            f"{latitude:.6f}"
        ])

        quantidade += 1

        if quantidade % 50000 == 0:
            print("Registros salvos:", quantidade)

dados.close()

print("Extracao concluida!")
print("Total de registros:", quantidade)
print("Arquivo criado:", saida)

if quantidade < 500000:
    print("ATENCAO: menos de 500 mil registros foram extraidos.")
