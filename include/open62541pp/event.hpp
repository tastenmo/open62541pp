#pragma once

#include <cstdint>
#include <string_view>

#include "open62541pp/types.hpp"
#include "open62541pp/ua/nodeids.hpp"

namespace opcua {

class Server;

/**
 * Create and trigger events.
 *
 * @see https://reference.opcfoundation.org/Core/Part3/v105/docs/4.7
 * @see https://reference.opcfoundation.org/Core/Part5/v105/docs/6.4.2
 */
class Event {
public:
    /// Create an event with the underlying (abstract) node representation.
    explicit Event(Server& connection, const NodeId& eventType = ObjectTypeId::BaseEventType);

    /// Delete the node representation of the event.
    ~Event();

    Event(const Event&) = default;
    Event(Event&&) noexcept = default;

    Event& operator=(const Event&) = delete;
    Event& operator=(Event&&) noexcept = delete;

    /// Get the server instance.
    Server& connection() noexcept {
        return *connection_;
    }

    /// Get the server instance.
    const Server& connection() const noexcept {
        return *connection_;
    }

    /// Get the NodeId of the underlying node representation.
    const NodeId& id() const noexcept {
        return id_;
    }

    /// Set the source name (optional).
    Event& writeSourceName(std::string_view sourceName);

    /// Set the time of the event (UTC).
    Event& writeTime(DateTime time);

    /// Set the urgency/priority of the event from 1 (lowest) to 1000 (highest).
    Event& writeSeverity(uint16_t severity);

    /// Set a human-readable and localizable text description of the event.
    Event& writeMessage(const LocalizedText& message);

    /// Set arbitrary properties of the event (for custom event types).
    Event& writeProperty(const QualifiedName& propertyName, const Variant& value);

    /// Trigger the event.
    /// @param originId Origin node of the event (requires `EventNotifier` attribute)
    /// @return Unique `EventId` generated by server
    ByteString trigger(const NodeId& originId = ObjectId::Server);

private:
    Server* connection_;
    NodeId id_;
};

/// @relates Event
bool operator==(const Event& lhs, const Event& rhs) noexcept;

/// @relates Event
bool operator!=(const Event& lhs, const Event& rhs) noexcept;

}  // namespace opcua
