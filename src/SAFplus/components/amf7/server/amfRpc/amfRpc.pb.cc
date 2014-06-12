// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: amfRpc.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "amfRpc.pb.h"

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
namespace amfRpc {

namespace {

const ::google::protobuf::Descriptor* StartComponentRequest_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  StartComponentRequest_reflection_ = NULL;
const ::google::protobuf::Descriptor* StartComponentResponse_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  StartComponentResponse_reflection_ = NULL;
const ::google::protobuf::Descriptor* StopComponentRequest_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  StopComponentRequest_reflection_ = NULL;
const ::google::protobuf::Descriptor* StopComponentResponse_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  StopComponentResponse_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_amfRpc_2eproto() {
  protobuf_AddDesc_amfRpc_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "amfRpc.proto");
  GOOGLE_CHECK(file != NULL);
  StartComponentRequest_descriptor_ = file->message_type(0);
  static const int StartComponentRequest_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(StartComponentRequest, name_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(StartComponentRequest, command_),
  };
  StartComponentRequest_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      StartComponentRequest_descriptor_,
      StartComponentRequest::default_instance_,
      StartComponentRequest_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(StartComponentRequest, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(StartComponentRequest, _unknown_fields_),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(StartComponentRequest, _extensions_),
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(StartComponentRequest));
  StartComponentResponse_descriptor_ = file->message_type(1);
  static const int StartComponentResponse_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(StartComponentResponse, err_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(StartComponentResponse, pid_),
  };
  StartComponentResponse_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      StartComponentResponse_descriptor_,
      StartComponentResponse::default_instance_,
      StartComponentResponse_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(StartComponentResponse, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(StartComponentResponse, _unknown_fields_),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(StartComponentResponse, _extensions_),
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(StartComponentResponse));
  StopComponentRequest_descriptor_ = file->message_type(2);
  static const int StopComponentRequest_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(StopComponentRequest, pid_),
  };
  StopComponentRequest_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      StopComponentRequest_descriptor_,
      StopComponentRequest::default_instance_,
      StopComponentRequest_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(StopComponentRequest, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(StopComponentRequest, _unknown_fields_),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(StopComponentRequest, _extensions_),
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(StopComponentRequest));
  StopComponentResponse_descriptor_ = file->message_type(3);
  static const int StopComponentResponse_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(StopComponentResponse, err_),
  };
  StopComponentResponse_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      StopComponentResponse_descriptor_,
      StopComponentResponse::default_instance_,
      StopComponentResponse_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(StopComponentResponse, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(StopComponentResponse, _unknown_fields_),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(StopComponentResponse, _extensions_),
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(StopComponentResponse));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_amfRpc_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    StartComponentRequest_descriptor_, &StartComponentRequest::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    StartComponentResponse_descriptor_, &StartComponentResponse::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    StopComponentRequest_descriptor_, &StopComponentRequest::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    StopComponentResponse_descriptor_, &StopComponentResponse::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_amfRpc_2eproto() {
  delete StartComponentRequest::default_instance_;
  delete StartComponentRequest_reflection_;
  delete StartComponentResponse::default_instance_;
  delete StartComponentResponse_reflection_;
  delete StopComponentRequest::default_instance_;
  delete StopComponentRequest_reflection_;
  delete StopComponentResponse::default_instance_;
  delete StopComponentResponse_reflection_;
}

void protobuf_AddDesc_amfRpc_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::SAFplus::Rpc::protobuf_AddDesc_SAFplusPBExt_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\014amfRpc.proto\022\022SAFplus.Rpc.amfRpc\032\022SAFp"
    "lusPBExt.proto\"A\n\025StartComponentRequest\022"
    "\014\n\004name\030\001 \001(\t\022\017\n\007command\030\002 \001(\t*\t\010\350\007\020\200\200\200\200"
    "\002\"=\n\026StartComponentResponse\022\013\n\003err\030\001 \001(\005"
    "\022\013\n\003pid\030\002 \001(\005*\t\010\350\007\020\200\200\200\200\002\".\n\024StopComponen"
    "tRequest\022\013\n\003pid\030\001 \001(\005*\t\010\350\007\020\200\200\200\200\002\"/\n\025Stop"
    "ComponentResponse\022\013\n\003err\030\001 \001(\005*\t\010\350\007\020\200\200\200\200"
    "\0022\327\001\n\006amfRpc\022g\n\016startComponent\022).SAFplus"
    ".Rpc.amfRpc.StartComponentRequest\032*.SAFp"
    "lus.Rpc.amfRpc.StartComponentResponse\022d\n"
    "\rstopComponent\022(.SAFplus.Rpc.amfRpc.Stop"
    "ComponentRequest\032).SAFplus.Rpc.amfRpc.St"
    "opComponentResponseB\t\200\001\000\210\001\000\220\001\001", 510);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "amfRpc.proto", &protobuf_RegisterTypes);
  StartComponentRequest::default_instance_ = new StartComponentRequest();
  StartComponentResponse::default_instance_ = new StartComponentResponse();
  StopComponentRequest::default_instance_ = new StopComponentRequest();
  StopComponentResponse::default_instance_ = new StopComponentResponse();
  StartComponentRequest::default_instance_->InitAsDefaultInstance();
  StartComponentResponse::default_instance_->InitAsDefaultInstance();
  StopComponentRequest::default_instance_->InitAsDefaultInstance();
  StopComponentResponse::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_amfRpc_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_amfRpc_2eproto {
  StaticDescriptorInitializer_amfRpc_2eproto() {
    protobuf_AddDesc_amfRpc_2eproto();
  }
} static_descriptor_initializer_amfRpc_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int StartComponentRequest::kNameFieldNumber;
const int StartComponentRequest::kCommandFieldNumber;
#endif  // !_MSC_VER

