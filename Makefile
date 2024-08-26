all:
	g++ -g src/*.cpp src/**/**/*.cpp -o ./out/main

generate:
	out/main.exe -g out/data-256000.bin 256000 42
	out/main.exe -g out/data-512000.bin 512000 42
	out/main.exe -g out/data-921600.bin 921600 42
	out/main.exe -g out/data-1572864.bin 1572864 42

win-generate:
	out\main.exe -g out\data-256000.bin 256000 42
	out\main.exe -g out\data-512000.bin 512000 42
	out\main.exe -g out\data-921600.bin 921600 42
	out\main.exe -g out\data-1572864.bin 1572864 42
