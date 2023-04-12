g++ ProgettoGame.cpp map.cpp -lncurses -o ProgettoGame
./ProgettoGame

g++ main.cpp Character.cpp Hero.cpp Enemy.cpp JumpingEnemy.cpp ThiefEnemy.cpp FlyingEnemyY.cpp FLyingEnemyX.cpp BossEnemy.cpp -lncurses -o game
./game.exe

g++ ProgettoGame.cpp map.cpp Entities/Character.cpp Entities/Hero.cpp Entities/Enemy.cpp Entities/JumpingEnemy.cpp Entities/ThiefEnemy.cpp Entities/FlyingEnemyY.cpp Entities/FLyingEnemyX.cpp Entities/BossEnemy.cpp -lncurses -o ProgettoGame
./ProgettoGame