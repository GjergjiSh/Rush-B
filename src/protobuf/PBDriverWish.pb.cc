// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: PBDriverWish.proto

#include "PBDriverWish.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

PROTOBUF_PRAGMA_INIT_SEG
namespace PBDriverWish {
constexpr PBDriverWish::PBDriverWish(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : left_servo_(0)
  , right_servo_(0)
  , top_servo_(0){}
struct PBDriverWishDefaultTypeInternal {
  constexpr PBDriverWishDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~PBDriverWishDefaultTypeInternal() {}
  union {
    PBDriverWish _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PBDriverWishDefaultTypeInternal _PBDriverWish_default_instance_;
}  // namespace PBDriverWish
static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_PBDriverWish_2eproto[1];
static constexpr ::PROTOBUF_NAMESPACE_ID::EnumDescriptor const** file_level_enum_descriptors_PBDriverWish_2eproto = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_PBDriverWish_2eproto = nullptr;

const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_PBDriverWish_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::PBDriverWish::PBDriverWish, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::PBDriverWish::PBDriverWish, left_servo_),
  PROTOBUF_FIELD_OFFSET(::PBDriverWish::PBDriverWish, right_servo_),
  PROTOBUF_FIELD_OFFSET(::PBDriverWish::PBDriverWish, top_servo_),
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, sizeof(::PBDriverWish::PBDriverWish)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::PBDriverWish::_PBDriverWish_default_instance_),
};

const char descriptor_table_protodef_PBDriverWish_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\022PBDriverWish.proto\022\014PBDriverWish\"J\n\014PB"
  "DriverWish\022\022\n\nleft_servo\030\001 \001(\002\022\023\n\013right_"
  "servo\030\002 \001(\002\022\021\n\ttop_servo\030\003 \001(\002b\006proto3"
  ;
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_PBDriverWish_2eproto_once;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_PBDriverWish_2eproto = {
  false, false, 118, descriptor_table_protodef_PBDriverWish_2eproto, "PBDriverWish.proto", 
  &descriptor_table_PBDriverWish_2eproto_once, nullptr, 0, 1,
  schemas, file_default_instances, TableStruct_PBDriverWish_2eproto::offsets,
  file_level_metadata_PBDriverWish_2eproto, file_level_enum_descriptors_PBDriverWish_2eproto, file_level_service_descriptors_PBDriverWish_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK ::PROTOBUF_NAMESPACE_ID::Metadata
descriptor_table_PBDriverWish_2eproto_metadata_getter(int index) {
  ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&descriptor_table_PBDriverWish_2eproto);
  return descriptor_table_PBDriverWish_2eproto.file_level_metadata[index];
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY static ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptorsRunner dynamic_init_dummy_PBDriverWish_2eproto(&descriptor_table_PBDriverWish_2eproto);
namespace PBDriverWish {

// ===================================================================

class PBDriverWish::_Internal {
 public:
};

PBDriverWish::PBDriverWish(::PROTOBUF_NAMESPACE_ID::Arena* arena)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena) {
  SharedCtor();
  RegisterArenaDtor(arena);
  // @@protoc_insertion_point(arena_constructor:PBDriverWish.PBDriverWish)
}
PBDriverWish::PBDriverWish(const PBDriverWish& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::memcpy(&left_servo_, &from.left_servo_,
    static_cast<size_t>(reinterpret_cast<char*>(&top_servo_) -
    reinterpret_cast<char*>(&left_servo_)) + sizeof(top_servo_));
  // @@protoc_insertion_point(copy_constructor:PBDriverWish.PBDriverWish)
}

void PBDriverWish::SharedCtor() {
::memset(reinterpret_cast<char*>(this) + static_cast<size_t>(
    reinterpret_cast<char*>(&left_servo_) - reinterpret_cast<char*>(this)),
    0, static_cast<size_t>(reinterpret_cast<char*>(&top_servo_) -
    reinterpret_cast<char*>(&left_servo_)) + sizeof(top_servo_));
}

PBDriverWish::~PBDriverWish() {
  // @@protoc_insertion_point(destructor:PBDriverWish.PBDriverWish)
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

void PBDriverWish::SharedDtor() {
  GOOGLE_DCHECK(GetArena() == nullptr);
}

void PBDriverWish::ArenaDtor(void* object) {
  PBDriverWish* _this = reinterpret_cast< PBDriverWish* >(object);
  (void)_this;
}
void PBDriverWish::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void PBDriverWish::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void PBDriverWish::Clear() {
// @@protoc_insertion_point(message_clear_start:PBDriverWish.PBDriverWish)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  ::memset(&left_servo_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&top_servo_) -
      reinterpret_cast<char*>(&left_servo_)) + sizeof(top_servo_));
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* PBDriverWish::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // float left_servo = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 13)) {
          left_servo_ = ::PROTOBUF_NAMESPACE_ID::internal::UnalignedLoad<float>(ptr);
          ptr += sizeof(float);
        } else goto handle_unusual;
        continue;
      // float right_servo = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 21)) {
          right_servo_ = ::PROTOBUF_NAMESPACE_ID::internal::UnalignedLoad<float>(ptr);
          ptr += sizeof(float);
        } else goto handle_unusual;
        continue;
      // float top_servo = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 29)) {
          top_servo_ = ::PROTOBUF_NAMESPACE_ID::internal::UnalignedLoad<float>(ptr);
          ptr += sizeof(float);
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag,
            _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
            ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* PBDriverWish::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:PBDriverWish.PBDriverWish)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // float left_servo = 1;
  if (!(this->left_servo() <= 0 && this->left_servo() >= 0)) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteFloatToArray(1, this->_internal_left_servo(), target);
  }

  // float right_servo = 2;
  if (!(this->right_servo() <= 0 && this->right_servo() >= 0)) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteFloatToArray(2, this->_internal_right_servo(), target);
  }

  // float top_servo = 3;
  if (!(this->top_servo() <= 0 && this->top_servo() >= 0)) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteFloatToArray(3, this->_internal_top_servo(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:PBDriverWish.PBDriverWish)
  return target;
}

