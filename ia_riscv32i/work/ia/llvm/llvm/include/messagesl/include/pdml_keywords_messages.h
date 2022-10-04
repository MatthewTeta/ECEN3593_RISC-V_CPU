#ifndef ERR_PDML_KEYWORDS_H_
#define ERR_PDML_KEYWORDS_H_

#include "formatl/format_number.h"
#include "common/codasip_integer.h"
#include "utility/enumutils.h"
#include "utility/location.h"
#include "pdml_keywords_enum.h"

namespace codasip {
namespace pdml {

const std::string SUBSTITUTES = "substitutes";
const std::string VARIABLES = "variables";
const std::string ELEMENT = "element";
const std::string SET = "set";
const std::string SCENARIO = "scenario";
const std::string ADDRESS_SPACE = "address_space";
const std::string PROGRAM = "program";
const std::string START = "start";
const std::string REGISTER_INIT = "register_init";
const std::string INSTRUCTIONS = "instructions";
const std::string SCENARIOS = "scenarios";
const std::string END = "end";
const std::string ASSEMBLY = "assembly";
const std::string ASSEMBLER = "assembler";
const std::string CONSTRAINTS = "constraints";
const std::string VARIANTS = "variants";
const std::string DIFFERENT = "different";
const std::string DIVISIBLE = "divisible";
const std::string GENERATE_AFTER = "generate_after";
const std::string ILLEGAL = "illegal";
const std::string LABEL = "label";
const std::string LATENCY = "latency";
const std::string MAX_DEPTH = "max_depth";
const std::string MAX_OFFSET = "max_offset";
const std::string PREFIX = "prefix";
const std::string SIZE = "size";
const std::string WEIGHTS = "weights";
const std::string LOAD_RANGE = "load_range";
const std::string STORE_RANGE = "store_range";
const std::string ALIGNMENT = "alignment";
const std::string DEFAULT = "default";
const std::string MIN = "min";
const std::string MAX = "max";

}   // namespace pdml
}   // namespace codasip

#endif // ERR_PDML_KEYWORDS_H_
