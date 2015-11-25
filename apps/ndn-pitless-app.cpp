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

#include "ndn-pitless-app.hpp"
#include "ns3/log.h"
#include "ns3/assert.h"
#include "ns3/packet.h"

#include "model/ndn-l3-protocol.hpp"
#include "model/ndn-app-face.hpp"

NS_LOG_COMPONENT_DEFINE("ndn.PITlessApp");

namespace ns3 {
namespace ndn {

NS_OBJECT_ENSURE_REGISTERED(PITlessApp);

TypeId
PITlessApp::GetTypeId(void)
{
  static TypeId tid = TypeId("ns3::ndn::PITlessApp")
                        .SetGroupName("Ndn")
                        .SetParent<App>()
                        .AddConstructor<PITlessApp>();
  return tid;
}

PITlessApp::PITlessApp()
  : App()
{
}

void
PITlessApp::DoInitialize()
{
  App::DoInitialize();
}

void
PITlessApp::DoDispose(void)
{
  App::DoDispose();
}

void
PITlessApp::OnInterest(shared_ptr<const Interest> interest)
{
  App::OnInterest(interest);
}

void
PITlessApp::OnData(shared_ptr<const Data> data)
{
  App::OnData(data);
}

// Application Methods
void
PITlessApp::StartApplication() // Called at time specified by Start
{
  NS_LOG_FUNCTION_NOARGS();

  NS_ASSERT(m_active != true);
  m_active = true;

  NS_ASSERT_MSG(GetNode()->GetObject<L3Protocol>() != 0,
                "Ndn stack should be installed on the node " << GetNode());

  // step 1. Create a face
  m_face = std::make_shared<AppFace>(this);

  // step 2. Add face to the Ndn stack
  GetNode()->GetObject<L3Protocol>()->addFace(m_face, true);
}

void
PITlessApp::StopApplication() // Called at time specified by Stop
{
  App::StopApplication();
}

} // namespace ndn
} // namespace ns3
