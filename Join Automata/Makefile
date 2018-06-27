# Makefile do Trabalho de Estrutura de Dados e Algoritmos I - MATA40
# Simulação de Agência Bancária Otimizada utilizando conceito de árvore binária AVL
# Maiores detalhes do desenvolvimento, vide https://github.com/gustavooquinteiro/SearchBinaryTree

# Nome do projeto e do executável encontrado no diretório corrente após compilação
PROJ_NAME = JoinAutomata

# Arquivos .c encontrados em src/
C_SOURCE = $(wildcard ./src/*.cpp)

# Arquivos .h encontrados em lib/
H_SOURCE = $(wildcard ./lib/*.h)

# Arquivos objetos .o encontrados em obj/ após compilação
OBJ = $(subst .cpp,.o,$(subst src,obj,$(C_SOURCE)))

# Compilador utilizado em testes: gcc (GCC) 7.2.1 20171224  
CC = g++

# Flags utilizadas na compilação
CC_FLAGS = -c \
           -g \

# Comando de construção de diretório
MKDIR = mkdir -p
						
# Comando de limpeza de alvos 
RM = rm -rf

GREEN=\033[0;32m
NC=\033[0m

# Regras de compilação
all: objFolder $(PROJ_NAME)

$(PROJ_NAME): $(OBJ)
	@ echo -e -n " [${GREEN} OK ${NC}]"
	@ $(CC) $^ -o $@ 
	@ echo " Construido binário $@"

./obj/%.o: ./src/%.cpp ./lib/%.h
	@ echo -e -n " [${GREEN} OK ${NC}]"
	@ $(CC) $< $(CC_FLAGS) -o $@
	@ echo " Compilado $< em $@"

# Regra de criação de diretório para os objetos
objFolder:
	@ echo -e -n " [${GREEN} OK ${NC}]"
	@ $(MKDIR) obj
	@ echo ' Criado diretório para objetos'

# Regra de limpeza de objetos e executável
clean:
	@ echo -e -n " [${GREEN} OK ${NC}]"
	@ $(RM) obj $(PROJ_NAME) *~ *.o
	@ echo ' Workspace limpo'

.PHONY: all clean