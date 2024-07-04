// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: grps.brpc.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_grps_2ebrpc_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_grps_2ebrpc_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3009000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3009002 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/service.h>
#include "grps.pb.h"
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_grps_2ebrpc_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_grps_2ebrpc_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxillaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[1]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_grps_2ebrpc_2eproto;
PROTOBUF_NAMESPACE_OPEN
PROTOBUF_NAMESPACE_CLOSE
namespace grps {
namespace protos {
namespace v1 {

// ===================================================================


// ===================================================================

class GrpsBrpcService_Stub;

class GrpsBrpcService : public ::PROTOBUF_NAMESPACE_ID::Service {
 protected:
  // This class should be treated as an abstract interface.
  inline GrpsBrpcService() {};
 public:
  virtual ~GrpsBrpcService();

  typedef GrpsBrpcService_Stub Stub;

  static const ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor* descriptor();

  virtual void Predict(::PROTOBUF_NAMESPACE_ID::RpcController* controller,
                       const ::grps::protos::v1::GrpsMessage* request,
                       ::grps::protos::v1::GrpsMessage* response,
                       ::google::protobuf::Closure* done);
  virtual void PredictByHttp(::PROTOBUF_NAMESPACE_ID::RpcController* controller,
                       const ::grps::protos::v1::EmptyGrpsMessage* request,
                       ::grps::protos::v1::EmptyGrpsMessage* response,
                       ::google::protobuf::Closure* done);
  virtual void Online(::PROTOBUF_NAMESPACE_ID::RpcController* controller,
                       const ::grps::protos::v1::GrpsMessage* request,
                       ::grps::protos::v1::GrpsMessage* response,
                       ::google::protobuf::Closure* done);
  virtual void Offline(::PROTOBUF_NAMESPACE_ID::RpcController* controller,
                       const ::grps::protos::v1::GrpsMessage* request,
                       ::grps::protos::v1::GrpsMessage* response,
                       ::google::protobuf::Closure* done);
  virtual void CheckLiveness(::PROTOBUF_NAMESPACE_ID::RpcController* controller,
                       const ::grps::protos::v1::GrpsMessage* request,
                       ::grps::protos::v1::GrpsMessage* response,
                       ::google::protobuf::Closure* done);
  virtual void CheckReadiness(::PROTOBUF_NAMESPACE_ID::RpcController* controller,
                       const ::grps::protos::v1::GrpsMessage* request,
                       ::grps::protos::v1::GrpsMessage* response,
                       ::google::protobuf::Closure* done);
  virtual void ServerMetadata(::PROTOBUF_NAMESPACE_ID::RpcController* controller,
                       const ::grps::protos::v1::GrpsMessage* request,
                       ::grps::protos::v1::GrpsMessage* response,
                       ::google::protobuf::Closure* done);
  virtual void ModelMetadata(::PROTOBUF_NAMESPACE_ID::RpcController* controller,
                       const ::grps::protos::v1::GrpsMessage* request,
                       ::grps::protos::v1::GrpsMessage* response,
                       ::google::protobuf::Closure* done);

  // implements Service ----------------------------------------------

  const ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor* GetDescriptor();
  void CallMethod(const ::PROTOBUF_NAMESPACE_ID::MethodDescriptor* method,
                  ::PROTOBUF_NAMESPACE_ID::RpcController* controller,
                  const ::PROTOBUF_NAMESPACE_ID::Message* request,
                  ::PROTOBUF_NAMESPACE_ID::Message* response,
                  ::google::protobuf::Closure* done);
  const ::PROTOBUF_NAMESPACE_ID::Message& GetRequestPrototype(
    const ::PROTOBUF_NAMESPACE_ID::MethodDescriptor* method) const;
  const ::PROTOBUF_NAMESPACE_ID::Message& GetResponsePrototype(
    const ::PROTOBUF_NAMESPACE_ID::MethodDescriptor* method) const;

 private:
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(GrpsBrpcService);
};

class GrpsBrpcService_Stub : public GrpsBrpcService {
 public:
  GrpsBrpcService_Stub(::PROTOBUF_NAMESPACE_ID::RpcChannel* channel);
  GrpsBrpcService_Stub(::PROTOBUF_NAMESPACE_ID::RpcChannel* channel,
                   ::PROTOBUF_NAMESPACE_ID::Service::ChannelOwnership ownership);
  ~GrpsBrpcService_Stub();

