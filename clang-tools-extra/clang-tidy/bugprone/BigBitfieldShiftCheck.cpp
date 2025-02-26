//===--- BigBitfieldShiftCheck.cpp - clang-tidy ---------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "BigBitfieldShiftCheck.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang::tidy::bugprone {

void BigBitfieldShiftCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(
    binaryOperator(
      hasOperatorName("<<"),
      hasLHS(
        implicitCastExpr(
          hasSourceExpression(
            memberExpr(
              hasDeclaration(
                fieldDecl(
                  anyOf(
                    hasBitWidth(33),
                    hasBitWidth(34),
                    hasBitWidth(35),
                    hasBitWidth(36),
                    hasBitWidth(37),
                    hasBitWidth(38),
                    hasBitWidth(39),
                    hasBitWidth(40),
                    hasBitWidth(41),
                    hasBitWidth(42),
                    hasBitWidth(43),
                    hasBitWidth(44),
                    hasBitWidth(45),
                    hasBitWidth(46),
                    hasBitWidth(47),
                    hasBitWidth(48),
                    hasBitWidth(49),
                    hasBitWidth(50),
                    hasBitWidth(51),
                    hasBitWidth(52),
                    hasBitWidth(53),
                    hasBitWidth(54),
                    hasBitWidth(55),
                    hasBitWidth(56),
                    hasBitWidth(57),
                    hasBitWidth(58),
                    hasBitWidth(59),
                    hasBitWidth(60),
                    hasBitWidth(61),
                    hasBitWidth(62),
                    hasBitWidth(63)
                  )
                ).bind("bitfield")
              )
            )
          )
        )
      )
    ).bind("shift"),
    this);
}

void BigBitfieldShiftCheck::check(const MatchFinder::MatchResult &Result) {
  const auto *ShiftOp = Result.Nodes.getNodeAs<BinaryOperator>("shift");
  const auto *Field = Result.Nodes.getNodeAs<FieldDecl>("bitfield");

  if (!ShiftOp || !Field)
    return;

  diag(ShiftOp->getOperatorLoc(),
    "left-shift operator applied to bitfield %0 with bit width > 32")
    << Field->getName();
}

} // namespace clang::tidy::bugprone
