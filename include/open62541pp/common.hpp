#pragma once

#include <cstdint>
#include <string_view>

#include "open62541pp/bitmask.hpp"

namespace opcua {

/// Namespace index.
/// @see https://reference.opcfoundation.org/Core/Part3/v105/docs/8.2.2
using NamespaceIndex = uint16_t;

/// Namespace with index and URI.
struct Namespace {
    NamespaceIndex index;
    std::string_view uri;
};

/// Type index of the ::UA_TYPES array.
using TypeIndex = uint16_t;

/**
 * Attribute identifiers.
 * @see UA_AttributeId
 * @see https://reference.opcfoundation.org/Core/Part3/v105/docs/5.9
 */
enum class AttributeId : int32_t {
    // clang-format off
    NodeId                  = 1,   /**< @include{doc} attributes/nodeid.dox */
    NodeClass               = 2,   /**< @include{doc} attributes/nodeclass.dox */
    BrowseName              = 3,   /**< @include{doc} attributes/browsename.dox */
    DisplayName             = 4,   /**< @include{doc} attributes/displayname.dox */
    Description             = 5,   /**< @include{doc} attributes/description.dox */
    WriteMask               = 6,   /**< @include{doc} attributes/writemask.dox */
    UserWriteMask           = 7,   /**< @include{doc} attributes/userwritemask.dox */
    IsAbstract              = 8,   /**< @include{doc} attributes/isabstract.dox */
    Symmetric               = 9,   /**< @include{doc} attributes/symmetric.dox */
    InverseName             = 10,  /**< @include{doc} attributes/inversename.dox */
    ContainsNoLoops         = 11,  /**< @include{doc} attributes/containsnoloops.dox */
    EventNotifier           = 12,  /**< @include{doc} attributes/eventnotifier.dox */
    Value                   = 13,  /**< @include{doc} attributes/value.dox */
    DataType                = 14,  /**< @include{doc} attributes/datatype.dox */
    ValueRank               = 15,  /**< @include{doc} attributes/valuerank.dox */
    ArrayDimensions         = 16,  /**< @include{doc} attributes/arraydimensions.dox */
    AccessLevel             = 17,  /**< @include{doc} attributes/accesslevel.dox */
    UserAccessLevel         = 18,  /**< @include{doc} attributes/useraccesslevel.dox */
    MinimumSamplingInterval = 19,  /**< @include{doc} attributes/minimumsamplinginterval.dox */
    Historizing             = 20,  /**< @include{doc} attributes/historizing.dox */
    Executable              = 21,  /**< @include{doc} attributes/executable.dox */
    UserExecutable          = 22,  /**< @include{doc} attributes/userexecutable.dox */
    DataTypeDefinition      = 23,  /**< @include{doc} attributes/datatypedefinition.dox */
    RolePermissions         = 24,  /**< @include{doc} attributes/rolepermissions.dox */
    UserRolePermissions     = 25,  /**< @include{doc} attributes/userrolepermissions.dox */
    AccessRestrictions      = 26,  /**< @include{doc} attributes/accessrestrictions.dox */
    AccessLevelEx           = 27,  /**< @include{doc} attributes/accesslevelex.dox */
    // clang-format on
};

/**
 * Node class.
 *
 * The enum can be used as a bitmask and allows bitwise operations, e.g.:
 * @code
 * auto mask = NodeClass::Object | NodeClass::Variable;
 * @endcode
 *
 * @see UA_NodeClass
 * @see https://reference.opcfoundation.org/Core/Part3/v105/docs/8.29
 */
enum class NodeClass : int32_t {
    // clang-format off
    Unspecified   = 0,
    Object        = 1,
    Variable      = 2,
    Method        = 4,
    ObjectType    = 8,
    VariableType  = 16,
    ReferenceType = 32,
    DataType      = 64,
    View          = 128,
    // clang-format on
};

template <>
struct IsBitmaskEnum<NodeClass> : std::true_type {};

/**
 * Access level.
 * Indicates how the value of an variable can be accessed (read/write) and if it contains current
 * and/or historic data.
 * @see https://reference.opcfoundation.org/Core/Part3/v104/docs/8.57
 */
enum class AccessLevel : uint8_t {
    // clang-format off
    None           = 0U,
    CurrentRead    = 1U << 0U,
    CurrentWrite   = 1U << 1U,
    HistoryRead    = 1U << 2U,
    HistoryWrite   = 1U << 3U,
    SemanticChange = 1U << 4U,
    StatusWrite    = 1U << 5U,
    TimestampWrite = 1U << 6U,
    // clang-format on
};

template <>
struct IsBitmaskEnum<AccessLevel> : std::true_type {};

/**
 * Write mask.
 * Indicates which attributes of a node a writeable.
 * @see https://reference.opcfoundation.org/Core/Part3/v105/docs/5.2.7
 * @see https://reference.opcfoundation.org/Core/Part3/v105/docs/8.60
 */
enum class WriteMask : uint32_t {
    // clang-format off
    None                    = 0U,
    AccessLevel             = 1U << 0U,
    ArrayDimensions         = 1U << 1U,
    BrowseName              = 1U << 2U,
    ContainsNoLoops         = 1U << 3U,
    DataType                = 1U << 4U,
    Description             = 1U << 5U,
    DisplayName             = 1U << 6U,
    EventNotifier           = 1U << 7U,
    Executable              = 1U << 8U,
    Historizing             = 1U << 9U,
    InverseName             = 1U << 10U,
    IsAbstract              = 1U << 11U,
    MinimumSamplingInterval = 1U << 12U,
    NodeClass               = 1U << 13U,
    NodeId                  = 1U << 14U,
    Symmetric               = 1U << 15U,
    UserAccessLevel         = 1U << 16U,
    UserExecutable          = 1U << 17U,
    UserWriteMask           = 1U << 18U,
    ValueRank               = 1U << 19U,
    WriteMask               = 1U << 20U,
    ValueForVariableType    = 1U << 21U,
    DataTypeDefinition      = 1U << 22U,
    RolePermissions         = 1U << 23U,
    AccessRestrictions      = 1U << 24U,
    AccessLevelEx           = 1U << 25U,
    // clang-format on
};

template <>
struct IsBitmaskEnum<WriteMask> : std::true_type {};

/**
 * Value rank.
 * Indicates whether the value attribute of the variable is an array and how many dimensions the
 * array has.
 * @see https://reference.opcfoundation.org/Core/Part3/v105/docs/5.6.2
 */
enum class ValueRank : int32_t {
    // clang-format off
    ScalarOrOneDimension = -3,  // UA_VALUERANK_SCALAR_OR_ONE_DIMENSION
    Any                  = -2,  // UA_VALUERANK_ANY
    Scalar               = -1,  // UA_VALUERANK_SCALAR
    OneOrMoreDimensions  = 0,   // UA_VALUERANK_ONE_OR_MORE_DIMENSIONS
    OneDimension         = 1,   // UA_VALUERANK_ONE_DIMENSION
    TwoDimensions        = 2,   // UA_VALUERANK_TWO_DIMENSIONS
    ThreeDimensions      = 3,   // UA_VALUERANK_THREE_DIMENSIONS
    // clang-format on
};

/**
 * Event notifier.
 * Indicates if a node can be used to subscribe to events or read/write historic events.
 * @see https://reference.opcfoundation.org/Core/Part3/v105/docs/8.59
 */
enum class EventNotifier : uint8_t {
    // clang-format off
    None              = 0,
    SubscribeToEvents = 1,
    HistoryRead       = 4,
    HistoryWrite      = 8,
    // clang-format on
};

template <>
struct IsBitmaskEnum<EventNotifier> : std::true_type {};

/**
 * Modelling rules.
 * @see https://reference.opcfoundation.org/Core/Part3/v105/docs/6.4.4
 */
enum class ModellingRule : uint16_t {
    // clang-format off
    Mandatory            = 78,     // UA_NS0ID_MODELLINGRULE_MANDATORY
    Optional             = 80,     // UA_NS0ID_MODELLINGRULE_OPTIONAL
    ExposesItsArray      = 83,     // UA_NS0ID_MODELLINGRULE_EXPOSESITSARRAY
    OptionalPlaceholder  = 11508,  // UA_NS0ID_MODELLINGRULE_OPTIONALPLACEHOLDER
    MandatoryPlaceholder = 11510,  // UA_NS0ID_MODELLINGRULE_MANDATORYPLACEHOLDER
    // clang-format on
};

}  // namespace opcua
