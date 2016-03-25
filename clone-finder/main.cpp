// Declares clang::SyntaxOnlyAction.
#include <iostream>
#include <fstream>
#include <sstream>
#include "clang/Frontend/FrontendActions.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
// Declares llvm::cl::extrahelp.
#include "llvm/Support/CommandLine.h"
#include "CloneFinder.h"

using namespace clang::tooling;
using namespace llvm;

// Apply a custom category to all command-line options so that they are the
// only ones displayed.
static cl::OptionCategory MyToolCategory("clang-clone-finder options");

std::string getFileContents(const std::string& path) {
    std::ifstream inputStream(path);
    std::stringstream buffer;
    buffer << inputStream.rdbuf();
    return buffer.str();
}

bool hasEnding (std::string const &fullString, std::string const &ending) {
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}

int main(int argc, const char **argv) {
    CommonOptionsParser OptionsParser(argc, argv, MyToolCategory);

    std::vector<clang::ASTUnit*> asts;

    for (CompileCommand s : OptionsParser.getCompilations().getAllCompileCommands()) {

        std::string filename;

        std::string allArgs = "";

        for (std::string arg : s.CommandLine) {
            if (hasEnding(arg, ".cpp") || hasEnding(arg, ".cc") || hasEnding(arg, ".c") || hasEnding(arg, ".cxx")) {
                filename = arg;
            }
        }

        s.CommandLine.erase(std::find(s.CommandLine.begin(), s.CommandLine.end(), filename));

        std::string code = getFileContents(filename);

        auto ast = clang::tooling::buildASTFromCodeWithArgs(code, s.CommandLine, filename);

        assert(ast.get());
        asts.push_back(ast.release());
    }

    CloneFinder cloneFinder;
    cloneFinder.searchAST(asts);

    /*clang::tooling::buildASTFromCodeWithArgs();

    ClangTool Tool(OptionsParser.getCompilations(),
                   OptionsParser.getSourcePathList());
    return Tool.run(newFrontendActionFactory<clang::SyntaxOnlyAction>().get()); */
}