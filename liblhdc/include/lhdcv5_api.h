/*
 ******************************************************************
 LHDC 5.0 utilities API header
 ******************************************************************
 */

#ifndef __LHDCV5_API_H__
#define __LHDCV5_API_H__

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @enum LHDCV5BT_SAMPLE_FREQ_T
 * @brief Available sample rates
 */
typedef enum __LHDCV5_SAMPLE_FREQ__
{
  LHDCV5_SR_44100HZ  =  44100,
  LHDCV5_SR_48000HZ  =  48000,
  LHDCV5_SR_96000HZ  =  96000,
  LHDCV5_SR_192000HZ = 192000,
} LHDCV5BT_SAMPLE_FREQ_T;

/**
 * @enum LHDCV5BT_SMPL_FMT_T
 * @brief Available bits depth
 */
typedef enum __LHDCV5BT_SMPL_FMT__
{
  LHDCV5BT_SMPL_FMT_S16 = 16,
  LHDCV5BT_SMPL_FMT_S24 = 24,
} LHDCV5BT_SMPL_FMT_T;

/**
 * @enum LHDCV5_SAMPLE_FRAME_T
 * @brief Number of samples in an encoder frame
 *
 * "Samples per encode frame" under frame durations and sample rates
 */
typedef enum __LHDCV5_SAMPLE_FRAME__
{
  LHDCV5_SAMPLE_FRAME_2P5MS_44100KHZ    = 120,
  LHDCV5_SAMPLE_FRAME_2P5MS_48000KHZ    = 120,
  LHDCV5_SAMPLE_FRAME_2P5MS_96000KHZ    = 240,
  LHDCV5_SAMPLE_FRAME_2P5MS_192000KHZ   = 480,

  LHDCV5_SAMPLE_FRAME_5MS_44100KHZ  = 240,
  LHDCV5_SAMPLE_FRAME_5MS_48000KHZ  = 240,
  LHDCV5_SAMPLE_FRAME_5MS_96000KHZ  = 480,
  LHDCV5_SAMPLE_FRAME_5MS_192000KHZ = 960,

  LHDCV5_SAMPLE_FRAME_10MS_44100KHZ  = 480,
  LHDCV5_SAMPLE_FRAME_10MS_48000KHZ  = 480,
  LHDCV5_SAMPLE_FRAME_10MS_96000KHZ  = 960,
  LHDCV5_SAMPLE_FRAME_10MS_192000KHZ = 1920,
  LHDCV5_MAX_SAMPLE_FRAME = 1920,
} LHDCV5_SAMPLE_FRAME_T;

/**
 * @enum LHDCV5_FRAME_DURATION_T
 * @brief Frame duration
 *
 * Encoding Frame durations (unit: 0.1 ms)
 */
typedef enum __LHDCV5_FRAME_DURATION__
{
  LHDCV5_FRAME_2P5MS = 25,
  LHDCV5_FRAME_5MS   = 50,
  LHDCV5_FRAME_10MS  = 100,
} LHDCV5_FRAME_DURATION_T;

/**
 * @enum LHDCV5_ENC_INTERVAL_T
 * @brief Encode interval/tick
 *
 * Encoding interval duration (unit: ms)
 */
typedef enum __LHDCV5_ENC_INTERVAL__
{
  LHDCV5_ENC_INTERVAL_10MS = 10,
  LHDCV5_ENC_INTERVAL_20MS = 20,
} LHDCV5_ENC_INTERVAL_T;

/**
 * @enum LHDCV5_ENC_QUALITY_MODE_T
 * @brief Audio encoding quality mode
 *
 * Mode of audio encoding quality mechanisms: fixed bitrate/adaptive bitrate
 */
typedef enum __LHDCV5_ENC_QUALITY_MODE__
{
  LHDCV5_ENC_FIXED_BITRATE = 0,
  LHDCV5_ENC_AUTO_BITRATE = 1,
} LHDCV5_ENC_QUALITY_MODE_T;

/**
 * @enum LHDCV5_QUALITY_T
 * @brief Audio encoding quality level index
 *
 * Index of audio encoding quality levels and mode control commands
 */
