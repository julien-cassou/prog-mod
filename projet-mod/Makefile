
# === Variables ===
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -std=c++17

# === Fichiers objets ===
OBJS_TEST = test.o coord.o Animal.o Jeu.o
OBJS_MAIN = main.o coord.o Animal.o Jeu.o

# === Exécutables ===
EXEC_TEST = test
EXEC_MAIN = prog

# === Règle par défaut ===
all: $(EXEC_TEST)

# === Compilation du programme principal ===
$(EXEC_MAIN): $(OBJS_MAIN)
	$(CXX) -o $@ $^

# === Compilation des tests ===
$(EXEC_TEST): $(OBJS_TEST)
	$(CXX) -o $@ $^

# === Compilation des fichiers .cpp en .o ===
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# === Nettoyage ===
clean:
	rm -f *.o $(EXEC_TEST) $(EXEC_MAIN)
