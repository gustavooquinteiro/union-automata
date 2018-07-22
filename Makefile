# Makefile do Trabalho de Linguagens Formais e Automatos - MATA50
# União de automatos deterministicos
# Maiores detalhes do desenvolvimento, vide https://github.com/gustavooquinteiro/union-automata

# Nome do projeto e do executável encontrado no diretório corrente após compilação
PROJ_NAME = JoinAutomata

# Arquivos .c encontrados em src/
C_SOURCE = $(wildcard ./src/*.cpp)

# Arquivos .h encontrados em lib/
H_SOURCE = $(wildcard ./lib/*.h)

# Arquivos objetos .o encontrados em obj/ após compilação
OBJ = $(subst .cpp,.o,$(subst src,obj,$(C_SOURCE)))

# Compilador utilizado
CC = g++

# Flags utilizadas na compilação
CC_FLAGS = -c \
	-Wall\
	-Wpedantic\
	-Wextra\
	-g \

	
OPT_FLAGS = -Ofast\
	-O2 \
	
# Comando de construção de diretório
MKDIR = mkdir -p
						
# Comando de limpeza de alvos 
RM = rm -rf

GREEN=\033[0;32m
NC=\033[0m

# Regras de compilação
all: objFolder $(PROJ_NAME)

$(PROJ_NAME): $(OBJ)
	@ $(CC) $(OPT_FLAGS) $^ -o $@ 
	@ echo -e -n " [${GREEN} OK ${NC}]"
	@ echo " Construido binário $@"

./obj/%.o: ./src/%.cpp ./lib/%.h
	@ $(CC) $< $(CC_FLAGS) -o $@
	@ echo -e -n " [${GREEN} OK ${NC}]"
	@ echo " Compilado $< em $@"

# Regra de criação de diretório para os objetos
objFolder:
	@ $(MKDIR) obj
	@ echo -e -n " [${GREEN} OK ${NC}]"
	@ echo ' Criado diretório para objetos'

# Regra de limpeza de objetos e executável
clean:
	@ $(RM) obj $(PROJ_NAME)
	@ echo -e -n " [${GREEN} OK ${NC}]"
	@ echo ' Workspace limpo'

.PHONY: all clean
