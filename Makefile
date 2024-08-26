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

win-sort:
#B=8388608 (8Mb)
	out\main.exe -s out\data-256000.bin 8388608 1048576 out\data-sorted-256000-8MB-S8.bin
#B=8388608 (16Mb)
	out\main.exe -s out\data-256000.bin 8388608 2097152 out\data-sorted-256000-8MB-S4.bin
#B=8388608 (32Mb)
	out\main.exe -s out\data-256000.bin 8388608 4194304 out\data-sorted-256000-8MB-S2.bin

win-read:
	out\main.exe -r out\data-sorted-256000-8MB-S8.bin out\data-sorted-256000-8MB-S8.txt
	out\main.exe -r out\data-sorted-256000-8MB-S4.bin out\data-sorted-256000-8MB-S4.txt
	out\main.exe -r out\data-sorted-256000-8MB-S2.bin out\data-sorted-256000-8MB-S2.txt