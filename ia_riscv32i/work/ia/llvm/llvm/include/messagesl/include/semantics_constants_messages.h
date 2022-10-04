#ifndef ERR_SEMANTICS_CONSTANTS_H_
#define ERR_SEMANTICS_CONSTANTS_H_

#include "formatl/format_number.h"
#include "common/codasip_integer.h"
#include "utility/enumutils.h"
#include "utility/location.h"
#include "semantics_constants_enum.h"

namespace codasip {
namespace semantics {

CODASIP_ENUM_CLASS_STR_DEFAULT(Alias, ALIAS_UNDEF,
    (ALIAS_UNDEF = 0, "UNDEF"),
    (ALIAS_ASSEMBLER = 1, "ASSEMBLER"),
    (ALIAS_COMPILER = 2, "COMPILER"));

CODASIP_ENUM_CLASS_STR_DEFAULT(InterruptReturn, INTERRUPT_RETURN_UNDEF,
    (INTERRUPT_RETURN_UNDEF = 0, "UNDEF"),
    (INTERRUPT_RETURN_MACHINE = 1, "MACHINE"),
    (INTERRUPT_RETURN_USER = 2, "USER"),
    (INTERRUPT_RETURN_SUPERVISOR = 3, "SUPERVISOR"));

CODASIP_ENUM_CLASS_STR_DEFAULT(Validity, VALIDITY_UNDEF,
    (VALIDITY_UNDEF = 0, "UNDEF"),
    (VALIDITY_OK = 1, "OK"),
    (VALIDITY_COMPILER_UNUSED = 2, "COMPILER_UNUSED"),
    (VALIDITY_UNDEFINED = 3, "UNDEFINED"),
    (VALIDITY_EXTRACTOR_REMOVED = 4, "EXTRACTOR_REMOVED"));

CODASIP_ENUM_CLASS_STR_DEFAULT(VliwType, VLIW_TYPE_UNDEF,
    (VLIW_TYPE_UNDEF = 0, "UNDEF"),
    (VLIW_TYPE_PARALLEL = 1, "PARALLEL"),
    (VLIW_TYPE_SEQUENTIAL = 2, "SEQUENTIAL"));

}   // namespace semantics
}   // namespace codasip

#endif // ERR_SEMANTICS_CONSTANTS_H_
