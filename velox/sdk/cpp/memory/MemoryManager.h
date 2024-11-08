/*
* Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H
#include "folly/json/dynamic.h"
#include "sdk/cpp/common/Global.h"


namespace facebook::velox::memory {
class MemoryPool;
}
namespace facebook::velox::sdk::memory {
class MemoryManager {
 public:
  static std::shared_ptr<MemoryManager> get();
  std::shared_ptr<velox::memory::MemoryPool> rootVeloxMemoryPool();
  std::shared_ptr<velox::memory::MemoryPool> defaultLeafVeloxMemoryPool();
  std::shared_ptr<facebook::velox::memory::MemoryPool> createQueryPool(
      const std::string& queryId, int64_t bytes);
  std::shared_ptr<velox::memory::MemoryPool> vectorBatchMemoryPool();
  std::shared_ptr<velox::memory::MemoryPool> dictExecutionMemoryPool();
  std::shared_ptr<velox::memory::MemoryPool> planMemoryPool();
  folly::dynamic toJsonString(
      std::shared_ptr<velox::memory::MemoryPool> memoryPool);

  std::string memoryStatics();
};
} // namespace facebook::velox::sdk::memory

#endif // MEMORYMANAGER_H