  inline ::PROTOBUF_NAMESPACE_ID::RpcChannel* channel() { return channel_; }

  // implements GrpsBrpcService ------------------------------------------

  void Predict(::PROTOBUF_NAMESPACE_ID::RpcController* controller,
                       const ::grps::protos::v1::GrpsMessage* request,
                       ::grps::protos::v1::GrpsMessage* response,
                       ::google::protobuf::Closure* done);
  void PredictByHttp(::PROTOBUF_NAMESPACE_ID::RpcController* controller,
                       const ::grps::protos::v1::EmptyGrpsMessage* request,
                       ::grps::protos::v1::EmptyGrpsMessage* response,
                       ::google::protobuf::Closure* done);
  void Online(::PROTOBUF_NAMESPACE_ID::RpcController* controller,
                       const ::grps::protos::v1::GrpsMessage* request,
                       ::grps::protos::v1::GrpsMessage* response,
                       ::google::protobuf::Closure* done);
  void Offline(::PROTOBUF_NAMESPACE_ID::RpcController* controller,
                       const ::grps::protos::v1::GrpsMessage* request,
                       ::grps::protos::v1::GrpsMessage* response,
                       ::google::protobuf::Closure* done);
  void CheckLiveness(::PROTOBUF_NAMESPACE_ID::RpcController* controller,
                       const ::grps::protos::v1::GrpsMessage* request,
                       ::grps::protos::v1::GrpsMessage* response,
                       ::google::protobuf::Closure* done);
  void CheckReadiness(::PROTOBUF_NAMESPACE_ID::RpcController* controller,
                       const ::grps::protos::v1::GrpsMessage* request,
                       ::grps::protos::v1::GrpsMessage* response,
                       ::google::protobuf::Closure* done);
  void ServerMetadata(::PROTOBUF_NAMESPACE_ID::RpcController* controller,
                       const ::grps::protos::v1::GrpsMessage* request,
                       ::grps::protos::v1::GrpsMessage* response,
                       ::google::protobuf::Closure* done);
  void ModelMetadata(::PROTOBUF_NAMESPACE_ID::RpcController* controller,
                       const ::grps::protos::v1::GrpsMessage* request,
                       ::grps::protos::v1::GrpsMessage* response,
                       ::google::protobuf::Closure* done);
 private:
  ::PROTOBUF_NAMESPACE_ID::RpcChannel* channel_;
  bool owns_channel_;
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(GrpsBrpcService_Stub);
};


// -------------------------------------------------------------------

class MonitorService_Stub;

class MonitorService : public ::PROTOBUF_NAMESPACE_ID::Service {
 protected:
  // This class should be treated as an abstract interface.
  inline MonitorService() {};
 public:
  virtual ~MonitorService();

  typedef MonitorService_Stub Stub;

  static const ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor* descriptor();

  virtual void Metrics(::PROTOBUF_NAMESPACE_ID::RpcController* controller,
                       const ::grps::protos::v1::EmptyGrpsMessage* request,
                       ::grps::protos::v1::EmptyGrpsMessage* response,
                       ::google::protobuf::Closure* done);
  virtual void SeriesData(::PROTOBUF_NAMESPACE_ID::RpcController* controller,
                       const ::grps::protos::v1::EmptyGrpsMessage* request,
                       ::grps::protos::v1::EmptyGrpsMessage* response,
                       ::google::protobuf::Closure* done);

  // implements Service ----------------------------------------------

  const ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor* GetDescriptor();
  void CallMethod(const ::PROTOBUF_NAMESPACE_ID::MethodDescriptor* method,
                  ::PROTOBUF_NAMESPACE_ID::RpcController* controller,
                  const ::PROTOBUF_NAMESPACE_ID::Message* request,
                  ::PROTOBUF_NAMESPACE_ID::Message* response,
                  ::google::protobuf::Closure* done);
  const ::PROTOBUF_NAMESPACE_ID::Message& GetRequestPrototype(
    const ::PROTOBUF_NAMESPACE_ID::MethodDescriptor* method) const;
  const ::PROTOBUF_NAMESPACE_ID::Message& GetResponsePrototype(
    const ::PROTOBUF_NAMESPACE_ID::MethodDescriptor* method) const;