typedef enum __LHDCV5_QUALITY__
{
  // standard quality index (sync to UI)
  LHDCV5_QUALITY_LOW0 = 0,
  LHDCV5_QUALITY_LOW1,
  LHDCV5_QUALITY_LOW2,
  LHDCV5_QUALITY_LOW3,
  LHDCV5_QUALITY_LOW4,
  LHDCV5_QUALITY_LOW,
  LHDCV5_QUALITY_MID,
  LHDCV5_QUALITY_HIGH,
  LHDCV5_QUALITY_HIGH1,
  LHDCV5_QUALITY_HIGH2,
  LHDCV5_QUALITY_HIGH3,
  LHDCV5_QUALITY_HIGH4,
  LHDCV5_QUALITY_HIGH5,
  LHDCV5_QUALITY_AUTO,
  // end of standard (not sync to UI)
  LHDCV5_QUALITY_MIN_BITRATE = LHDCV5_QUALITY_LOW0,
  LHDCV5_QUALITY_MAX_BITRATE = LHDCV5_QUALITY_HIGH5,

  // quality mode control command
  LHDCV5_QUALITY_CTRL_RESET_ABR = 128,  //base of control command
  // end of control
  LHDCV5_QUALITY_CTRL_END,

  // always at bottom of table
  LHDCV5_QUALITY_INVALID
} LHDCV5_QUALITY_T;

/**
 * @def ABR/VBR DEFAULT BITRATE INX
 * @brief Defined default quality index of adaptive bitrate
 */
#define LHDCV5_ABR_DEFAULT_BITRATE_INX (LHDCV5_QUALITY_LOW)
#define LHDCV5_VBR_DEFAULT_BITRATE_INX (LHDCV5_QUALITY_HIGH)

/**
 * @enum LHDCV5_VERSION_T
 * @brief encoder version number
 *
 */
typedef enum __LHDCV5_VERSION__
{
  LHDCV5_VERSION_1 = 1,
  LHDCV5_VERSION_INVALID
} LHDCV5_VERSION_T;

/**
 * @enum LHDCV5_LOSSLESS_STATUS_T
 * @brief lossless encode feature enable/disable status
 *
 */
typedef enum __LHDCV5_LOSSLESS_STATUS__
{
  LHDCV5_LLESS_DISABLED = 0,
  LHDCV5_LLESS_ENABLED = 1,
} LHDCV5_LOSSLESS_STATUS_T;

/**
 * @enum LHDCV5_LOSSLESS_ON_STATUS_T
 * @brief lossless encode mode runtime ON/OFF status
 *
 */
typedef enum __LHDCV5_LOSSLESS_ON_STATUS__
{
  LHDCV5_LLESS_OFF = 0,
  LHDCV5_LLESS_ON = 1,
} LHDCV5_LOSSLESS_ON_STATUS_T;

/**
 * @enum LHDCV5_LOG_LEVEL_T
 * @brief encoder internal logging control level
 *
 */
typedef enum __LHDCV5_LOG_LEVEL__
{
  LHDCV5_LOG_LEVEL_EMERG = 0,
  LHDCV5_LOG_LEVEL_ALERT,
  LHDCV5_LOG_LEVEL_CRIT,
  LHDCV5_LOG_LEVEL_ERROR,
  LHDCV5_LOG_LEVEL_WARNING,
  LHDCV5_LOG_LEVEL_NOTICE,
  LHDCV5_LOG_LEVEL_INFO,
  LHDCV5_LOG_LEVEL_DEBUG,
  LHDCV5_LOG_LEVEL_VERBOSE,
} LHDCV5_LOG_LEVEL_T;

/**
 * @enum LHDCV5_FUNC_RET_T
 * @brief encoder function return codes
 *
 */
