LLVMHOME=/home/sakura/llvm/llvm/
LLVMCONFIG=$(LLVMHOME)/Debug+Asserts/bin/llvm-config
CXXFLAGS=-I$(LLVMHOME)/tools/clang/include \
		 -fno-rtti \
		 `$(LLVMCONFIG) --cxxflags`

# clangParse required starting from tut04
# clangAST and clangSema required starting from tut06
# clangRewrite required in tut09
LDFLAGS= `$(LLVMCONFIG) --ldflags`
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

all: var-func-dumper

clean:
	rm -rf var-func-dumper var-func-dumper.o

var-func-dumper: var-func-dumper.o
	g++ $(LDFLAGS) -o var-func-dumper var-func-dumper.o $(LIBS)


var-func-dumper.o: var-func-dumper.cc
