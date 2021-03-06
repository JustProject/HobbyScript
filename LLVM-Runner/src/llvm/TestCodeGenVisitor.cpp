//
// Created by 刘丰恺 on 2018/8/3.
//

#include "unitcpp/UnitTest++.h"
#include "json.hpp"
#include "../visitor/AstVisitor.h"
#include "LLVMCodeGenVisitor.h"
using json = nlohmann::json;

SUITE (TestCodeGen) {
    static Pointer<AstNode> toAst(const json &inputJson) {
        AstVisitor visitor(inputJson);
        return visitor.visit();
    }

    TEST (NumberGenTest1) {
        json input = json::parse(R"({"token":{"value":1,"lineNumber":1,"tag":270},"tag":270,"type":"NumberLiteral"})");
        auto root = toAst(input);
        auto number = std::static_pointer_cast<NumberLiteral>(root);
        LLVMCodeGenVisitor visitor(root);
        auto result = visitor.visit_number(root);
        auto result_float = (ConstantFP *) result;
        UNITTEST_CHECK(result);
        UNITTEST_CHECK(result_float);
        UNITTEST_CHECK_EQUAL(1, result_float->getValueAPF().convertToDouble());
    }

    TEST (BinaryGenTest1) {
        json input = json::parse(R"({"afterPoint":0,"children":[{"token":{"value":1,"lineNumber":1,"tag":270},"tag":270,"type":"NumberLiteral"},{"token":{"text":"+","lineNumber":1,"tag":264},"tag":264,"type":"AstLeaf"},{"token":{"value":1111,"lineNumber":1,"tag":270},"tag":270,"type":"NumberLiteral"}],"tag":279,"type":"BinaryExpr"}
)");
        auto root = toAst(input);
        auto binary_expr = std::static_pointer_cast<BinaryExpr>(root);
        LLVMCodeGenVisitor visitor(root);
        auto result = visitor.visit();
        UNITTEST_CHECK(result);

        if (auto *FnIR = result) {
            fprintf(stderr, "Read top-level expression:");
            FnIR->print(llvm::errs());
            fprintf(stderr, "\n");
        }

        auto result_float = (ConstantFP *) result;
        UNITTEST_CHECK(result_float);
        UNITTEST_CHECK_EQUAL(1112, result_float->getValueAPF().convertToDouble());
    }
}


