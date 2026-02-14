#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "lhdcv5BT.h"
#include "lhdcv5BT_abr.h"

#include <cutils/log.h>

#define CASE_RETURN_STR(type) \
    case type:                  \
    return #type;

// lib debug logger:
#define LHDCV5_LOG_LEVEL_CFG (LHDCV5_LOG_LEVEL_DEBUG)
static char log_buff[256] = "";
static void print_log_cb(char *msg)
{
  if (msg == NULL)
  {
    return;
  }

  ALOGI("%s", msg);
}

static const char * rate_to_string
(
    LHDCV5_QUALITY_T	q
)
{
  switch (q)
  {
    CASE_RETURN_STR(LHDCV5_QUALITY_LOW0);
    CASE_RETURN_STR(LHDCV5_QUALITY_LOW1);
    CASE_RETURN_STR(LHDCV5_QUALITY_LOW2);
    CASE_RETURN_STR(LHDCV5_QUALITY_LOW3);
    CASE_RETURN_STR(LHDCV5_QUALITY_LOW4);
    CASE_RETURN_STR(LHDCV5_QUALITY_LOW);
    CASE_RETURN_STR(LHDCV5_QUALITY_MID);
    CASE_RETURN_STR(LHDCV5_QUALITY_HIGH);
    CASE_RETURN_STR(LHDCV5_QUALITY_HIGH1);
    CASE_RETURN_STR(LHDCV5_QUALITY_HIGH2);
    CASE_RETURN_STR(LHDCV5_QUALITY_HIGH3);
    CASE_RETURN_STR(LHDCV5_QUALITY_HIGH4);
    CASE_RETURN_STR(LHDCV5_QUALITY_HIGH5);
    CASE_RETURN_STR(LHDCV5_QUALITY_AUTO);
    CASE_RETURN_STR(LHDCV5_QUALITY_CTRL_RESET_ABR);
    CASE_RETURN_STR(LHDCV5_QUALITY_CTRL_END);
    default:
      return "UNKNOW_QUALITY_INDEX";
  }
}

/*
 ******************************************************************
 LHDC library public API group
 ******************************************************************
 */

int32_t lhdcv5BT_free_handle
(
    HANDLE_LHDCV5_BT  handle
) 
{
  int32_t func_ret = LHDCV5_FRET_SUCCESS;

  if (handle == NULL)
  {
    LHDC_LOGE ("Handle is NULL!");
    func_ret = LHDCV5_FRET_INVALID_HANDLE_CB;
    goto ENC_EXIT_FUNC;
  }

  // reset resources only, not free memory
  func_ret = lhdcv5_util_free_handle (handle);
  if (func_ret < LHDCV5_FRET_SUCCESS)
  {
    LHDC_LOGE ("Fail to reset handle (%d)!", func_ret);
    func_ret = LHDCV5_FRET_ERROR;
    goto ENC_EXIT_FUNC;
  }

  // free handle memory
  if (handle)
  {
    LHDC_LOGI ("free handle %p!", handle);
    free(handle);
    handle = NULL;
  }

ENC_EXIT_FUNC:
  return func_ret;
}



