all:
	g++ -g src/*.cpp src/**/**/*.cpp -o ./out/main

generate:
	out/main.exe -g out/data-256000.bin 256000 24
	out/main.exe -g out/data-512000.bin 512000 69
	out/main.exe -g out/data-921600.bin 921600 51

win-generate:
	out\main.exe -g out\data-256000.bin 256000 24
	out\main.exe -g out\data-512000.bin 512000 69
	out\main.exe -g out\data-921600.bin 921600 51

win-sort:
#B=8388608 (8Mb) S=B/8
	out\main.exe -s out\data-256000.bin 8388608 1048576 out\data-sorted-256000-8MB-S8.bin

win-read:
	out\main.exe -r out\data-sorted-256000-8MB-S8.bin out\data-sorted-256000-8MB-S8.txt