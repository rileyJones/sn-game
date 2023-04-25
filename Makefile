project_name = game

run: build
	./build/${project_name}

build: cmake src
	cmake --build build

cmake: CMakeLists.txt
	cd build; cmake .. 

clean:
	rm -r build/*