int32_t lhdcv5BT_get_handle
(
    uint32_t  version,
    HANDLE_LHDCV5_BT  *handle
) 
{
  int32_t func_ret = LHDCV5_FRET_SUCCESS;
  uint32_t mem_req_bytes = 0;
  version = 1;

  HANDLE_LHDCV5_BT hLhdcBT = NULL;

  if (version != LHDCV5_VERSION_1)
  {
    LHDC_LOGE ("Invalid version (%u)!", version);
    func_ret = LHDCV5_FRET_ERROR;
    goto ENC_EXIT_FUNC;
  }

  if (handle == NULL)
  {
    LHDC_LOGE ("Input parameter is NULL!");
    func_ret = LHDCV5_FRET_INVALID_INPUT_PARAM;
    goto ENC_EXIT_FUNC;
  }

  // (debug) register a printing function for lib debug logs
  func_ret = lhdcv5_util_enc_register_log_cb(
      (void*)&print_log_cb, log_buff, 256, LHDCV5_LOG_LEVEL_CFG);
  if (func_ret < LHDCV5_FRET_SUCCESS)
  {
    LHDC_LOGE ("Fail to register logger function to lib (%d)!", func_ret);
    func_ret = LHDCV5_FRET_ERROR;
    goto ENC_EXIT_FUNC;
  }

  func_ret = lhdcv5_util_get_mem_req (
      version,
      &mem_req_bytes);
  if (func_ret < LHDCV5_FRET_SUCCESS || mem_req_bytes <= 0)
  {
    LHDC_LOGE ("Fail to get required memory size (%d)!", func_ret);
    func_ret = LHDCV5_FRET_ERROR;
    goto ENC_EXIT_FUNC;
  }

  hLhdcBT = (HANDLE_LHDCV5_BT)malloc(mem_req_bytes);
  if (hLhdcBT == NULL)
  {
    LHDC_LOGE ("Fail to allocate memory for encoder!");
    func_ret = LHDCV5_FRET_ERROR;
    goto ENC_EXIT_FUNC;
  }

  // func_ret = lhdcv5_util_get_handle (
  //     hLhdcBT,
  //     version,
  //     mem_req_bytes);
  typedef int32_t (*lhdcv5_get_handle_compat_t)(int32_t ver, void *ptr, uint32_t size);
  ALOGI("[Shimlhdc] Calling blob get_handle with SWAPPED args: ver=%d, ptr=%p", version, hLhdcBT);
  func_ret = ((lhdcv5_get_handle_compat_t)lhdcv5_util_get_handle)(
      version,       // Arg 1: Version (put x0)
      hLhdcBT,       // Arg 2: Handle Pointer (put x1)
      mem_req_bytes  // Arg 3: Size (put x2)
  );

  if (func_ret < LHDCV5_FRET_SUCCESS)
  {
    LHDC_LOGE ("Fail to get handle (%d)!", func_ret);
    free(hLhdcBT);
    func_ret = LHDCV5_FRET_ERROR;
    goto ENC_EXIT_FUNC;
  }

  *handle = hLhdcBT;

  if ((*handle) == NULL)
  {
    LHDC_LOGE ("Get handle NULL!");
    func_ret = LHDCV5_FRET_INVALID_HANDLE_CB;
    goto ENC_EXIT_FUNC;
  }

ENC_EXIT_FUNC:
  return func_ret;
}

int32_t lhdcv5BT_set_lossless_raw_enable
(
    HANDLE_LHDCV5_BT  handle,
    uint32_t          enabled
)
{
  int32_t func_ret = LHDCV5_FRET_SUCCESS;

  if (handle == NULL)
  {
    LHDC_LOGE ("Handle is NULL!");
    func_ret = LHDCV5_FRET_INVALID_HANDLE_CB;
    goto ENC_EXIT_FUNC;
  }

  if (enabled != LHDCV5_LLESS_ENABLED && enabled != LHDCV5_LLESS_DISABLED) {
    LHDC_LOGE ("invalid input!");
    func_ret = LHDCV5_FRET_INVALID_HANDLE_CB;
    goto ENC_EXIT_FUNC;
  }

  func_ret = lhdcv5_util_set_lossless_raw_enabled(handle, enabled);
  if (func_ret < LHDCV5_FRET_SUCCESS)
  {
    LHDC_LOGE ("Failed to set lossless raw mode (%d)!", func_ret);
    func_ret = LHDCV5_FRET_ERROR;
    goto ENC_EXIT_FUNC;
  }

  LHDC_LOGI ("set lossless raw mode (%u)!", enabled);

ENC_EXIT_FUNC:
  return func_ret;
}

int32_t lhdcv5BT_get_bitrate
(
    HANDLE_LHDCV5_BT  handle,
    uint32_t          *bitrate
) 
{
  int32_t func_ret = LHDCV5_FRET_SUCCESS;

  if (handle == NULL)
  {
    LHDC_LOGE ("Handle is NULL!");
    func_ret = LHDCV5_FRET_INVALID_HANDLE_CB;
    goto ENC_EXIT_FUNC;
  }

  if (bitrate == NULL)
  {
    LHDC_LOGE ("Input parameter is NULL!");
    func_ret = LHDCV5_FRET_INVALID_INPUT_PARAM;
    goto ENC_EXIT_FUNC;
  }

  func_ret = lhdcv5_util_get_current_bitrate (handle, bitrate);
  if (func_ret < LHDCV5_FRET_SUCCESS)
  {
    LHDC_LOGE ("Failed to get bit rate (%d)!", func_ret);
    func_ret = LHDCV5_FRET_ERROR;
    goto ENC_EXIT_FUNC;
  }

  LHDC_LOGI ("get current bitrate (%u)!", *bitrate);

ENC_EXIT_FUNC:
  return func_ret;
}

