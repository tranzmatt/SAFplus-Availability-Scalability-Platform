// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: SAFplusPBExt.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "SAFplusPBExt.pb.h"

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

namespace SAFplus {
namespace Rpc {

namespace {

const ::google::protobuf::Descriptor* NO_RESPONSE_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  NO_RESPONSE_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_SAFplusPBExt_2eproto() {
  protobuf_AddDesc_SAFplusPBExt_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "SAFplusPBExt.proto");
  GOOGLE_CHECK(file != NULL);
  NO_RESPONSE_descriptor_ = file->message_type(0);
  static const int NO_RESPONSE_offsets_[1] = {
  };
  NO_RESPONSE_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      NO_RESPONSE_descriptor_,
      NO_RESPONSE::default_instance_,
      NO_RESPONSE_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(NO_RESPONSE, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(NO_RESPONSE, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(NO_RESPONSE));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_SAFplusPBExt_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    NO_RESPONSE_descriptor_, &NO_RESPONSE::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_SAFplusPBExt_2eproto() {
  delete NO_RESPONSE::default_instance_;
  delete NO_RESPONSE_reflection_;
}

void protobuf_AddDesc_SAFplusPBExt_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::protobuf_AddDesc_google_2fprotobuf_2fdescriptor_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\022SAFplusPBExt.proto\022\013SAFplus.Rpc\032 googl"
    "e/protobuf/descriptor.proto\"\r\n\013NO_RESPON"
    "SE:.\n\006c_type\022\035.google.protobuf.FieldOpti"
    "ons\030\352\007 \001(\t:2\n\nc_existing\022\035.google.protob"
    "uf.FieldOptions\030\353\007 \001(\tB\t\200\001\000\210\001\000\220\001\001", 193);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "SAFplusPBExt.proto", &protobuf_RegisterTypes);
  NO_RESPONSE::default_instance_ = new NO_RESPONSE();
  ::google::protobuf::internal::ExtensionSet::RegisterExtension(
    &::google::protobuf::FieldOptions::default_instance(),
    1002, 9, false, false);
  ::google::protobuf::internal::ExtensionSet::RegisterExtension(
    &::google::protobuf::FieldOptions::default_instance(),
    1003, 9, false, false);
  NO_RESPONSE::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_SAFplusPBExt_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_SAFplusPBExt_2eproto {
  StaticDescriptorInitializer_SAFplusPBExt_2eproto() {
    protobuf_AddDesc_SAFplusPBExt_2eproto();
  }
} static_descriptor_initializer_SAFplusPBExt_2eproto_;

// ===================================================================

#ifndef _MSC_VER
#endif  // !_MSC_VER

NO_RESPONSE::NO_RESPONSE()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void NO_RESPONSE::InitAsDefaultInstance() {
}

NO_RESPONSE::NO_RESPONSE(const NO_RESPONSE& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void NO_RESPONSE::SharedCtor() {
  _cached_size_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

NO_RESPONSE::~NO_RESPONSE() {
  SharedDtor();
}

void NO_RESPONSE::SharedDtor() {
  if (this != default_instance_) {
  }
}

void NO_RESPONSE::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* NO_RESPONSE::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return NO_RESPONSE_descriptor_;
}

const NO_RESPONSE& NO_RESPONSE::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_SAFplusPBExt_2eproto();
  return *default_instance_;
}

NO_RESPONSE* NO_RESPONSE::default_instance_ = NULL;

NO_RESPONSE* NO_RESPONSE::New() const {
  return new NO_RESPONSE;
}

void NO_RESPONSE::Clear() {
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool NO_RESPONSE::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
        ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
      return true;
    }
    DO_(::google::protobuf::internal::WireFormat::SkipField(
          input, tag, mutable_unknown_fields()));
  }
  return true;
#undef DO_
}

void NO_RESPONSE::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* NO_RESPONSE::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int NO_RESPONSE::ByteSize() const {
  int total_size = 0;

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

void NO_RESPONSE::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const NO_RESPONSE* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const NO_RESPONSE*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void NO_RESPONSE::MergeFrom(const NO_RESPONSE& from) {
  GOOGLE_CHECK_NE(&from, this);
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void NO_RESPONSE::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void NO_RESPONSE::CopyFrom(const NO_RESPONSE& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool NO_RESPONSE::IsInitialized() const {

  return true;
}

void NO_RESPONSE::Swap(NO_RESPONSE* other) {
  if (other != this) {
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata NO_RESPONSE::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = NO_RESPONSE_descriptor_;
  metadata.reflection = NO_RESPONSE_reflection_;
  return metadata;
}

const ::std::string c_type_default("");
::google::protobuf::internal::ExtensionIdentifier< ::google::protobuf::FieldOptions,
    ::google::protobuf::internal::StringTypeTraits, 9, false >
  c_type(kCTypeFieldNumber, c_type_default);
const ::std::string c_existing_default("");
::google::protobuf::internal::ExtensionIdentifier< ::google::protobuf::FieldOptions,
    ::google::protobuf::internal::StringTypeTraits, 9, false >
  c_existing(kCExistingFieldNumber, c_existing_default);

// @@protoc_insertion_point(namespace_scope)

}  // namespace Rpc
}  // namespace SAFplus

// @@protoc_insertion_point(global_scope)
