// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_CAST_LOGGING_SIMPLE_EVENT_SUBSCRIBER_H_
#define MEDIA_CAST_LOGGING_SIMPLE_EVENT_SUBSCRIBER_H_

#include <vector>

#include "base/threading/thread_checker.h"
#include "media/cast/logging/raw_event_subscriber.h"

namespace media {
namespace cast {

// RawEventSubscriber implementation that records all incoming raw events
// in std::vector's.
// The user of this class can call the GetXXXEventsAndReset functions to get
// list of events that have acccumulated since last inovcation.
class SimpleEventSubscriber : public RawEventSubscriber {
 public:
  SimpleEventSubscriber();

  virtual ~SimpleEventSubscriber();

  // RawEventSubscriber implementations.
  virtual void OnReceiveFrameEvent(const FrameEvent& frame_event) OVERRIDE;
  virtual void OnReceivePacketEvent(const PacketEvent& packet_event) OVERRIDE;
  virtual void OnReceiveGenericEvent(const GenericEvent& generic_event)
      OVERRIDE;

  // Assigns frame events received so far to |frame_events| and clears them
  // from this object.
  void GetFrameEventsAndReset(std::vector<FrameEvent>* frame_events);

  // Assigns packet events received so far to |packet_events| and clears them
  // from this object.
  void GetPacketEventsAndReset(std::vector<PacketEvent>* packet_events);

  // Assigns generic events received so far to |generic_events| and clears them
  // from this object.
  void GetGenericEventsAndReset(std::vector<GenericEvent>* generic_events);

 private:
  std::vector<FrameEvent> frame_events_;
  std::vector<PacketEvent> packet_events_;
  std::vector<GenericEvent> generic_events_;

  // All functions must be called on the main thread.
  base::ThreadChecker thread_checker_;

  DISALLOW_COPY_AND_ASSIGN(SimpleEventSubscriber);
};

}  // namespace cast
}  // namespace media

#endif  // MEDIA_CAST_LOGGING_SIMPLE_EVENT_SUBSCRIBER_H_
