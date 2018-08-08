//
// Created by 刘丰恺 on 2018/8/1.
//

#include "AstVisitor.h"

AstVisitor::AstVisitor(const json &load) {
    this->load_json = load;
}

AstVisitor::~AstVisitor() {
    this->load_json.clear();
}

const json &AstVisitor::get_json() {
    return load_json;
}

Pointer<AstNode> AstVisitor::visit_ast_node(const json &node) {
    return nullptr;
}

Pointer<AstNode> AstVisitor::visit_ast_leaf(const json &node) {
    return Pointer<AstLeaf>(new AstLeaf(node));
}

Pointer<AstNode> AstVisitor::visit_binary_expr(const json &node) {
    std::vector<json> children = node["children"];
    auto left = visit(children[0]);
    auto op = visit(children[1]);
    auto right = visit(children[2]);
    Pointer<AstNodeList> pointer(new AstNodeList({left, op, right}));
    return Pointer<BinaryExpr>(new BinaryExpr(node, pointer));
}

Pointer<AstNode> AstVisitor::visit_ast_list(const json &node) {
    jsonVector children = node["children"];
    Pointer<AstNodeList> children_list(new AstNodeList());
    std::for_each(children.begin(), children.end(), [this, children_list](auto child_json) {
        Pointer<AstNode> child = visit(child_json);
        children_list->push_back(child);
    });

    return Pointer<AstList>(new AstList(node, children_list));
}

Pointer<AstNode> AstVisitor::visit_number(const json &node) {
    return Pointer<NumberLiteral>(new NumberLiteral(node));
}

Pointer<AstNode> AstVisitor::visit(const json &load_json) {
    int tag = load_json["tag"];
    Pointer<AstNode> result;
    switch (tag) {
        case BINARY_EXPR: {
            result = visit_binary_expr(load_json);
            break;
        }

        case NUMBER_LITERAL: {
            result = visit_number(load_json);
            break;
        }

        case AST_LEAF: {
            result = visit_ast_leaf(load_json);
            break;
        }

        case AST_LIST: {
            result = visit_ast_list(load_json);
            break;
        }

        default: {
            break;
        }
    }

//    std::cout << result->get_json().dump(4) << std::endl;
    return result;
}

Pointer<AstNode> AstVisitor::visit() {
    return visit(this->load_json);
}

