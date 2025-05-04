
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -std=c++17
SFML_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system

<<<<<<< Updated upstream
# === Fichiers objets ===
OBJS_TEST = test.o coord.o
OBJS_MAIN = main.o coord.o

# === Exécutables ===
EXEC_TEST = tests
=======
OBJS_TEST1 = test.o coord.o
OBJS_TEST2 = test2.o coord.o Animal.o Jeu.o
OBJS_MAIN = main.o coord.o Animal.o Jeu.o

EXEC_TEST1 = test
EXEC_TEST2 = test2
<<<<<<< Updated upstream
>>>>>>> Stashed changes
EXEC_MAIN = prog
=======
EXEC_MAIN = main
>>>>>>> Stashed changes

all: $(EXEC_MAIN) $(EXEC_TEST1) $(EXEC_TEST2)

$(EXEC_MAIN): $(OBJS_MAIN)
	$(CXX) -o $@ $^ $(SFML_FLAGS)

$(EXEC_TEST1): $(OBJS_TEST1)
	$(CXX) -o $@ $^

$(EXEC_TEST2): $(OBJS_TEST2)
	$(CXX) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


clean:
	rm -f *.o $(EXEC_TEST) $(EXEC_MAIN)
