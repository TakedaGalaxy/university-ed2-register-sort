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
	out\main.exe -s out\data-256000.bin 8388608 1048576 out\data-sorted-256000-8MB-S8.bin
	out\main.exe -s out\data-256000.bin 8388608 2097152 out\data-sorted-256000-8MB-S4.bin
	out\main.exe -s out\data-256000.bin 8388608 4194304 out\data-sorted-256000-8MB-S2.bin
#B=8388608 (8Mb)
#B=8388608 (16Mb)
#B=8388608 (32Mb)

win-read:
	out\main.exe -r out\data-sorted-256000-8MB-S8.bin out\data-sorted-256000-8MB-S8.txt
	out\main.exe -r out\data-sorted-256000-8MB-S4.bin out\data-sorted-256000-8MB-S4.txt
	out\main.exe -r out\data-sorted-256000-8MB-S2.bin out\data-sorted-256000-8MB-S2.txt