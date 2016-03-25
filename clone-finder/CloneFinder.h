#ifndef STANDALONE_CLONEFINDER_H
#define STANDALONE_CLONEFINDER_H


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

using namespace clang;
using namespace clang::vfs;
using namespace clang::tooling;
using namespace llvm;


class FindNamedClassVisitor
        : public RecursiveASTVisitor<FindNamedClassVisitor> {
    
public:
    explicit FindNamedClassVisitor(ASTContext *Context)
            : Context(Context) {}

    bool VisitStmt(Stmt *S) {
        FoldingSetNodeID id;
        S->Profile(id, *Context, false);
        unsigned hash = id.ComputeHash();

        if (hashes.find(hash) == hashes.end()) {
            hashes[hash] = S;
        } else {
            std::cerr << "\n\n\n\n\n############################\nFound clone:" << std::endl;
            hashes[hash]->getLocStart().dump(Context->getSourceManager());
            std::cerr << std::endl;
            hashes[hash]->dump();
            std::cerr << "\n############################" << std::endl;
            S->getLocStart().dump(Context->getSourceManager());
            std::cerr << std::endl;
            S->dump();
            std::cerr << "\n############################" << std::endl;
        }

        return true;
    }

private:
    ASTContext *Context;
    std::map<unsigned, Stmt*> hashes;
};


class CloneFinder {

public:
    void searchAST(std::vector<ASTUnit*>& asts) {
        for (ASTUnit* ast : asts) {
            FindNamedClassVisitor visitor(&ast->getASTContext());
            visitor.TraverseTranslationUnitDecl(ast->getASTContext().getTranslationUnitDecl());
        }
    }
};


#endif //STANDALONE_CLONEFINDER_H
