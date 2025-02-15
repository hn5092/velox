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

#pragma once

#include <pybind11/embed.h>

namespace facebook::velox::py {

/// Register hive connector using a given `connectorId` and connector `configs`.
void registerHive(
    const std::string& connectorId,
    std::unordered_map<std::string, std::string> configs = {});

/// Register tpch connector using a given `connectorId` and connector `configs`.
void registerTpch(
    const std::string& connectorId,
    std::unordered_map<std::string, std::string> configs = {});

/// Unregister a connector.
void unregister(const std::string& connectorId);

/// Unregister all connectors that have been registered by this module.
void unregisterAll();

} // namespace facebook::velox::py
