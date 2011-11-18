#include <iostream>

#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/Host.h"
#include "llvm/ADT/IntrusiveRefCntPtr.h"

#include "clang/Basic/Builtins.h"
#include "clang/Basic/FileSystemOptions.h"
#include "clang/Basic/FileManager.h"
#include "clang/Basic/IdentifierTable.h"
#include "clang/Basic/SourceManager.h"
#include "clang/Basic/TargetOptions.h"
#include "clang/Basic/TargetInfo.h"
#include "clang/Basic/LangOptions.h"
#include "clang/Basic/FileManager.h"
#include "clang/Basic/TargetOptions.h"
#include "clang/Basic/TargetInfo.h"
#include "clang/Basic/FileManager.h"
#include "clang/Basic/SourceManager.h"
#include "clang/Basic/IdentifierTable.h"
#include "clang/Basic/Builtins.h"
#include "clang/Basic/TargetInfo.h"

#include "clang/Lex/HeaderSearch.h"
#include "clang/Lex/Preprocessor.h"


#include "clang/Frontend/DiagnosticOptions.h"
#include "clang/Frontend/TextDiagnosticPrinter.h"
#include "clang/Frontend/HeaderSearchOptions.h"
#include "clang/Frontend/Utils.h"
#include "clang/Frontend/PreprocessorOptions.h"
#include "clang/Frontend/FrontendOptions.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/DiagnosticOptions.h"
#include "clang/Frontend/TextDiagnosticPrinter.h"
#include "clang/Frontend/HeaderSearchOptions.h"
#include "clang/Frontend/Utils.h"
#include "clang/Frontend/PreprocessorOptions.h"
#include "clang/Frontend/FrontendOptions.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/DiagnosticOptions.h"
#include "clang/Frontend/TextDiagnosticPrinter.h"
#include "clang/Frontend/ASTUnit.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/HeaderSearchOptions.h"
#include "clang/Frontend/Utils.h"
#include "clang/Frontend/PreprocessorOptions.h"
#include "clang/Frontend/FrontendOptions.h"
#include "clang/Frontend/CompilerInstance.h"

#include "clang/AST/ASTContext.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/AST/DeclBase.h"
#include "clang/AST/Type.h"
#include "clang/AST/Decl.h"
#include "clang/AST/DeclGroup.h"
#include "clang/AST/CXXInheritance.h"
#include "clang/AST/ASTContext.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/AST/DeclBase.h"
#include "clang/AST/Type.h"
#include "clang/AST/Decl.h"
#include "clang/AST/DeclGroup.h"
#include "clang/AST/CXXInheritance.h"
#include "clang/AST/ASTContext.h"

#include "clang/Sema/Sema.h"
#include "clang/Sema/Lookup.h"
#include "clang/Sema/Ownership.h"

#include "clang/Parse/Parser.h"
#include "clang/Parse/ParseAST.h"

#include "clang/Index/CallGraph.h"
#include "clang/Index/Indexer.h"
#include "clang/Index/TranslationUnit.h"
#include "clang/Index/DeclReferenceMap.h"
#include "clang/Index/SelectorMap.h"
#include "clang/Index/Handlers.h"
#include "clang/Index/CallGraph.h"
#include "clang/Index/Indexer.h"
#include "clang/Index/Analyzer.h"
#include "clang/Index/TranslationUnit.h"
#include "clang/Index/DeclReferenceMap.h"


#include "clang/Lex/HeaderSearch.h"
#include "clang/Lex/Preprocessor.h"

#include "clang/StaticAnalyzer/Core/CheckerManager.h"
#include "clang/StaticAnalyzer/Core/CheckerManager.h"
#include "clang/StaticAnalyzer/Frontend/CheckerRegistration.h"
#include "clang/StaticAnalyzer/Core/PathSensitive/AnalysisManager.h"
#include "clang/StaticAnalyzer/Core/PathSensitive/ExprEngine.h"
//#include "clang/StaticAnalyzer/Core/PathSensitive/TransferFuncs.h"
#include "clang/StaticAnalyzer/Core/CheckerManager.h"
#include "clang/StaticAnalyzer/Checkers/LocalCheckers.h"