int32_t lhdcv5BT_set_bitrate
(
    HANDLE_LHDCV5_BT  handle,
    uint32_t          bitrate_inx
)
{
  int32_t   func_ret = LHDCV5_FRET_SUCCESS;
  uint32_t  bitrate_inx_set = LHDCV5_QUALITY_INVALID;
  uint32_t  lless_enabled = 0;

  if (handle == NULL)
  {
    LHDC_LOGE ("Handle is NULL!");
    func_ret = LHDCV5_FRET_INVALID_HANDLE_CB;
    goto ENC_EXIT_FUNC;
  }

  func_ret = lhdcv5_util_get_lossless_enabled(handle, &lless_enabled);
  if (func_ret < LHDCV5_FRET_SUCCESS)
  {
    LHDC_LOGE ("Failed to get lossless enabled (%d)!", func_ret);
    func_ret = LHDCV5_FRET_ERROR;
    goto ENC_EXIT_FUNC;
  }

  // handle standard/control index
  switch(bitrate_inx)
  {
    case LHDCV5_QUALITY_CTRL_RESET_ABR:
    {
      if (lless_enabled == 1)
      {
        bitrate_inx = LHDCV5_VBR_DEFAULT_BITRATE_INX;
      }
      else
      {
        bitrate_inx = LHDCV5_ABR_DEFAULT_BITRATE_INX;
        lhdcv5BT_autoBR_reset_abr_index();
      }

      func_ret = lhdcv5_util_set_target_bitrate_inx (
          handle,
          bitrate_inx,
          &bitrate_inx_set);
      if (func_ret < LHDCV5_FRET_SUCCESS)
      {
        LHDC_LOGE ("lhdcv5_util_set_target_bitrate_inx error (%d)!", func_ret);
        func_ret = LHDCV5_FRET_ERROR;
        goto ENC_EXIT_FUNC;
      }
    }
    break;

    case LHDCV5_QUALITY_HIGH5:
    case LHDCV5_QUALITY_HIGH4:
    case LHDCV5_QUALITY_HIGH3:
    case LHDCV5_QUALITY_HIGH2:
    case LHDCV5_QUALITY_HIGH1:
    case LHDCV5_QUALITY_HIGH:
    case LHDCV5_QUALITY_MID:
    case LHDCV5_QUALITY_LOW:
    case LHDCV5_QUALITY_LOW4:
    case LHDCV5_QUALITY_LOW3:
    case LHDCV5_QUALITY_LOW2:
    case LHDCV5_QUALITY_LOW1:
    case LHDCV5_QUALITY_LOW0:
    {
      func_ret = lhdcv5_util_set_target_bitrate_inx (
          handle,
          bitrate_inx,
          &bitrate_inx_set);
      if (func_ret < LHDCV5_FRET_SUCCESS)
      {
        LHDC_LOGE ("lhdcv5_util_set_target_bitrate_inx error (%d)!", func_ret);
        func_ret = LHDCV5_FRET_ERROR;
        goto ENC_EXIT_FUNC;
      }
    }
    break;

    case LHDCV5_QUALITY_AUTO:
    default:
    {
      LHDC_LOGE ("Not supported index (%s)", rate_to_string (bitrate_inx));
      func_ret = LHDCV5_FRET_ERROR;
      goto ENC_EXIT_FUNC;
    }
    break;
  }

  if (func_ret < LHDCV5_FRET_SUCCESS)
  {
    LHDC_LOGE ("failed to set bitrate (%d) err(%d)!", bitrate_inx, func_ret);
    func_ret = LHDCV5_FRET_ERROR;
    goto ENC_EXIT_FUNC;
  }

  LHDC_LOGI ("quality config index:(%s) -> actual bitrate index:(%s)",
      rate_to_string(bitrate_inx), rate_to_string (bitrate_inx_set));

ENC_EXIT_FUNC:
  return func_ret;
}

