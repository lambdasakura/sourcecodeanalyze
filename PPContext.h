#ifndef PP_CONTEXT
#define PP_CONTEXT

#include <string>

#include "llvm/Config/config.h"
#include "llvm/Support/raw_ostream.h"


#include "clang/Basic/Diagnostic.h"
#include "clang/Basic/TargetInfo.h"
#include "clang/Basic/SourceManager.h"
#include "clang/Basic/FileManager.h"

#include "clang/Lex/HeaderSearch.h"
#include "clang/Lex/Preprocessor.h"

#include "clang/Frontend/TextDiagnosticPrinter.h"

struct PPContext {

  clang::DiagnosticConsumer* diagClient;
  clang::Diagnostic diags;
  clang::LangOptions opts;
  clang::TargetInfo* target;
  clang::SourceManager sm;
  clang::FileManager fm;
  clang::HeaderSearch headers;
  clang::Preprocessor pp;
  

  // // Takes ownership of client.

  PPContext(clang::DiagnosticConsumer* client = 0,
            const std::string& triple = "i686-pc-linux"
            // LLVM_HOSTTRIPLE
            )
      : diagClient(client == 0 ?
                   new clang::TextDiagnosticPrinter(
                       new llvm::raw_os_ostream(std::cout) ,
                       null ) : client ),
      diags(diagClient),
      target(clang::TargetInfo::CreateTargetInfo(triple)),
      headers(fm),
      pp(diags, opts, *target, sm, headers)
  {
    // Configure warnings to be similar to what command-line `clang` outputs
    // (see tut03).
    // XXX: move warning initialization to libDriver
    using namespace clang;
    diags.setDiagnosticMapping(diag::warn_pp_undef_identifier,diag::MAP_IGNORE);
  }

  ~PPContext()
  {
    delete diagClient;
    delete target;
  }

};

#endif