#include <llvm/Support/Host.h>
#include <clang/AST/ASTConsumer.h>
#include <clang/AST/Decl.h>
#include <clang/AST/DeclGroup.h>
#include <clang/Basic/TargetInfo.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/CompilerInvocation.h>
#include <clang/Parse/ParseAST.h>

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <time.h>

class ASTUnitTU : public clang::idx::TranslationUnit {
	clang::ASTUnit *AST;
	clang::idx::DeclReferenceMap DeclRefMap;
	clang::idx::SelectorMap SelMap;

public:
	ASTUnitTU(clang::ASTUnit *ast) 
		: AST(ast), DeclRefMap(AST->getASTContext()), SelMap(AST->getASTContext()) {
	}

	virtual clang::ASTContext &getASTContext() {
		return AST->getASTContext();
	}

	virtual clang::Preprocessor &getPreprocessor() {
		return AST->getPreprocessor();
	}

	virtual clang::DiagnosticsEngine &getDiagnostic() {
		return AST->getDiagnostics();
	}

	virtual clang::DeclReferenceMap &getDeclReferenceMap() {
		return DeclRefMap;
	}

	virtual clang::SelectorMap &getSelectorMap() {
		return SelMap;
	}
};


class MyASTConsumer : public clang::ASTConsumer
{
public:
	MyASTConsumer() : clang::ASTConsumer() { }
	virtual ~MyASTConsumer() { }

	virtual void HandleTopLevelDecl( clang::DeclGroupRef d)
	{
		////static int count = 0;
		//clang::DeclGroupRef::iterator it;
		//for( it = d.begin(); it != d.end(); it++)
		//{
		//	//count++;
		//	clang::VarDecl *vd = llvm::dyn_cast<clang::VarDecl>(*it);
		//	if(!vd)
		//	{
		//		continue;
		//	}
		//	std::cout << vd << std::endl;
		//	if( vd->isFileVarDecl() /*&& vd->hasExternalStorage()*/ )
		//	{
		//		std::cerr << "Read top-level variable decl: '";
		//		std::cerr << vd->getDeclName().getAsString() ;
		//		std::cerr << std::endl;
		//	}
		//}
	}
};


class Handler : public clang::idx::TULocationHandler {
public:
	Handler(clang::SourceManager* _sourceManager) {
		this->sourceManager = _sourceManager;
	}
private:
	clang::SourceManager* sourceManager;
	void Handle(clang::TULocation TULoc)  {
		auto a = TULoc.dyn_AsStmt();
		auto hogehoge = TULoc.getParentDecl();
		std::cout << hogehoge->getDeclKindName();
		clang::FunctionDecl* fd = llvm::dyn_cast<clang::FunctionDecl>(hogehoge);
		if(fd) {
			a->dump();

			auto hoge = this->sourceManager->getSpellingLineNumber(TULoc.getSourceRange().getBegin());
			std::cout <<  "used in: " << fd->getDeclName().getAsString() << hoge << std::endl;
		} else {
			std::cout << "are-?" << std::endl;		}
	}
};

