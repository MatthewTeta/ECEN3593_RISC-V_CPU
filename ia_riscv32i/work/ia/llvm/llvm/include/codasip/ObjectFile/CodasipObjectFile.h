/**
 * Codasip s.r.o.
 *
 * CONFIDENTIAL
 *
 * Copyright 2019 Codasip s.r.o.
 *
 * All Rights Reserved.
 *
 * NOTICE: All information contained in this file, is and shall remain the
 * property of Codasip s.r.o. and its suppliers, if any.
 *
 * The intellectual and technical concepts contained herein are confidential and
 * proprietary to Codasip s.r.o. and are protected by trade secret and copyright
 * law.  In addition, elements of the technical concepts may be patent pending.
 *
 * This file is part of the Codasip Studio product. No part of the Studio
 * product, including this file, may be use, copied, modified, or distributed
 * except in accordance with the terms contained in Codasip license agreement
 * under which you obtained this file.
 *
 *  \file
 *  \author Martin Ministr
 *  \date   18. 3. 2019
 *  \brief  Declaration/Implementation of the class.
 */

#ifndef INCLUDE_CODASIP_OBJECTFILE_CODASIPOBJECTFILE_H_
#define INCLUDE_CODASIP_OBJECTFILE_CODASIPOBJECTFILE_H_

#include <map>

#include "codasip/ObjectFile/CodasipAddressSpace.h"
#include "codasip/ObjectFile/CodasipSectionInfo.h"
#include "llvm/ADT/APInt.h"
#include "llvm/Object/ELFObjectFile.h"

/* The origin of the following macros is 'include/elf/internal.h'
   located in the GNU Binutils project.  */

/* .tbss is special.  It doesn't contribute memory space to normal
   segments and it doesn't take file space in normal segments.  */
#define ELF_TBSS_SPECIAL(sec_hdr, segment)                                     \
  (((sec_hdr)->sh_flags & ELF::SHF_TLS) != 0 &&                                \
   (sec_hdr)->sh_type == ELF::SHT_NOBITS && (segment)->p_type != ELF::PT_TLS)

#define ELF_SECTION_SIZE(sec_hdr, segment)                                     \
  (ELF_TBSS_SPECIAL(sec_hdr, segment) ? 0 : (sec_hdr)->sh_size)

/* Decide if the section SEC_HDR is in SEGMENT.  If CHECK_VMA, then
   VMAs are checked for alloc sections.  If STRICT, then a zero size
   section won't match at the end of a segment, unless the segment
   is also zero size.  Regardless of STRICT and CHECK_VMA, zero size
   sections won't match at the start or end of PT_DYNAMIC, unless
   PT_DYNAMIC is itself zero sized.  */
