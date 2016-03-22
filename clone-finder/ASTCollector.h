#ifndef STANDALONE_ASTCOLLECTOR_H
#define STANDALONE_ASTCOLLECTOR_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "clang/AST/ASTConsumer.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/FrontendAction.h"
#include "clang/Tooling/Tooling.h"
#include "clang/Driver/Compilation.h"
#include "clang/Driver/Driver.h"
#include "clang/Driver/Tool.h"
#include "clang/Driver/ToolChain.h"
#include "clang/Frontend/ASTUnit.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/FrontendDiagnostic.h"
#include "clang/Frontend/TextDiagnosticPrinter.h"
#include "clang/Tooling/ArgumentsAdjusters.h"
#include "clang/Tooling/CompilationDatabase.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/Config/llvm-config.h"
#include "llvm/Option/Option.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/Host.h"
#include "llvm/Support/raw_ostream.h"
#include "clang/Serialization/ASTWriter.h"
#include "clang/Serialization/ASTReader.h"

#include "InterProcessArgs.h"
#include "CCXXEnvOverwriter.h"

using namespace clang;
using namespace clang::vfs;
using namespace clang::tooling;
using namespace llvm;


std::map<unsigned, Stmt*> hashes;

class FindNamedClassVisitor
        : public RecursiveASTVisitor<FindNamedClassVisitor> {
public:
    explicit FindNamedClassVisitor(ASTContext *Context)
            : Context(Context) {}

    bool VisitCXXRecordDecl(CXXRecordDecl *Declaration) {
        if (Declaration->getQualifiedNameAsString() == "n") {
            FullSourceLoc FullLocation = Context->getFullLoc(Declaration->getLocStart());
            if (FullLocation.isValid())
                llvm::outs() << "Found declaration at "
                << FullLocation.getSpellingLineNumber() << ":"
                << FullLocation.getSpellingColumnNumber() << "\n";


        }
        return true;
    }

    bool VisitStmt(Stmt *S) {
        S->dump();
        FoldingSetNodeID id;
        S->Profile(id, *Context, false);
        unsigned hash = id.ComputeHash();

        if (hashes.find(hash) == hashes.end()) {
            hashes[hash] = S;
        } else {
            std::cerr << "\n\n\n\n\n############################\nFound clone:" << std::endl;
            hashes[hash]->dump();
            std::cerr << "############################" << std::endl;
            S->dump();
            std::cerr << "############################" << std::endl;
        }

        return true;
    }

private:
    ASTContext *Context;
};

std::string getFileContents(const char *filename)
{
    std::ifstream in(filename, std::ios::in | std::ios::binary);
    if (in)
    {
        return(std::string((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>()));
    }
    throw std::domain_error("Couldn't find file " + std::string(filename));
}

class ASTCollector {

    struct LoadedAST {

    };

public:

    void loadAst(std::vector<std::string>& args) {

    }

};


#endif //STANDALONE_ASTCOLLECTOR_H
