#include "AST/Directive.h"
#include <Support/Reflection.h>
namespace clice {

struct CommentHandler : public clang::CommentHandler {
    Directive& directive;

    CommentHandler(Directive& directive) : directive(directive) {}

    virtual bool HandleComment(clang::Preprocessor& preproc, clang::SourceRange Comment) {
        // directive.comments.push_back(Comment);
        return false;
    }
};

struct PPCallback : clang::PPCallbacks {
    PPCallback(Directive& directive) : directive(directive) {}

    Directive& directive;

    void FileChanged(clang::SourceLocation loc,
                     clang::PPCallbacks::FileChangeReason reason,
                     clang::SrcMgr::CharacteristicKind fileType,
                     clang::FileID id) override {
        llvm::outs() << "FileChanged, reason: " << enum_name(reason) << "\n";
        loc.dump(directive.sourceManager);
    }

    void InclusionDirective(clang::SourceLocation HashLoc,
                            const clang::Token& IncludeTok,
                            llvm::StringRef FileName,
                            bool IsAngled,
                            clang::CharSourceRange FilenameRange,
                            clang::OptionalFileEntryRef File,
                            clang::StringRef SearchPath,
                            llvm::StringRef RelativePath,
                            const clang::Module* SuggestedModule,
                            bool ModuleImported,
                            clang::SrcMgr::CharacteristicKind FileType) override {
        // TODO: record all include files
        llvm::SmallVector<char> RealPath;
        // fs::make_absolute(SearchPath + "/" + RelativePath, RealPath);
        // path::remove_dots(RealPath, /*remove_dot_dot=*/true);
        // llvm::outs() << RealPath << "\n";
    }

    void PragmaDirective(clang::SourceLocation Loc, clang::PragmaIntroducerKind Introducer) override {
        // llvm::outs() << "PragmaDirective\n";
    }

    void If(clang::SourceLocation Loc,
            clang::SourceRange ConditionRange,
            clang::PPCallbacks::ConditionValueKind ConditionValue) override {
        // llvm::outs() << "If\n";
    }

    void Elif(clang::SourceLocation loc,
              clang::SourceRange conditionRange,
              clang::PPCallbacks::ConditionValueKind conditionValue,
              clang::SourceLocation ifLoc) override {}

    void Ifdef(clang::SourceLocation loc, const clang::Token& name, const clang::MacroDefinition& definition) override {
    }

    void Elifdef(clang::SourceLocation loc,
                 const clang::Token& name,
                 const clang::MacroDefinition& definition) override {}

    void Elifdef(clang::SourceLocation loc, clang::SourceRange conditionRange, clang::SourceLocation ifLoc) override {}

    void Ifndef(clang::SourceLocation loc,
                const clang::Token& name,
                const clang::MacroDefinition& definition) override {}

    // invoke when #elifndef is taken
    void Elifndef(clang::SourceLocation loc,
                  const clang::Token& name,
                  const clang::MacroDefinition& definition) override {}

    // invoke when #elifndef is skipped
    void Elifndef(clang::SourceLocation loc, clang::SourceRange conditionRange, clang::SourceLocation ifLoc) override {}

    void Else(clang::SourceLocation loc, clang::SourceLocation ifLoc) override {}

    void Endif(clang::SourceLocation loc, clang::SourceLocation ifLoc) override {}

    void MacroDefined(const clang::Token& MacroNameTok, const clang::MacroDirective* MD) override {}
};

clang::CommentHandler* Directive::handler() { return new CommentHandler(*this); }

std::unique_ptr<clang::PPCallbacks> Directive::callback() { return std::make_unique<PPCallback>(*this); }

}  // namespace clice