int32_t lhdcv5BT_set_max_bitrate
(
    HANDLE_LHDCV5_BT  handle,
    uint32_t          max_bitrate_inx
) 
{
  uint32_t max_bitrate_inx_set = LHDCV5_QUALITY_INVALID; //for return check
  int32_t func_ret = LHDCV5_FRET_SUCCESS;

  if (handle == NULL)
  {
    LHDC_LOGE ("Handle is NULL!");
    func_ret = LHDCV5_FRET_INVALID_HANDLE_CB;
    goto ENC_EXIT_FUNC;
  }

  // max_bitrate_inx policy: LOW0 ~ MAX
  if (max_bitrate_inx > LHDCV5_QUALITY_MAX_BITRATE)
  {
    LHDC_LOGE ("Invalid max bit rate index (%u)!", max_bitrate_inx);
    func_ret = LHDCV5_FRET_INVALID_INPUT_PARAM;
    goto ENC_EXIT_FUNC;
  }

  func_ret = lhdcv5_util_set_max_bitrate_inx (handle, max_bitrate_inx, &max_bitrate_inx_set);
  if (func_ret < LHDCV5_FRET_SUCCESS)
  {
    LHDC_LOGE ("failed to set max. bit rate index (%u), (%d)!", max_bitrate_inx, func_ret);
    func_ret = LHDCV5_FRET_ERROR;
    goto ENC_EXIT_FUNC;
  }

  LHDC_LOGI ("Update Max target bitrate(%s)", rate_to_string (max_bitrate_inx_set));

ENC_EXIT_FUNC:
  return func_ret;
}


int32_t lhdcv5BT_set_min_bitrate
(
    HANDLE_LHDCV5_BT  handle,
    uint32_t          min_bitrate_inx
)
{
  uint32_t  min_bitrate_inx_set = LHDCV5_QUALITY_INVALID;
  int32_t  func_ret = LHDCV5_FRET_SUCCESS;

  if (handle == NULL)
  {
    LHDC_LOGE ("Handle is NULL!");
    func_ret = LHDCV5_FRET_INVALID_HANDLE_CB;
    goto ENC_EXIT_FUNC;
  }

  // min policy:
  if (min_bitrate_inx > LHDCV5_QUALITY_MAX_BITRATE)
  {
    LHDC_LOGE ("Invalid min bit rate index (%u)!", min_bitrate_inx);
    func_ret = LHDCV5_FRET_INVALID_INPUT_PARAM;
    goto ENC_EXIT_FUNC;
  }

  func_ret = lhdcv5_util_set_min_bitrate_inx (handle, min_bitrate_inx, &min_bitrate_inx_set);
  if (func_ret < LHDCV5_FRET_SUCCESS)
  {
    LHDC_LOGE ("failed to set min. bit rate (%d)!", func_ret);
    func_ret = LHDCV5_FRET_ERROR;
    goto ENC_EXIT_FUNC;
  }

  LHDC_LOGI ("Set MinBitrate = %u (%s)", min_bitrate_inx_set,
      rate_to_string (min_bitrate_inx_set));

ENC_EXIT_FUNC:
  return func_ret;
}

// State variables for ABR
static float smoothed_queue = 0.0f;
static LHDCV5_QUALITY_T current_quality = LHDCV5_QUALITY_LOW;
static int upgrade_cooldown_counter = 0;

/**
 * Helper: Map filtered queue value to recommended quality level
 */
static LHDCV5_QUALITY_T get_target_quality(float q_val) {
    if (q_val <= 3.0f)  return LHDCV5_QUALITY_HIGH;  // 900kbps
    if (q_val <= 5.0f)  return LHDCV5_QUALITY_MID;   // 520kbps
    if (q_val <= 7.0f)  return LHDCV5_QUALITY_LOW;   // 390kbps
    if (q_val <= 9.0f)  return LHDCV5_QUALITY_LOW4;  // 320kbps
    if (q_val <= 11.0f) return LHDCV5_QUALITY_LOW3;  // 260kbps
    if (q_val <= 14.0f) return LHDCV5_QUALITY_LOW2;  // 200kbps
    if (q_val <= 17.0f) return LHDCV5_QUALITY_LOW1;  // 160kbps
    return LHDCV5_QUALITY_LOW0;                      // 130kbps
}

