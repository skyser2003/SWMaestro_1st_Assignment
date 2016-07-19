// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: struct/struct_cs.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "struct/struct_cs.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace PKS {

namespace {

const ::google::protobuf::Descriptor* CS_HIGH_SCORE_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  CS_HIGH_SCORE_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_struct_2fstruct_5fcs_2eproto() {
  protobuf_AddDesc_struct_2fstruct_5fcs_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "struct/struct_cs.proto");
  GOOGLE_CHECK(file != NULL);
  CS_HIGH_SCORE_descriptor_ = file->message_type(0);
  static const int CS_HIGH_SCORE_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(CS_HIGH_SCORE, name_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(CS_HIGH_SCORE, score_),
  };
  CS_HIGH_SCORE_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      CS_HIGH_SCORE_descriptor_,
      CS_HIGH_SCORE::default_instance_,
      CS_HIGH_SCORE_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(CS_HIGH_SCORE, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(CS_HIGH_SCORE, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(CS_HIGH_SCORE));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_struct_2fstruct_5fcs_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    CS_HIGH_SCORE_descriptor_, &CS_HIGH_SCORE::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_struct_2fstruct_5fcs_2eproto() {
  delete CS_HIGH_SCORE::default_instance_;
  delete CS_HIGH_SCORE_reflection_;
}

void protobuf_AddDesc_struct_2fstruct_5fcs_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\026struct/struct_cs.proto\022\003PKS\",\n\rCS_HIGH"
    "_SCORE\022\014\n\004name\030\001 \002(\t\022\r\n\005score\030\002 \002(\005", 75);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "struct/struct_cs.proto", &protobuf_RegisterTypes);
  CS_HIGH_SCORE::default_instance_ = new CS_HIGH_SCORE();
  CS_HIGH_SCORE::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_struct_2fstruct_5fcs_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_struct_2fstruct_5fcs_2eproto {
  StaticDescriptorInitializer_struct_2fstruct_5fcs_2eproto() {
    protobuf_AddDesc_struct_2fstruct_5fcs_2eproto();
  }
} static_descriptor_initializer_struct_2fstruct_5fcs_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int CS_HIGH_SCORE::kNameFieldNumber;
const int CS_HIGH_SCORE::kScoreFieldNumber;
#endif  // !_MSC_VER

CS_HIGH_SCORE::CS_HIGH_SCORE()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:PKS.CS_HIGH_SCORE)
}

void CS_HIGH_SCORE::InitAsDefaultInstance() {
}

CS_HIGH_SCORE::CS_HIGH_SCORE(const CS_HIGH_SCORE& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:PKS.CS_HIGH_SCORE)
}

void CS_HIGH_SCORE::SharedCtor() {
  ::google::protobuf::internal::GetEmptyString();
  _cached_size_ = 0;
  name_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  score_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

CS_HIGH_SCORE::~CS_HIGH_SCORE() {
  // @@protoc_insertion_point(destructor:PKS.CS_HIGH_SCORE)
  SharedDtor();
}

void CS_HIGH_SCORE::SharedDtor() {
  if (name_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete name_;
  }
  if (this != default_instance_) {
  }
}

void CS_HIGH_SCORE::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* CS_HIGH_SCORE::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return CS_HIGH_SCORE_descriptor_;
}

const CS_HIGH_SCORE& CS_HIGH_SCORE::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_struct_2fstruct_5fcs_2eproto();
  return *default_instance_;
}

CS_HIGH_SCORE* CS_HIGH_SCORE::default_instance_ = NULL;

CS_HIGH_SCORE* CS_HIGH_SCORE::New() const {
  return new CS_HIGH_SCORE;
}

void CS_HIGH_SCORE::Clear() {
  if (_has_bits_[0 / 32] & 3) {
    if (has_name()) {
      if (name_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        name_->clear();
      }
    }
    score_ = 0;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool CS_HIGH_SCORE::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:PKS.CS_HIGH_SCORE)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required string name = 1;
      case 1: {
        if (tag == 10) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_name()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->name().data(), this->name().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "name");
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(16)) goto parse_score;
        break;
      }

      // required int32 score = 2;
      case 2: {
        if (tag == 16) {
         parse_score:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &score_)));
          set_has_score();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectAtEnd()) goto success;
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:PKS.CS_HIGH_SCORE)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:PKS.CS_HIGH_SCORE)
  return false;
#undef DO_
}

void CS_HIGH_SCORE::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:PKS.CS_HIGH_SCORE)
  // required string name = 1;
  if (has_name()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->name().data(), this->name().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "name");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      1, this->name(), output);
  }

  // required int32 score = 2;
  if (has_score()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(2, this->score(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:PKS.CS_HIGH_SCORE)
}

::google::protobuf::uint8* CS_HIGH_SCORE::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:PKS.CS_HIGH_SCORE)
  // required string name = 1;
  if (has_name()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->name().data(), this->name().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "name");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        1, this->name(), target);
  }

  // required int32 score = 2;
  if (has_score()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(2, this->score(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:PKS.CS_HIGH_SCORE)
  return target;
}

int CS_HIGH_SCORE::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required string name = 1;
    if (has_name()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->name());
    }

    // required int32 score = 2;
    if (has_score()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->score());
    }

  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void CS_HIGH_SCORE::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const CS_HIGH_SCORE* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const CS_HIGH_SCORE*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void CS_HIGH_SCORE::MergeFrom(const CS_HIGH_SCORE& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_name()) {
      set_name(from.name());
    }
    if (from.has_score()) {
      set_score(from.score());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void CS_HIGH_SCORE::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void CS_HIGH_SCORE::CopyFrom(const CS_HIGH_SCORE& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool CS_HIGH_SCORE::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000003) != 0x00000003) return false;

  return true;
}

void CS_HIGH_SCORE::Swap(CS_HIGH_SCORE* other) {
  if (other != this) {
    std::swap(name_, other->name_);
    std::swap(score_, other->score_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata CS_HIGH_SCORE::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = CS_HIGH_SCORE_descriptor_;
  metadata.reflection = CS_HIGH_SCORE_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace PKS

// @@protoc_insertion_point(global_scope)