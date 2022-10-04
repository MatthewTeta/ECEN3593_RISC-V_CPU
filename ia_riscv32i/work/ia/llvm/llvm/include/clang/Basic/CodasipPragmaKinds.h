//==== CODASIP ====
// Added a whole file
/*
 * CodasipPragmaKinds.h
 *
 *  Created on: Sep 2, 2013
 *      Author: ihusar
 */

#ifndef CODASIPPRAGMAKINDS_H_
#define CODASIPPRAGMAKINDS_H_

namespace clang {

enum CodasipPragmaKind
{
	CODASIP_PRAGMA_unknown,
	CODASIP_PRAGMA_ise,
	//CODASIP_PRAGMA_vector,
	//CODASIP_PRAGMA_novector,
	//CODASIP_PRAGMA_ivdep,
	CODASIP_PRAGMA_ifconv,
	CODASIP_PRAGMA_profiler_start,
	CODASIP_PRAGMA_profiler_end,
	CODASIP_PRAGMA_hwloop,
	CODASIP_PRAGMA_count
};

const char* const CodasipPragmaNames[CODASIP_PRAGMA_count] =
{
	"unknown",
	"ise",
	//"vector",
	//"novector",
	//"ivdep",
	"ifconv",
	"profiler_start",
	"profiler_end",
	"hwloop"
};

} // namespace llvm

#endif /* CODASIPPRAGMAKINDS_H_ */
