# Nome do compilador
CC = gcc

# Flags de compilação
CFLAGS = -Wall -g

# Diretórios
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
INC_DIR = include

# Arquivos fonte
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Gera os arquivos .o correspondentes em obj/
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Nome do executável
TARGET = $(BIN_DIR)/matop

# Regras principais
all: create_dirs $(TARGET)

# Regra para criar diretórios se não existirem
create_dirs:
	@mkdir -p $(OBJ_DIR) $(BIN_DIR)

# Compilação do executável
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compilação de arquivos objeto
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DIR)/%.h
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

# Regra especial para matop.c (onde está o main)
$(OBJ_DIR)/matop.o: $(SRC_DIR)/matop.c
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

# Executar o programa com os três comandos
run: all
	./$(TARGET) -s -x 5 -y 5
	./$(TARGET) -m -x 5 -y 5
	./$(TARGET) -t -x 5 -y 5

# Limpa arquivos compilados
clean:
	rm -rf $(OBJ_DIR)/*.o $(TARGET)

# Limpa tudo (arquivos objeto, executáveis e diretórios)
clean_all:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Phony targets
.PHONY: all run clean clean_all