#define ELF_SECTION_IN_SEGMENT_1(sec_hdr, segment, check_vma, strict)          \
  ((/* Only PT_LOAD, PT_GNU_RELRO and PT_TLS segments can contain              \
       SHF_TLS sections.  */                                                   \
    ((((sec_hdr)->sh_flags & ELF::SHF_TLS) != 0) &&                            \
     ((segment)->p_type == ELF::PT_TLS ||                                      \
      (segment)->p_type == ELF::PT_GNU_RELRO ||                                \
      (segment)->p_type ==                                                     \
          ELF::PT_LOAD)) /* PT_TLS segment contains only SHF_TLS sections,     \
                            PT_PHDR no sections at all.  */                                                          \
    || (((sec_hdr)->sh_flags & ELF::SHF_TLS) == 0 &&                           \
        (segment)->p_type != ELF::PT_TLS &&                                    \
        (segment)->p_type !=                                                   \
            ELF::PT_PHDR)) /* Any section besides one of type SHT_NOBITS must  \
                              have file offsets within the segment.  */                                               \
   && ((sec_hdr)->sh_type == ELF::SHT_NOBITS ||                                \
       ((sec_hdr)->sh_offset >= (segment)->p_offset &&                         \
        (!(strict) || ((sec_hdr)->sh_offset - (segment)->p_offset <=           \
                       (segment)->p_filesz - 1)) &&                            \
        (((sec_hdr)->sh_offset - (segment)->p_offset +                         \
          ELF_SECTION_SIZE(sec_hdr, segment)) <=                               \
         (segment)->p_filesz))) /* SHF_ALLOC sections must have VMAs within    \
                                   the segment.  */                            \
   && (!(check_vma) || ((sec_hdr)->sh_flags & ELF::SHF_ALLOC) == 0 ||          \
       ((sec_hdr)->sh_addr >= (segment)->p_vaddr &&                            \
        (!(strict) || ((sec_hdr)->sh_addr - (segment)->p_vaddr <=              \
                       (segment)->p_memsz - 1)) &&                             \
        (((sec_hdr)->sh_addr - (segment)->p_vaddr +                            \
          ELF_SECTION_SIZE(sec_hdr, segment)) <=                               \
         (segment)->p_memsz))) /* No zero size sections at start or end of     \
                                  PT_DYNAMIC.  */                              \
   &&                                                                          \
   ((segment)->p_type != ELF::PT_DYNAMIC || (sec_hdr)->sh_size != 0 ||         \
    (segment)->p_memsz == 0 ||                                                 \
    (((sec_hdr)->sh_type == ELF::SHT_NOBITS ||                                 \
      ((sec_hdr)->sh_offset > (segment)->p_offset &&                           \
       ((sec_hdr)->sh_offset - (segment)->p_offset < (segment)->p_filesz))) && \
     (((sec_hdr)->sh_flags & ELF::SHF_ALLOC) == 0 ||                           \
      ((sec_hdr)->sh_addr > (segment)->p_vaddr &&                              \
       ((sec_hdr)->sh_addr - (segment)->p_vaddr < (segment)->p_memsz))))))

#define ELF_SECTION_IN_SEGMENT(sec_hdr, segment)                               \
  (ELF_SECTION_IN_SEGMENT_1(sec_hdr, segment, 1, 0))

namespace llvm {

// Forward declaration
class DataExtractor;

/**
 *  \brief  Converts LLVM APInt into Codasip integer.
 *          Converts only bits matching specified bit-width at maximum.
 *  \param[out] dst Destination Codasip integer
 *  \param[in]  src Source LLVM APInt
 *  \param[in]  bitWidth bit-width
 */
template <class T>
void APIntToCodasipInt(T &dst, const llvm::APInt &src,
                       const unsigned int bitWidth) {
  dst = 0;

  const unsigned int llvmWordCount =
      (bitWidth + (llvm::APInt::APINT_BITS_PER_WORD - 1)) /
      llvm::APInt::APINT_BITS_PER_WORD;

  // copy to result per APInt words, underlying words in APInt are backwards
  for (size_t i = 0; i < llvmWordCount; i++) {
    dst <<= llvm::APInt::APINT_BITS_PER_WORD;
    dst |= src.getRawData()[llvmWordCount - i - 1];
  }
}

/**
 *  \brief  Codasip encapsulation over LLVM ObjectFile object.
 */
class CodasipObjectFile {
public:
  /// Container for address spaces
  typedef std::vector<CodasipAddressSpace> AddressSpacesType;

  ~CodasipObjectFile();
  /**
   *  \brief  Create Codasip object file of given executable or object file.
   *          Returns null on failure.
   *  \param[in]  path Executable/object file path
   */
  static std::unique_ptr<CodasipObjectFile> create(const std::string &path);
  /**
   *  \brief  Create Codasip object file that is facade over passed LLVM object
   * file. Returns null on failure. \param[in]  executable Executable/object
   * file \param[in]  binary CodasipObjectFile will own the passed binary if
   * passed
   */
  static std::unique_ptr<CodasipObjectFile>
  create(const object::ObjectFile &executable,
         object::OwningBinary<object::Binary> binary =
             object::OwningBinary<object::Binary>());
  /**
   *  \brief  Try to match address spaces to sections on non-Codasip ELFs.
   */
  void initSectionToAddressSpaceNonCodasip();
  /**
   *  \{
   *  \brief  Getter.
   */
  uint32_t getDefaultWordBitWidth() const;
  uint32_t getDefaultByteBitWidth() const;
  bool isLittleEndian() const;
  const object::ObjectFile &getReference() const;
  const AddressSpacesType &getAddressSpaces() const;
  /**
   *  \}
   *  \{
   *  \brief  Setter.
   */
  void addAddressSpace(const CodasipAddressSpace &);
  /// \}
  /**
   *  \brief  Return section of given index, use only when really needed, slow.
   * Prefer foreach. \param[in]  index
   */
  const object::SectionRef getSection(const size_t index) const;
  /// \brief  Get section count.
  size_t getSectionCount() const;
  /// \brief  Get start address (entry point) for simulation.
  uint64_t getStartAddress() const;
  /// \brief  Determines whether this is an harvard architecture.
  bool isHarvard() const;

