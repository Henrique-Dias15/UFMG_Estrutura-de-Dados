import pandas as pd
import matplotlib.pyplot as plt

# Função para carregar os dados do CSV
def carregar_dados(arquivo):
    try:
        # Lê o arquivo CSV em um DataFrame
        dados = pd.read_csv(arquivo)
        return dados
    except Exception as e:
        print(f"Erro ao carregar o arquivo: {e}")
        return None

# Função para gerar gráficos individuais de tempos
def grafico_linhas(dados, saida):
    # Configurações iniciais
    metodos = dados['Metodo'].unique()
    criterios = dados['Criterio'].unique()
    tamanhos = dados[['Tamanho (r)', 'Payload (p)']].drop_duplicates()
    
    # Itera por cada critério
    for criterio in criterios:
        plt.figure(figsize=(14, 8))
        
        for metodo in metodos:
            tempos = []
            labels = []
            
            for _, row in tamanhos.iterrows():
                r, p = row['Tamanho (r)'], row['Payload (p)']
                subdados = dados[(dados['Criterio'] == criterio) & 
                                 (dados['Metodo'] == metodo) & 
                                 (dados['Tamanho (r)'] == r) & 
                                 (dados['Payload (p)'] == p)]
                
                if not subdados.empty:
                    tempos.append(subdados['Tempo(ns)'].values[0] / 1e6)  # Converte ns para ms
                    labels.append(f"r{r}p{p}")  # Cria rótulos para os eixos
            
            # Adiciona a linha para o critério e método
            plt.plot(labels, tempos, marker='o', label=metodo)
        
        # Configuração do gráfico
        plt.xlabel("Tamanho (r, p)")
        plt.ylabel("Tempo (ms)")
        plt.title(f"Tempos de Execução - {criterio}")
        plt.xticks(rotation=45)
        plt.legend(loc="upper left", bbox_to_anchor=(1, 1))
        plt.tight_layout()
        
        # Salva e exibe o gráfico
        plt.savefig(f"{saida}_{criterio}.png")
        plt.close()

# Função para gerar gráficos comparativos de tempos
def grafico_comparativo_linhas(dados, saida):
    # Configurações iniciais
    metodos = dados['Metodo'].unique()
    criterios = dados['Criterio'].unique()
    tamanhos = dados[['Tamanho (r)', 'Payload (p)']].drop_duplicates()
    
    plt.figure(figsize=(14, 8))
    
    # Itera por cada critério
    for criterio in criterios:
        for metodo in metodos:
            tempos = []
            labels = []
            
            for _, row in tamanhos.iterrows():
                r, p = row['Tamanho (r)'], row['Payload (p)']
                subdados = dados[(dados['Criterio'] == criterio) & 
                                 (dados['Metodo'] == metodo) & 
                                 (dados['Tamanho (r)'] == r) & 
                                 (dados['Payload (p)'] == p)]
                
                if not subdados.empty:
                    tempos.append(subdados['Tempo(ns)'].values[0] / 1e6)  # Converte ns para ms
                    labels.append(f"r{r}p{p}")  # Cria rótulos para os eixos
            
            # Adiciona a linha para o critério e método
            plt.plot(labels, tempos, marker='o', label=f"{criterio} - {metodo}")
    
    # Configuração do gráfico
    plt.xlabel("Tamanho (r, p)")
    plt.ylabel("Tempo (ms)")
    plt.title("Comparativo de Tempos de Execução")
    plt.xticks(rotation=45)
    plt.legend(loc="upper left", bbox_to_anchor=(1, 1))
    plt.tight_layout()
    
    # Salva e exibe o gráfico
    plt.savefig(saida)

# Função principal
def main():
    arquivo = "/home/henrique/Estrutura de Dados/TP1/Resultados/Tempos/tempos.xcsv"  # Nome do arquivo
    saida = "comparativo_tempos_linhas.png"  # Nome do arquivo de saída
    
    print("Carregando dados...")
    dados = carregar_dados(arquivo)

    if dados is not None:
        print("Gerando gráficos de tempos...")
        grafico_linhas(dados, saida)
        print(f"Gráficos salvos como {saida}_<criterio>.png")
        print("Gerando gráfico comparativo de tempos...")
        grafico_comparativo_linhas(dados, saida)
        print(f"Gráfico salvo como {saida}")

if __name__ == "__main__":
    main()
