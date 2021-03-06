/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2005, 2006 INRIA
 * Copyright (c) 2009 MIRKO BANCHI
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Authors: Mathieu Lacage <mathieu.lacage@sophia.inria.fr>
 *          Mirko Banchi <mk.banchi@gmail.com>
 */

#ifndef MAC_LOW_TRANSMISSION_PARAMETERS_H
#define MAC_LOW_TRANSMISSION_PARAMETERS_H

#include "ns3/nstime.h"
#include "ns3/uinteger.h"

namespace ns3 {

/**
 * \brief control how a packet is transmitted.
 * \ingroup wifi
 *
 * The ns3::MacLow::StartTransmission method expects
 * an instance of this class to describe how the packet
 * should be transmitted.
 */
class MacLowTransmissionParameters
{
public:
  MacLowTransmissionParameters ();

  /**
   * Wait ACKTimeout for an ACK. If we get an ACK
   * on time, call MacLowTransmissionListener::GotAck.
   * Call MacLowTransmissionListener::MissedAck otherwise.
   */
  void EnableAck (void);
  /**
   *   - wait PIFS after end-of-tx. If idle, call
   *     MacLowTransmissionListener::MissedAck.
   *   - if busy at end-of-tx+PIFS, wait end-of-rx
   *   - if Ack ok at end-of-rx, call
   *     MacLowTransmissionListener::GotAck.
   *   - if Ack not ok at end-of-rx, report call
   *     MacLowTransmissionListener::MissedAck
   *     at end-of-rx+SIFS.
   *
   * This is really complicated but it is needed for
   * proper HCCA support.
   */
  void EnableFastAck (void);
  /**
   *  - if busy at end-of-tx+PIFS, call
   *    MacLowTransmissionListener::GotAck
   *  - if idle at end-of-tx+PIFS, call
   *    MacLowTransmissionListener::MissedAck
   */
  void EnableSuperFastAck (void);
  /**
   * Wait BASICBLOCKACKTimeout for a Basic Block Ack Response frame.
   */
  void EnableBasicBlockAck (void);
  /**
   * Wait COMPRESSEDBLOCKACKTimeout for a Compressed Block Ack Response frame.
   */
  void EnableCompressedBlockAck (void);
  /**
   * NOT IMPLEMENTED FOR NOW
   */
  void EnableMultiTidBlockAck (void);
  /**
   * Send a RTS, and wait CTSTimeout for a CTS. If we get a
   * CTS on time, call MacLowTransmissionListener::GotCts
   * and send data. Otherwise, call MacLowTransmissionListener::MissedCts
   * and do not send data.
   */
  void EnableRts (void);
  /**
   * \param size size of next data to send after current packet is
   *        sent.
   *
   * Add the transmission duration of the next data to the
   * durationId of the outgoing packet and call
   * MacLowTransmissionListener::StartNextFragment at the end of
   * the current transmission + SIFS.
   */
  void EnableNextData (uint32_t size);

  /**
   * The ongoing transmission is bounded in time.
   */
  void SetAsBoundedTransmission (void);
  /**
   * Check if the current transmission is bounded in time.
   * \return True if the current transmission is bounded in time.
   */
  bool IsTransmissionBounded (void) const;
  /**
   * SetMaximumTransmissionDuration
   * \param duration
   */
  void SetMaximumTransmissionDuration (Time duration);
  /**
   * GetMaximumTransmissionDuration
   * \return
   */
  Time GetMaximumTransmissionDuration (void) const;
  /**
   * IsCbapAccessPeriod
   * \return
   */
  bool IsCbapAccessPeriod (void) const;
  /**
   * \brief SetTransmitInSericePeriod
   */
  void SetTransmitInSericePeriod ();
  /**
   * \param durationId the value to set in the duration/Id field of
   *        the outgoing packet.
   *
   * Ignore all other durationId calculation and simply force the
   * packet's durationId field to this value.
   */
  void EnableOverrideDurationId (Time durationId);
  /**
   * Do not force the duration/id field of the packet: its
   * value is automatically calculated by the MacLow before
   * calling WifiPhy::Send.
   */
  void DisableOverrideDurationId (void);
  /**
   * \returns true if a duration/id was forced with
   *         EnableOverrideDurationId, false otherwise.
   */
  bool HasDurationId (void) const;
  /**
   * \returns the duration/id forced by EnableOverrideDurationId
   */
  Time GetDurationId (void) const;

  /**
   * Do not wait for Ack after data transmission. Typically
   * used for Broadcast and multicast frames.
   */
  void DisableAck (void);
  /**
   * Do not send rts and wait for cts before sending data.
   */
  void DisableRts (void);
  /**
   * Do not attempt to send data burst after current transmission
   */
  void DisableNextData (void);
  /**
   * \returns true if must wait for ACK after data transmission,
   *          false otherwise.
   *
   * This methods returns true when any of MustWaitNormalAck,
   * MustWaitFastAck, or MustWaitSuperFastAck return true.
   */
  bool MustWaitAck (void) const;
  /**
   * \returns true if normal ACK protocol should be used, false
   *          otherwise.
   *
   * \sa EnableAck
   */
  bool MustWaitNormalAck (void) const;
  /**
   * \returns true if fast ack protocol should be used, false
   *          otherwise.
   *
   * \sa EnableFastAck
   */
  bool MustWaitFastAck (void) const;
  /**
   * \returns true if super fast ack protocol should be used, false
   *          otherwise.
   *
   * \sa EnableSuperFastAck
   */
  bool MustWaitSuperFastAck (void) const;
  /**
   * \returns true if block ack mechanism is used, false otherwise.
   *
   * \sa EnableBlockAck
   */
  bool MustWaitBasicBlockAck (void) const;
  /**
   * \returns true if compressed block ack mechanism is used, false otherwise.
   *
   * \sa EnableCompressedBlockAck
   */
  bool MustWaitCompressedBlockAck (void) const;
  /**
   * \returns true if multi-tid block ack mechanism is used, false otherwise.
   *
   * \sa EnableMultiTidBlockAck
   */
  bool MustWaitMultiTidBlockAck (void) const;
  /**
   * \returns true if RTS should be sent and CTS waited for before
   *          sending data, false otherwise.
   */
  bool MustSendRts (void) const;
  /**
   * \returns true if EnableNextData was called, false otherwise.
   */
  bool HasNextPacket (void) const;
  /**
   * \returns the size specified by EnableNextData.
   */
  uint32_t GetNextPacketSize (void) const;

private:
  friend std::ostream &operator << (std::ostream &os, const MacLowTransmissionParameters &params);
  uint32_t m_nextSize; //!< the next size
  /// wait ack enumerated type
  enum
  {
    ACK_NONE,
    ACK_NORMAL,
    ACK_FAST,
    ACK_SUPER_FAST,
    BLOCK_ACK_BASIC,
    BLOCK_ACK_COMPRESSED,
    BLOCK_ACK_MULTI_TID
  } m_waitAck; //!< wait ack
  bool m_sendRts; //!< send an RTS?
  Time m_overrideDurationId; //!< override duration ID
  bool m_boundedTransmission;//!< Bounded transmission by time
  Time m_transmissionDuration;//!< Duration of the transmission
  bool m_transmitInServicePeriod;
};

/**
 * Serialize MacLowTransmissionParameters to ostream in a human-readable form.
 *
 * \param os std::ostream
 * \param params MacLowTransmissionParameters
 * \return std::ostream
 */
std::ostream &operator << (std::ostream &os, const MacLowTransmissionParameters &params);

} //namespace ns3

#endif /* MAC_LOW_TRANSMISSION_PARAMETERS_H */