  // methods to read various section attributes and content, they depends on
  // ObjectFile itself
  /**
   *  \brief  Get word bit-width of section.
   *  \param[in]  section
   */
  uint32_t getWordBitWidth(const object::SectionRef &section) const;
  /**
   *  \brief  Get byte bit-width of section.
   *  \param[in]  section
   */
  uint32_t getByteBitWidth(const object::SectionRef &section) const;
  /**
   *  \brief  Get byte per word of section.
   *  \param[in]  section
   *  \param[in]  loadAddress Depends on the address space context
   */
  uint16_t getBytesPerWord(const object::SectionRef &section,
                           const bool loadAddress) const;
  /**
   *  \brief  Get ELF load memory address (LMA) from virtual memory address
   * (VMA). \param[in]  section
   */
  uint64_t getLoadAddress(const object::SectionRef &section) const;
  /**
   *  \brief  Get size of section in bytes.
   *  \param[in]  section
   *  \param[in]  loadAddress Depends on the address space context
   */
  uint64_t getSize(const object::SectionRef &section,
                   const bool loadAddress) const;
  /**
   *  \brief  Get size of section in words.
   *  \param[in]  section
   *  \param[in]  loadAddress Depends on the address space context
   */
  size_t getSizeInWords(const object::SectionRef &section,
                        const bool loadAddress) const;
  /**
   *  \brief  Get byte from section on given offset.
   *  \param[out] word
   *  \param[in, out] offset
   *  \param[in]  section
   *  \param[in]  loadAddress Depends on the address space context
   */
  void getByte(APInt &byte, const uint32_t offset,
               const object::SectionRef &section, const bool loadAddress) const;
  /**
   *  \brief  Get word from section on given offset.
   *  \param[out] word
   *  \param[in, out] offset
   *  \param[in]  section
   *  \param[in]  loadAddress Depends on the address space context
   */
  void getWord(APInt &word, const uint32_t offset,
               const object::SectionRef &section, const bool loadAddress) const;
  /**
   *  \brief  Get address space to given section. Same as
   * GetVirtualAddressSpace. \param[in]  section
   */
  const CodasipAddressSpace &
  getAddressSpace(const object::SectionRef &section) const;
  /**
   *  \brief  Get virtual address space to given section. Fails when address
   * space is missing. \param[in]  section
   */
  const CodasipAddressSpace &
  getVirtualAddressSpace(const object::SectionRef &section) const;
  /**
   *  \brief  Get load address space to given section. Fails when address space
   * is missing. \param[in]  section
   */
  const CodasipAddressSpace &
  getLoadAddressSpace(const object::SectionRef &section) const;
  /**
   *  \brief  Determines whether given section has address space. Same as
   * HasVirtualAddressSpace. \param[in]  section
   */
  bool hasAddressSpace(const object::SectionRef &section) const;
  /**
   *  \brief  Determines whether given section has virtual address space.
   *  \param[in]  section
   */
  bool hasVirtualAddressSpace(const object::SectionRef &section) const;
  /**
   *  \brief  Determines whether given section has load address space.
   *  \param[in]  section
   */
  bool hasLoadAddressSpace(const object::SectionRef &section) const;
  /**
   *  \brief  Determines if section is allocatable.
   *  \param[in]  section
   */
  bool isAllocatable(const object::SectionRef &section) const;
  /**
   *  \brief  Determines if section is little endian.
   *  \param[in]  section
   */
  bool isLittleEndian(const object::SectionRef &section) const;
  /**
   *  \brief  Determines whether given section is internal.
   *          Section name starts with ".debug" or type is SYMBOL or STRING.
   *  \param[in]  section
   */
  bool isInternal(const llvm::object::SectionRef &section) const;
  /**
   *  \brief  Read a host byte of given section.
   *          Update offset after successful read. Fails on unsuccessful read.
   *  \param[in, out] offset
   *  \param[in]  section
   */
  uint8_t getU8(uint32_t &offset,
                const llvm::object::SectionRef &section) const;
  /**
   *  \brief  Read two host bytes of given section.
   *          Update offset after successful read. Fails on unsuccessful read.
   *  \param[in, out] offset
   *  \param[in]  section
   */
  uint16_t getU16(uint32_t &offset,
                  const llvm::object::SectionRef &section) const;
  /**
   *  \brief  Read four host bytes of given section.
   *          Update offset after successful read. Fails on unsuccessful read.
   *  \param[in, out] offset
   *  \param[in]  section
   */
  uint32_t getU32(uint32_t &offset,
                  const llvm::object::SectionRef &section) const;
  /**
   *  \brief  Read eight host bytes of given section.
   *          Update offset after successful read. Fails on unsuccessful read.
   *  \param[in, out] offset
   *  \param[in]  section
   */
  uint64_t getU64(uint32_t &offset,
                  const llvm::object::SectionRef &section) const;
  /**
   *  \brief  Read zero terminated string.
   *  \param[in, out] offset
   *  \param[in]  section
   *  \return Reference on zero terminated string.
   */
  StringRef getZeroStringRef(uint32_t &offset,
                             const llvm::object::SectionRef &section) const;