int32_t lhdcv5BT_adjust_bitrate(HANDLE_LHDCV5_BT handle, uint32_t raw_queue_len)
{
    int32_t func_ret = 0;
    uint32_t result_inx = 0;

    // 1. Apply EMA filtering (alpha=0.08 for high stability)
    const float alpha = 0.08f;
    smoothed_queue = (alpha * (float)raw_queue_len) + ((1.0f - alpha) * smoothed_queue);

    // 2. Calculate baseline target based on smoothed queue
    LHDCV5_QUALITY_T target_quality = get_target_quality(smoothed_queue);

    // 3. Hysteresis: Apply penalty for conservative upgrade
    if (target_quality > current_quality) {
        // Test if the link can handle +3.0 more queue pressure
        float penalized_queue = smoothed_queue + 3.0f;
        LHDCV5_QUALITY_T conservative_target = get_target_quality(penalized_queue);

        // Limit the upgrade to a more conservative level
        if (conservative_target < target_quality) {
            target_quality = conservative_target;
        }

        // Clamp to current to ensure we only move upward
        if (target_quality < current_quality) {
            target_quality = current_quality;
        }
    }

    // 4. Update cooldown timer
    if (upgrade_cooldown_counter > 0) {
        upgrade_cooldown_counter--;
    }

    // 5. Execute bitrate switching
    if (target_quality != current_quality) {

        // A. Downscale: Immediate execution, reset cooldown
        if (target_quality < current_quality) {
            func_ret = lhdcv5_util_set_target_bitrate_inx(handle, (uint32_t)target_quality, &result_inx);
            if (func_ret >= 0) {
                ALOGI("[Shim_Down] Q:%.2f, %d->%d. Reset Cool.", smoothed_queue, current_quality, target_quality);
                current_quality = target_quality;
                upgrade_cooldown_counter = 125; // 2.5s lock @ 50Hz
            }
        }

            // B. Upscale: Check if cooldown has expired
        else if (target_quality > current_quality) {
            if (upgrade_cooldown_counter == 0) {
                func_ret = lhdcv5_util_set_target_bitrate_inx(handle, (uint32_t)target_quality, &result_inx);
                if (func_ret >= 0) {
                    ALOGI("[Shim_Up] Q:%.2f, %d->%d. Cool.", smoothed_queue, current_quality, target_quality);
                    current_quality = target_quality;
                    upgrade_cooldown_counter = 50; // 1s lock to prevent rapid jumps
                }
            }
        }
    }

    // Heartbeat log: Every 2 seconds
    static int log_counter = 0;
    if (log_counter++ % 100 == 0) {
        ALOGI("[Shim_Heartbeat] Raw:%u, Sm:%.2f, Cur:%d, Cool:%d",
              raw_queue_len, smoothed_queue, current_quality, upgrade_cooldown_counter);
    }

    return func_ret;
}

int32_t lhdcv5BT_init_encoder
(
    HANDLE_LHDCV5_BT  handle,
    uint32_t      sampling_freq,
    uint32_t      bits_per_sample,
    uint32_t      arg4,
    uint32_t      arg5,
    uint32_t      mtu,
    uint32_t      interval,
    uint32_t      is_lossless_enable
)
{
  int32_t func_ret = LHDCV5_FRET_SUCCESS;

  uint32_t final_bitrate_inx = LHDCV5_QUALITY_LOW3;
  uint32_t final_frame_duration = 50; // 5ms

  ALOGI("[Shim] BT_Stack sent: arg4=%u, arg5=%u", arg4, arg5);
  ALOGI("[Shim] Correcting params for Blob -> BR_Idx=%u, Dur=%u",
        final_bitrate_inx, final_frame_duration);

  if (handle == NULL) {
    return LHDCV5_FRET_INVALID_HANDLE_CB;
  }

  func_ret = lhdcv5_util_init_encoder (
      handle,
      sampling_freq,
      bits_per_sample,
      final_bitrate_inx,
      final_frame_duration,
      mtu,
      interval,
      is_lossless_enable);

  if (func_ret < LHDCV5_FRET_SUCCESS) {
    ALOGE("[Shim] lhdcv5_util_init_encoder failed: %d", func_ret);
    return LHDCV5_FRET_ERROR;
  }

  ALOGI("[Shim] Init success! LHDC should start playing now.");
  return func_ret;
}



