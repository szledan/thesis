### thesis

all:
	make thesis
	make grayscale

hunspell:
	hunspell -d hu_HU -i utf-8 -t -p paper/hunspell/words paper/src/szakdolgozat.tex

install.deps:
	./scripts/install-deps.sh

install.deps.dev:
	./scripts/install-deps.sh --dev

clean:
	rm -rf build/*

dist.clean:
	rm -rf build

thesis:
	cmake -H. -Bbuild
	make -C build

grayscale: src
	./scripts/convert-grayscale.sh build/paper/src/szakdolgozat.pdf build/paper/src/szakdolgozat-gs.pdf

examples:
	make -C build/paper/examples

src: examples
	make -C build/paper/src

### code

code.fetch:
	./scripts/fetch-code.sh git@github.com:szledan/gepard.git thesis-dev

code.remove:
	rm -rf code/gepard
