docker run --rm -v $(pwd):/work eguerin/antlr4cpp bash -c "cd /work; make ANTLR4_INCDIR=/usr/include/antlr4-runtime ANTLR4_BINDIR=/bin ANTLR4_LIBDIR=/lib/x86_64-linux-gnu"