typedef enum __LHDCV5_FUNC_RET__
{
  LHDCV5_FRET_SUCCESS                   =     0,
  LHDCV5_FRET_INVALID_INPUT_PARAM       =    -1,
  LHDCV5_FRET_INVALID_HANDLE_CB         =    -2,
  LHDCV5_FRET_INVALID_HANDLE_PARA       =    -3,
  LHDCV5_FRET_INVALID_HANDLE_ENC        =    -4,
  LHDCV5_FRET_INVALID_HANDLE_CBUF       =    -5,
  LHDCV5_FRET_INVALID_HANDLE_AR         =    -6,
  LHDCV5_FRET_INVALID_CODEC             =    -7,
  LHDCV5_FRET_CODEC_NOT_READY           =    -8,
  LHDCV5_FRET_AR_NOT_READY              =    -9,
  LHDCV5_FRET_ERROR                     =   -10,
  LHDCV5_FRET_BUF_NOT_ENOUGH            =   -11,
} LHDCV5_FUNC_RET_T;

/**
 * @typedef HANDLE_LHDCV5_BT
 * @brief A custom type to represent (void *)
 *
 * opaque data type to encoder handle
 */
typedef void * HANDLE_LHDCV5_BT;


/*
 ******************************************************************
 LHDCV5 encoder utilities functions group
 ******************************************************************
 */

/**
 * @brief Get encoder lib version text
 *
 * @param[out] version: a pointer to char string.
 *
 * @return
 *  LHDCV5_FRET_SUCCESS: Succeed
 *  otherwise: Warning or Failure
 *
 */
int32_t lhdcv5_util_get_lib_version_string
(
    char** version
);

/**
 * @brief Register a logger(printing function) callback instance from external.
 *
 * @details
 *  To allow encoder log printing in platform independent.
 *
 * @param[in/out] cb: a pointer to the callback function of logger.
 * @param[out] msg_buf: buffer for storing the char string.
 * @param[in] buf_size: bytes of buffer size.
 * @param[in] level: an integer of log level.
 *
 * @return
 *  LHDCV5_FRET_SUCCESS: Succeed
 *  otherwise: Warning or Failure
 */
int32_t lhdcv5_util_enc_register_log_cb
(
    void  *cb,
    char  *msg_buff,
    uint32_t buf_size,
    int32_t  level
);

/**
 * @brief Reset resources in encoder handle.
 *
 * @details
 *  Cleaning data in encoder handle, this will not free the memory.
 *
 * @param[in] handle: a pointer to the handle allocated to the encoder.
 *
 * @return
 *  LHDCV5_FRET_SUCCESS: Succeed
 *  otherwise: Warning or Failure
 *
 * @note To release encoder handle, programmer must free the memory manually.
 */
int32_t lhdcv5_util_free_handle
(
    HANDLE_LHDCV5_BT  handle
);

/**
 * @brief Get the size of memory required by encoder handle.
 *
 * @param[in] version: the version of encoder, see LHDCV5_VERSION_T.
 * @param[out] mem_req_bytes: size bytes required by encoder handle.
 *
 * @return
 *  LHDCV5_FRET_SUCCESS: Succeed
 *  otherwise: Warning or Failure
 *
 */
int32_t lhdcv5_util_get_mem_req
(
    uint32_t  version,
    uint32_t  *mem_req_bytes
);

/**
 * @brief Initialize the encoder handle
 *
 * @param[in] handle: a pointer to the handle allocated to the encoder.
 * @param[in] version: the version of encoder, see LHDCV5_VERSION_T.
 * @param[in] mem_size: memory size in bytes of the input handle.
 *
 * @return
 *  LHDCV5_FRET_SUCCESS: Succeed
 *  otherwise: Warning or Failure
 *
 */
int32_t lhdcv5_util_get_handle
(
    HANDLE_LHDCV5_BT  handle,
    uint32_t  version,
    uint32_t  mem_size
);

/**
 * @brief Get the current bitrate (kbps)
 *
 * @param[in] handle: a pointer to the handle allocated to the encoder.
 * @param[out] bitrate: current bitrate (kbps).
 *
 * @return
 *  LHDCV5_FRET_SUCCESS: Succeed
 *  otherwise: Warning or Failure
 *
 */
int32_t lhdcv5_util_get_current_bitrate
(
    HANDLE_LHDCV5_BT  handle,
    uint32_t  *bitrate
);

