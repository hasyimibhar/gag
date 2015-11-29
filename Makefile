CC = g++
CFLAGS = -Wall
LFLAGS = -lcurses
TARGET_NAME = gag
OBJS = obj/Application.o obj/ColorPairManager.o obj/Common.o obj/Log.o obj/Timer.o \
obj/Bullet.o obj/FirePower.o obj/Goal.o obj/InfoPopup.o obj/Mushroom.o obj/Player.o obj/PlayerCheckPoint.o \
obj/PlayerSpawnPoint.o obj/Spike.o obj/Tile.o obj/Camera.o obj/CollisionManager.o obj/Entity.o \
obj/GameContent.o obj/Level.o obj/LevelManager.o obj/LevelTimeManager.o obj/TextInput.o obj/World.o \
obj/CreditsState.o obj/EditorState.o obj/GameState.o obj/MainMenuState.o

main: $(OBJS) bin levels
	$(CC) -o bin/$(TARGET_NAME) $(CFLAGS) $(LFLAGS) src/main.cpp $(OBJS)

obj/Application.o: obj
	$(CC) -c $(CLFAGS) -o obj/Application.o src/Application/Application.cpp

obj/ColorPairManager.o: obj
	$(CC) -c $(CLFAGS) -o obj/ColorPairManager.o src/Common/ColorPairManager.cpp

obj/Common.o: obj
	$(CC) -c $(CLFAGS) -o obj/Common.o src/Common/Common.cpp

obj/Log.o: obj
	$(CC) -c $(CLFAGS) -o obj/Log.o src/Common/Log.cpp

obj/Timer.o: src/Common/Timer.h obj
	$(CC) -c $(CLFAGS) -o obj/Timer.o src/Common/Timer.cpp

obj/Bullet.o: obj
	$(CC) -c $(CLFAGS) -o obj/Bullet.o src/Entities/Bullet.cpp

obj/FirePower.o: obj
	$(CC) -c $(CLFAGS) -o obj/FirePower.o src/Entities/FirePower.cpp

obj/Goal.o: obj
	$(CC) -c $(CLFAGS) -o obj/Goal.o src/Entities/Goal.cpp

obj/InfoPopup.o: obj
	$(CC) -c $(CLFAGS) -o obj/InfoPopup.o src/Entities/InfoPopup.cpp

obj/Mushroom.o: obj
	$(CC) -c $(CLFAGS) -o obj/Mushroom.o src/Entities/Mushroom.cpp

obj/Player.o: obj
	$(CC) -c $(CLFAGS) -o obj/Player.o src/Entities/Player.cpp

obj/PlayerCheckPoint.o: obj
	$(CC) -c $(CLFAGS) -o obj/PlayerCheckPoint.o src/Entities/PlayerCheckPoint.cpp

obj/PlayerSpawnPoint.o: obj
	$(CC) -c $(CLFAGS) -o obj/PlayerSpawnPoint.o src/Entities/PlayerSpawnPoint.cpp

obj/Spike.o: obj
	$(CC) -c $(CLFAGS) -o obj/Spike.o src/Entities/Spike.cpp

obj/Tile.o: obj
	$(CC) -c $(CLFAGS) -o obj/Tile.o src/Entities/Tile.cpp

obj/Camera.o: obj
	$(CC) -c $(CLFAGS) -o obj/Camera.o src/Game/Camera.cpp

obj/CollisionManager.o: obj
	$(CC) -c $(CLFAGS) -o obj/CollisionManager.o src/Game/CollisionManager.cpp

obj/Entity.o: obj
	$(CC) -c $(CLFAGS) -o obj/Entity.o src/Game/Entity.cpp

obj/GameContent.o: obj
	$(CC) -c $(CLFAGS) -o obj/GameContent.o src/Game/GameContent.cpp

obj/Level.o: obj
	$(CC) -c $(CLFAGS) -o obj/Level.o src/Game/Level.cpp

obj/LevelManager.o: obj
	$(CC) -c $(CLFAGS) -o obj/LevelManager.o src/Game/LevelManager.cpp

obj/LevelTimeManager.o: obj
	$(CC) -c $(CLFAGS) -o obj/LevelTimeManager.o src/Game/LevelTimeManager.cpp

obj/TextInput.o: obj
	$(CC) -c $(CLFAGS) -o obj/TextInput.o src/Game/TextInput.cpp

obj/World.o: obj
	$(CC) -c $(CLFAGS) -o obj/World.o src/Game/World.cpp

obj/CreditsState.o: obj
	$(CC) -c $(CLFAGS) -o obj/CreditsState.o src/States/CreditsState.cpp

obj/EditorState.o: obj
	$(CC) -c $(CLFAGS) -o obj/EditorState.o src/States/EditorState.cpp

obj/GameState.o: obj
	$(CC) -c $(CLFAGS) -o obj/GameState.o src/States/GameState.cpp

obj/MainMenuState.o: obj
	$(CC) -c $(CLFAGS) -o obj/MainMenuState.o src/States/MainMenuState.cpp

levels: bin
	cp -r dist/* bin

obj:
	mkdir obj

bin:
	mkdir bin

clean:
	rm -rf {obj,bin}