StartComponentRequest::StartComponentRequest()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void StartComponentRequest::InitAsDefaultInstance() {
}

StartComponentRequest::StartComponentRequest(const StartComponentRequest& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void StartComponentRequest::SharedCtor() {
  _cached_size_ = 0;
  name_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  command_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

StartComponentRequest::~StartComponentRequest() {
  SharedDtor();
}

void StartComponentRequest::SharedDtor() {
  if (name_ != &::google::protobuf::internal::kEmptyString) {
    delete name_;
  }
  if (command_ != &::google::protobuf::internal::kEmptyString) {
    delete command_;
  }
  if (this != default_instance_) {
  }
}

void StartComponentRequest::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* StartComponentRequest::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return StartComponentRequest_descriptor_;
}

const StartComponentRequest& StartComponentRequest::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_amfRpc_2eproto();
  return *default_instance_;
}

StartComponentRequest* StartComponentRequest::default_instance_ = NULL;

StartComponentRequest* StartComponentRequest::New() const {
  return new StartComponentRequest;
}

void StartComponentRequest::Clear() {
  _extensions_.Clear();
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (has_name()) {
      if (name_ != &::google::protobuf::internal::kEmptyString) {
        name_->clear();
      }
    }
    if (has_command()) {
      if (command_ != &::google::protobuf::internal::kEmptyString) {
        command_->clear();
      }
    }
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool StartComponentRequest::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional string name = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_name()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->name().data(), this->name().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(18)) goto parse_command;
        break;
      }

      // optional string command = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_command:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_command()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->command().data(), this->command().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectAtEnd()) return true;
        break;
      }

      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        if ((8000u <= tag)) {
          DO_(_extensions_.ParseField(tag, input, default_instance_,
                                      mutable_unknown_fields()));
          continue;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void StartComponentRequest::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional string name = 1;
  if (has_name()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->name().data(), this->name().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      1, this->name(), output);
  }

  // optional string command = 2;
  if (has_command()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->command().data(), this->command().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      2, this->command(), output);
  }

  // Extension range [1000, 536870912)
  _extensions_.SerializeWithCachedSizes(
      1000, 536870912, output);

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* StartComponentRequest::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // optional string name = 1;
  if (has_name()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->name().data(), this->name().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        1, this->name(), target);
  }

  // optional string command = 2;
  if (has_command()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->command().data(), this->command().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        2, this->command(), target);
  }

  // Extension range [1000, 536870912)
  target = _extensions_.SerializeWithCachedSizesToArray(
      1000, 536870912, target);

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int StartComponentRequest::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional string name = 1;
    if (has_name()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->name());
    }

    // optional string command = 2;
    if (has_command()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->command());
    }

  }
  total_size += _extensions_.ByteSize();

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

