LLVMHOME=/Users/sakura/llvm/llvm/
LLVMCONFIG=$(LLVMHOME)/Debug+Asserts/bin/llvm-config
CXXFLAGS=-I$(LLVMHOME)/tools/clang/include \
		 -fno-rtti \
		 `$(LLVMCONFIG) --cxxflags`

# clangParse required starting from tut04
# clangAST and clangSema required starting from tut06
# clangRewrite required in tut09
LDFLAGS= `$(LLVMCONFIG) --ldflags --libs`
LIBS= -lclangAnalysis \
      -lclangStaticAnalyzerCore \
      -lclangARCMigrate \
      -lclangIndex \
      -lclangFrontendTool \
      -lclangBasic \
      -lclangSema \
      -lclangStaticAnalyzerCheckers \
      -lclangCodeGen \
      -lclangStaticAnalyzerFrontend \
      -lclangFrontend \
      -lclangCodeGen \
      -lclangAnalysis \
      -lclangRewrite \
      -lclangSema \
      -lclangFrontend \
      -lclangSerialization \
      -lclangDriver \
      -lclangAST \
      -lclangParse \
      -lclangLex \
      -lclangBasic \
      -lLLVMCore \
      -lLLVMSupport \
      -lLLVMMC \
      -lLLVMBitWriter -lLLVMBitReader -lLLVMCodeGen -lLLVMAnalysis \
      -lLLVMTarget

all: cross-ref-dump

clean:
	rm -rf cross-ref-dump cross-ref-dump.o

cross-ref-dump: main.o
	clang++ $(LDFLAGS) -o main main.o $(LIBS)


main.o: main.cpp