size_t PBDriverWish::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:PBDriverWish.PBDriverWish)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // float left_servo = 1;
  if (!(this->left_servo() <= 0 && this->left_servo() >= 0)) {
    total_size += 1 + 4;
  }

  // float right_servo = 2;
  if (!(this->right_servo() <= 0 && this->right_servo() >= 0)) {
    total_size += 1 + 4;
  }

  // float top_servo = 3;
  if (!(this->top_servo() <= 0 && this->top_servo() >= 0)) {
    total_size += 1 + 4;
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void PBDriverWish::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:PBDriverWish.PBDriverWish)
  GOOGLE_DCHECK_NE(&from, this);
  const PBDriverWish* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<PBDriverWish>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:PBDriverWish.PBDriverWish)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:PBDriverWish.PBDriverWish)
    MergeFrom(*source);
  }
}

void PBDriverWish::MergeFrom(const PBDriverWish& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:PBDriverWish.PBDriverWish)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (!(from.left_servo() <= 0 && from.left_servo() >= 0)) {
    _internal_set_left_servo(from._internal_left_servo());
  }
  if (!(from.right_servo() <= 0 && from.right_servo() >= 0)) {
    _internal_set_right_servo(from._internal_right_servo());
  }
  if (!(from.top_servo() <= 0 && from.top_servo() >= 0)) {
    _internal_set_top_servo(from._internal_top_servo());
  }
}

void PBDriverWish::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:PBDriverWish.PBDriverWish)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void PBDriverWish::CopyFrom(const PBDriverWish& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:PBDriverWish.PBDriverWish)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool PBDriverWish::IsInitialized() const {
  return true;
}

void PBDriverWish::InternalSwap(PBDriverWish* other) {
  using std::swap;
  _internal_metadata_.Swap<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(PBDriverWish, top_servo_)
      + sizeof(PBDriverWish::top_servo_)
      - PROTOBUF_FIELD_OFFSET(PBDriverWish, left_servo_)>(
          reinterpret_cast<char*>(&left_servo_),
          reinterpret_cast<char*>(&other->left_servo_));
}

::PROTOBUF_NAMESPACE_ID::Metadata PBDriverWish::GetMetadata() const {
  return GetMetadataStatic();
}


// @@protoc_insertion_point(namespace_scope)
}  // namespace PBDriverWish
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::PBDriverWish::PBDriverWish* Arena::CreateMaybeMessage< ::PBDriverWish::PBDriverWish >(Arena* arena) {
  return Arena::CreateMessageInternal< ::PBDriverWish::PBDriverWish >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