void StartComponentRequest::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const StartComponentRequest* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const StartComponentRequest*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void StartComponentRequest::MergeFrom(const StartComponentRequest& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_name()) {
      set_name(from.name());
    }
    if (from.has_command()) {
      set_command(from.command());
    }
  }
  _extensions_.MergeFrom(from._extensions_);
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void StartComponentRequest::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void StartComponentRequest::CopyFrom(const StartComponentRequest& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool StartComponentRequest::IsInitialized() const {


  if (!_extensions_.IsInitialized()) return false;  return true;
}

void StartComponentRequest::Swap(StartComponentRequest* other) {
  if (other != this) {
    std::swap(name_, other->name_);
    std::swap(command_, other->command_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
    _extensions_.Swap(&other->_extensions_);
  }
}

::google::protobuf::Metadata StartComponentRequest::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = StartComponentRequest_descriptor_;
  metadata.reflection = StartComponentRequest_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int StartComponentResponse::kErrFieldNumber;
const int StartComponentResponse::kPidFieldNumber;
#endif  // !_MSC_VER

StartComponentResponse::StartComponentResponse()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void StartComponentResponse::InitAsDefaultInstance() {
}

StartComponentResponse::StartComponentResponse(const StartComponentResponse& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void StartComponentResponse::SharedCtor() {
  _cached_size_ = 0;
  err_ = 0;
  pid_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

StartComponentResponse::~StartComponentResponse() {
  SharedDtor();
}

void StartComponentResponse::SharedDtor() {
  if (this != default_instance_) {
  }
}

void StartComponentResponse::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* StartComponentResponse::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return StartComponentResponse_descriptor_;
}

const StartComponentResponse& StartComponentResponse::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_amfRpc_2eproto();
  return *default_instance_;
}

StartComponentResponse* StartComponentResponse::default_instance_ = NULL;

StartComponentResponse* StartComponentResponse::New() const {
  return new StartComponentResponse;
}

void StartComponentResponse::Clear() {
  _extensions_.Clear();
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    err_ = 0;
    pid_ = 0;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool StartComponentResponse::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional int32 err = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &err_)));
          set_has_err();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(16)) goto parse_pid;
        break;
      }

      // optional int32 pid = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_pid:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &pid_)));
          set_has_pid();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectAtEnd()) return true;
        break;
      }

      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        if ((8000u <= tag)) {
          DO_(_extensions_.ParseField(tag, input, default_instance_,
                                      mutable_unknown_fields()));
          continue;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void StartComponentResponse::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional int32 err = 1;
  if (has_err()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->err(), output);
  }

  // optional int32 pid = 2;
  if (has_pid()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(2, this->pid(), output);
  }

  // Extension range [1000, 536870912)
  _extensions_.SerializeWithCachedSizes(
      1000, 536870912, output);

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* StartComponentResponse::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // optional int32 err = 1;
  if (has_err()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, this->err(), target);
  }

  // optional int32 pid = 2;
  if (has_pid()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(2, this->pid(), target);
  }

  // Extension range [1000, 536870912)
  target = _extensions_.SerializeWithCachedSizesToArray(
      1000, 536870912, target);

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int StartComponentResponse::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional int32 err = 1;
    if (has_err()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->err());
    }

    // optional int32 pid = 2;
    if (has_pid()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->pid());
    }

  }
  total_size += _extensions_.ByteSize();

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

void StartComponentResponse::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const StartComponentResponse* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const StartComponentResponse*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void StartComponentResponse::MergeFrom(const StartComponentResponse& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_err()) {
      set_err(from.err());
    }
    if (from.has_pid()) {
      set_pid(from.pid());
    }
  }
  _extensions_.MergeFrom(from._extensions_);
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void StartComponentResponse::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void StartComponentResponse::CopyFrom(const StartComponentResponse& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool StartComponentResponse::IsInitialized() const {


  if (!_extensions_.IsInitialized()) return false;  return true;
}

void StartComponentResponse::Swap(StartComponentResponse* other) {
  if (other != this) {
    std::swap(err_, other->err_);
    std::swap(pid_, other->pid_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
    _extensions_.Swap(&other->_extensions_);
  }
}

::google::protobuf::Metadata StartComponentResponse::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = StartComponentResponse_descriptor_;
  metadata.reflection = StartComponentResponse_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int StopComponentRequest::kPidFieldNumber;
#endif  // !_MSC_VER

StopComponentRequest::StopComponentRequest()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void StopComponentRequest::InitAsDefaultInstance() {
}

StopComponentRequest::StopComponentRequest(const StopComponentRequest& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void StopComponentRequest::SharedCtor() {
  _cached_size_ = 0;
  pid_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

StopComponentRequest::~StopComponentRequest() {
  SharedDtor();
}

void StopComponentRequest::SharedDtor() {
  if (this != default_instance_) {
  }
}

void StopComponentRequest::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* StopComponentRequest::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return StopComponentRequest_descriptor_;
}

const StopComponentRequest& StopComponentRequest::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_amfRpc_2eproto();
  return *default_instance_;
}

StopComponentRequest* StopComponentRequest::default_instance_ = NULL;

StopComponentRequest* StopComponentRequest::New() const {
  return new StopComponentRequest;
}

void StopComponentRequest::Clear() {
  _extensions_.Clear();
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    pid_ = 0;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool StopComponentRequest::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional int32 pid = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &pid_)));
          set_has_pid();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectAtEnd()) return true;
        break;
      }

      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        if ((8000u <= tag)) {
          DO_(_extensions_.ParseField(tag, input, default_instance_,
                                      mutable_unknown_fields()));
          continue;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void StopComponentRequest::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional int32 pid = 1;
  if (has_pid()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->pid(), output);
  }

  // Extension range [1000, 536870912)
  _extensions_.SerializeWithCachedSizes(
      1000, 536870912, output);

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* StopComponentRequest::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // optional int32 pid = 1;
  if (has_pid()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, this->pid(), target);
  }

  // Extension range [1000, 536870912)
  target = _extensions_.SerializeWithCachedSizesToArray(
      1000, 536870912, target);

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int StopComponentRequest::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional int32 pid = 1;
    if (has_pid()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->pid());
    }

  }
  total_size += _extensions_.ByteSize();

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

