#ifndef ERR_SEMANTICS_KEYWORDS_H_
#define ERR_SEMANTICS_KEYWORDS_H_

#include "formatl/format_number.h"
#include "common/codasip_integer.h"
#include "utility/enumutils.h"
#include "utility/location.h"
#include "semantics_keywords_enum.h"

namespace codasip {
namespace semantics {

const std::string VERSION = "version";
const std::string DESIGN_PATH = "design_path";
const std::string PREPROCESSOR_DEFINE = "preprocessor_define";
const std::string VLIW_INFO = "vliw_info";
const std::string TYPE = "type";
const std::string PREFIX = "prefix";
const std::string SUFFIX = "suffix";
const std::string REGISTER_CLASS = "register_class";
const std::string BITS = "bits";
const std::string OVERLAP = "overlap";
const std::string PHYSICAL = "physical";
const std::string REGISTERS = "registers";
const std::string SET = "set";
const std::string INSTRUCTION = "instruction";
const std::string SUBINSTRUCTION = "subinstruction";
const std::string EMULATION = "emulation";
const std::string PEEPHOLE = "peephole";
const std::string INSTRUCTIONS = "instructions";
const std::string PATTERN = "pattern";
const std::string REPLACE = "replace";
const std::string MAPPING = "mapping";
const std::string OPERANDS = "operands";
const std::string ASSEMBLY = "assembly";
const std::string ASSEMBLER = "assembler";
const std::string BINARY = "binary";
const std::string BIT = "bit";
const std::string SEMANTICS = "semantics";
const std::string IMMOP = "immop";
const std::string REGOP = "regop";
const std::string REG = "reg";
const std::string CTLZ = "ctlz";
const std::string CTTZ = "cttz";
const std::string CTPOP = "ctpop";
const std::string BSWAP = "bswap";
const std::string BITREVERSE = "bitreverse";
const std::string FABS = "fabs";
const std::string FCEIL = "fceil";
const std::string FCOS = "fcos";
const std::string FEXP = "fexp";
const std::string FFLOOR = "ffloor";
const std::string FLOG = "flog";
const std::string FNEG = "fneg";
const std::string FRINT = "frint";
const std::string FROUND = "fround";
const std::string FSIN = "fsin";
const std::string FSQRT = "fsqrt";
const std::string FTRUNC = "ftrunc";
const std::string ADD = "add";
const std::string SUB = "sub";
const std::string MUL = "mul";
const std::string SDIV = "sdiv";
const std::string UDIV = "udiv";
const std::string SREM = "srem";
const std::string UREM = "urem";
const std::string AND = "and";
const std::string OR = "or";
const std::string XOR = "xor";
const std::string SHL = "shl";
const std::string SRL = "srl";
const std::string SRA = "sra";
const std::string ROTL = "rotl";
const std::string ROTR = "rotr";
const std::string CARRY_ADD = "carry_add";
const std::string CARRY_SUB = "carry_sub";
const std::string OVERFLOW_ADD = "overflow_add";
const std::string OVERFLOW_SUB = "overflow_sub";
const std::string FADD = "fadd";
const std::string FSUB = "fsub";
const std::string FMUL = "fmul";
const std::string FDIV = "fdiv";
const std::string FREM = "frem";
const std::string FPOW = "fpow";
const std::string FPOWI = "fpowi";
const std::string CONCAT_VECTORS = "concat_vectors";
const std::string EXTRACT_SUBVECTOR = "extract_subvector";
const std::string EXTRACT_VECTOR_ELT = "extract_vector_elt";
const std::string FP_TO_FX = "fp_to_fx";
const std::string FX_TO_FP = "fx_to_fp";
const std::string FX_TO_INT = "fx_to_int";
const std::string INT_TO_FX = "int_to_fx";
const std::string SELECT = "select";
const std::string CARRY_ADDC = "carry_addc";
const std::string CARRY_SUBC = "carry_subc";
const std::string OVERFLOW_ADDC = "overflow_addc";
const std::string OVERFLOW_SUBC = "overflow_subc";
const std::string FMA = "fma";
const std::string INSERT_VECTOR_ELT = "insert_vector_elt";
const std::string SHUFFLE = "shuffle";
const std::string VSELECT = "vselect";
const std::string FX_DIV = "fx_div";
const std::string FX_MUL = "fx_mul";
const std::string ZERO_EXTEND = "zero_extend";
const std::string SIGN_EXTEND = "sign_extend";
const std::string ANY_EXTEND = "any_extend";
const std::string TRUNCATE = "truncate";
const std::string BITCAST = "bitcast";
const std::string SINT_TO_FP = "sint_to_fp";
const std::string UINT_TO_FP = "uint_to_fp";
const std::string FP_TO_SINT = "fp_to_sint";
const std::string FP_TO_UINT = "fp_to_uint";
const std::string FP_EXTEND = "fp_extend";
const std::string FP_ROUND = "fp_round";
const std::string SETOEQ = "setoeq";
const std::string SETOGT = "setogt";
const std::string SETOGE = "setoge";
const std::string SETOLT = "setolt";
const std::string SETOLE = "setole";
const std::string SETONE = "setone";
const std::string SETO = "seto";
const std::string SETUO = "setuo";
const std::string SETUEQ = "setueq";
const std::string SETUGT = "setugt";
const std::string SETUGE = "setuge";
const std::string SETULT = "setult";
const std::string SETULE = "setule";
const std::string SETUNE = "setune";
const std::string SETEQ = "seteq";
const std::string SETGT = "setgt";
const std::string SETGE = "setge";
const std::string SETLT = "setlt";
const std::string SETLE = "setle";
const std::string SETNE = "setne";
const std::string FLAG_COMPARE = "flag_compare";
const std::string BUILD_VECTOR = "BUILD_VECTOR";
const std::string GET_PC = "get_pc";
const std::string HALT = "halt";
const std::string HAS_SIDE_EFFECTS = "has_side_effects";
const std::string HW_LOOP = "hw_loop";
const std::string JUMP = "jump";
const std::string LOAD = "load";
const std::string NATURAL_SHUFFLE = "natural_shuffle";
const std::string NOP = "nop";
const std::string PREDICATE_FALSE = "predicate_false";
const std::string PREDICATE_TRUE = "predicate_true";
const std::string RET = "ret";
const std::string SIGN_EXTEND_INREG = "sign_extend_inreg";
const std::string STORE = "store";
const std::string SYSCALL = "syscall";
const std::string UNDEF = "undef";
const std::string ALIAS = "alias";
const std::string SUBTARGETS = "subtargets";
const std::string BUILTIN = "builtin";
const std::string INTERRUPT_RETURN = "interrupt_return";
const std::string VALIDITY = "validity";
const std::string PRIORITY = "priority";
const std::string COMMENT = "comment";
const std::string ELEMENT_TREE = "element_tree";
const std::string SCHEDULE_CLASS = "schedule_class";
const std::string SLOTS = "slots";
const std::string TRUE = "true";
const std::string FALSE = "false";

}   // namespace semantics
}   // namespace codasip

#endif // ERR_SEMANTICS_KEYWORDS_H_
