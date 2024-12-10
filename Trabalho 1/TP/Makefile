# Diretórios
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
INCLUDE_DIR = include
ANALISAMEM_SRC_DIR = analisamem/src
ANALISAMEM_INCLUDE_DIR = analisamem/include
RESULT_DIR = resultados

# Nome do executável final
EXEC = tp1.out
ANALISAMEM_EXEC = analisamem.out

# Compilador e flags
CFLAGS += -g
CXX = g++
CXXFLAGS = -Wall -I$(INCLUDE_DIR)
CC = gcc
CFLAGS = -Wall -I$(INCLUDE_DIR) -I$(ANALISAMEM_INCLUDE_DIR)
LDFLAGS = -lm

# Lista de arquivos fonte e objetos
CPP_SRCS = $(wildcard $(SRC_DIR)/*.cpp)
C_SRCS = $(wildcard $(SRC_DIR)/*.c)
SRCS = $(CPP_SRCS) $(C_SRCS)
CPP_OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(CPP_SRCS))
C_OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(C_SRCS))
OBJS = $(CPP_OBJS) $(C_OBJS)

ANALISAMEM_SRCS = $(wildcard $(ANALISAMEM_SRC_DIR)/*.c)
ANALISAMEM_OBJS = $(patsubst $(ANALISAMEM_SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(ANALISAMEM_SRCS))

# Tamanhos de vetores padrão
R_SIZES = 1000 5000
P_SIZES = 1000 5000

# Alvo padrão para compilar o executável principal
all: $(BIN_DIR)/$(EXEC)

# Linkagem do executável principal
$(BIN_DIR)/$(EXEC): $(OBJS) | $(BIN_DIR)
	$(CXX) $(OBJS) -o $(BIN_DIR)/$(EXEC)

# Compilação do analisamem
$(BIN_DIR)/$(ANALISAMEM_EXEC): $(ANALISAMEM_OBJS) | $(BIN_DIR)
	$(CC) $(CFLAGS) $(ANALISAMEM_OBJS) -o $@ $(LDFLAGS)

# Compilação dos arquivos objeto
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(ANALISAMEM_SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Criação dos diretórios necessários
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Execução do programa principal
run: $(BIN_DIR)/$(EXEC)
	./$(BIN_DIR)/$(EXEC)

# Execução do analisamem
run_analisamem: $(BIN_DIR)/$(ANALISAMEM_EXEC)
	@echo "Executando analisamem..."
	$(BIN_DIR)/$(ANALISAMEM_EXEC) -i $(RESULT_DIR)/memoria_corrigida.xcsv -p $(RESULT_DIR)/analise -f png
	@echo "Análise concluída! Resultados salvos em $(RESULT_DIR)."


# Limpeza dos arquivos compilados
clean:
	rm -rf $(OBJ_DIR)/*.o $(BIN_DIR)/$(EXEC) $(BIN_DIR)/$(ANALISAMEM_EXEC)

# Indica que 'all', 'clean', 'run', e 'run_analisamem' não são arquivos
.PHONY: all clean run run_analisamem