void StopComponentRequest::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const StopComponentRequest* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const StopComponentRequest*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void StopComponentRequest::MergeFrom(const StopComponentRequest& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_pid()) {
      set_pid(from.pid());
    }
  }
  _extensions_.MergeFrom(from._extensions_);
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void StopComponentRequest::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void StopComponentRequest::CopyFrom(const StopComponentRequest& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool StopComponentRequest::IsInitialized() const {


  if (!_extensions_.IsInitialized()) return false;  return true;
}

void StopComponentRequest::Swap(StopComponentRequest* other) {
  if (other != this) {
    std::swap(pid_, other->pid_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
    _extensions_.Swap(&other->_extensions_);
  }
}

::google::protobuf::Metadata StopComponentRequest::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = StopComponentRequest_descriptor_;
  metadata.reflection = StopComponentRequest_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int StopComponentResponse::kErrFieldNumber;
#endif  // !_MSC_VER

StopComponentResponse::StopComponentResponse()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void StopComponentResponse::InitAsDefaultInstance() {
}

StopComponentResponse::StopComponentResponse(const StopComponentResponse& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void StopComponentResponse::SharedCtor() {
  _cached_size_ = 0;
  err_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

StopComponentResponse::~StopComponentResponse() {
  SharedDtor();
}

void StopComponentResponse::SharedDtor() {
  if (this != default_instance_) {
  }
}

void StopComponentResponse::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* StopComponentResponse::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return StopComponentResponse_descriptor_;
}

const StopComponentResponse& StopComponentResponse::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_amfRpc_2eproto();
  return *default_instance_;
}

StopComponentResponse* StopComponentResponse::default_instance_ = NULL;

StopComponentResponse* StopComponentResponse::New() const {
  return new StopComponentResponse;
}

void StopComponentResponse::Clear() {
  _extensions_.Clear();
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    err_ = 0;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool StopComponentResponse::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional int32 err = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &err_)));
          set_has_err();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectAtEnd()) return true;
        break;
      }

      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        if ((8000u <= tag)) {
          DO_(_extensions_.ParseField(tag, input, default_instance_,
                                      mutable_unknown_fields()));
          continue;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void StopComponentResponse::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional int32 err = 1;
  if (has_err()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->err(), output);
  }

  // Extension range [1000, 536870912)
  _extensions_.SerializeWithCachedSizes(
      1000, 536870912, output);

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* StopComponentResponse::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // optional int32 err = 1;
  if (has_err()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, this->err(), target);
  }

  // Extension range [1000, 536870912)
  target = _extensions_.SerializeWithCachedSizesToArray(
      1000, 536870912, target);

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int StopComponentResponse::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional int32 err = 1;
    if (has_err()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->err());
    }

  }
  total_size += _extensions_.ByteSize();

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

void StopComponentResponse::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const StopComponentResponse* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const StopComponentResponse*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void StopComponentResponse::MergeFrom(const StopComponentResponse& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_err()) {
      set_err(from.err());
    }
  }
  _extensions_.MergeFrom(from._extensions_);
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void StopComponentResponse::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void StopComponentResponse::CopyFrom(const StopComponentResponse& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool StopComponentResponse::IsInitialized() const {


  if (!_extensions_.IsInitialized()) return false;  return true;
}

void StopComponentResponse::Swap(StopComponentResponse* other) {
  if (other != this) {
    std::swap(err_, other->err_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
    _extensions_.Swap(&other->_extensions_);
  }
}

::google::protobuf::Metadata StopComponentResponse::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = StopComponentResponse_descriptor_;
  metadata.reflection = StopComponentResponse_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace amfRpc
}  // namespace Rpc
}  // namespace SAFplus

// @@protoc_insertion_point(global_scope)
