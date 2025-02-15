/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "velox/common/dynamic_registry/DynamicUdf.h"

// This file defines a mock function that will be dynamically linked and
// registered. There are no restrictions as to how the function needs to be
// defined, but the library (.so) needs to provide a `void registry()` C
// function in the top-level namespace.
//
// (note the extern "C" directive to prevent the compiler from mangling the
// symbol name).

namespace facebook::velox::common::dynamicRegistry {

template <typename T>
struct DynamicFunction {
  VELOX_DEFINE_FUNCTION_TYPES(T);
  FOLLY_ALWAYS_INLINE bool call(
      out_type<Varchar>& result,
      const arg_type<Varchar>& in) {
    result = in;
    return true;
  }
};

} // namespace facebook::velox::common::dynamicRegistry

extern "C" {

void registry() {
  facebook::velox::registerFunction<
      facebook::velox::common::dynamicRegistry::DynamicFunction,
      facebook::velox::Varchar,
      facebook::velox::Varchar>({"dynamic_overload"});
}
}