/**
 * @brief Get the current bitrate index
 *
 * @param[in] handle: a pointer to the handle allocated to the encoder.
 * @param[out] bitrate_inx: current bitrate index.
 *
 * @return
 *  LHDCV5_FRET_SUCCESS: Succeed
 *  otherwise: Warning or Failure
 *
 */
int32_t lhdcv5_util_get_current_bitrate_inx
(
    HANDLE_LHDCV5_BT  handle,
    uint32_t  *bitrate_inx
);

/**
 * @brief Set target bitrate by the index
 *
 * @param[in] handle: a pointer to the handle allocated to the encoder.
 * @param[in] bitrate_inx: target bitrate index(not including LHDCV5_QUALITY_AUTO) to set.
 * @param[out] bitrate_inx_set: result of the set bitrate index.
 *
 * @return
 *  LHDCV5_FRET_SUCCESS: Succeed
 *  otherwise: Warning or Failure
 *
 */
int32_t lhdcv5_util_set_target_bitrate_inx
(
    HANDLE_LHDCV5_BT  handle,
    uint32_t  bitrate_inx,
    uint32_t  *bitrate_inx_set
);

/**
 * @brief Set the maximum bitrate index
 *
 * @param[in] handle: a pointer to the handle allocated to the encoder.
 * @param[in] max_bitrate_inx: target max bitrate index to set.
 * @param[out] max_bitrate_inx_set: result of the set max bitrate index.
 *
 * @return
 *  LHDCV5_FRET_SUCCESS: Succeed
 *  otherwise: Warning or Failure
 *
 */
int32_t lhdcv5_util_set_max_bitrate_inx
(
    HANDLE_LHDCV5_BT  handle,
    uint32_t  max_bitrate_inx,
    uint32_t  *max_bitrate_inx_set
);

/**
 * @brief Set the minimum bitrate index
 *
 * @param[in] handle: a pointer to the handle allocated to the encoder.
 * @param[in] min_bitrate_inx: target min bitrate index to set.
 * @param[out] min_bitrate_inx_set: result of the set min bitrate index.
 *
 * @return
 *  LHDCV5_FRET_SUCCESS: Succeed
 *  otherwise: Warning or Failure
 *
 */
int32_t lhdcv5_util_set_min_bitrate_inx
(
    HANDLE_LHDCV5_BT  handle,
    uint32_t  min_bitrate_inx,
    uint32_t  *min_bitrate_inx_set
);

/**
 * @brief Initialize the encoder for audio.
 *
 * @param[in] handle: a pointer to the handle allocated to the encoder.
 * @param[in] sampling_freq: target sample rate, ex: 48000(48KHz)
 * @param[in] bits_per_sample: bit-per-sample, ex: 16 or 24.
 * @param[in] bitrate_inx: target quality index.
 * @param[in] frame_duration: frame duration, unit of 0.1ms, ex: 50(5ms), 100(10ms).
 * @param[in] mtu: max transmitting size for an encoded packet in byte.
 * @param[in] interval: period of encoding, ex: 20(20ms).
 * @param[in] is_lossless_enable: enable/disable lossless encoding feature.
 *
 * @return
 *  LHDCV5_FRET_SUCCESS: Succeed
 *  otherwise: Warning or Failure
 *
 */
int32_t lhdcv5_util_init_encoder
(
    HANDLE_LHDCV5_BT  handle,
    uint32_t  sampling_freq,
    uint32_t  bits_per_sample,
    uint32_t  bitrate_inx,
    uint32_t  frame_duration,
    uint32_t  mtu,
    uint32_t  interval,
    uint32_t  is_lossless_enable
);

/**
 * @brief Get number of samples per encode frame.
 *
 * @param[in] handle: a pointer to the handle allocated to the encoder.
 * @param[out] block_size: number of samples per encode frame.
 *
 * @return
 *  LHDCV5_FRET_SUCCESS: Succeed
 *  otherwise: Warning or Failure
 *
 */
