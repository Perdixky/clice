#pragma once

#include <cstdint>
#include <limits>
#include <compare>
#include <vector>
#include <string>

namespace clang {
class Sema;
}

namespace clice::index {

/// Used to discribe the kind of relation between two symbols.
enum class RelationKind : uint32_t {
    Invalid,
    Declaration,
    Definition,
    Reference,
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

    /// When target is a partial specialization of source.
    PartialSpecialization,
    /// When target is a full specialization of source.
    FullSpecialization,
    /// When target is an explicit instantiation of source.
    ImplicitInstantiation,

    // When target is a caller of source.
    Caller,
    // When target is a callee of source.
    Callee,
};

inline RelationKind operator| (RelationKind lhs, RelationKind rhs) {
    return static_cast<RelationKind>(static_cast<uint32_t>(lhs) | static_cast<uint32_t>(rhs));
}

inline RelationKind operator& (RelationKind lhs, RelationKind rhs) {
    return static_cast<RelationKind>(static_cast<uint32_t>(lhs) & static_cast<uint32_t>(rhs));
}

inline RelationKind& operator|= (RelationKind& lhs, RelationKind rhs) {
    lhs = lhs | rhs;
    return lhs;
}

inline RelationKind& operator&= (RelationKind& lhs, RelationKind rhs) {
    lhs = lhs & rhs;
    return lhs;
}

/// Represent a position in the source code, the line and column are 1-based.
struct Position {
    /// The line of the position.
    uint32_t line = 0;
    /// The column of the position.
    uint32_t column = 0;

    friend std::strong_ordering operator<=> (const Position&, const Position&) = default;
};

struct Location {
    /// Begin position of the location.
    Position begin = {};
    /// End position of the location.
    Position end = {};
    /// The index of the file in the `Index::files`.
    /// When the value of file is equal to MAX_UINT32, it means the location is invalid.
    uint32_t file = std::numeric_limits<uint32_t>::max();

    bool isValid() const {
        return file != std::numeric_limits<uint32_t>::max();
    }

    explicit operator bool () const {
        return isValid();
    }

    friend std::strong_ordering operator<=> (const Location&, const Location&) = default;
};

/// This defines the structures that directly generated by the indexer.
/// It could be used to serialized to other formats like binary or JSON.
namespace memory {

template <typename T>
using Value = T;

template <typename T>
using Array = std::vector<T>;

using String = std::string;

#define MAKE_CLANGD_HAPPY
#include "Index.h"

}  // namespace memory

/// index the given translation unit.
memory::Index index(clang::Sema& sema);

}  // namespace clice::index
