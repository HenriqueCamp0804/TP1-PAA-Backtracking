# Define o compilador
CC = gcc

# Flags de compilação
CFLAGS = -Wall -g -std=c99

# --- DEFINIÇÃO DE PASTAS ---
# Onde o executável final vai ficar
BINDIR = bin
# Onde os arquivos objeto (.o) temporários vão ficar
OBJDIR = obj
# O nome do executável
TARGET = $(BINDIR)/expresso_interestelar

# Lista de arquivos fonte
SRCS = main.c mapa.c backtracking.c

# Lista de arquivos objeto (agora dentro da pasta obj/)
OBJS = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

# --- LÓGICA DO MODO DE ANÁLISE ---
ifeq ($(ANALISE), 1)
	CFLAGS += -DMODO_ANALISE
	@echo "--- Compilando em MODO DE ANÁLISE ---"
endif

# --- REGRAS DE COMPILAÇÃO ---

# Regra padrão: 'all'
all: $(TARGET)

# Regra para criar o executável final
$(TARGET): $(OBJS)
	# Cria o diretório 'bin' se ele não existir
	@mkdir -p $(BINDIR)
	# Linka os .o para criar o executável dentro de 'bin'
	@echo "--- Linkando o programa final: $(TARGET) ---"
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Regra para compilar .c em .o (e colocar em obj/)
$(OBJDIR)/%.o: %.c
	# Cria o diretório 'obj' se ele não existir
	@mkdir -p $(OBJDIR)
	# Compila o .c para um .o dentro de 'obj'
	@echo "--- Compilando $< para $@ ---"
	$(CC) $(CFLAGS) -c $< -o $@

# Regra de limpeza (A MAIS IMPORTANTE)
clean:
	@echo "--- Limpando diretórios bin/ e obj/ ---"
	# Remove FORÇADAMENTE as pastas inteiras 'bin' e 'obj'
	rm -rf $(BINDIR) $(OBJDIR)