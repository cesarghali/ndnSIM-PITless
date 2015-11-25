/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/**
 * Copyright (c) 2011-2015  Regents of the University of California.
 *
 * This file is part of ndnSIM. See AUTHORS for complete list of ndnSIM authors and
 * contributors.
 *
 * ndnSIM is free software: you can redistribute it and/or modify it under the terms
 * of the GNU General Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any later version.
 *
 * ndnSIM is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.  See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * ndnSIM, e.g., in COPYING.md file.  If not, see <http://www.gnu.org/licenses/>.
 **/

#ifndef NDN_PITLESS_APP_H
#define NDN_PITLESS_APP_H

#include "ns3/ndnSIM/model/ndn-common.hpp"
#include "ns3/ndnSIM/model/ndn-app-face.hpp"

#include "ns3/ptr.h"
#include "ns3/callback.h"
#include "ns3/traced-callback.h"

#include "ndn-app.hpp"

namespace ns3 {

class Packet;

namespace ndn {

/**
 * \ingroup ndn
 * \defgroup ndn-apps NDN applications
 */
/**
 * @ingroup ndn-apps
 * @brief Base class that all NDN applications should be derived from.
 *
 * The class implements virtual calls onInterest, onNack, and onData
 */
class PITlessApp : public App {
public:
  static TypeId
  GetTypeId();

  /**
   * @brief Default constructor
   */
  PITlessApp();

  /**
   * @brief Method that will be called every time new Interest arrives
   * @param interest Interest header
   * @param packet   "Payload" of the interests packet. The actual payload should be zero, but
   * packet itself
   *                 may be useful to get packet tags
   */
  virtual void
  OnInterest(shared_ptr<const Interest> interest);

  /**
   * @brief Method that will be called every time new Data arrives
   * @param contentObject Data header
   * @param payload payload (potentially virtual) of the Data packet (may include packet tags of
   * original packet)
   */
  virtual void
  OnData(shared_ptr<const Data> data);

protected:
  virtual void
  DoInitialize();

  virtual void
  DoDispose();

  // inherited from Application base class. Originally they were private
  virtual void
  StartApplication(); ///< @brief Called at time specified by Start

  virtual void
  StopApplication(); ///< @brief Called at time specified by Stop
};

} // namespace ndn
} // namespace ns3

#endif // NDN_APP_H
