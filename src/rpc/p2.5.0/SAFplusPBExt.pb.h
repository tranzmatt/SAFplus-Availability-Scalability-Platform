// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: SAFplusPBExt.proto

#ifndef PROTOBUF_SAFplusPBExt_2eproto__INCLUDED
#define PROTOBUF_SAFplusPBExt_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2005000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2005000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/unknown_field_set.h>
#include "google/protobuf/descriptor.pb.h"
// @@protoc_insertion_point(includes)

namespace SAFplus {
namespace Rpc {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_SAFplusPBExt_2eproto();
void protobuf_AssignDesc_SAFplusPBExt_2eproto();
void protobuf_ShutdownFile_SAFplusPBExt_2eproto();

class NO_RESPONSE;

// ===================================================================

class NO_RESPONSE : public ::google::protobuf::Message {
 public:
  NO_RESPONSE();
  virtual ~NO_RESPONSE();

  NO_RESPONSE(const NO_RESPONSE& from);

  inline NO_RESPONSE& operator=(const NO_RESPONSE& from) {
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
  static const NO_RESPONSE& default_instance();

  void Swap(NO_RESPONSE* other);

  // implements Message ----------------------------------------------

  NO_RESPONSE* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const NO_RESPONSE& from);
  void MergeFrom(const NO_RESPONSE& from);
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

  // @@protoc_insertion_point(class_scope:SAFplus.Rpc.NO_RESPONSE)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;


  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[1];

  friend void  protobuf_AddDesc_SAFplusPBExt_2eproto();
  friend void protobuf_AssignDesc_SAFplusPBExt_2eproto();
  friend void protobuf_ShutdownFile_SAFplusPBExt_2eproto();

  void InitAsDefaultInstance();
  static NO_RESPONSE* default_instance_;
};
// ===================================================================

static const int kCTypeFieldNumber = 1002;
extern ::google::protobuf::internal::ExtensionIdentifier< ::google::protobuf::FieldOptions,
    ::google::protobuf::internal::StringTypeTraits, 9, false >
  c_type;
static const int kCExistingFieldNumber = 1003;
extern ::google::protobuf::internal::ExtensionIdentifier< ::google::protobuf::FieldOptions,
    ::google::protobuf::internal::StringTypeTraits, 9, false >
  c_existing;

// ===================================================================

// NO_RESPONSE


// @@protoc_insertion_point(namespace_scope)

}  // namespace Rpc
}  // namespace SAFplus

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_SAFplusPBExt_2eproto__INCLUDED
