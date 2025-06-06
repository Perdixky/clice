#pragma once

#include "Support/Enum.h"

namespace clice {

struct RelationKind : refl::Enum<RelationKind, true, uint32_t> {
    enum Kind : uint32_t {
        Invalid,
        Declaration,
        Definition,
        Reference,
        WeakReference,
        // Write Relation.
        Read,
        Write,
        Interface,
        Implementation,
        /// When target is a type definition of source, source is possible type or constructor.
        TypeDefinition,

        /// When target is a base class of source.
        Base,
        /// When target is a derived class of source.
        Derived,

        /// When target is a constructor of source.
        Constructor,
        /// When target is a destructor of source.
        Destructor,

        // When target is a caller of source.
        Caller,
        // When target is a callee of source.
        Callee,
    };

    using Enum::Enum;

    constexpr bool isDeclOrDef() {
        return is_one_of(Declaration, Definition);
    }

    constexpr bool isReference() {
        return is_one_of(Reference, WeakReference);
    }

    constexpr bool isBetweenSymbol() {
        return is_one_of(Interface,
                         Implementation,
                         TypeDefinition,
                         Base,
                         Derived,
                         Constructor,
                         Destructor);
    }

    constexpr bool isCall() {
        return is_one_of(Caller, Callee);
    }
};

}  // namespace clice
