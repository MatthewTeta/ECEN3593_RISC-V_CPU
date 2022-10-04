#ifndef ERR_CODAL_KEYWORDS_H_
#define ERR_CODAL_KEYWORDS_H_

#include "formatl/format_number.h"
#include "common/codasip_integer.h"
#include "utility/enumutils.h"
#include "utility/location.h"
#include "codal_keywords_enum.h"
#include "messagesl/include/codal_constants_messages.h" // generate_imports_package

namespace codasip {
namespace codal {

const std::string LLVM_CLASS = "llvm_class";
const std::string CLASS_LATENCY = "latency";
const std::string DELAY_SLOT = "delay_slot";
const std::string BITS = "bits";
const std::string SIZE = "size";
const std::string FLAG = "flag";
const std::string ENDIANNESS = "endianness";
const std::string INTERFACES = "interfaces";
const std::string INTERFACE = "interface";
const std::string PORT = "port";
const std::string TYPE = "type";
const std::string ASSEMBLY = "assembly";
const std::string ASSEMBLER = "assembler";
const std::string BINARY = "binary";
const std::string TIMING = "timing";
const std::string DECODERS = "decoders";
const std::string RETURN = "return";
const std::string INSTRUCTIONS = "instructions";
const std::string PATTERN = "pattern";
const std::string REPLACE = "replace";
const std::string INLINE = "inline";
const std::string VOID = "void";
const std::string BREAK = "break";
const std::string CONTINUE = "continue";
const std::string CASE = "case";
const std::string SWITCH = "switch";
const std::string IF = "if";
const std::string ENUM = "enum";
const std::string SEMANTICS = "semantics";
const std::string USE = "use";
const std::string PIPELINE = "pipeline";
const std::string OVERLAP = "overlap";
const std::string DFF = "dff";
const std::string DATAPORT = "dataport";
const std::string MAIN = "main";
const std::string RESET = "reset";
const std::string LATENCY = "latency";
const std::string CODAL_UNALIGNED = "unaligned";
const std::string ARBITER = "arbiter";
const std::string DECODER = "decoder";
const std::string IA = "ia";
const std::string CA = "ca";
const std::string LINE_SIZE = "line_size";
const std::string NUM_WAYS = "num_ways";
const std::string RPL_POLICY = "rpl_policy";
const std::string WRITE_ALLOCATE = "write_allocate";
const std::string WRITE_BACK = "write_back";
const std::string NON_CACHEABLE = "non_cacheable";
const std::string DIRECTION = "direction";
const std::string OPEN = "open";
const std::string CURRENT_ADDRESS = "current_address";
const std::string BUS = "bus";
const std::string CACHE = "cache";
const std::string COMPONENT = "component";
const std::string DEFAULT = "default";
const std::string WRITE_MASK = "write_mask";
const std::string SCHEDULE_CLASS = "schedule_class";
const std::string SET = "set";
const std::string EVENT = "event";
const std::string ELEMENT = "element";
const std::string ATTRIBUTE = "attribute";
const std::string EMULATION = "emulation";
const std::string PEEPHOLE = "peephole";
const std::string SIGNAL = "signal";
const std::string START = "start";
const std::string ROOTS = "roots";
const std::string CONNECT = "connect";
const std::string ADDRESS_SPACE = "address_space";
const std::string ALIAS = "alias";
const std::string ASSEMBLE_CONFIGURATION = "assembler_configuration";
const std::string REGISTER = "register";
const std::string REGISTER_FILE = "register_file";
const std::string MEMORY = "memory";
const std::string EXTERN = "extern";
const std::string CUSTOM_SCHEDULE = "custom_schedule";
const std::string PROPERTIES_INSTRUCTION = "instruction";
const std::string PROPERTIES_INSTRUCTION_SLOT = "SLOT";
const std::string PROPERTIES_INSTRUCTION_SEQUENCE = "SEQUENCE";
const std::string PROPERTIES_PROFILER = "profiler";
const std::string PROPERTIES_REGISTER_OPERAND = "register_operand";
const std::string PROPERTIES_REGISTER_CLASS = "register_class";
const std::string PROPERTIES_PIPELINE = "pipeline";
const std::string PROPERTIES_SYNTHESIS = "synthesis";
const std::string PROPERTIES_ASSEMBLER_ALIAS = "assembler_alias";
const std::string PROPERTIES_COMPILER_ALIAS = "compiler_alias";
const std::string PROPERTIES_IGNORE = "ignore";
const std::string PROPERTIES_OPERAND = "operand";
const std::string PRIORITY = "priority";
const std::string SETTINGS = "settings";
const std::string REL_JUMP_CONST = "rel_jump_const";
const std::string COMMENT_PREFIX = "comment_prefix";
const std::string CODE_SECTION_BYTE_ALIGNMENT = "section_byte_alignment";
const std::string LE_INSTRUCTION_PARCEL_BYTES = "le_instruction_parcel_bytes";
const std::string SYMBOL_PREFIX = "symbol_prefix";
const std::string ALIGN_BEHAVIOR = "align_behavior";
const std::string NEW_LINE_DELIMITER = "new_line_delimiter";
const std::string INSTRUCTION_ADDRESS = "instruction_address";
const std::string INSTRUCTUON_VALID = "instructuon_valid";
const std::string ENABLE = "enable";
const std::string HW_BREAK_REQUEST = "hw_break_request";
const std::string SW_BREAK_REQUEST = "sw_break_request";
const std::string TRACE_JUMP_ADDRESS = "trace_jump_address";
const std::string TRACE_JUMP_TYPE = "trace_jump_type";
const std::string COMPILER_SETTINGS = "compiler";
const std::string POINTER_SIZE = "pointer_size";
const std::string FUNCTION_ALIGNMENT = "function_alignment";
const std::string STACK_ALIGNMENT = "stack_alignment";
const std::string INTERRUPT_HANDLER_ALIGNMENT = "interrupt_handler_alignment";
const std::string MAX_DATA_ADDRESS_BITS = "max_data_address_bits";
const std::string MAX_PROGRAM_ADDRESS_BITS = "max_program_address_bits";
const std::string BUNDLE_ALIGN_JUMP_TARGET = "bundle_align_jump_target";
const std::string POINTER_REGISTER_CLASS = "pointer_register_class";
const std::string REPRESENTATIVE_REGISTER_CLASS = "representative_register_class";
const std::string TYPE_SPACE_MAPPING = "type_space_mapping";
const std::string STACK_REGISTER_SPACE_MAPPING = "stack_register_space_mapping";
const std::string LEGAL_TYPES = "legal_types";
const std::string DATALAYOUT = "datalayout";
const std::string STACK_POINTER = "stack_pointer";
const std::string BASE_POINTER = "base_pointer";
const std::string AUXILIARY_REGISTER = "auxiliary_register";
const std::string RETURN_ADDRESS = "return_address";
const std::string CARRY_FLAG = "carry_flag";
const std::string OVERFLOW_FLAG = "overflow_flag";
const std::string SIGN_FLAG = "sign_flag";
const std::string ZERO_FLAG = "zero_flag";
const std::string CALLEE_SAVED = "callee_saved";
const std::string CALLEE_SAVED_LEAF = "callee_saved_leaf";
const std::string FUNCTION_RESULT = "function_result";
const std::string FUNCTION_PARAMS = "function_params";
const std::string UNUSED_REGISTERS = "unused_registers";
const std::string VERBATIM_TEXT = "verbatim_text";
const std::string ELIMINATE_DATA_HAZARDS = "eliminate_data_hazards";
const std::string ELIMINATE_STRUCTURAL_HAZARDS = "eliminate_structural_hazards";
const std::string ORDER = "order";

}   // namespace codal
}   // namespace codasip

#endif // ERR_CODAL_KEYWORDS_H_
