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
