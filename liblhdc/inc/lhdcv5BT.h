#ifndef _LHDCV5BT_H_
#define _LHDCV5BT_H_

#undef LOG_TAG
#define LOG_TAG "lhdcv5BT_enc"

#define LHDC_LOGE(fmt, ...) \
  ALOGE("%s: " fmt, __func__, ##__VA_ARGS__)
#define LHDC_LOGI(fmt, ...) \
  ALOGI("%s: " fmt, __func__, ##__VA_ARGS__)
#define LHDC_LOGD(fmt, ...) \
  ALOGD("%s: " fmt, __func__, ##__VA_ARGS__)

#ifdef __cplusplus
extern "C" {
#endif

#include "lhdcv5_api.h"

//----------------------------------------------------------------
// lhdcv5BT_free_handle ()
//
// Free all resources allocated
//  Parameter
//    handle: a pointer to the resource allocated and is returned
//        by function lhdcv5BT_get_handle ()
//  Return
//    LHDCV5_FRET_SUCCESS: Succeed to free all resources
//    otherwise: Fail to free all resources
//----------------------------------------------------------------
int32_t lhdcv5BT_free_handle 
(
    HANDLE_LHDCV5_BT  handle
);

//----------------------------------------------------------------
// lhdcv5BT_get_handle ()
//
// Allocate resources required by LHDC 5.0 Encoder
//  Parameter
//    version: version defined in BT A2DP capability
//    handle: a pointer to the resource allocated
//  Return
//    LHDCV5_FRET_SUCCESS: Succeed to allocate resources
//    otherwise: Fail to allocate resources
//----------------------------------------------------------------
int32_t lhdcv5BT_get_handle 
(
    uint32_t          version,
    HANDLE_LHDCV5_BT  *handle
);

//----------------------------------------------------------------
// lhdcv5BT_set_lossless_raw_enable ()
//
// Enable lossless raw mode (only activate when lossless is enabled)
//  Parameter
//    handle: a pointer to the resource allocated and is returned
//        by function lhdcv5BT_get_handle ()
//    enable: enable(1)/disable(0)
//  Return
//    LHDCV5_FRET_SUCCESS: Succeed to allocate resources
//    otherwise: Fail to allocate resources
//----------------------------------------------------------------
int32_t lhdcv5BT_set_lossless_raw_enable
(
    HANDLE_LHDCV5_BT  handle,
    uint32_t          enabled
);

//----------------------------------------------------------------
// lhdcv5BT_get_bitrate ()
//
// Get current bitrate used during LHDC 5.0 encoding
//  Parameter
//    handle: a pointer to the resource allocated and is returned
//        by function lhdcv5BT_get_handle ()
//    bitrate: a pointer to bit rate used during LHDC 5.0 encoding,
//         range [64000, 1000000]
//  Return
//    LHDCV5_FRET_SUCCESS: Succeed to allocate resources
//    otherwise: Fail to allocate resources
//----------------------------------------------------------------
int32_t lhdcv5BT_get_bitrate
(
    HANDLE_LHDCV5_BT  handle,
    uint32_t          *bitrate
);

//----------------------------------------------------------------
// lhdcv5BT_set_bitrate ()
//
// Set the bit rate used during LHDC 5.0 encoding
//  Parameter
//    handle: a pointer to the resource allocated and is returned
//        by function lhdcBT_get_handle ()
//    bitrate_inx: an index of bit rate to set
//  Return
//    LHDCV5_FRET_SUCCESS: succeed to set the bit rate
//    Other: fail to set the bit rate
//----------------------------------------------------------------
int32_t lhdcv5BT_set_bitrate
(
    HANDLE_LHDCV5_BT  handle,
    uint32_t          bitrate_inx
);

//----------------------------------------------------------------
// lhdcv5BT_set_max_bitrate ()
//
// Set the MAX. bit rate for LHDC 5.0 encoding
//  Parameter
//    handle: a pointer to the resource allocated and is returned
//        by function lhdcBT_get_handle ()
//    max_bitrate_inx: MAX. bit rate (index) for LHDC 5.0 encoding
//  Return
//    LHDCV5_FRET_SUCCESS: succeed to set the MAX. bit rate
//    Other: fail to set the MAX. bit rate
//----------------------------------------------------------------
int32_t lhdcv5BT_set_max_bitrate
(
    HANDLE_LHDCV5_BT  handle,
    uint32_t          max_bitrate_inx
);

//----------------------------------------------------------------
// lhdcv5BT_set_min_bitrate ()
//
// Set the MIN. bit rate for LHDC 5.0 encoding
//  Parameter
//    handle: a pointer to the resource allocated and is returned
//        by function lhdcBT_get_handle ()
//    min_bitrate_inx: MIN. bit rate (index) for LHDC 5.0 encoding
//  Return
//    LHDCV5_FRET_SUCCESS: succeed to set the MIN. bit rate
//    Other: fail to set the MIN. bit rate
//----------------------------------------------------------------
int32_t lhdcv5BT_set_min_bitrate
(
    HANDLE_LHDCV5_BT  handle,
    uint32_t          min_bitrate_inx
);

//----------------------------------------------------------------
// lhdcv5BT_adjust_bitrate () - ABR
//
// Adjust bit rate automatically according to number of packets in queue for LHDC 5.0 encoding
//  Parameter
//    handle: a pointer to the resource allocated and is returned
//        by function lhdcBT_get_handle ()
//    queue_len: number of packets in queue
//  Return
//    LHDCV5_FRET_SUCCESS: succeed to adjust bit rate automatically
//    Other: fail to adjust bit rate automatically
//----------------------------------------------------------------
int32_t lhdcv5BT_adjust_bitrate
(
    HANDLE_LHDCV5_BT  handle,
    uint32_t          queueLen
);

//----------------------------------------------------------------
// lhdcv5BT_init_encoder ()
//
// Initialize LHDC 5.0 encoder
//  Parameter
//    handle: a pointer to the resource allocated and is returned
//        by function lhdcBT_get_handle ()
//    sampling_freq: sample frequency
//    bit_per_sample: bits per sample
//    bitrate_inx: bit rate index
//    mtu: BT A2DP MTU
//    interval: interval: period of time triggering LHDC 5.0 encoding in ms
//  Return
//    LHDCV5_FRET_SUCCESS: succeed to initialize
//    Other: fail to initialize.
//----------------------------------------------------------------
int32_t lhdcv5BT_init_encoder
(
    HANDLE_LHDCV5_BT  handle,
    uint32_t          sampling_freq,
    uint32_t          bits_per_sample,
    uint32_t          frame_duration,
    uint32_t          bitrate_inx,
    uint32_t          mtu,
    uint32_t          interval,
    uint32_t          is_lossless_enable
);

//----------------------------------------------------------------
// lhdcv5BT_get_block_Size ()
//
// Get number of samples per block for LHDC 5.0 encoder
//  Parameter
//    handle: a pointer to the resource allocated and is returned by function lhdcv5Bt_get_handle ()
//    samples_per_frame: number of samples per block returned
//  Return
//    LHDCV5_FRET_SUCCESS: succeed to get number of samples per block
//    Other: fail to get number of samples per block.
//----------------------------------------------------------------
int32_t lhdcv5BT_get_block_Size
(
    HANDLE_LHDCV5_BT  handle,
    uint32_t          *samples_per_frame
);

//----------------------------------------------------------------
// lhdcv5BT_encode ()
//
// Encode pcm samples by LHDC 5.0
//  Parameter
//    handle: a pointer to the resource allocated and is returned
//        by function lhdcBT_get_handle ()
//    p_in_pcm: a pointer to a buffer contains PCM samples for encoding
//    p_out_buf: a pointer to a buffer to put encoded stream
//    out_buf_bytes: output buffer's size (in byte)
//    p_out_bytes: a pointer to number of bytes of encoded stream in buffer
//    p_out_frames: a pointer to number of frames of encoded stream in buffer
//  Return
//    LHDCV5_FRET_SUCCESS: succeed to encode pcm samples
//    Other: fail to encode pcm samples
//----------------------------------------------------------------
int32_t lhdcv5BT_encode
(
    HANDLE_LHDCV5_BT  handle,
    void              *pcm_in,
    uint32_t          pcm_in_size,
    uint8_t           *out_buf,
    uint32_t          out_buf_size,
    uint32_t          *p_out_bytes,
    uint32_t          *p_out_frames
);

int32_t lhdcv5BT_set_improved_low_bitrate
(
    HANDLE_LHDCV5_BT  handle,
    uint32_t          enable
);

#ifdef __cplusplus
}
#endif

#endif /* _LHDCV5BT_H_ */