int32_t lhdcv5_util_get_block_Size
(
    HANDLE_LHDCV5_BT  handle,
    uint32_t  *block_size
);

/**
 * @brief Encode audio samples by encoder
 *
 * @param[in] handle: a pointer to the handle allocated to the encoder.
 * @param[in] p_pcm: a pointer to the input pcm frame buffer.
 * @param[in] pcm_in_size: size of the input pcm frame buffer.
 * @param[out] out_buf: a pointer to the output encoded frame buffer.
 * @param[in] out_buf_size: size of the output encoded frame buffer.
 * @param[out] written: total bytes of the output encoded frames.
 * @param[out] out_frame_num: total number of the output encoded frames.
 *
 * @return
 *  LHDCV5_FRET_SUCCESS: Succeed
 *  otherwise: Warning or Failure
 *
 */
int32_t lhdcv5_util_enc_process
(
    HANDLE_LHDCV5_BT  handle,
    uint8_t  *pcm_in,
    uint32_t  pcm_in_size,
    uint8_t  *out_buf,
    uint32_t  out_buf_size,
    uint32_t  *written_bytes,
    uint32_t  *out_frame_num
);

/**
 * @brief Get bitrate (kbps) from bitrate index
 *
 * @param[in] bitrate_inx: target bitrate index.
 * @param[out] bitrate: resulting bitrate(kbps).
 *
 * @return
 *  LHDCV5_FRET_SUCCESS: Succeed
 *  otherwise: Warning or Failure
 *
 */
int32_t lhdcv5_util_get_bitrate
(
    uint32_t  bitrate_inx,
    uint32_t  *bitrate
);

/**
 * @brief Get bitrate index from bitrate
 *
 * @param[in] bitrate: target bitrate (kbps).
 * @param[out] bitrate_inx: resulting bitrate index.
 *
 * @return
 *  LHDCV5_FRET_SUCCESS: Succeed
 *  otherwise: Warning or Failure
 *
 */
int32_t lhdcv5_util_get_bitrate_inx
(
    uint32_t  bitrate,
    uint32_t  *bitrate_inx
);

/**
 * @brief Set VBR lossy ratio threshold (percentage)
 *
 * @param[in] handle: a pointer to the handle allocated to the encoder.
 * @param[in] value: percentage to lossy statistics ratio threshold.
 *
 * @note if ratio of lossy frames > threshold, increase the bitrate to improve lossless level.
 *
 * @return
 *  LHDCV5_FRET_SUCCESS: Succeed
 *  otherwise: Warning or Failure
 *
 */
int32_t lhdcv5_util_set_vbr_up_th
(
    HANDLE_LHDCV5_BT  handle,
    uint32_t  value
);

/**
 * @brief Set VBR lossless ratio threshold (percentage)
 *
 * @param[in] handle: a pointer to the handle allocated to the encoder.
 * @param[in] value: percentage to lossy statistics ratio threshold.
 *
 * @note if ratio of lossless frames > threshold, decrease the bitrate to save bandwidth.
 *
 * @return
 *  LHDCV5_FRET_SUCCESS: Succeed
 *  otherwise: Warning or Failure
 *
 */
int32_t lhdcv5_util_set_vbr_dn_th
(
    HANDLE_LHDCV5_BT  handle,
    uint32_t  value
);

/**
 * @brief Set VBR lossy ratio statistics interval.
 *
 * @param[in] handle: a pointer to the handle allocated to the encoder.
 * @param[in] value: number of intervals to perform checking.
 *
 * @return
 *  LHDCV5_FRET_SUCCESS: Succeed
 *  otherwise: Warning or Failure
 *
 */
int32_t lhdcv5_util_set_vbr_up_intv
(
    HANDLE_LHDCV5_BT  handle,
    uint32_t  value
);

/**
 * @brief Set VBR lossless ratio statistics interval.
 *
 * @param[in] handle: a pointer to the handle allocated to the encoder.
 * @param[in] value: number of intervals to perform checking.
 *
 * @return
 *  LHDCV5_FRET_SUCCESS: Succeed
 *  otherwise: Warning or Failure
 *
 */
