// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.

#pragma once

#include "export.h"
#include "mrs_errors.h"
#include "interop_api.h"
#include "../src/log_helpers.h"

extern "C" {

using mrsResult = Microsoft::MixedReality::WebRTC::Result;
using mrsNativeVideoHandle = mrsObjectHandle;

//
// Native rendering
//

enum class VideoKind : int32_t {
  kNone = 0,
  kI420 = 1,
  kARGB = 2,
};

struct TextureDesc {
  void* texture{nullptr};
  int width{0};
  int height{0};
};

/// Signature of rendering method called by Unity.
typedef void(MR_UNITYPLUGIN__CALL* VideoRenderMethod)();

/// Create a native renderer and return a handle to it.
MR_UNITYPLUGIN__API mrsNativeVideoHandle MR_UNITYPLUGIN__CALL
mrsNativeRenderer_Create(mrsRemoteVideoTrackHandle videoTrackHandle) noexcept;

/// Destroy a native renderer.
MR_UNITYPLUGIN__API mrsResult MR_UNITYPLUGIN__CALL
mrsNativeRenderer_Destroy(mrsNativeVideoHandle nativeVideoHandle) noexcept;

//// Register textures for remote video and start rendering it.
//// Calling this will override anything that is currently
//// subscribed to the FrameReady call back on the VideoTrack.
MR_UNITYPLUGIN__API mrsResult MR_UNITYPLUGIN__CALL
mrsNativeRenderer_EnableRemoteVideo(mrsNativeVideoHandle nativeVideoHandle,
                                    VideoKind format,
                                    TextureDesc textures[],
                                    int textureCount) noexcept;

/// Clear remote textures and stop rendering remote video.
MR_UNITYPLUGIN__API mrsResult MR_UNITYPLUGIN__CALL
mrsNativeRenderer_DisableRemoteVideo(mrsNativeVideoHandle nativeVideoHandle) noexcept;

/// Returns the rendering method called by Unity.
MR_UNITYPLUGIN__API VideoRenderMethod MR_UNITYPLUGIN__CALL
mrsNativeRenderer_GetVideoUpdateMethod() noexcept;

//
// Utils
//

/// Pipe log entries to Unity's log.
MR_UNITYPLUGIN__API void MR_UNITYPLUGIN__CALL
mrsNativeRenderer_SetLoggingFunctions(UnityLogger::LogFunction logDebugFunc,
                                      UnityLogger::UnityLogger::LogFunction logErrorFunc,
                                      UnityLogger::LogFunction logWarningFunc);
}
