# Makefile para o Trabalho Prático 1 - PAA
# Expresso Interestelar com Backtracking
# MSYS2/MinGW64 Compatible

# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -pedantic
LDFLAGS = -lm

# Diretórios
SRC_DIR = .
OBJ_DIR = obj
BIN_DIR = bin

# Nome do executável
TARGET = expresso_interestelar

# ============================================
# AJUSTE AQUI OS SEUS ARQUIVOS .C
# ============================================
# Liste todos os arquivos .c do seu projeto
# Exemplo: main.c backtracking.c mapa.c 
SRC_FILES = main.c backtracking.c mapa.c 

# Não precisa mexer daqui pra baixo
SOURCES = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJECTS_ANALISE = $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%_analise.o)

# Cores para output
GREEN = \033[0;32m
YELLOW = \033[1;33m
RED = \033[0;31m
BLUE = \033[0;34m
NC = \033[0m

# ============================================
# REGRAS PRINCIPAIS
# ============================================

# Regra padrão - compila em modo NORMAL
all: directories $(BIN_DIR)/$(TARGET)
	@echo "$(GREEN)✓ Compilação concluída com sucesso (modo NORMAL)!$(NC)"
	@echo "$(BLUE)Execute com: ./$(BIN_DIR)/$(TARGET)$(NC)"

# Compila em modo ANÁLISE (com estatísticas de recursão)
analise: directories $(BIN_DIR)/$(TARGET)_analise
	@echo "$(GREEN)✓ Compilação concluída com sucesso (modo ANÁLISE)!$(NC)"
	@echo "$(BLUE)Execute com: ./$(BIN_DIR)/$(TARGET)_analise$(NC)"

# ============================================
# COMPILAÇÃO DOS OBJETOS
# ============================================

# Compilação normal
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "$(YELLOW)Compilando $<...$(NC)"
	@$(CC) $(CFLAGS) -c $< -o $@

# Compilação para modo análise
$(OBJ_DIR)/%_analise.o: $(SRC_DIR)/%.c
	@echo "$(YELLOW)Compilando $< (modo análise)...$(NC)"
	@$(CC) $(CFLAGS) -DMODO_ANALISE -c $< -o $@

# ============================================
# LINKAGEM
# ============================================

# Linkagem normal
$(BIN_DIR)/$(TARGET): $(OBJECTS)
	@echo "$(YELLOW)Linkando $(TARGET)...$(NC)"
	@$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

# Linkagem modo análise
$(BIN_DIR)/$(TARGET)_analise: $(OBJECTS_ANALISE)
	@echo "$(YELLOW)Linkando $(TARGET) (modo análise)...$(NC)"
	@$(CC) $(OBJECTS_ANALISE) -o $@ $(LDFLAGS)

# ============================================
# UTILITÁRIOS
# ============================================

# Cria diretórios necessários
directories:
	@mkdir -p $(OBJ_DIR) $(BIN_DIR)

# Limpa arquivos compilados
clean:
	@echo "$(RED)Limpando arquivos compilados...$(NC)"
	@rm -rf $(OBJ_DIR) $(BIN_DIR)
	@echo "$(GREEN)✓ Limpeza concluída!$(NC)"

# Recompila tudo do zero
rebuild: clean all

# Recompila modo análise do zero
rebuild_analise: clean analise

# Executa o programa em modo normal
run: all
	@echo "$(BLUE)=== EXECUTANDO MODO NORMAL ===$(NC)"
	@./$(BIN_DIR)/$(TARGET)

# Executa o programa em modo análise
run_analise: analise
	@echo "$(BLUE)=== EXECUTANDO MODO ANÁLISE ===$(NC)"
	@./$(BIN_DIR)/$(TARGET)_analise

# Testa com um arquivo específico (uso: make test FILE=testes/mapa1.txt)
test: all
	@if [ -z "$(FILE)" ]; then \
		echo "$(RED)Erro: Especifique um arquivo com FILE=caminho$(NC)"; \
		echo "$(YELLOW)Exemplo: make test FILE=testes/mapa1.txt$(NC)"; \
		exit 1; \
	else \
		echo "$(BLUE)=== TESTANDO COM $(FILE) ===$(NC)"; \
		./$(BIN_DIR)/$(TARGET) $(FILE); \
	fi

# Testa em modo análise com arquivo específico
test_analise: analise
	@if [ -z "$(FILE)" ]; then \
		echo "$(RED)Erro: Especifique um arquivo com FILE=caminho$(NC)"; \
		echo "$(YELLOW)Exemplo: make test_analise FILE=testes/mapa1.txt$(NC)"; \
		exit 1; \
	else \
		echo "$(BLUE)=== TESTANDO COM $(FILE) (modo análise) ===$(NC)"; \
		./$(BIN_DIR)/$(TARGET)_analise $(FILE); \
	fi

# Mostra os arquivos que serão compilados
show:
	@echo "$(BLUE)Arquivos fonte:$(NC)"
	@echo "$(SOURCES)"
	@echo ""
	@echo "$(BLUE)Objetos (normal):$(NC)"
	@echo "$(OBJECTS)"
	@echo ""
	@echo "$(BLUE)Objetos (análise):$(NC)"
	@echo "$(OBJECTS_ANALISE)"

# Mostra informações de ajuda
help:
	@echo "$(BLUE)============================================$(NC)"
	@echo "$(BLUE)  Makefile - TP1 PAA (Expresso Interestelar)$(NC)"
	@echo "$(BLUE)============================================$(NC)"
	@echo ""
	@echo "$(YELLOW)Comandos disponíveis:$(NC)"
	@echo "  $(GREEN)make$(NC)                    - Compila em modo NORMAL"
	@echo "  $(GREEN)make analise$(NC)            - Compila em modo ANÁLISE"
	@echo "  $(GREEN)make run$(NC)                - Compila e executa (modo normal)"
	@echo "  $(GREEN)make run_analise$(NC)        - Compila e executa (modo análise)"
	@echo "  $(GREEN)make test FILE=x$(NC)        - Testa com arquivo específico"
	@echo "  $(GREEN)make test_analise FILE=x$(NC) - Testa em modo análise"
	@echo "  $(GREEN)make clean$(NC)              - Remove arquivos compilados"
	@echo "  $(GREEN)make rebuild$(NC)            - Recompila tudo do zero"
	@echo "  $(GREEN)make show$(NC)               - Mostra arquivos do projeto"
	@echo "  $(GREEN)make help$(NC)               - Mostra esta mensagem"
	@echo ""
	@echo "$(YELLOW)Exemplos:$(NC)"
	@echo "  make test FILE=testes/mapa1.txt"
	@echo "  make test_analise FILE=testes/mapa_complexo.txt"
	@echo ""

# Evita conflitos com arquivos de mesmo nome
.PHONY: all analise clean rebuild rebuild_analise run run_analise test test_analise show help directories