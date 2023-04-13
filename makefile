g++ ProgettoGame.cpp map.cpp -lncurses -o ProgettoGame
./ProgettoGame

g++ main.cpp Character.cpp Hero.cpp Enemy.cpp JumpingEnemy.cpp ThiefEnemy.cpp FlyingEnemyY.cpp FLyingEnemyX.cpp BossEnemy.cpp -lncurses -o game
./game.exe

g++ ProgettoGame.cpp map.cpp Entities/Character.cpp -lncurses -o ProgettoGame
./ProgettoGame

g++ ProgettoGame.cpp map.cpp Entities/Character.cpp oggetto.cpp -lncurses -o ProgettoGame
./ProgettoGame