int32_t lhdcv5_util_set_vbr_dn_intv
(
    HANDLE_LHDCV5_BT  handle,
    uint32_t  value
);

/**
 * @brief Get lossless enabled or disabled.
 *
 * @param[in] handle: a pointer to the handle allocated to the encoder.
 * @param[out] enable: enabled(1) or disabled(0).
 *
 * @return
 *  LHDCV5_FRET_SUCCESS: Succeed
 *  otherwise: Warning or Failure
 *
 */
int32_t lhdcv5_util_get_lossless_enabled
(
    HANDLE_LHDCV5_BT  handle,
    uint32_t  *enable
);

/**
 * @brief Get encoding audio quality mode.
 *
 * @param[in] handle: a pointer to the handle allocated to the encoder.
 * @param[out] qm: fixed or adaptive mode, see LHDCV5_ENC_QUALITY_MODE_T.
 *
 * @return
 *  LHDCV5_FRET_SUCCESS: Succeed
 *  otherwise: Warning or Failure
 *
 */
int32_t lhdcv5_util_get_quality_mode
(
    HANDLE_LHDCV5_BT  handle,
    uint32_t  *qm
);

/**
 * @brief Get lossless runtime status ON(1)/OFF(0)
 *
 * @param[in] handle: a pointer to the handle allocated to the encoder.
 * @param[out] status: lossless runtime status: ON(1)/OFF(0).
 *
 * @return
 *  LHDCV5_FRET_SUCCESS: Succeed
 *  otherwise: Warning or Failure
 *
 */
int32_t lhdcv5_util_get_lossless_status
(
    HANDLE_LHDCV5_BT  handle,
    uint32_t  *status
);

/**
 * @brief Get lossless raw mode enabled(1)/disabled(0)
 *
 * @param[in] handle: a pointer to the handle allocated to the encoder.
 * @param[out] enable: lossless raw mode enabled(1)/disabled(0).
 *
 * @return
 *  LHDCV5_FRET_SUCCESS: Succeed
 *  otherwise: Warning or Failure
 *
 */
int32_t lhdcv5_util_get_lossless_raw_enabled
(
    HANDLE_LHDCV5_BT  handle,
    uint32_t  *enable
);

/**
 * @brief Set lossless raw mode enabled(1)/disabled(0)
 *
 * @param[in] handle: a pointer to the handle allocated to the encoder.
 * @param[out] enable: lossless raw mode enabled(1)/disabled(0).
 *
 * @return
 *  LHDCV5_FRET_SUCCESS: Succeed
 *  otherwise: Warning or Failure
 *
 */
int32_t lhdcv5_util_set_lossless_raw_enabled
(
    HANDLE_LHDCV5_BT  handle,
    uint32_t  enable
);

/**
 * @brief Set force encode(push out encoded frames in encoder buffer) enable/disable.
 *
 * @param[in] handle: a pointer to the handle allocated to the encoder.
 * @param[in] enable: force encode(1)/disabled(0).
 *
 * @note For debugging purpose only, push out all encoded frames in encoder.
 *
 * @return
 *  LHDCV5_FRET_SUCCESS: Succeed
 *  otherwise: Warning or Failure
 *
 */
int32_t lhdcv5_util_set_force_encode
(
    HANDLE_LHDCV5_BT  handle,
    uint32_t  enable
);

/**
 * @brief Perform lossless mode adaptive bitrate mechanism: VBR(Variable Bitrate)
 *
 * @param[in] handle: a pointer to the handle allocated to the encoder.
 *
 * @return
 *  LHDCV5_FRET_SUCCESS: Succeed
 *  otherwise: Warning or Failure
 *
 */
int32_t lhdcv5_util_vbr_process
(
    HANDLE_LHDCV5_BT  handle
);

/**
 * @brief Perform lossless raw mode adaptive bitrate mechanism: VBR-Plus(Variable Bitrate Plus)
 *
 * @param[in] handle: a pointer to the handle allocated to the encoder.
 *
 * @return
 *  LHDCV5_FRET_SUCCESS: Succeed
 *  otherwise: Warning or Failure
 *
 */
