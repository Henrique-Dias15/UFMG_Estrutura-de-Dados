#!/bin/bash

# Caminhos
TP_DIR="../TP"
ANALISAMEM_DIR="../analisamem"
MEMORIA_FILES=(
  "../Resultados/Memoria/quick"
  "../Resultados/Memoria/merge"
  "../Resultados/Memoria/heap"
)
OUTPUT_DIR="/tmp/out"
RESULTS_DIR="../Resultados/Memoria"

# Função para verificar erros e exibir mensagem
check_error() {
  if [ $? -ne 0 ]; then
    echo "Erro: $1"
    exit 1
  fi
}

# Função para corrigir um arquivo de log
corrigir_arquivo_inplace() {
  local input_file=$1
  echo "Corrigindo o arquivo $input_file..."

  # Corrigir linhas com número incorreto de campos
  awk 'NF == 7 || $1 == "I" || $1 == "F"' "$input_file" > "${input_file}.tmp" && mv "${input_file}.tmp" "$input_file"
  check_error "Erro ao corrigir o número de campos em $input_file."

  # Ajustar minid para ser 0, se necessário
  if ! awk '$1 == "E" || $1 == "L" {if ($4 == 0) found=1} END {exit !found}' "$input_file"; then
    awk '{if ($1 == "E" || $1 == "L") $4 = $4 -1 ; print}' "$input_file" > "${input_file}.tmp" && mv "${input_file}.tmp" "$input_file"
    check_error "Erro ao corrigir minid em $input_file."
  fi

  # Ajustar minfase para ser 0, se necessário
  if ! awk '$1 == "E" || $1 == "L" {if ($2 == 0) found=1} END {exit !found}' "$input_file"; then
    awk '{if ($1 == "E" || $1 == "L") $2 = $2 - 1; print}' "$input_file" > "${input_file}.tmp" && mv "${input_file}.tmp" "$input_file"
    check_error "Erro ao corrigir minfase em $input_file."
  fi

  echo "Arquivo corrigido com sucesso."
}

# Função para executar o analisamem e gerar gráficos
processar_memoria() {
  local input_file=$1
  local output_prefix=$2

  echo "Executando analisamem com o arquivo corrigido $input_file..."
  "$ANALISAMEM_DIR/bin/analisamem" -i "$input_file" -p "$output_prefix"
  check_error "Erro ao executar analisamem para $input_file."

}

# Passo 1: Limpar diretórios de resultados
echo "Limpando pastas de resultados e out..."
rm -rf "$RESULTS_DIR" "$OUTPUT_DIR"
mkdir -p "$RESULTS_DIR" "$OUTPUT_DIR"
check_error "Erro ao limpar as pastas."

# Passo 2: Executar make run dentro da pasta TP
echo "Executando 'make run' na pasta TP..."
cd "$TP_DIR" || exit
make run
check_error "Erro ao executar 'make run' na pasta TP."
cd - > /dev/null || exit

# Passo 3: Processar e corrigir arquivos de memória
for MEMORIA_FILE in "${MEMORIA_FILES[@]}"; do
  corrigir_arquivo_inplace "$MEMORIA_FILE"
done

# Passo 4: Executar analisamem e gerar gráficos
for MEMORIA_FILE in "${MEMORIA_FILES[@]}"; do
  BASENAME=$(basename "$MEMORIA_FILE")
  processar_memoria "$MEMORIA_FILE" "${OUTPUT_DIR}/${BASENAME}"
  echo "Executado para $MEMORIA_FILE"
done

# Passo 5: Mover os gráficos para o diretório de resultados
echo "Movendo os gráficos para $RESULTS_DIR..."
mv "$OUTPUT_DIR"/*.png "$RESULTS_DIR"
check_error "Erro ao mover os gráficos para $RESULTS_DIR."

# Finalização
echo "Processo concluído com sucesso!"