  // methods to read various symbol attributes
  /**
   *  \brief  Get symbol address.
   *  \param[in]  symbol
   */
  static uint64_t getSymbolAddress(const llvm::object::SymbolRef &symbol);
  /**
   *  \brief  Get symbol name.
   *  \param[in]  symbol
   */
  static llvm::StringRef getSymbolName(const llvm::object::SymbolRef &symbol);
  /**
   *  \brief  Determines whether symbol has section.
   *  \param[in]  symbol
   */
  static bool hasSymbolSection(const llvm::object::SymbolRef &symbol);
  /**
   *  \brief  Get symbol section.
   *  \param[in]  symbol
   */
  static llvm::object::SectionRef
  getSymbolSection(const llvm::object::SymbolRef &symbol);
  /**
   *  \brief  Get symbol type.
   *  \param[in]  symbol
   */
  static llvm::object::SymbolRef::Type
  getSymbolType(const llvm::object::SymbolRef &symbol);

private:
  /// Maps section name to section info
  typedef std::map<std::string, CodasipSectionInfo *> SectionInfosType;

  CodasipObjectFile(object::OwningBinary<object::Binary> owner,
                    const object::ObjectFile &reference);

  void init();
  void initSectionInfo();
  void initSectionInfoAddressSpaces();
  void InitOctetsPerByte();
  void parseAddressSpaces();
  void parseAddressSpaces(const object::SectionRef &);
  void parseAddressSpace(uint32_t &offset, const object::SectionRef &section);

  void getByte(APInt &byte, const uint32_t offset,
               const object::SectionRef &section) const;
  CodasipSectionInfo &getSectionInfo(const object::SectionRef &section) const;
  void readByte(APInt &byte, const uint32_t offset,
                const object::SectionRef &section) const;

