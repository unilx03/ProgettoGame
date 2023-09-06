SOURCES=ProgettoGame.cpp Map.cpp MapList.cpp MapManager.cpp Character.cpp Hero.cpp Enemy.cpp SetEnemiesList.cpp FlyingEnemyX.cpp FlyingEnemyY.cpp ThiefEnemy.cpp JumpingEnemy.cpp Drop.cpp OggettoMappa.cpp OggettoMarket.cpp MarketScreen.cpp EnemiesManager.cpp FileManager.cpp
EXECUTABLE=BunnyFury.exe

all: $(EXECUTABLE) clean

$(EXECUTABLE): $(SOURCES)
	g++  $(SOURCES) -lncurses -o $(EXECUTABLE)
	./$(EXECUTABLE)

clean:
	rm -f $(EXECUTABLE)