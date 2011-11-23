CXX=gcc -std=c++0x
LLVMHOME=/home/sakura/llvm/
LLVMCONFIG=$(LLVMHOME)/Debug+Asserts/bin/llvm-config
CXXFLAGS=-O2 -I$(LLVMHOME)/tools/clang/include \
		 -fno-rtti \
		 `$(LLVMCONFIG) --cxxflags`

# clangParse required starting from tut04
# clangAST and clangSema required starting from tut06
# clangRewrite required in tut09
LDFLAGS= -O2 `$(LLVMCONFIG) --ldflags --libs`
LIBS= -lLLVMMBlazeAsmPrinter \
-lclangFrontendTool \
-lLLVMARMDesc \
-lLLVMMBlazeDesc \
-lLLVMCppBackendInfo \
-lLLVMXCoreDesc \
-lLLVMARMAsmParser \
-lLLVMSupport \
-lclangParse \
-lLLVMPowerPCAsmPrinter \
-lclangAnalysis \
-lLLVMCellSPUDesc \
-lLLVMDebugInfo \
-lLLVMMSP430AsmPrinter \
-lLLVMX86Utils \
-lLLVMPTXInfo \
-lclangStaticAnalyzerCheckers \
-lLLVMSparcCodeGen \
-lLLVMX86Info \
-lLLVMSelectionDAG \
-lLLVMARMInfo \
-lLLVMMipsInfo \
-lLLVMXCoreCodeGen \
-lLLVMExecutionEngine \
-lLLVMLinker \
-lLLVMPTXAsmPrinter \
-lclangRewrite \
-lLLVMPTXCodeGen \
-lclangFrontend \
-lLLVMTransformUtils \
-lclangBasic \
-lclangCodeGen \
-lLLVMTarget \
-lLLVMMBlazeDisassembler \
-lLLVMPowerPCDesc \
-lLLVMCBackendCodeGen \
-lLLVMSparcInfo \
-lLLVMipo \
-lclangSerialization \
-lLLVMPowerPCCodeGen \
-lLLVMCppBackendCodeGen \
-lLLVMAnalysis \
-lLLVMPowerPCInfo \
-lLLVMMSP430Info \
-lLLVMCBackendInfo \
-lLLVMAsmPrinter \
-lLLVMMipsCodeGen \
-lLLVMMCParser \
-lclangIndex \
-lLLVMMC \
-lclangDriver \
-lLLVMPTXDesc \
-lLLVMSparcDesc \
-lLLVMMBlazeAsmParser \
-lLLVMTableGen \
-lLLVMMBlazeCodeGen \
-lLLVMCellSPUInfo \
-lLLVMJIT \
-lclangLex \
-lLLVMMCJIT \
-lLLVMScalarOpts \
-lLLVMARMDisassembler \
-lprofile_rt \
-lLLVMX86CodeGen \
-lclang \
-lLLVMCellSPUCodeGen \
-lLLVMMSP430CodeGen \
-lLLVMMSP430Desc \
-lLTO \
-lLLVMXCoreInfo \
-lEnhancedDisassembly \
-lLLVMipa \
-lLLVMARMAsmPrinter \
-lLLVMCore \
-lLLVMX86AsmParser \
-lclangStaticAnalyzerCore \
-lLLVMMCDisassembler \
-lLLVMBitWriter \
-lclangSema \
-lLLVMMBlazeInfo \
-lLLVMAsmParser \
-lLLVMInterpreter \
-lLLVMInstrumentation \
-lLLVMX86Desc \
-lLLVMX86AsmPrinter \
-lLLVMX86Disassembler \
-lLLVMARMCodeGen \
-lLLVMRuntimeDyld \
-lLLVMInstCombine \
-lLLVMMipsAsmPrinter \
-lclangAST \
-lLLVMBitReader \
-lLLVMCodeGen \
-lLLVMObject \
-lLLVMMipsDesc \
-lclangARCMigrate \
-lLLVMArchive \
-lclangStaticAnalyzerFrontend \
-lUnitTestMain \
-lclangAnalysis \
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
-lpthread \
-ldl \
-lLLVMBitWriter -lLLVMBitReader -lLLVMCodeGen -lLLVMAnalysis \
-lLLVMTarget

all: main

clean:
	rm -rf main main.o

main: main.o
	g++ $(LDFLAGS) -o main main.o $(LIBS)


main.o: main.cpp