  template <class ELFT>
  void getLoadAddressHelper(uint64_t &lma,
                            const object::ELFObjectFile<ELFT> &objectFile,
                            const object::ELFSectionRef &elfSection) const {
    const object::ELFFile<ELFT> &file = *objectFile.getELFFile();

    // prepare program headers
    Expected<typename object::ELFFile<ELFT>::Elf_Phdr_Range>
        programHeadersOrErr = file.program_headers();
    if (!programHeadersOrErr) {
      consumeError(programHeadersOrErr.takeError());
      report_fatal_error("Missing program headers in ELF.");
    }
    typename object::ELFFile<ELFT>::Elf_Phdr_Range &programHeaders =
        programHeadersOrErr.get();

    /* Some ELF linkers produce binaries with all the program header p_paddr
     * fields zero. If we have such a binary with more than one PT_LOAD header,
     * then leave the section lma equal
     * to vma so that we don't create sections with overlapping lma.  */
    unsigned int loadCount = 0;
    bool broken = false;
    for (const typename object::ELFFile<ELFT>::Elf_Phdr &phdr :
         programHeaders) {
      if (phdr.p_paddr != 0) {
        broken = true;
        break;
      } else if (phdr.p_type == ELF::PT_LOAD && phdr.p_memsz != 0) {
        ++loadCount;
      }
    }
    // Leave LMA untouched
    if (!broken && loadCount > 1)
      return;

    const uint32_t type = elfSection.getType();
    const uint64_t flags = elfSection.getFlags();
    const uint64_t address = elfSection.getAddress();
    const uint64_t offset = elfSection.getOffset();
    const uint64_t size = elfSection.getSize();

    loadCount = 0;
    for (typename object::ELFFile<ELFT>::Elf_Phdr phdr : programHeaders) {
      if ((phdr.p_type != ELF::PT_LOAD || (flags & ELF::SHF_TLS)) &&
          phdr.p_type != ELF::PT_TLS)
        continue;

      // partial initialization with data used in ELF_SECTION_IN_SEGMENT
      // using cast to ElfX_Addr to silence compiler warnings,
      // flags and size are 32-bit for 32-bit ELF and 64-bit for 64-bit ELF, but
      // in definition of Elf32_Shdr and Elf64_Shdr different types are used
      typename object::ELFFile<ELFT>::Elf_Shdr shdr;
      shdr.sh_name = 0;
      shdr.sh_type = type;
      shdr.sh_flags = (typename object::ELFFile<ELFT>::Elf_Addr)flags;
      shdr.sh_addr = address;
      shdr.sh_offset = offset;
      shdr.sh_size = (typename object::ELFFile<ELFT>::Elf_Addr)size;
      shdr.sh_link = 0;
      shdr.sh_info = 0;
      shdr.sh_addralign = 0;
      shdr.sh_entsize = 0;

      if (!ELF_SECTION_IN_SEGMENT(&shdr, &phdr))
        continue;

      if (type == ELF::SHT_NOBITS) {
        lma = (phdr.p_paddr + address - phdr.p_vaddr);
      } else {
        /* We used to use the same adjustment for SEC_LOAD sections, but that
         * doesn't work if the segment is packed with code from multiple VMAs.
         * Instead we calculate the section LMA based on the segment LMA.  It is
         * assumed that the segment will contain sections
         * with contiguous LMAs, even if the VMAs are not. */
        lma = (phdr.p_paddr + offset - phdr.p_offset);

        /* With contiguous segments, we can't tell from file offsets whether a
         * section with zero size should be placed at the end of one segment or
         * the beginning of the next. Decide based on vaddr. */
        if ((address >= phdr.p_vaddr) &&
            (address + size <= phdr.p_vaddr + phdr.p_memsz))
          break;
      }
    }
  }

  /// Owner of executable
  object::OwningBinary<object::Binary> Owner;
  /// Referenced LLVM object file
  const object::ObjectFile &Reference;
  /// Address spaces
  AddressSpacesType AddressSpaces;
  /// Section name to section info
  SectionInfosType SectionInfos;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
inline uint32_t CodasipObjectFile::getDefaultWordBitWidth() const {
  assert(Reference.isELF());
  return Reference.is64Bit() ? 64 : 32;
}

inline uint32_t CodasipObjectFile::getDefaultByteBitWidth() const { return 8; }

inline bool CodasipObjectFile::isLittleEndian() const {
  return Reference.isLittleEndian();
}

inline const object::ObjectFile &CodasipObjectFile::getReference() const {
  return Reference;
}

inline const CodasipObjectFile::AddressSpacesType &
CodasipObjectFile::getAddressSpaces() const {
  return AddressSpaces;
}

inline void CodasipObjectFile::addAddressSpace(const CodasipAddressSpace &as) {
  AddressSpaces.emplace_back(as);
}

inline bool CodasipObjectFile::isHarvard() const {
  return AddressSpaces.size() > 1;
}

} // namespace llvm

#undef ELF_TBSS_SPECIAL
#undef ELF_SECTION_SIZE
#undef ELF_SECTION_IN_SEGMENT_1
#undef ELF_SECTION_IN_SEGMENT

#endif // INCLUDE_CODASIP_OBJECTFILE_CODASIPOBJECTFILE_H_
