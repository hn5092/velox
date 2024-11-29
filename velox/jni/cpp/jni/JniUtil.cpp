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

#include "JniUtil.h"

#include "velox/jni/cpp/jni/JniCommon.h"
#include "velox/vector/BaseVector.h"

#include <sstream>
#include "glog/logging.h"

namespace facebook::velox::sdk {
bool JniUtil::jvmInited_ = false;
JavaVM* JniUtil::vm_ = nullptr;
__thread JNIEnv* JniUtil::tls_env = nullptr;

void JniUtil::Init(JavaVM* vm) {
  if (jvmInited_) {
    return;
  }
  vm_ = vm;
  jvmInited_ = true;
}

jmethodID JniUtil::getMethodID(
    JNIEnv* env,
    const std::string& className,
    const std::string& methodName,
    const std::string& sig,
    bool isStatic) {
  jmethodID methodId;
  jclass localCls = env->FindClass(className.c_str());
  //
  if (localCls == nullptr) {
    if (env->ExceptionOccurred())
      env->ExceptionDescribe();
  }
  VELOX_CHECK_NOT_NULL(localCls, "Failed to find JniUtil class.");
  //
  auto gloableCls = reinterpret_cast<jclass>(env->NewGlobalRef(localCls));
  if (gloableCls == nullptr) {
    if (env->ExceptionOccurred())
      env->ExceptionDescribe();
  }
  VELOX_CHECK_NOT_NULL(localCls, "Failed to find JniUtil class.");
  env->DeleteLocalRef(localCls);
  if (env->ExceptionOccurred()) {
    env->ExceptionDescribe();
  }
  VELOX_CHECK(
      !env->ExceptionOccurred(),
      "Failed to delete local reference to JniUtil class.");
  if (isStatic) {
    methodId = env->GetStaticMethodID(
        gloableCls,
        methodName.c_str(),

        sig.c_str());
  } else {
    methodId = env->GetMethodID(
        gloableCls,
        methodName.c_str(),

        sig.c_str());
  }
  if (methodId == NULL) {
    if (env->ExceptionOccurred())
      env->ExceptionDescribe();
  }
  return methodId;
}

} // namespace facebook::velox::sdk
