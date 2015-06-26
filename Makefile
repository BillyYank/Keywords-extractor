all:
	g++ --std=c++11 main.cpp Extractor.cpp Helper.cpp  porter2_stemmer.cpp -o Extractor
