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

#define GROUP_SIZE 10
#define NUM_OF_GROUPS 16
#define NUM_OF_CONSUMERS NUM_OF_GROUPS * GROUP_SIZE
#define NUM_OF_ROUTERS 30
#define NUM_OF_PRODUCER 1
#define TOTAL_NODES NUM_OF_CONSUMERS + NUM_OF_ROUTERS + NUM_OF_PRODUCER

#define IN_ROUTERS_COUNT 13
#define OUT_ROUTERS_COUNT 17

int inRouters[IN_ROUTERS_COUNT] = {4, 7, 9, 13, 14, 15, 16, 19, 21, 22, 23, 25, 27};
int outRouters[OUT_ROUTERS_COUNT] = {0, 1, 2, 3, 5, 6, 8, 10, 11, 12, 17, 18, 20, 24, 26, 28, 29};

ofstream intDelayFile;

// delay is in nanoseconds.
void
InterestForwardingDelay(size_t id, ns3::Time eventTime, float delay)
{
    intDelayFile << id << "\t" << eventTime.GetNanoSeconds() << "\t" << delay * 1000000000 << "\n";
}

// delay is in nanoseconds.
ofstream contentDelayFile;

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

  // Creating nodes
  NodeContainer nodes;
  nodes.Create(NUM_OF_CONSUMERS + NUM_OF_ROUTERS + NUM_OF_PRODUCER);

  // Connecting nodes using two links
  // Connecting nodes using two links
  PointToPointHelper p2p;
  // Connecting consumers to edge routers
  int g = 0;
  for (int i = 0; i < GROUP_SIZE; i++, g++)
    p2p.Install (nodes.Get (g), nodes.Get (0 + NUM_OF_CONSUMERS));      // C0 <--> R0
  for (int i = 0; i < GROUP_SIZE; i++, g++)
    p2p.Install (nodes.Get (g), nodes.Get (1 + NUM_OF_CONSUMERS));      // C1 <--> R1
  for (int i = 0; i < GROUP_SIZE; i++, g++)
    p2p.Install (nodes.Get (g), nodes.Get (3 + NUM_OF_CONSUMERS));      // C2 <--> R3
  for (int i = 0; i < GROUP_SIZE; i++, g++)
    p2p.Install (nodes.Get (g), nodes.Get (5 + NUM_OF_CONSUMERS));      // C3 <--> R5
  for (int i = 0; i < GROUP_SIZE; i++, g++)
    p2p.Install (nodes.Get (g), nodes.Get (6 + NUM_OF_CONSUMERS));      // C4 <--> R6
  for (int i = 0; i < GROUP_SIZE; i++, g++)
    p2p.Install (nodes.Get (g), nodes.Get (10 + NUM_OF_CONSUMERS));     // C5 <--> R10
  for (int i = 0; i < GROUP_SIZE; i++, g++)
    p2p.Install (nodes.Get (g), nodes.Get (8 + NUM_OF_CONSUMERS));      // C6 <--> R8
  for (int i = 0; i < GROUP_SIZE; i++, g++)
    p2p.Install (nodes.Get (g), nodes.Get (11 + NUM_OF_CONSUMERS));     // C7 <--> R11
  for (int i = 0; i < GROUP_SIZE; i++, g++)
    p2p.Install (nodes.Get (g), nodes.Get (12 + NUM_OF_CONSUMERS));     // C8 <--> R12
  for (int i = 0; i < GROUP_SIZE; i++, g++)
    p2p.Install (nodes.Get (g), nodes.Get (18 + NUM_OF_CONSUMERS));     // C9 <--> R18
  for (int i = 0; i < GROUP_SIZE; i++, g++)
    p2p.Install (nodes.Get (g), nodes.Get (17 + NUM_OF_CONSUMERS));    // C10 <--> R17
  for (int i = 0; i < GROUP_SIZE; i++, g++)
    p2p.Install (nodes.Get (g), nodes.Get (20 + NUM_OF_CONSUMERS));    // C11 <--> R20
  for (int i = 0; i < GROUP_SIZE; i++, g++)
    p2p.Install (nodes.Get (g), nodes.Get (24 + NUM_OF_CONSUMERS));    // C12 <--> R24
  for (int i = 0; i < GROUP_SIZE; i++, g++)
    p2p.Install (nodes.Get (g), nodes.Get (29 + NUM_OF_CONSUMERS));    // C13 <--> R2
  for (int i = 0; i < GROUP_SIZE; i++, g++)
    p2p.Install (nodes.Get (g), nodes.Get (28 + NUM_OF_CONSUMERS));    // C14 <--> R28
  for (int i = 0; i < GROUP_SIZE; i++, g++)
    p2p.Install (nodes.Get (g), nodes.Get (21 + NUM_OF_CONSUMERS));    // C15 <--> R21

  // Connect routers
  p2p.Install (nodes.Get (0 + NUM_OF_CONSUMERS), nodes.Get (9 + NUM_OF_CONSUMERS));      // R0 <--> R9
  p2p.Install (nodes.Get (1 + NUM_OF_CONSUMERS), nodes.Get (15 + NUM_OF_CONSUMERS));     // R1 <--> R15
  p2p.Install (nodes.Get (2 + NUM_OF_CONSUMERS), nodes.Get (9 + NUM_OF_CONSUMERS));      // R2 <--> R9
  p2p.Install (nodes.Get (3 + NUM_OF_CONSUMERS), nodes.Get (4 + NUM_OF_CONSUMERS));      // R3 <--> R4
  p2p.Install (nodes.Get (4 + NUM_OF_CONSUMERS), nodes.Get (7 + NUM_OF_CONSUMERS));      // R4 <--> R7
  p2p.Install (nodes.Get (4 + NUM_OF_CONSUMERS), nodes.Get (14 + NUM_OF_CONSUMERS));     // R4 <--> R14
  p2p.Install (nodes.Get (4 + NUM_OF_CONSUMERS), nodes.Get (9 + NUM_OF_CONSUMERS));      // R4 <--> R9
  p2p.Install (nodes.Get (4 + NUM_OF_CONSUMERS), nodes.Get (16 + NUM_OF_CONSUMERS));     // R4 <--> R16
  p2p.Install (nodes.Get (4 + NUM_OF_CONSUMERS), nodes.Get (25 + NUM_OF_CONSUMERS));     // R4 <--> R25
  p2p.Install (nodes.Get (5 + NUM_OF_CONSUMERS), nodes.Get (13 + NUM_OF_CONSUMERS));     // R5 <--> R13
  p2p.Install (nodes.Get (6 + NUM_OF_CONSUMERS), nodes.Get (7 + NUM_OF_CONSUMERS));      // R6 <--> R7
  p2p.Install (nodes.Get (7 + NUM_OF_CONSUMERS), nodes.Get (9 + NUM_OF_CONSUMERS));      // R7 <--> R9
  p2p.Install (nodes.Get (7 + NUM_OF_CONSUMERS), nodes.Get (14 + NUM_OF_CONSUMERS));     // R7 <--> R14
  p2p.Install (nodes.Get (7 + NUM_OF_CONSUMERS), nodes.Get (22 + NUM_OF_CONSUMERS));     // R7 <--> R22
  p2p.Install (nodes.Get (7 + NUM_OF_CONSUMERS), nodes.Get (23 + NUM_OF_CONSUMERS));     // R7 <--> R23
  p2p.Install (nodes.Get (8 + NUM_OF_CONSUMERS), nodes.Get (9 + NUM_OF_CONSUMERS));      // R8 <--> R9
  p2p.Install (nodes.Get (9 + NUM_OF_CONSUMERS), nodes.Get (13 + NUM_OF_CONSUMERS));     // R9 <--> R13
  p2p.Install (nodes.Get (9 + NUM_OF_CONSUMERS), nodes.Get (14 + NUM_OF_CONSUMERS));     // R9 <--> R14
  p2p.Install (nodes.Get (9 + NUM_OF_CONSUMERS), nodes.Get (22 + NUM_OF_CONSUMERS));     // R9 <--> R22
  p2p.Install (nodes.Get (9 + NUM_OF_CONSUMERS), nodes.Get (25 + NUM_OF_CONSUMERS));     // R9 <--> R25
  p2p.Install (nodes.Get (9 + NUM_OF_CONSUMERS), nodes.Get (27 + NUM_OF_CONSUMERS));     // R9 <--> R27
  p2p.Install (nodes.Get (10 + NUM_OF_CONSUMERS), nodes.Get (14 + NUM_OF_CONSUMERS));    // R10 <--> R14
  p2p.Install (nodes.Get (11 + NUM_OF_CONSUMERS), nodes.Get (13 + NUM_OF_CONSUMERS));    // R11 <--> R13
  p2p.Install (nodes.Get (12 + NUM_OF_CONSUMERS), nodes.Get (13 + NUM_OF_CONSUMERS));    // R12 <--> R13
  p2p.Install (nodes.Get (13 + NUM_OF_CONSUMERS), nodes.Get (14 + NUM_OF_CONSUMERS));    // R13 <--> R14
  p2p.Install (nodes.Get (13 + NUM_OF_CONSUMERS), nodes.Get (22 + NUM_OF_CONSUMERS));    // R13 <--> R22
  p2p.Install (nodes.Get (13 + NUM_OF_CONSUMERS), nodes.Get (25 + NUM_OF_CONSUMERS));    // R13 <--> R25
  p2p.Install (nodes.Get (13 + NUM_OF_CONSUMERS), nodes.Get (27 + NUM_OF_CONSUMERS));    // R13 <--> R27
  p2p.Install (nodes.Get (14 + NUM_OF_CONSUMERS), nodes.Get (15 + NUM_OF_CONSUMERS));    // R14 <--> R15
  p2p.Install (nodes.Get (14 + NUM_OF_CONSUMERS), nodes.Get (18 + NUM_OF_CONSUMERS));    // R14 <--> R18
  p2p.Install (nodes.Get (14 + NUM_OF_CONSUMERS), nodes.Get (19 + NUM_OF_CONSUMERS));    // R14 <--> R19
  p2p.Install (nodes.Get (15 + NUM_OF_CONSUMERS), nodes.Get (16 + NUM_OF_CONSUMERS));    // R15 <--> R16
  p2p.Install (nodes.Get (15 + NUM_OF_CONSUMERS), nodes.Get (19 + NUM_OF_CONSUMERS));    // R15 <--> R19
  p2p.Install (nodes.Get (15 + NUM_OF_CONSUMERS), nodes.Get (21 + NUM_OF_CONSUMERS));    // R15 <--> R21
  p2p.Install (nodes.Get (15 + NUM_OF_CONSUMERS), nodes.Get (22 + NUM_OF_CONSUMERS));    // R15 <--> R22
  p2p.Install (nodes.Get (15 + NUM_OF_CONSUMERS), nodes.Get (23 + NUM_OF_CONSUMERS));    // R15 <--> R23
  p2p.Install (nodes.Get (15 + NUM_OF_CONSUMERS), nodes.Get (25 + NUM_OF_CONSUMERS));    // R15 <--> R25
  p2p.Install (nodes.Get (15 + NUM_OF_CONSUMERS), nodes.Get (27 + NUM_OF_CONSUMERS));    // R15 <--> R27
  p2p.Install (nodes.Get (16 + NUM_OF_CONSUMERS), nodes.Get (23 + NUM_OF_CONSUMERS));    // R16 <--> R23
  p2p.Install (nodes.Get (16 + NUM_OF_CONSUMERS), nodes.Get (27 + NUM_OF_CONSUMERS));    // R16 <--> R27
  p2p.Install (nodes.Get (17 + NUM_OF_CONSUMERS), nodes.Get (23 + NUM_OF_CONSUMERS));    // R17 <--> R23
  // 18 done
  p2p.Install (nodes.Get (19 + NUM_OF_CONSUMERS), nodes.Get (22 + NUM_OF_CONSUMERS));    // R19 <--> R22
  p2p.Install (nodes.Get (20 + NUM_OF_CONSUMERS), nodes.Get (25 + NUM_OF_CONSUMERS));    // R20 <--> R25
  p2p.Install (nodes.Get (21 + NUM_OF_CONSUMERS), nodes.Get (22 + NUM_OF_CONSUMERS));    // R21 <--> R22
  p2p.Install (nodes.Get (21 + NUM_OF_CONSUMERS), nodes.Get (27 + NUM_OF_CONSUMERS));    // R21 <--> R27
  p2p.Install (nodes.Get (22 + NUM_OF_CONSUMERS), nodes.Get (23 + NUM_OF_CONSUMERS));    // R22 <--> R23
  p2p.Install (nodes.Get (22 + NUM_OF_CONSUMERS), nodes.Get (28 + NUM_OF_CONSUMERS));    // R22 <--> R28
  p2p.Install (nodes.Get (22 + NUM_OF_CONSUMERS), nodes.Get (29 + NUM_OF_CONSUMERS));    // R22 <--> R29
  p2p.Install (nodes.Get (23 + NUM_OF_CONSUMERS), nodes.Get (24 + NUM_OF_CONSUMERS));    // R23 <--> R24
  p2p.Install (nodes.Get (23 + NUM_OF_CONSUMERS), nodes.Get (25 + NUM_OF_CONSUMERS));    // R23 <--> R25
  p2p.Install (nodes.Get (23 + NUM_OF_CONSUMERS), nodes.Get (27 + NUM_OF_CONSUMERS));    // R23 <--> R27
  // 24 done
  // 25 done
  p2p.Install (nodes.Get (26 + NUM_OF_CONSUMERS), nodes.Get (27 + NUM_OF_CONSUMERS));    // R26 <--> R27
  // 27 done
  // 28 done
  // 29 done

    // Connecting producer(s)
    int producerId = 0 + NUM_OF_CONSUMERS + NUM_OF_ROUTERS;
    p2p.Install (nodes.Get (producerId), nodes.Get (0 + NUM_OF_CONSUMERS));      // P0 <--> R0

    // Install NDN stack without cache
    ndn::StackHelper ndnHelperNoCache;
    ndnHelperNoCache.SetDefaultRoutes(true);
    ndnHelperNoCache.SetOldContentStore("ns3::ndn::cs::Nocache"); // no cache
    for (int i = 0; i < NUM_OF_CONSUMERS; i++) {
    //   ndnHelperNoCache.Install(nodes.Get(i));
      ndnHelperNoCache.InstallPITless(nodes.Get(i));
    }

    // Install on producer
    // ndnHelperNoCache.Install(nodes.Get(producerId));
    ndnHelperNoCache.InstallPITless(nodes.Get(producerId));

    // Install on routers with cache
    ndn::StackHelper ndnHelperWithCache;
    ndnHelperWithCache.SetDefaultRoutes(true);
    // ndnHelperWithCache.SetOldContentStore("ns3::ndn::cs::Freshness::Lru", "MaxSize", "0");
    ndnHelperWithCache.SetOldContentStore("ns3::ndn::cs::Nocache");
    for (int i = NUM_OF_CONSUMERS; i < NUM_OF_CONSUMERS + NUM_OF_ROUTERS; i++) {
    //   ndnHelperWithCache.Install(nodes.Get(i));
    //   ndnHelperWithCache.InstallPITless(nodes.Get(i));
      ndnHelperWithCache.InstallPITlessWithCallback(nodes.Get(i), (size_t)&InterestForwardingDelay, (size_t)&ContentForwardingDelay, i);
    }

    ndn::GlobalRoutingHelper ndnGlobalRoutingHelper;
    ndnGlobalRoutingHelper.InstallAll();

    //ndn::AppDelayTracer::InstallAll(rttDelayFileName);

    // Consumer
    ndn::AppHelper consumerHelper("ns3::ndn::PITlessConsumerCbr");
    consumerHelper.SetPrefix("/producer"); // Consumer will request /producer/0, /producer/1, ...
    consumerHelper.SetAttribute("Frequency", StringValue("10")); // 10 interests a second
    consumerHelper.SetAttribute("RTTDelayCallback", UintegerValue((size_t)&RTTDelayCallback));
    for (int i = 0; i < NUM_OF_CONSUMERS; i++) {
      std::stringstream sstm;
      sstm << "/consumer/" << i;
      std::string prefix = sstm.str();
      consumerHelper.SetAttribute("SupportingName", StringValue(prefix));
      consumerHelper.Install(nodes.Get(i));
      ndnGlobalRoutingHelper.AddOrigins(prefix, nodes.Get(i));
    }

    // Producer
    ndn::AppHelper producerHelper("ns3::ndn::PITlessProducer");
    producerHelper.SetPrefix("/producer");
    producerHelper.SetAttribute("PayloadSize", StringValue("1024"));
    producerHelper.Install(nodes.Get(producerId)); // last node
    ndnGlobalRoutingHelper.AddOrigins("/producer", nodes.Get(producerId));

    // Choosing forwarding strategy
    ndn::StrategyChoiceHelper::InstallAll("/prefix", "/localhost/nfd/strategy/pitless-best-route");

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