// generate ASTUnit from source file.
clang::ASTUnit* generateASTUnitFromSource(const char** argv) {
	clang::CompilerInstance compiler;

	// Setup Diagnostic Options
	clang::DiagnosticOptions diagOpts;
	diagOpts.ErrorLimit = 30000;
	diagOpts.IgnoreWarnings = 1;
	diagOpts.TabStop = clang::DiagnosticOptions::DefaultTabStop;
	diagOpts.MessageLength = 0;
	diagOpts.NoRewriteMacros = 0;
	diagOpts.Pedantic = 0;
	diagOpts.PedanticErrors = 0;
	diagOpts.ShowCarets = 1;
	diagOpts.ShowColors = 0;
	diagOpts.ShowOverloads = clang::DiagnosticsEngine::Ovl_All;
	diagOpts.ShowColumn = 1;
	diagOpts.ShowFixits = 1;
	diagOpts.ShowLocation = 1;
	diagOpts.ShowOptionNames = 0;
	diagOpts.ShowCategories = 0;
	diagOpts.ShowSourceRanges = 0;
	diagOpts.ShowParseableFixits = 0;
	diagOpts.VerifyDiagnostics = 0;
	diagOpts.TemplateBacktraceLimit = clang::DiagnosticOptions::DefaultTemplateBacktraceLimit;
	diagOpts.MacroBacktraceLimit = clang::DiagnosticOptions::DefaultMacroBacktraceLimit;

	clang::TextDiagnosticPrinter diagPrinter(llvm::outs(), diagOpts);
	auto test = new clang::IgnoringDiagConsumer();
	auto diagnosticEngine = compiler.createDiagnostics(diagOpts,2,argv,test);
	compiler.setDiagnostics(diagnosticEngine.getPtr());
	//compiler.setDiagnostics(compiler.createDiagnostics(diagOpts,argc, argv));

	auto& diag = compiler.getDiagnostics();
	auto& invocation = compiler.getInvocation();

	clang::LangOptions langOpts;
	langOpts.BCPLComment = true;
	langOpts.Bool   = true;
	//langOpts.Microsoft = true;
	langOpts.CPlusPlus  = true;
	langOpts.CPlusPlus0x = true;
	langOpts.Exceptions  = true;
	langOpts.CXXExceptions = true;
	langOpts.MSBitfields = true;
	langOpts.NeXTRuntime = false;
	langOpts.NoBuiltin  = true;
	langOpts.CatchUndefined = false;
	langOpts.EmitAllDecls = true;
	//langOpts.MSCVersion  = _MSC_VER;

	invocation.setLangDefaults(langOpts,clang::IK_C);

	auto depOpts = invocation.getDependencyOutputOpts();
	depOpts.UsePhonyTargets = 1;

	clang::CompilerInvocation::CreateFromArgs(invocation, argv + 1, argv + 2, diag);
	compiler.setTarget(clang::TargetInfo::CreateTargetInfo(diag, compiler.getTargetOpts()));

	compiler.createFileManager();
	compiler.createSourceManager(compiler.getFileManager());
	compiler.createPreprocessor();
	compiler.createASTContext();
	compiler.setASTConsumer(new MyASTConsumer());
	compiler.createSema(clang::TU_Complete, nullptr);

	// To Parse C Source file from ARG
	auto& inputs = compiler.getFrontendOpts().Inputs;
	if (inputs.size() > 0) {
		compiler.InitializeSourceManager(inputs[0].second);
		clang::ParseAST(
			compiler.getPreprocessor(),
			&compiler.getASTConsumer(),
			compiler.getASTContext()
			);
	}

	return clang::ASTUnit::LoadFromCompilerInvocation(&invocation,
		llvm::IntrusiveRefCntPtr<clang::DiagnosticsEngine>(&diag));
}


int main(int argc, char** argv) {
	clock_t start,end;
	start = clock();

	// generate cross reference info
	clang::idx::Program Prog;
	clang::idx::Indexer Idxer(Prog);


	std::ifstream inf(argv[1], std::ios::in);
	std::cout << argv[1] << "read." <<std::endl;
	std::vector<std::string> lines;
	std::string line;

	while(getline(inf, line)) lines.push_back(line);

	inf.close();

	std::vector<std::string>::iterator itr;
	for(itr=lines.begin();itr!=lines.end();++itr) {
		std::cout << itr->c_str() << std::endl;
		const char* inputs[] = {argv[0],itr->c_str()};
		auto ast = generateASTUnitFromSource(inputs);
		//auto astTU = new ASTUnitTU(ast);
		//Idxer.IndexAST(astTU);
	}



	// get Entity  
	//clang::idx::Entity Ent =
	//	clang::idx::Entity::get("a", Idxer.getProgram());
	//std::cout << Ent.getPrintableName() << std::endl;

	//clang::FunctionDecl *FD;
	//auto decl = Ent.getDecl(ast->getASTContext());

	//clang::idx::TranslationUnit *TU;
	//llvm::tie(FD, TU) = Idxer.getDefinitionFor(Ent);

	////if (!FD) {
	////	std::cout << "not found" << std::endl;
	////	return 0;
	////}
	////Handler handler(&compiler.getSourceManager());

	//clang::idx::Analyzer* analyzer = new clang::idx::Analyzer(Idxer.getProgram(),Idxer);
	////analyzer->FindReferences(decl,handler);

	end = clock();
	printf("%.2f秒かかりました\n",(double)(end-start)/CLOCKS_PER_SEC);

	return 0;
}