int32_t lhdcv5BT_get_block_Size
(
    HANDLE_LHDCV5_BT  handle,
    uint32_t          *samples_per_frame
)
{
  int32_t func_ret = LHDCV5_FRET_SUCCESS;

  if (handle == NULL)
  {
    LHDC_LOGE ("Handle is NULL!");
    func_ret = LHDCV5_FRET_INVALID_HANDLE_CB;
    goto ENC_EXIT_FUNC;
  }

  if (samples_per_frame == NULL)
  {
    LHDC_LOGE ("Input parameter is NULL!");
    func_ret = LHDCV5_FRET_INVALID_HANDLE_CB;
    goto ENC_EXIT_FUNC;
  }

  func_ret = lhdcv5_util_get_block_Size (handle, samples_per_frame);
  if ((func_ret < LHDCV5_FRET_SUCCESS) || ((*samples_per_frame) <= 0))
  {
    LHDC_LOGE ("Failed to get block size (%d) (%d)!", func_ret, *samples_per_frame);
    func_ret = LHDCV5_FRET_ERROR;
    goto ENC_EXIT_FUNC;
  }

ENC_EXIT_FUNC:
  return func_ret;
}

int32_t lhdcv5BT_encode
(
    HANDLE_LHDCV5_BT  handle,
    void              *p_in_pcm,
    uint32_t          pcm_bytes,
    uint8_t           *p_out_buf,
    uint32_t          out_buf_bytes,
    uint32_t          *p_out_bytes,
    uint32_t          *p_out_frames
)
{
  int32_t func_ret = LHDCV5_FRET_SUCCESS;

  if (handle == NULL)
  {
    LHDC_LOGE ("Handle is NULL!");
    func_ret = LHDCV5_FRET_INVALID_HANDLE_CB;
    goto ENC_EXIT_FUNC;
  }

  if ((p_in_pcm == NULL) || (p_out_buf == NULL) ||
      (p_out_bytes == NULL) || (p_out_frames == NULL))
  {
    LHDC_LOGE ("input parameter is NULL!");
    func_ret = LHDCV5_FRET_INVALID_INPUT_PARAM;
    goto ENC_EXIT_FUNC;
  }

  func_ret = lhdcv5_util_enc_process (handle,
      p_in_pcm,
      pcm_bytes,
      p_out_buf,
      out_buf_bytes,
      p_out_bytes,
      p_out_frames);
  if (func_ret < LHDCV5_FRET_SUCCESS)
  {
    LHDC_LOGE ("Failed to encode pcm samples (%d)!", func_ret);
    func_ret = LHDCV5_FRET_ERROR;
    goto ENC_EXIT_FUNC;
  }

ENC_EXIT_FUNC:
  return func_ret;
}

int32_t lhdcv5BT_set_improved_low_bitrate
(
    HANDLE_LHDCV5_BT  handle,
    uint32_t          enable
)
{
  int32_t func_ret = LHDCV5_FRET_SUCCESS;

  if (handle == NULL)
  {
    LHDC_LOGE ("Handle is NULL!");
    func_ret = LHDCV5_FRET_INVALID_HANDLE_CB;
    goto ENC_EXIT_FUNC;
  }

  if (enable != 0 && enable != 1) {
    LHDC_LOGE ("invalid input!");
    func_ret = LHDCV5_FRET_INVALID_HANDLE_CB;
    goto ENC_EXIT_FUNC;
  }

  func_ret = lhdcv5_util_set_improved_low_bitrate(handle, enable);
  if (func_ret < LHDCV5_FRET_SUCCESS)
  {
    LHDC_LOGE ("Failed to set improved low bitrate mode (%d)!", func_ret);
    func_ret = LHDCV5_FRET_ERROR;
    goto ENC_EXIT_FUNC;
  }

  LHDC_LOGI ("set improved low bitrate mode (%u)!", enable);

ENC_EXIT_FUNC:
  return func_ret;
}

