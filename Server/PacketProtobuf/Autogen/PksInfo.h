#pragma once

#include "enum/enum_cs.pb.h"
#include "enum/enum_sc.pb.h"

#include "struct/struct_cs.pb.h"
#include "struct/struct_sc.pb.h"

// Declaration only
template <class PKS>
class PKSInfo;

template <>
class PKSInfo<PKS::CS_HIGH_SCORE>
{
public:
	static const PKENUM::CSPacketEnum enumVal = PKENUM::CSPacketEnum::CS_HIGH_SCORE;
};

template <>
class PKSInfo<PKS::SC_HIGH_SCORE_LIST>
{
public:
	static const PKENUM::SCPacketEnum enumVal = PKENUM::SCPacketEnum::SC_HIGH_SCORE_LIST;
};
