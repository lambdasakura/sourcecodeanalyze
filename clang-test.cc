#include <iostream>

#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/Host.h"

#include "clang/Frontend/DiagnosticOptions.h"
#include "clang/Frontend/TextDiagnosticPrinter.h"

#include "clang/Basic/LangOptions.h"
#include "clang/Basic/FileSystemOptions.h"

#include "clang/Basic/SourceManager.h"
#include "clang/Lex/HeaderSearch.h"
#include "clang/Basic/FileManager.h"

#include "clang/Frontend/HeaderSearchOptions.h"
#include "clang/Frontend/Utils.h"

#include "clang/Basic/TargetOptions.h"
#include "clang/Basic/TargetInfo.h"

#include "clang/Index/CallGraph.h"
#include "clang/Index/Indexer.h"
#include "clang/Index/TranslationUnit.h"
#include "clang/Index/DeclReferenceMap.h"
#include "clang/Index/SelectorMap.h"



#include "clang/Lex/Preprocessor.h"
#include "clang/Frontend/PreprocessorOptions.h"
#include "clang/Frontend/FrontendOptions.h"
#include "clang/Frontend/CompilerInstance.h"

#include "clang/Basic/IdentifierTable.h"
#include "clang/Basic/Builtins.h"

#include "clang/AST/ASTContext.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/Sema/Sema.h"
#include "clang/AST/DeclBase.h"
#include "clang/AST/Type.h"
#include "clang/AST/Decl.h"
#include "clang/Sema/Lookup.h"
#include "clang/Sema/Ownership.h"
#include "clang/AST/DeclGroup.h"
#include "clang/AST/CXXInheritance.h"
#include "clang/AST/ASTContext.h"

#include "clang/StaticAnalyzer/Core/CheckerManager.h"
#include "clang/Parse/Parser.h"

#include "clang/Parse/ParseAST.h"

class MyASTConsumer : public clang::ASTConsumer
{
 public:
  MyASTConsumer() : clang::ASTConsumer() { }
  virtual ~MyASTConsumer() { }
  
  virtual void HandleTranslationUnit(clang::ASTContext &Ctx) {

  }

  virtual void HandleTopLevelDecl( clang::DeclGroupRef d)
  {
    static int count = 0;
    
    clang::DeclGroupRef::iterator it;
    for( it = d.begin(); it != d.end(); it++)
    {
      
      std::cout << (*it)->getKind() <<std::endl;
      count++;
      clang::VarDecl *vd = llvm::dyn_cast<clang::VarDecl>(*it);
      if(vd)
      {
        //std::cout << vd << std::endl;
        if( vd->isFileVarDecl() /*&& vd->hasExternalStorage()*/ )
        {
          std::cerr << "Read top-level variable decl: '";
          std::cerr << vd->getDeclName().getAsString() ;
          std::cerr << std::endl;
        }
      }
      
      clang::FunctionDecl *fd = 
          llvm::dyn_cast<clang::FunctionDecl>(*it);
      if(!fd)
      {
        continue;
      }
      //std::cout << fd << std::endl;
      std::cerr << "Function decl: '";
      std::cerr << fd->getDeclName().getAsString() ;
      std::cerr << std::endl;
    }
  }
};

class ASTUnitTU : public clang::idx::TranslationUnit {
  clang::ASTContext* astContext;
  clang::Preprocessor* pp;
  clang::DiagnosticsEngine diagnostic;
  clang::idx::DeclReferenceMap DeclRefMap;
  clang::idx::SelectorMap SelMap;

 public:
  ASTUnitTU(clang::ASTContext* _astContext,
            clang::Preprocessor* _pp,
            clang::DiagnosticsEngine _diagnostic,
            clang::idx::DeclReferenceMap declRefMap,
            clang::idx::SelectorMap selMap
            )
      :
      astContext(_astContext),
      pp(_pp),
      diagnostic(_diagnostic),
      DeclRefMap(declRefMap),
      SelMap(selMap)
  {};

  virtual clang::ASTContext &getASTContext() {
    return *astContext;
  }

  virtual clang::Preprocessor &getPreprocessor() {
    return *pp;
  }

  virtual clang::DiagnosticsEngine &getDiagnostic() {
    return diagnostic;
  }

  virtual clang::idx::DeclReferenceMap &getDeclReferenceMap() {
    return DeclRefMap;
  }

  virtual clang::idx::SelectorMap &getSelectorMap() {
    return SelMap;
  }
};