int32_t lhdcv5_util_vbr_plus_process
(
    HANDLE_LHDCV5_BT  handle
);

/**
 * @brief Get current MTU configuration.
 *
 * @param[in] handle: a pointer to the handle allocated to the encoder.
 * @param[out] current_mtu: current MTU size in bytes.
 *
 * @return
 *  LHDCV5_FRET_SUCCESS: Succeed
 *  otherwise: Warning or Failure
 *
 */
int32_t lhdcv5_util_get_current_mtu
(
    HANDLE_LHDCV5_BT  handle,
    uint32_t  *current_mtu
);

/**
 * @brief Set current MTU configuration.
 *
 * @param[in] handle: a pointer to the handle allocated to the encoder.
 * @param[in] target_mtu: target MTU size in bytes.
 *
 * @return
 *  LHDCV5_FRET_SUCCESS: Succeed
 *  otherwise: Warning or Failure
 *
 */
int32_t lhdcv5_util_set_current_mtu
(
    HANDLE_LHDCV5_BT  handle,
    uint32_t  target_mtu
);

/**
 * @brief Clean VBR, VBR-plus statistics - upgrade scenario.
 *
 * @param[in] handle: a pointer to the handle allocated to the encoder.
 *
 * @return
 *  LHDCV5_FRET_SUCCESS: Succeed
 *  otherwise: Warning or Failure
 *
 */
int32_t lhdcv5_util_reset_up_bitrate_vbr
(
    HANDLE_LHDCV5_BT  handle
);

/**
 * @brief Clean VBR, VBR-plus statistics - downgrade scenario.
 *
 * @param[in] handle: a pointer to the handle allocated to the encoder.
 *
 * @return
 *  LHDCV5_FRET_SUCCESS: Succeed
 *  otherwise: Warning or Failure
 *
 */
int32_t lhdcv5_util_reset_down_bitrate_vbr
(
    HANDLE_LHDCV5_BT  handle
);

/**
 * @brief Get license authentication text of encoder.
 *
 * @param[out] str_buf: a pointer to the string buffer.
 * @param[in] buf_byte_size: a pointer to the handle allocated to the encoder.
 *
 * @return
 *  LHDCV5_FRET_SUCCESS: Succeed
 *  otherwise: Warning or Failure
 *
 */
int32_t lhdcv5_util_get_lib_auth_string
(
    uint8_t  *str_buf,
    uint32_t  buf_byte_size
);

/* * *********************************************************************************
 * APIs only supported when Meta feature is enabled (default: disabled)
 * * *********************************************************************************/
/**
 * @brief Set and embed meta data (8 BYTEs) to following encoded frames
 *
 * @param[in] handle: a pointer to the handle allocated to the encoder.
 * @param[in] enable_embed_meta:
 *            1: enable to embed meta data (8 BYTEs) to next encoded frame.
 *            0: disable to embed meta data.
 * @param[in] meta_data: a pointer to a buffer contains meta data (8 BYTEs).
 * @param[in] embed_frame_cnt: number of continuous encoded frames to apply the meta data.
 *
 * @return
 *  LHDCV5_FRET_SUCCESS: Succeed
 *  otherwise: Warning or Failure
 *
 */
int32_t lhdcv5_util_meta_set_data
(
    HANDLE_LHDCV5_BT handle,
    int32_t  enable_embed_meta,
    uint8_t  *meta_data,
    int32_t  embed_frame_cnt
);

/**
 * @brief Set enabled/disabled of improved low bitrate
 *
 * @param[in] handle: a pointer to the handle allocated to the encoder.
 * @param[in] enable: improved low bitrate capability: enable(1)/disable(0).
 *
 * @return
 *  LHDCV5_FRET_SUCCESS: Succeed
 *  otherwise: Warning or Failure
 *
 */
int32_t lhdcv5_util_set_improved_low_bitrate
(
    HANDLE_LHDCV5_BT handle,
    uint32_t enable
);


#ifdef __cplusplus
}
#endif
#endif //End of __LHDCV5_API_H__
