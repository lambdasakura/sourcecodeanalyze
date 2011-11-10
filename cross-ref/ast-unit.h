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



class ASTUnitTU : public clang::idx::TranslationUnit {
  llvm::IntrusiveRefCntPtr<clang::ASTContext> astContext;
  llvm::IntrusiveRefCntPtr<clang::Preprocessor> pp;

  clang::DiagnosticsEngine* diagnostic;
  clang::idx::DeclReferenceMap* declRefMap;
  clang::idx::SelectorMap* selMap;

 public:
  ASTUnitTU(llvm::IntrusiveRefCntPtr<clang::ASTContext>  _astContext,
            llvm::IntrusiveRefCntPtr<clang::Preprocessor> _pp,
            clang::DiagnosticsEngine* _diagnostic
      
            )
      :
      astContext(_astContext),
      pp(_pp),
      diagnostic(_diagnostic)
  {
    this->declRefMap = new clang::idx::DeclReferenceMap(*_astContext);
    this->selMap = new clang::idx::SelectorMap(*_astContext);
  };

  virtual clang::ASTContext &getASTContext() {
    return *astContext;
  }

  virtual clang::Preprocessor &getPreprocessor() {
    return *pp;
  }

  virtual clang::DiagnosticsEngine &getDiagnostic() {
    return *diagnostic;
  }

  virtual clang::idx::DeclReferenceMap &getDeclReferenceMap() {
    return *declRefMap;
  }

  virtual clang::idx::SelectorMap &getSelectorMap() {
    return *selMap;
  }
};
