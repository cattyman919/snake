PHONY: all

all:
	ninja -C build
	./build/snake

clean:
	rm -rf build
