#pragma once

#include "enum/enum_cs.pb.h"
#include "enum/enum_sc.pb.h"

#include "struct/struct_cs.pb.h"
#include "struct/struct_sc.pb.h"

// Declaration only
template <int ENUM>
class PKENUMInfo;

template <>
class PKENUMInfo<static_cast<int>(PKENUM::CSPacketEnum::CS_HIGH_SCORE)>
{
public:
	using PKS = PKS::CS_HIGH_SCORE;
};

template <>
class PKENUMInfo<static_cast<int>(PKENUM::SCPacketEnum::SC_HIGH_SCORE_LIST)>
{
public:
	using PKS = PKS::SC_HIGH_SCORE_LIST;
};
