#pragma once

#include <stdbool.h>
#include <stdio.h>

/// @brief Tree that represents arithmetic expression
typedef struct ExpressionTree ExpressionTree;

/// @brief Reads expression tree from stream in format (`operator` `argumentA` `argumentB`),
/// where `operator` is eiter `+`, `-`, `*` or `/` and both `argumentA` and `argumentB` are
/// expressions or integer numbers
/// @param tree `ExpressionTree` pointer to write result into
/// @param stream Stream to read expression tree from
/// @return `true` if read successfully, `false` otherwise (allocation failed or incorrect format)
bool readExpressionTree(ExpressionTree **tree, FILE *stream);

/// @brief Prints tree in tree form:
///
/// `(operator)`
///
/// ` |-[argumentA]`
///
/// ` |-[argumentB]`
/// @param tree Tree to print
/// @param stream Stream to print tree to
void printAsTree(ExpressionTree *tree, FILE *stream);

/// @brief Prints tree in expression form:
///
/// `(argumentA operator argumentB)`
/// @param tree Tree to print
/// @param stream Stream to print tree to
void printAsExpression(ExpressionTree *tree, FILE *stream);

/// @brief Evaluates expression represented by tree
/// @param tree Tree to evaluate
/// @return Evaluated value
int evaluateExpressionTree(ExpressionTree *tree);

/// @brief Disposes tree
/// @param tree Tree to dispose
void disposeTree(ExpressionTree *tree);
