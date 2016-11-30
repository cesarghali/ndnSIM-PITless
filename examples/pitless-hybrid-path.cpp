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

// ndn-simple.cpp

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/ndnSIM-module.h"

#include "ns3/ndnSIM/NFD/daemon/fw/pitless-strategy.hpp"

namespace ns3 {

ofstream intDelayFile;

// delay is in nanoseconds.
void
InterestForwardingDelay(size_t id, ns3::Time eventTime, float delay)
{
    intDelayFile << id << "\t" << eventTime.GetNanoSeconds() << "\t" << delay * 1000000000 << "\n";
}

ofstream contentDelayFile;

// delay is in nanoseconds.
void
ContentForwardingDelay(size_t id, ns3::Time eventTime, float delay)
{
    contentDelayFile << id << "\t" << eventTime.GetNanoSeconds() << "\t" << delay * 1000000000 << "\n";
}

ofstream rttDelayFile;

void
RTTDelayCallback(size_t id, ns3::Time eventTime, float delay, int hopCount)
{
  rttDelayFile << id << "\t" << eventTime.GetNanoSeconds() << "\t" << delay * 1000000000 << "\t" << hopCount << "\n";
}


int
main(int argc, char* argv[])
{
  // setting default parameters for PointToPoint links and channels
  Config::SetDefault("ns3::PointToPointNetDevice::DataRate", StringValue("1000Mbps"));
  Config::SetDefault("ns3::PointToPointChannel::Delay", StringValue("10ms"));
  Config::SetDefault("ns3::DropTailQueue::MaxPackets", StringValue("4294967295"));

  // Read optional command-line parameters
  int simulationTime = 1000;
  std::string intDelayFileName = "int-delays.txt";
  std::string contentDelayFileName = "content-delays.txt";
  std::string rttDelayFileName = "rtt-delays.txt";

  CommandLine cmd;
  cmd.AddValue("time", "simulation time argument", simulationTime);
  cmd.AddValue("intdelay", "delay name", intDelayFileName);
  cmd.AddValue("contentdelay", "delay name", contentDelayFileName);
  cmd.AddValue("rttdelay", "delay name", rttDelayFileName);
  cmd.Parse(argc, argv);

  intDelayFile.open(intDelayFileName);
  contentDelayFile.open(contentDelayFileName);
  rttDelayFile.open(rttDelayFileName);

  NodeContainer nodes;
  int numNodes = 3;
  nodes.Create(numNodes);

  PointToPointHelper p2p;
  for (int i = 0; i < numNodes - 1; i++) {
    p2p.Install (nodes.Get (i), nodes.Get (i + 1));
  }

  int consumerId = 0;
  int producerId = numNodes - 1;

  // Install NDN stack without cache
  ndn::StackHelper ndnHelperNoCache;
  ndnHelperNoCache.SetDefaultRoutes(true);
  ndnHelperNoCache.SetOldContentStore("ns3::ndn::cs::Nocache"); // no cache
  ndnHelperNoCache.Install(nodes.Get(consumerId));

  // Install on producer
  ndnHelperNoCache.Install(nodes.Get(producerId));

  // Install on routers with cache
  ndn::StackHelper ndnHelperWithCache;
  ndnHelperWithCache.SetDefaultRoutes(true);
  ndnHelperWithCache.SetOldContentStore("ns3::ndn::cs::Freshness::Lru", "MaxSize", "0");
  for (int i = consumerId + 1; i < producerId; i++) {
      // ndnHelperWithCache.Install(nodes.Get(i));
      // ndnHelperWithCache.InstallPITless(nodes.Get(i));

      // XXX: install bridge and set the supporting name here
      ndnHelperWithCache.InstallPITlessWithCallback(nodes.Get(i), (size_t)&InterestForwardingDelay, (size_t)&ContentForwardingDelay, i);
  }

  ndn::GlobalRoutingHelper ndnGlobalRoutingHelper;
  ndnGlobalRoutingHelper.InstallAll();

  // Consumer
  ndn::AppHelper consumerHelper("ns3::ndn::ConsumerCbr");
  consumerHelper.SetPrefix("/producer"); // Consumer will request /producer/0, /producer/1, ...
  consumerHelper.SetAttribute("Frequency", StringValue("10")); // 10 interests a second
  // consumerHelper.SetAttribute("RTTDelayCallback", UintegerValue((size_t)&RTTDelayCallback));
  // std::stringstream sstm;
  // sstm << "/consumer/" << consumerId;
  // std::string prefix = sstm.str();
  // consumerHelper.SetAttribute("SupportingName", StringValue(prefix));
  consumerHelper.Install(nodes.Get(consumerId));

  // add routable prefix to the bridge
  std:string prefix = "/router";
  ndnGlobalRoutingHelper.AddOrigins(prefix, nodes.Get(1));

  // Producer
  ndn::AppHelper producerHelper("ns3::ndn::Producer");
  producerHelper.SetPrefix("/producer");
  producerHelper.SetAttribute("PayloadSize", StringValue("1024"));
  producerHelper.Install(nodes.Get(producerId)); // last node
  ndnGlobalRoutingHelper.AddOrigins("/producer", nodes.Get(producerId));

  // Choosing forwarding strategy
  ndn::StrategyChoiceHelper::Install(nodes.Get(0), "/prefix", "/localhost/nfd/strategy/best-route");
  ndn::StrategyChoiceHelper::Install(nodes.Get(1), "/prefix", "/localhost/nfd/strategy/pitless-best-route");
  ndn::StrategyChoiceHelper::Install(nodes.Get(2), "/prefix", "/localhost/nfd/strategy/best-route");

  ndn::GlobalRoutingHelper::CalculateRoutes();

  Simulator::Stop(Seconds(simulationTime));

  Simulator::Run();
  Simulator::Destroy();

  intDelayFile.flush();
  intDelayFile.close();

  contentDelayFile.flush();
  contentDelayFile.close();

  rttDelayFile.flush();
  rttDelayFile.close();

  return 0;
}

} // namespace ns3

int
main(int argc, char* argv[])
{
  return ns3::main(argc, argv);
}
