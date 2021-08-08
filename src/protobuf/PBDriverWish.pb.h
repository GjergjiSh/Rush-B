// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: PBDriverWish.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_PBDriverWish_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_PBDriverWish_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3009000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3009000 < PROTOBUF_MIN_PROTOC_VERSION
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
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_PBDriverWish_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_PBDriverWish_2eproto {
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
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_PBDriverWish_2eproto;
namespace PBDriverWish {
class PBDriverWish;
class PBDriverWishDefaultTypeInternal;
extern PBDriverWishDefaultTypeInternal _PBDriverWish_default_instance_;
}  // namespace PBDriverWish
PROTOBUF_NAMESPACE_OPEN
template<> ::PBDriverWish::PBDriverWish* Arena::CreateMaybeMessage<::PBDriverWish::PBDriverWish>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace PBDriverWish {

// ===================================================================

class PBDriverWish :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:PBDriverWish.PBDriverWish) */ {
 public:
  PBDriverWish();
  virtual ~PBDriverWish();

  PBDriverWish(const PBDriverWish& from);
  PBDriverWish(PBDriverWish&& from) noexcept
    : PBDriverWish() {
    *this = ::std::move(from);
  }

  inline PBDriverWish& operator=(const PBDriverWish& from) {
    CopyFrom(from);
    return *this;
  }
  inline PBDriverWish& operator=(PBDriverWish&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const PBDriverWish& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const PBDriverWish* internal_default_instance() {
    return reinterpret_cast<const PBDriverWish*>(
               &_PBDriverWish_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(PBDriverWish& a, PBDriverWish& b) {
    a.Swap(&b);
  }
  inline void Swap(PBDriverWish* other) {
    if (other == this) return;
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline PBDriverWish* New() const final {
    return CreateMaybeMessage<PBDriverWish>(nullptr);
  }

  PBDriverWish* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<PBDriverWish>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const PBDriverWish& from);
  void MergeFrom(const PBDriverWish& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  #if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  #else
  bool MergePartialFromCodedStream(
      ::PROTOBUF_NAMESPACE_ID::io::CodedInputStream* input) final;
  #endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  void SerializeWithCachedSizes(
      ::PROTOBUF_NAMESPACE_ID::io::CodedOutputStream* output) const final;
  ::PROTOBUF_NAMESPACE_ID::uint8* InternalSerializeWithCachedSizesToArray(
      ::PROTOBUF_NAMESPACE_ID::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(PBDriverWish* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "PBDriverWish.PBDriverWish";
  }
  private:
  inline ::PROTOBUF_NAMESPACE_ID::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_PBDriverWish_2eproto);
    return ::descriptor_table_PBDriverWish_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kLeftServoFieldNumber = 1,
    kRightServoFieldNumber = 2,
    kTopServoFieldNumber = 3,
  };
  // int32 left_servo = 1;
  void clear_left_servo();
  ::PROTOBUF_NAMESPACE_ID::int32 left_servo() const;
  void set_left_servo(::PROTOBUF_NAMESPACE_ID::int32 value);

  // int32 right_servo = 2;
  void clear_right_servo();
  ::PROTOBUF_NAMESPACE_ID::int32 right_servo() const;
  void set_right_servo(::PROTOBUF_NAMESPACE_ID::int32 value);

  // int32 top_servo = 3;
  void clear_top_servo();
  ::PROTOBUF_NAMESPACE_ID::int32 top_servo() const;
  void set_top_servo(::PROTOBUF_NAMESPACE_ID::int32 value);

  // @@protoc_insertion_point(class_scope:PBDriverWish.PBDriverWish)
 private:
  class _Internal;

  ::PROTOBUF_NAMESPACE_ID::internal::InternalMetadataWithArena _internal_metadata_;
  ::PROTOBUF_NAMESPACE_ID::int32 left_servo_;
  ::PROTOBUF_NAMESPACE_ID::int32 right_servo_;
  ::PROTOBUF_NAMESPACE_ID::int32 top_servo_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_PBDriverWish_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// PBDriverWish

// int32 left_servo = 1;
inline void PBDriverWish::clear_left_servo() {
  left_servo_ = 0;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 PBDriverWish::left_servo() const {
  // @@protoc_insertion_point(field_get:PBDriverWish.PBDriverWish.left_servo)
  return left_servo_;
}
inline void PBDriverWish::set_left_servo(::PROTOBUF_NAMESPACE_ID::int32 value) {
  
  left_servo_ = value;
  // @@protoc_insertion_point(field_set:PBDriverWish.PBDriverWish.left_servo)
}

// int32 right_servo = 2;
inline void PBDriverWish::clear_right_servo() {
  right_servo_ = 0;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 PBDriverWish::right_servo() const {
  // @@protoc_insertion_point(field_get:PBDriverWish.PBDriverWish.right_servo)
  return right_servo_;
}
inline void PBDriverWish::set_right_servo(::PROTOBUF_NAMESPACE_ID::int32 value) {
  
  right_servo_ = value;
  // @@protoc_insertion_point(field_set:PBDriverWish.PBDriverWish.right_servo)
}

// int32 top_servo = 3;
inline void PBDriverWish::clear_top_servo() {
  top_servo_ = 0;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 PBDriverWish::top_servo() const {
  // @@protoc_insertion_point(field_get:PBDriverWish.PBDriverWish.top_servo)
  return top_servo_;
}
inline void PBDriverWish::set_top_servo(::PROTOBUF_NAMESPACE_ID::int32 value) {
  
  top_servo_ = value;
  // @@protoc_insertion_point(field_set:PBDriverWish.PBDriverWish.top_servo)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace PBDriverWish

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_PBDriverWish_2eproto
