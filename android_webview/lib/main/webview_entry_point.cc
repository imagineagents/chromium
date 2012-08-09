// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "android_webview/lib/main/webview_main_delegate.h"
#include "base/android/jni_android.h"
#include "content/public/app/android_library_loader_hooks.h"
#include "content/public/app/content_main.h"

// This is called by the VM when the shared library is first loaded.
// Most of the initialization is done in LibraryLoadedOnMainThread(), not here.
JNI_EXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved) {
  base::android::InitVM(vm);
  JNIEnv* env = base::android::AttachCurrentThread();
  if (!content::RegisterLibraryLoaderEntryHook(env)) {
    return -1;
  }

  content::SetContentMainDelegate(new android_webview::WebViewMainDelegate());

  return JNI_VERSION_1_4;
}
