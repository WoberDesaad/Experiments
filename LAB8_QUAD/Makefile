GXX=g++ -O3 -Wall
GFLAGS=-O3
GDFLAGS=-O3 -Wall -pg
LDFLAGS=-lpng -ldl

all:
	$(GXX) $(GFLAGS) quadcompress.cpp $(LDFLAGS) -o QUAD_COMPRESS
	$(GXX) $(GFLAGS) quaddecompress.cpp $(LDFLAGS) -o QUAD_DECOMPRESS

debug:
	$(GXX) $(GDFLAGS) quadcompress.cpp $(LDFLAGS) -o QUAD_COMPRESS
	$(GXX) $(GDFLAGS) quaddecompress.cpp $(LDFLAGS) -o QUAD_DECOMPRESS

clean:
	rm *~ QUAD_COMPRESS QUAD_DECOMPRESS out.png *.z