// ============= CUSTOM STUB =============
int32_t lhdcv5_util_enc_register_log_cb(void *cb, char *msg_buff, uint32_t buf_size, int32_t level) {
    (void)cb;
    (void)msg_buff;
    (void)buf_size;
    (void)level;
    return 0;
}

int32_t lhdcv5_util_set_lossless_raw_enabled(HANDLE_LHDCV5_BT handle, uint32_t enable) {
    (void)handle;
    (void)enable;
    return 0;
}

int32_t lhdcv5_util_get_lossless_enabled(HANDLE_LHDCV5_BT handle, uint32_t *enable) {
    (void)handle;
    if (enable) *enable = 0; // Disabled
    return 0;
}

int32_t lhdcv5_util_get_lossless_raw_enabled(HANDLE_LHDCV5_BT handle, uint32_t *enable) {
    (void)handle;
    if (enable) *enable = 0; // Disabled
    return 0;
}

int32_t lhdcv5_util_get_lossless_status(HANDLE_LHDCV5_BT handle, uint32_t *status) {
    (void)handle;
    if (status) *status = 0; // OFF
    return 0;
}

int32_t lhdcv5_util_get_current_bitrate(HANDLE_LHDCV5_BT handle, uint32_t *bitrate) {
    (void)handle;
    if (bitrate == NULL) return -1;

    uint32_t kbps = 390;

    switch (current_quality) {
        case LHDCV5_QUALITY_LOW0: kbps = 130; break;
        case LHDCV5_QUALITY_LOW1: kbps = 160; break;
        case LHDCV5_QUALITY_LOW2: kbps = 200; break;
        case LHDCV5_QUALITY_LOW3: kbps = 260; break;
        case LHDCV5_QUALITY_LOW4: kbps = 320; break;
        case LHDCV5_QUALITY_LOW:  kbps = 390; break;
        case LHDCV5_QUALITY_MID:  kbps = 520; break;
        case LHDCV5_QUALITY_HIGH: kbps = 900; break;
        case LHDCV5_QUALITY_HIGH1: kbps = 1000; break;

        default: kbps = 390; break;
    }

    *bitrate = kbps;
    return 0;
}

int32_t lhdcv5_util_get_quality_mode(HANDLE_LHDCV5_BT handle, uint32_t *qm) {
    (void)handle;
    if (qm) {
        *qm = 1;
    }
    return 0;
}

int32_t lhdcv5_util_set_improved_low_bitrate(HANDLE_LHDCV5_BT handle, uint32_t enable) {
    (void)handle;
    (void)enable;
    return 0;
}

int32_t lhdcv5_util_reset_down_bitrate_vbr(HANDLE_LHDCV5_BT handle) {
    (void)handle;
    return 0;
}

int32_t lhdcv5_util_reset_up_bitrate_vbr(HANDLE_LHDCV5_BT handle) {
    (void)handle;
    return 0;
}

int32_t lhdcv5_util_vbr_plus_process(HANDLE_LHDCV5_BT handle) {
    (void)handle;
    return 0;
}

int32_t lhdcv5_util_vbr_process(HANDLE_LHDCV5_BT handle) {
    (void)handle;
    return 0;
}

int32_t lhdcv5_util_set_vbr_up_th(HANDLE_LHDCV5_BT handle, uint32_t val) {
    (void)handle; (void)val;
    return 0;
}

int32_t lhdcv5_util_set_vbr_dn_th(HANDLE_LHDCV5_BT handle, uint32_t val) {
    (void)handle; (void)val;
    return 0;
}

int32_t lhdcv5_util_set_vbr_up_intv(HANDLE_LHDCV5_BT handle, uint32_t val) {
    (void)handle; (void)val;
    return 0;
}

int32_t lhdcv5_util_set_vbr_dn_intv(HANDLE_LHDCV5_BT handle, uint32_t val) {
    (void)handle; (void)val;
    return 0;
}