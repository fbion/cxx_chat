clean:
	echo "start clean\n"

test:
	echo "start test\n"

build:
	g++ ./src/*.cpp ./src/*/*.cpp -luv -o main.out