int main()
{

  // Indexerをセットアップする
  clang::idx::Program Prog;
  clang::idx::Indexer Idxer(Prog);
  
  
  // 言語オプションをセットアップする。
  clang::LangOptions langOpts;
  langOpts.BCPLComment = true;
  langOpts.Bool   = true;
  langOpts.CPlusPlus  = true;
  langOpts.CPlusPlus0x = true;
  langOpts.Exceptions  = true;
  langOpts.CXXExceptions = true;
  langOpts.MSBitfields = true;
  langOpts.NeXTRuntime = false;
  langOpts.NoBuiltin  = true;

  // DiagnosticsEngine Initialize
  clang::DiagnosticOptions diagOpts;
  clang::TextDiagnosticPrinter diagPrinter(llvm::outs(), diagOpts);
  diagPrinter.BeginSourceFile(langOpts, NULL);

  llvm::IntrusiveRefCntPtr<clang::DiagnosticIDs>
      diagIds(new clang::DiagnosticIDs());
  clang::DiagnosticsEngine diagEngine(diagIds, &diagPrinter, false);
  clang::Diagnostic diag(&diagEngine);

  // Triple Initialize
  llvm::Triple triple;
  triple.setArch(llvm::Triple::x86);
  triple.setVendor(llvm::Triple::PC);
  triple.setOS(llvm::Triple::Linux);
  clang::TargetOptions targetOpts;
  targetOpts.Triple = triple.getTriple();
  clang::TargetInfo* targetInfo
      = clang::TargetInfo::CreateTargetInfo(diagEngine, targetOpts);

  // SourceManager Initialize
  clang::FileSystemOptions fileSysOpts;
  clang::FileManager fileMgr(fileSysOpts);
  clang::SourceManager srcMgr(diagEngine, fileMgr);

  // HeaderSearch Initialize
  clang::HeaderSearch headerSearch(fileMgr);
  clang::HeaderSearchOptions headerSearchOpts;
  headerSearchOpts.UseLibcxx = 1;
  // headerSearchOpts.Verbose = 1;
  headerSearchOpts.AddPath("/usr/include/linux",
                           clang::frontend::Angled,
                           false,    false,    false);
  headerSearchOpts.AddPath("/usr/include/c++/4.4/tr1",
                           clang::frontend::Angled,
                           false,    false,    false);
  headerSearchOpts.AddPath("/usr/include/c++/4.4",
                           clang::frontend::Angled,
                           false,false,    false);
  clang::ApplyHeaderSearchOptions(headerSearch,
                                  headerSearchOpts,
                                  langOpts,
                                  triple);


  // Preprocessor Initialize
  clang::CompilerInstance compiler;
  clang::Preprocessor pp(diagEngine,
                         langOpts,
                         targetInfo,
                         srcMgr,
                         headerSearch,
                         compiler);
  clang::PreprocessorOptions ppOpts;
  clang::FrontendOptions frontendOpts;
  clang::InitializePreprocessor(pp,
                                ppOpts,
                                headerSearchOpts,
                                frontendOpts);


  // choose target file
  const clang::FileEntry *pFile = fileMgr.getFile("./hello.cc");
  srcMgr.createMainFileID(pFile);
  clang::IdentifierTable identifierTable(langOpts);
  clang::SelectorTable selectorTable;
  clang::Builtin::Context builtinContext;
  builtinContext.InitializeTarget(*targetInfo);
  
  // generate ASTContext
  clang::ASTContext astContext(
      langOpts,
      srcMgr,
      targetInfo,
      identifierTable,
      selectorTable,
      builtinContext,
      0 );

  MyASTConsumer astConsumer;

  clang::Sema sema(
      pp,
      astContext,
      astConsumer);
  sema.Initialize();
  clang::ParseAST(pp, &astConsumer, astContext);

  clang::idx::DeclReferenceMap declRefMap(astContext);
  clang::idx::SelectorMap selMap(astContext);

  clang::ASTContext astContext2(
      langOpts,
      srcMgr,
      targetInfo,
      identifierTable,
      selectorTable,
      builtinContext,
      0 );
  ASTUnitTU* astUnitTU = new ASTUnitTU(&astContext2,
                                       &pp,
                                       astContext.getDiagnostics(),
                                       declRefMap,
                                       selMap
                                       );
  Idxer.IndexAST(astUnitTU);
  clang::idx::Entity Ent = 
      clang::idx::Entity::get("func", Idxer.getProgram());
  std::cout << Ent.getPrintableName() << std::endl;

  clang::FunctionDecl *FD;
  clang::idx::TranslationUnit *TU;
  llvm::tie(FD, TU) = Idxer.getDefinitionFor(Ent);

  if (!FD) {
    std::cout << "not found" << std::endl;
    return 0;
  }


  return 0;
}