 private:
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(MonitorService);
};

class MonitorService_Stub : public MonitorService {
 public:
  MonitorService_Stub(::PROTOBUF_NAMESPACE_ID::RpcChannel* channel);
  MonitorService_Stub(::PROTOBUF_NAMESPACE_ID::RpcChannel* channel,
                   ::PROTOBUF_NAMESPACE_ID::Service::ChannelOwnership ownership);
  ~MonitorService_Stub();

  inline ::PROTOBUF_NAMESPACE_ID::RpcChannel* channel() { return channel_; }

  // implements MonitorService ------------------------------------------

  void Metrics(::PROTOBUF_NAMESPACE_ID::RpcController* controller,
                       const ::grps::protos::v1::EmptyGrpsMessage* request,
                       ::grps::protos::v1::EmptyGrpsMessage* response,
                       ::google::protobuf::Closure* done);
  void SeriesData(::PROTOBUF_NAMESPACE_ID::RpcController* controller,
                       const ::grps::protos::v1::EmptyGrpsMessage* request,
                       ::grps::protos::v1::EmptyGrpsMessage* response,
                       ::google::protobuf::Closure* done);
 private:
  ::PROTOBUF_NAMESPACE_ID::RpcChannel* channel_;
  bool owns_channel_;
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(MonitorService_Stub);
};


// -------------------------------------------------------------------

class JsService_Stub;

class JsService : public ::PROTOBUF_NAMESPACE_ID::Service {
 protected:
  // This class should be treated as an abstract interface.
  inline JsService() {};
 public:
  virtual ~JsService();

  typedef JsService_Stub Stub;

  static const ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor* descriptor();

  virtual void JqueryMinJs(::PROTOBUF_NAMESPACE_ID::RpcController* controller,
                       const ::grps::protos::v1::EmptyGrpsMessage* request,
                       ::grps::protos::v1::EmptyGrpsMessage* response,
                       ::google::protobuf::Closure* done);
  virtual void FloatMinJs(::PROTOBUF_NAMESPACE_ID::RpcController* controller,
                       const ::grps::protos::v1::EmptyGrpsMessage* request,
                       ::grps::protos::v1::EmptyGrpsMessage* response,
                       ::google::protobuf::Closure* done);

  // implements Service ----------------------------------------------

  const ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor* GetDescriptor();
  void CallMethod(const ::PROTOBUF_NAMESPACE_ID::MethodDescriptor* method,
                  ::PROTOBUF_NAMESPACE_ID::RpcController* controller,
                  const ::PROTOBUF_NAMESPACE_ID::Message* request,
                  ::PROTOBUF_NAMESPACE_ID::Message* response,
                  ::google::protobuf::Closure* done);
  const ::PROTOBUF_NAMESPACE_ID::Message& GetRequestPrototype(
    const ::PROTOBUF_NAMESPACE_ID::MethodDescriptor* method) const;
  const ::PROTOBUF_NAMESPACE_ID::Message& GetResponsePrototype(
    const ::PROTOBUF_NAMESPACE_ID::MethodDescriptor* method) const;

 private:
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(JsService);
};

class JsService_Stub : public JsService {
 public:
  JsService_Stub(::PROTOBUF_NAMESPACE_ID::RpcChannel* channel);
  JsService_Stub(::PROTOBUF_NAMESPACE_ID::RpcChannel* channel,
                   ::PROTOBUF_NAMESPACE_ID::Service::ChannelOwnership ownership);
  ~JsService_Stub();

  inline ::PROTOBUF_NAMESPACE_ID::RpcChannel* channel() { return channel_; }

  // implements JsService ------------------------------------------

  void JqueryMinJs(::PROTOBUF_NAMESPACE_ID::RpcController* controller,
                       const ::grps::protos::v1::EmptyGrpsMessage* request,
                       ::grps::protos::v1::EmptyGrpsMessage* response,
                       ::google::protobuf::Closure* done);
  void FloatMinJs(::PROTOBUF_NAMESPACE_ID::RpcController* controller,
                       const ::grps::protos::v1::EmptyGrpsMessage* request,
                       ::grps::protos::v1::EmptyGrpsMessage* response,
                       ::google::protobuf::Closure* done);
 private:
  ::PROTOBUF_NAMESPACE_ID::RpcChannel* channel_;
  bool owns_channel_;
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(JsService_Stub);
};


// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace v1
}  // namespace protos
}  // namespace grps

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_grps_2ebrpc_2eproto
