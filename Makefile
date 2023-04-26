project_name = game

build: cmake src
	cmake --build build

run: build
	./build/${project_name}

cmake: CMakeLists.txt
	cd build; cmake .. 

clean:
	rm -r build/*
