all:
	nvcc -rdc=true sha256.cu sha1.cu md2.cu md5.cu blake2b.cu keccak.cu main.cpp -o bench

run: all
	./bench

clean:
	rm bench