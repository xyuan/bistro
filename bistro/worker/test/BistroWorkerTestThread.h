/*
 *  Copyright (c) 2015, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  LICENSE file in the root directory of this source tree. An additional grant
 *  of patent rights can be found in the PATENTS file in the same directory.
 *
 */
#pragma once

#include <thrift/lib/cpp/util/ScopedServerThread.h>

#include "bistro/bistro/remote/RemoteWorkerState.h"
#include "bistro/bistro/utils/TemporaryFile.h"
#include "bistro/bistro/worker/BistroWorkerHandler.h"

namespace facebook { namespace bistro {

namespace cpp2 {
  class BistroWorkerAsyncClient;
}

class ThriftMonitorTestThread;
class BistroWorkerHandler;

/**
 * Running BistroWorker service on threads for testing
 */
class BistroWorkerTestThread {
public:
  explicit BistroWorkerTestThread(BistroWorkerHandler::SchedulerClientFn);

  std::shared_ptr<cpp2::BistroWorkerAsyncClient> getClient();

  cpp2::RunningTask runTask(
    const std::string& job,
    const std::string& node,
    const std::vector<std::string>& cmd,
    cpp2::TaskSubprocessOptions subproc_opts = cpp2::TaskSubprocessOptions()
  );

  RemoteWorkerState::State getState() const;
  cpp2::BistroWorker getWorker() const;
  cpp2::BistroInstanceID getSchedulerID() const;

  void prepareSuicide();

private:
  std::shared_ptr<BistroWorkerHandler> workerPtr_;

  TemporaryDir dataDir_;
  apache::thrift::util::ScopedServerThread sst_;  // Destroy threads first
};

}}
