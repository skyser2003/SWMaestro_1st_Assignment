// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: struct/struct_cs.proto

#ifndef PROTOBUF_struct_2fstruct_5fcs_2eproto__INCLUDED
#define PROTOBUF_struct_2fstruct_5fcs_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2006000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2006001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

namespace PKS {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_struct_2fstruct_5fcs_2eproto();
void protobuf_AssignDesc_struct_2fstruct_5fcs_2eproto();
void protobuf_ShutdownFile_struct_2fstruct_5fcs_2eproto();

class CS_HIGH_SCORE;

// ===================================================================

class CS_HIGH_SCORE : public ::google::protobuf::Message {
 public:
  CS_HIGH_SCORE();
  virtual ~CS_HIGH_SCORE();

  CS_HIGH_SCORE(const CS_HIGH_SCORE& from);

  inline CS_HIGH_SCORE& operator=(const CS_HIGH_SCORE& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const CS_HIGH_SCORE& default_instance();

  void Swap(CS_HIGH_SCORE* other);

  // implements Message ----------------------------------------------

  CS_HIGH_SCORE* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const CS_HIGH_SCORE& from);
  void MergeFrom(const CS_HIGH_SCORE& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required string name = 1;
  inline bool has_name() const;
  inline void clear_name();
  static const int kNameFieldNumber = 1;
  inline const ::std::string& name() const;
  inline void set_name(const ::std::string& value);
  inline void set_name(const char* value);
  inline void set_name(const char* value, size_t size);
  inline ::std::string* mutable_name();
  inline ::std::string* release_name();
  inline void set_allocated_name(::std::string* name);

  // required int32 score = 2;
  inline bool has_score() const;
  inline void clear_score();
  static const int kScoreFieldNumber = 2;
  inline ::google::protobuf::int32 score() const;
  inline void set_score(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:PKS.CS_HIGH_SCORE)
 private:
  inline void set_has_name();
  inline void clear_has_name();
  inline void set_has_score();
  inline void clear_has_score();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::std::string* name_;
  ::google::protobuf::int32 score_;
  friend void  protobuf_AddDesc_struct_2fstruct_5fcs_2eproto();
  friend void protobuf_AssignDesc_struct_2fstruct_5fcs_2eproto();
  friend void protobuf_ShutdownFile_struct_2fstruct_5fcs_2eproto();

  void InitAsDefaultInstance();
  static CS_HIGH_SCORE* default_instance_;
};
// ===================================================================


// ===================================================================

// CS_HIGH_SCORE

// required string name = 1;
inline bool CS_HIGH_SCORE::has_name() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void CS_HIGH_SCORE::set_has_name() {
  _has_bits_[0] |= 0x00000001u;
}
inline void CS_HIGH_SCORE::clear_has_name() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void CS_HIGH_SCORE::clear_name() {
  if (name_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    name_->clear();
  }
  clear_has_name();
}
inline const ::std::string& CS_HIGH_SCORE::name() const {
  // @@protoc_insertion_point(field_get:PKS.CS_HIGH_SCORE.name)
  return *name_;
}
inline void CS_HIGH_SCORE::set_name(const ::std::string& value) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    name_ = new ::std::string;
  }
  name_->assign(value);
  // @@protoc_insertion_point(field_set:PKS.CS_HIGH_SCORE.name)
}
inline void CS_HIGH_SCORE::set_name(const char* value) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    name_ = new ::std::string;
  }
  name_->assign(value);
  // @@protoc_insertion_point(field_set_char:PKS.CS_HIGH_SCORE.name)
}
inline void CS_HIGH_SCORE::set_name(const char* value, size_t size) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    name_ = new ::std::string;
  }
  name_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:PKS.CS_HIGH_SCORE.name)
}
inline ::std::string* CS_HIGH_SCORE::mutable_name() {
  set_has_name();
  if (name_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    name_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:PKS.CS_HIGH_SCORE.name)
  return name_;
}
inline ::std::string* CS_HIGH_SCORE::release_name() {
  clear_has_name();
  if (name_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = name_;
    name_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void CS_HIGH_SCORE::set_allocated_name(::std::string* name) {
  if (name_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete name_;
  }
  if (name) {
    set_has_name();
    name_ = name;
  } else {
    clear_has_name();
    name_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:PKS.CS_HIGH_SCORE.name)
}

// required int32 score = 2;
inline bool CS_HIGH_SCORE::has_score() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void CS_HIGH_SCORE::set_has_score() {
  _has_bits_[0] |= 0x00000002u;
}
inline void CS_HIGH_SCORE::clear_has_score() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void CS_HIGH_SCORE::clear_score() {
  score_ = 0;
  clear_has_score();
}
inline ::google::protobuf::int32 CS_HIGH_SCORE::score() const {
  // @@protoc_insertion_point(field_get:PKS.CS_HIGH_SCORE.score)
  return score_;
}
inline void CS_HIGH_SCORE::set_score(::google::protobuf::int32 value) {
  set_has_score();
  score_ = value;
  // @@protoc_insertion_point(field_set:PKS.CS_HIGH_SCORE.score)
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace PKS

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_struct_2fstruct_5fcs_2eproto__INCLUDED