#include "Compiler/Compilation.h"
#include "Feature/SignatureHelp.h"

namespace clice::feature {

namespace {

class SignatureHelpCollector final : public clang::CodeCompleteConsumer {
public:
    SignatureHelpCollector(clang::CodeCompleteOptions options) :
        clang::CodeCompleteConsumer(options), allocator(new clang::GlobalCodeCompletionAllocator()),
        info(allocator) {}

    void ProcessOverloadCandidates(clang::Sema& sema,
                                   unsigned CurrentArg,
                                   OverloadCandidate* candidates,
                                   unsigned count,
                                   clang::SourceLocation openParLoc,
                                   bool braced) final {
        llvm::outs() << "ProcessOverloadCandidates\n";
        auto range = llvm::make_range(candidates, candidates + count);
        for(auto& candidate: range) {
            switch(candidate.getKind()) {
                case clang::CodeCompleteConsumer::OverloadCandidate::CK_Function: {
                    break;
                }
                case clang::CodeCompleteConsumer::OverloadCandidate::CK_FunctionTemplate: {
                    break;
                }
                case clang::CodeCompleteConsumer::OverloadCandidate::CK_FunctionType: {
                    break;
                }
                case clang::CodeCompleteConsumer::OverloadCandidate::CK_FunctionProtoTypeLoc: {
                    break;
                }
                case clang::CodeCompleteConsumer::OverloadCandidate::CK_Template: {
                    break;
                }
                case clang::CodeCompleteConsumer::OverloadCandidate::CK_Aggregate: {
                    break;
                }
            }
        }
    }

    clang::CodeCompletionAllocator& getAllocator() final {
        return *allocator;
    }

    clang::CodeCompletionTUInfo& getCodeCompletionTUInfo() final {
        return info;
    }

private:
    std::shared_ptr<clang::GlobalCodeCompletionAllocator> allocator;
    clang::CodeCompletionTUInfo info;
};

}  // namespace

std::vector<SignatureHelpItem> signatureHelp(CompilationParams& params,
                                             const config::SignatureHelpOption& option) {
    // std::vector<SignatureHelpItem> completions;
    // auto consumer = new SignatureHelpCollector({});
    //
    // if(auto info = compile(params, consumer)) {
    //    for(auto& item: completions) {}
    //    return completions;
    //} else {
    //    std::abort();
    //}
    return std::vector<SignatureHelpItem>{};
}

}  // namespace clice::feature

