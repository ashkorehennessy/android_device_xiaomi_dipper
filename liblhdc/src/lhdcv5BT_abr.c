#include <stdlib.h>
#include <string.h>

#include "lhdcv5BT.h"
#include "lhdcv5BT_abr.h"

#include <cutils/log.h>

//// default bitrate tables for lossy-only: ABR
static uint32_t auto_bitrate_adjust_table_lhdcv5_44k_25f[] =
{
    LHDCV5_QUALITY_LOW4,
    LHDCV5_QUALITY_LOW,
    LHDCV5_QUALITY_MID,
    LHDCV5_QUALITY_MID,
    LHDCV5_QUALITY_MID,
    LHDCV5_QUALITY_MID
};
static uint32_t auto_bitrate_adjust_table_lhdcv5_44k_50f[] =
{
    LHDCV5_QUALITY_LOW1,
    LHDCV5_QUALITY_LOW2,
    LHDCV5_QUALITY_LOW3,
    LHDCV5_QUALITY_LOW4,
    LHDCV5_QUALITY_LOW,
    LHDCV5_QUALITY_LOW
};
static uint32_t auto_bitrate_adjust_table_lhdcv5_44k_100f[] =
{
    LHDCV5_QUALITY_LOW0,
    LHDCV5_QUALITY_LOW1,
    LHDCV5_QUALITY_LOW2,
    LHDCV5_QUALITY_LOW3,
    LHDCV5_QUALITY_LOW4,
    LHDCV5_QUALITY_LOW
};

static uint32_t auto_bitrate_adjust_table_lhdcv5_48k_25f[] =
{
    LHDCV5_QUALITY_LOW4,
    LHDCV5_QUALITY_LOW,
    LHDCV5_QUALITY_MID,
    LHDCV5_QUALITY_MID,
    LHDCV5_QUALITY_MID,
    LHDCV5_QUALITY_MID
};
static uint32_t auto_bitrate_adjust_table_lhdcv5_48k_50f[] =
{
    LHDCV5_QUALITY_LOW1,
    LHDCV5_QUALITY_LOW2,
    LHDCV5_QUALITY_LOW3,
    LHDCV5_QUALITY_LOW4,
    LHDCV5_QUALITY_LOW,
    LHDCV5_QUALITY_LOW
};
static uint32_t auto_bitrate_adjust_table_lhdcv5_48k_100f[] =
{
    LHDCV5_QUALITY_LOW0,
    LHDCV5_QUALITY_LOW1,
    LHDCV5_QUALITY_LOW2,
    LHDCV5_QUALITY_LOW3,
    LHDCV5_QUALITY_LOW4,
    LHDCV5_QUALITY_LOW
};

static uint32_t auto_bitrate_adjust_table_lhdcv5_96k_25f[] =
{
    LHDCV5_QUALITY_LOW4,
    LHDCV5_QUALITY_LOW,
    LHDCV5_QUALITY_MID,
    LHDCV5_QUALITY_MID,
    LHDCV5_QUALITY_MID,
    LHDCV5_QUALITY_MID
};
static uint32_t auto_bitrate_adjust_table_lhdcv5_96k_50f[] =
{
    LHDCV5_QUALITY_LOW3,
    LHDCV5_QUALITY_LOW4,
    LHDCV5_QUALITY_LOW,
    LHDCV5_QUALITY_LOW,
    LHDCV5_QUALITY_LOW,
    LHDCV5_QUALITY_LOW
};
static uint32_t auto_bitrate_adjust_table_lhdcv5_96k_100f[] =
{
    LHDCV5_QUALITY_LOW3,
    LHDCV5_QUALITY_LOW4,
    LHDCV5_QUALITY_LOW,
    LHDCV5_QUALITY_LOW,
    LHDCV5_QUALITY_LOW,
    LHDCV5_QUALITY_LOW
};

static uint32_t auto_bitrate_adjust_table_lhdcv5_192k_25f[] =
{
    LHDCV5_QUALITY_LOW4,
    LHDCV5_QUALITY_LOW,
    LHDCV5_QUALITY_MID,
    LHDCV5_QUALITY_MID,
    LHDCV5_QUALITY_MID,
    LHDCV5_QUALITY_MID
};
static uint32_t auto_bitrate_adjust_table_lhdcv5_192k_50f[] =
{
    LHDCV5_QUALITY_LOW3,
    LHDCV5_QUALITY_LOW4,
    LHDCV5_QUALITY_LOW,
    LHDCV5_QUALITY_LOW,
    LHDCV5_QUALITY_LOW,
    LHDCV5_QUALITY_LOW
};
static uint32_t auto_bitrate_adjust_table_lhdcv5_192k_100f[] =
{
    LHDCV5_QUALITY_LOW3,
    LHDCV5_QUALITY_LOW4,
    LHDCV5_QUALITY_LOW,
    LHDCV5_QUALITY_LOW,
    LHDCV5_QUALITY_LOW,
    LHDCV5_QUALITY_LOW
};

//// default bitrate tables for lossless/raw: VBR-lossy layer
// frame duration 2.5ms:
static uint32_t auto_bitrate_adjust_table_lhdcv5_lless25_48k_16b[] =
{
    LHDCV5_QUALITY_LOW1,
    LHDCV5_QUALITY_LOW2,
    LHDCV5_QUALITY_LOW3,
    LHDCV5_QUALITY_LOW4,
    LHDCV5_QUALITY_LOW,
    LHDCV5_QUALITY_MID
};

static uint32_t auto_bitrate_adjust_table_lhdcv5_lless25_48k_24b[] =
{
    LHDCV5_QUALITY_LOW1,
    LHDCV5_QUALITY_LOW2,
    LHDCV5_QUALITY_LOW3,
    LHDCV5_QUALITY_LOW4,
    LHDCV5_QUALITY_LOW,
    LHDCV5_QUALITY_MID
};

static uint32_t auto_bitrate_adjust_table_lhdcv5_lless25_96k_24b[] =
{
    LHDCV5_QUALITY_LOW1,
    LHDCV5_QUALITY_LOW2,
    LHDCV5_QUALITY_LOW3,
    LHDCV5_QUALITY_LOW4,
    LHDCV5_QUALITY_LOW,
    LHDCV5_QUALITY_MID
};

// frame duration 5ms:
static uint32_t auto_bitrate_adjust_table_lhdcv5_lless50_48k_16b[] =
{
    LHDCV5_QUALITY_LOW1,
    LHDCV5_QUALITY_LOW2,
    LHDCV5_QUALITY_LOW3,
    LHDCV5_QUALITY_LOW4,
    LHDCV5_QUALITY_LOW,
    LHDCV5_QUALITY_MID
};

static uint32_t auto_bitrate_adjust_table_lhdcv5_lless50_48k_24b[] =
{
    LHDCV5_QUALITY_LOW1,
    LHDCV5_QUALITY_LOW2,
    LHDCV5_QUALITY_LOW3,
    LHDCV5_QUALITY_LOW4,
    LHDCV5_QUALITY_LOW,
    LHDCV5_QUALITY_MID
};

static uint32_t auto_bitrate_adjust_table_lhdcv5_lless50_96k_24b[] =
{
    LHDCV5_QUALITY_LOW1,
    LHDCV5_QUALITY_LOW2,
    LHDCV5_QUALITY_LOW3,
    LHDCV5_QUALITY_LOW4,
    LHDCV5_QUALITY_LOW,
    LHDCV5_QUALITY_MID
};

// auto bitrate mechanism control handle
lhdcv5_abr_cb_t handle_abr;


//----------------------------------------------------------------
// lhdcv5_enc_abr_adjust_bitrate ()
//
// Adjust bit rate automatically according to number of packets in queue for LHDC 5.0 encoding
//  Parameter
//    handle: a pointer to the resource allocated and is returned
//        by function lhdcBT_get_handle ()
//    queueLen: number of remaining packets in output queue notify from streaming system
//  Return
//    LHDCV5_FRET_SUCCESS: succeed to adjust bit rate automatically
//    otherwise: fail to adjust bit rate automatically
//----------------------------------------------------------------
static int32_t lhdcv5_enc_abr_adjust_bitrate
(
    HANDLE_LHDCV5_BT handle,
    uint32_t queueLen
)
{
  int32_t func_ret = LHDCV5_FRET_SUCCESS;
  uint32_t queueLength = 0;
  uint32_t queuSumTmp = 0;
  uint32_t last_bitrate_inx = 0;
  uint32_t last_bitrate = 0;
  uint32_t new_abr_bitrate_inx = 0;
  uint32_t new_bitrate_inx = 0;
  uint32_t new_bitrate = 0;
  uint32_t new_bitrate_inx_set = 0;
  uint32_t abr_down_bitrate_idx = ABR_DOWN_TARGET_STAGE;
  uint32_t abr_promote_to_vbr_table_idx = LHDCV5_AUTOBITRATE_ADJTABLE_MAX_INDEX;
  uint32_t abr_to_vbr_promote_bitrate_idx = VBR_PROMOTE_TO_LOSSLESS_INDEX;
  uint32_t loss_enable = 0;

  if (handle == NULL)
  {
    LHDC_LOGE ("handle is NULL!");
    func_ret = LHDCV5_FRET_INVALID_HANDLE_CB;
    goto ABR_EXIT_FUNC;
  }

  // Check bitrate downgrade condition
  if (handle_abr.down_bitrate_count >= ABR_DOWN_RATE_TIME_CNT)
  {
    queueLength = handle_abr.down_bitrate_sum / handle_abr.down_bitrate_count;

    // clean ABR down statistics parameters
    handle_abr.down_bitrate_count = 0;
    handle_abr.down_bitrate_sum = 0;

    if (queueLength > ABR_DOWN_QUEUE_LENGTH_THRESHOLD)
    {
      // get current bitrate value
      func_ret = lhdcv5_util_get_current_bitrate (handle, &last_bitrate);
      if (func_ret < LHDCV5_FRET_SUCCESS)
      {
        LHDC_LOGE ("[AUTO_BITRATE][ABR_ADJ][DN] get current bitrate error (%d)", func_ret);
        func_ret = LHDCV5_FRET_ERROR;
        goto ABR_EXIT_FUNC;
      }

      // get current bitrate's index
      func_ret = lhdcv5_util_get_bitrate_inx (last_bitrate, &last_bitrate_inx);
      if (func_ret < LHDCV5_FRET_SUCCESS)
      {
        LHDC_LOGE ("[AUTO_BITRATE][ABR_ADJ][DN] get current bitrate's index error (%d)", func_ret);
        func_ret = LHDCV5_FRET_ERROR;
        goto ABR_EXIT_FUNC;
      }

      // get new bitrate index
      new_abr_bitrate_inx = abr_down_bitrate_idx;
      if (new_abr_bitrate_inx > LHDCV5_AUTOBITRATE_ADJTABLE_MAX_INDEX)
      {
        LHDC_LOGE ("[AUTO_BITRATE][ABR_ADJ][DN] error! new index > max index in abr_table!");
        func_ret = LHDCV5_FRET_ERROR;
        goto ABR_EXIT_FUNC;
      }
      new_bitrate_inx = handle_abr.abr_table[new_abr_bitrate_inx];

      // get new bitrate value
      func_ret = lhdcv5_util_get_bitrate (new_bitrate_inx, &new_bitrate);
      if (func_ret < LHDCV5_FRET_SUCCESS)
      {
        LHDC_LOGE ("[AUTO_BITRATE][ABR_ADJ][DN] get new bitrate value error (%d)", func_ret);
        func_ret = LHDCV5_FRET_ERROR;
        goto ABR_EXIT_FUNC;
      }

      // set new bitrate check
      if (new_bitrate_inx <= last_bitrate_inx && new_abr_bitrate_inx < handle_abr.gABR_table_index)
      {
        LHDC_LOGE ("[AUTO_BITRATE][ABR_ADJ][DN] qLen:%u set bitrate[%u](%u) to abr_table[%u]:bitrate[%u](%u)",
            queueLength,
            last_bitrate_inx,
            last_bitrate,
            new_abr_bitrate_inx,
            new_bitrate_inx,
            new_bitrate);

        func_ret = lhdcv5_util_set_target_bitrate_inx (handle, new_bitrate_inx, &new_bitrate_inx_set);
        if (func_ret < LHDCV5_FRET_SUCCESS)
        {
          LHDC_LOGE ("[AUTO_BITRATE][ABR_ADJ][DN] lhdcv5_util_set_target_bitrate_inx error (%d)", func_ret);
          func_ret = LHDCV5_FRET_ERROR;
          goto ABR_EXIT_FUNC;
        }

        func_ret = lhdcv5_util_get_bitrate (new_bitrate_inx_set, &new_bitrate);
        if (func_ret < LHDCV5_FRET_SUCCESS)
        {
          LHDC_LOGE ("[AUTO_BITRATE][ABR_ADJ][DN] get result bitrate value error (%d)", func_ret);
          func_ret = LHDCV5_FRET_ERROR;
          goto ABR_EXIT_FUNC;
        }

        LHDC_LOGE ("[AUTO_BITRATE][ABR_ADJ][DN] resulting set bitrate[%u](%u) done",
            new_bitrate_inx_set,
            new_bitrate);

        // update current index of abr_table
        handle_abr.gABR_table_index = new_abr_bitrate_inx;

        // clean up statistics parameters
        handle_abr.up_bitrate_count = 0;
        handle_abr.up_bitrate_sum = 0;
      }
      else
      {
        // not need to change bitrate
        handle_abr.gABR_table_index = new_abr_bitrate_inx;
      }
    }
    else
    {
      // condition not matched, do nothing
    }
  }


  // Check bitrate upgrade condition
  if (handle_abr.up_bitrate_count >= ABR_UP_RATE_TIME_CNT)
  {
    queuSumTmp = handle_abr.up_bitrate_sum;

    // clean ABR up statistics parameters
    handle_abr.up_bitrate_count = 0;
    handle_abr.up_bitrate_sum = 0;

    if (queuSumTmp < ABR_UP_QUEUE_LENGTH_THRESHOLD)
    {
      // get current bitrate value
      func_ret = lhdcv5_util_get_current_bitrate (handle, &last_bitrate);
      if (func_ret < LHDCV5_FRET_SUCCESS)
      {
        LHDC_LOGE ("[AUTO_BITRATE][ABR_ADJ][UP] get current bitrate error (%d)", func_ret);
        func_ret = LHDCV5_FRET_ERROR;
        goto ABR_EXIT_FUNC;
      }

      // get current bitrate's index
      func_ret = lhdcv5_util_get_bitrate_inx (last_bitrate, &last_bitrate_inx);
      if (func_ret < LHDCV5_FRET_SUCCESS)
      {
        LHDC_LOGE ("[AUTO_BITRATE][ABR_ADJ][UP] get current bitrate's index error (%d)", func_ret);
        func_ret = LHDCV5_FRET_ERROR;
        goto ABR_EXIT_FUNC;
      }

      // get temp new bitrate index
      if (handle_abr.gABR_table_index < LHDCV5_AUTOBITRATE_ADJTABLE_MAX_INDEX)
      {
        new_abr_bitrate_inx = handle_abr.gABR_table_index + 1;
      }
      else
      {
        new_abr_bitrate_inx = handle_abr.gABR_table_index;
      }
      new_bitrate_inx = handle_abr.abr_table[new_abr_bitrate_inx];

      // get temp new bitrate value
      func_ret = lhdcv5_util_get_bitrate (new_bitrate_inx, &new_bitrate);
      if (func_ret < LHDCV5_FRET_SUCCESS)
      {
        LHDC_LOGE ("[AUTO_BITRATE][ABR_ADJ][UP] get new bitrate value error (%d)", func_ret);
        func_ret = LHDCV5_FRET_ERROR;
        goto ABR_EXIT_FUNC;
      }

      func_ret = lhdcv5_util_get_lossless_enabled(handle, &loss_enable);
      if (func_ret < LHDCV5_FRET_SUCCESS)
      {
        LHDC_LOGE ("Failed lhdcv5_util_get_lossless_enabled (%d)!", func_ret);
        func_ret = LHDCV5_FRET_ERROR;
        goto ABR_EXIT_FUNC;
      }

      if (loss_enable == LHDCV5_LLESS_ENABLED)
      {
        // check if able to promote to VBR-lossless layer (when lossless is enabled)
        if (handle_abr.gABR_table_index == abr_promote_to_vbr_table_idx)
        {
          new_bitrate_inx = abr_to_vbr_promote_bitrate_idx;

          if (new_bitrate_inx >= last_bitrate_inx)
          {
            // upgrade bitrate to the VBR-lossless layer
            func_ret = lhdcv5_util_set_target_bitrate_inx (handle, new_bitrate_inx, &new_bitrate_inx_set);
            if (func_ret < LHDCV5_FRET_SUCCESS)
            {
              LHDC_LOGE ("[AUTO_BITRATE][ABR_ADJ][PROMOTE] lhdcv5_util_set_target_bitrate_inx error (%d)", func_ret);
              func_ret = LHDCV5_FRET_ERROR;
              goto ABR_EXIT_FUNC;
            }

            func_ret = lhdcv5_util_get_bitrate (new_bitrate_inx_set, &new_bitrate);
            if (func_ret < LHDCV5_FRET_SUCCESS)
            {
              LHDC_LOGE ("[AUTO_BITRATE][ABR_ADJ][PROMOTE] get result bitrate value error (%d)", func_ret);
              func_ret = LHDCV5_FRET_ERROR;
              goto ABR_EXIT_FUNC;
            }

            LHDC_LOGE ("[AUTO_BITRATE][ABR_ADJ][PROMOTE] resulting set bitrate[%u](%u) done",
                new_bitrate_inx_set,
                new_bitrate);

            // reset all statistics parameters
            handle_abr.down_bitrate_count = 0;
            handle_abr.down_bitrate_sum = 0;
            handle_abr.up_bitrate_count = 0;
            handle_abr.up_bitrate_sum = 0;

            func_ret = lhdcv5_util_reset_down_bitrate_vbr (handle);
            if (func_ret < LHDCV5_FRET_SUCCESS)
            {
              LHDC_LOGE ("[AUTO_BITRATE][ABR_ADJ][PROMOTE] lhdcv5_util_reset_down_bitrate_vbr error %d", func_ret);
              func_ret = LHDCV5_FRET_ERROR;
              goto ABR_EXIT_FUNC;
            }

            func_ret = lhdcv5_util_reset_up_bitrate_vbr (handle);
            if (func_ret < LHDCV5_FRET_SUCCESS)
            {
              LHDC_LOGE ("[AUTO_BITRATE][ABR_ADJ][PROMOTE] lhdcv5_util_reset_up_bitrate_vbr error %d",  func_ret);
              func_ret = LHDCV5_FRET_ERROR;
              goto ABR_EXIT_FUNC;
            }

            LHDC_LOGE ("[AUTO_BITRATE][ABR_ADJ][PROMOTE] abr_table[%u]:bitrate[%u] to bitrate[%u](%u)",
                handle_abr.gABR_table_index,
                handle_abr.abr_table[handle_abr.gABR_table_index],
                new_bitrate_inx_set,
                new_bitrate);
          }
          else
          {
            // lossless mode is enabled, but new bitrate is lesser than current's bitrate
            handle_abr.gABR_table_index = new_abr_bitrate_inx;
          }

          func_ret = LHDCV5_FRET_SUCCESS;
          goto ABR_EXIT_FUNC;
        }
      }

      // increase the bitrate in ABR or VBR-lossy layer
      if (new_bitrate_inx >= last_bitrate_inx && new_abr_bitrate_inx > handle_abr.gABR_table_index)
      {
        LHDC_LOGE ("[AUTO_BITRATE][ABR_ADJ][UP] qSum:%u set bitrate[%u](%u) to abr_table[%u]:bitrate[%u](%u)",
            queuSumTmp,
            last_bitrate_inx,
            last_bitrate,
            new_abr_bitrate_inx,
            new_bitrate_inx,
            new_bitrate);

        func_ret = lhdcv5_util_set_target_bitrate_inx (handle, new_bitrate_inx, &new_bitrate_inx_set);
        if (func_ret < LHDCV5_FRET_SUCCESS)
        {
          LHDC_LOGE ("[AUTO_BITRATE][ABR_ADJ][UP] lhdcv5_util_set_target_bitrate_inx error (%d)", func_ret);
          func_ret = LHDCV5_FRET_ERROR;
          goto ABR_EXIT_FUNC;
        }

        func_ret = lhdcv5_util_get_bitrate (new_bitrate_inx_set, &new_bitrate);
        if (func_ret < LHDCV5_FRET_SUCCESS)
        {
          LHDC_LOGE ("[AUTO_BITRATE][ABR_ADJ][UP] get result bitrate value error (%d)", func_ret);
          func_ret = LHDCV5_FRET_ERROR;
          goto ABR_EXIT_FUNC;
        }

        LHDC_LOGE ("[AUTO_BITRATE][ABR_ADJ][UP] resulting set bitrate[%u](%u) done",
            new_bitrate_inx_set,
            new_bitrate);

        // update current index of abr_table
        handle_abr.gABR_table_index = new_abr_bitrate_inx;

        // clean up statistics parameters
        handle_abr.down_bitrate_count = 0;
        handle_abr.down_bitrate_sum = 0;
      }
      else
      {
        // not need to change bitrate
        handle_abr.gABR_table_index = new_abr_bitrate_inx;
      }
    }
  }


  if (queueLen > 0)
  {
    handle_abr.up_bitrate_sum += queueLen;
    handle_abr.down_bitrate_sum += queueLen;
  }

  handle_abr.up_bitrate_count++;
  handle_abr.down_bitrate_count++;

ABR_EXIT_FUNC:
  return func_ret;
}


//----------------------------------------------------------------
// lhdcv5_enc_vbr_adjust_bitrate ()
//
// Adjust bit rate automatically according to number of lossless frames for LHDC 5.0 encoding
//  Parameter
//    handle: a pointer to the resource allocated and is returned
//        by function lhdcBT_get_handle ()
//    queueLen: number of remaining packets in output queue notify from streaming system
//  Return
//    LHDCV5_FRET_SUCCESS: succeed to adjust bit rate automatically
//    otherwise: fail to adjust bit rate automatically
//----------------------------------------------------------------
static int lhdcv5_enc_vbr_adjust_bitrate
(
    HANDLE_LHDCV5_BT handle,
    uint32_t queueLen
)
{
  int32_t func_ret = LHDCV5_FRET_SUCCESS;
  uint32_t queueLength = 0;
  uint32_t last_bitrate_inx = 0;
  uint32_t last_bitrate = 0;
  uint32_t new_abr_bitrate_inx = 0;
  uint32_t new_bitrate_inx = 0;
  uint32_t new_bitrate = 0;
  uint32_t new_bitrate_inx_set = 0;
  uint32_t vbr_to_abr_promote_bitrate_idx = VBR_DEMOTE_TO_LOSSY_INDEX;

  if (handle == NULL)
  {
    LHDC_LOGE ("handle is NULL!");
    func_ret = LHDCV5_FRET_INVALID_HANDLE_CB;
    goto ABR_EXIT_FUNC;
  }

  //
  // VBR-lossless layer to VBR-lossy layer scenario:
  //  fallback to the lossy mode bitrate while packet transmission goes bad
  //
  if (handle_abr.down_bitrate_count >= ABR_DOWN_RATE_TIME_CNT)
  {
    queueLength = handle_abr.down_bitrate_sum / handle_abr.down_bitrate_count;

    // clean down statistics parameters
    handle_abr.down_bitrate_count = 0;
    handle_abr.down_bitrate_sum = 0;

    if (queueLength > VBR_DEMOTE_TO_LOSSY_QLENGTH_THRESHOLD)
    {
      // get current bitrate value
      func_ret = lhdcv5_util_get_current_bitrate (handle, &last_bitrate);
      if (func_ret < LHDCV5_FRET_SUCCESS)
      {
        LHDC_LOGE ("[AUTO_BITRATE][VBR_ADJ][DEMOTE] get current bitrate error (%d)", func_ret);
        func_ret = LHDCV5_FRET_ERROR;
        goto ABR_EXIT_FUNC;
      }

      // get current bitrate's index
      func_ret = lhdcv5_util_get_bitrate_inx (last_bitrate, &last_bitrate_inx);
      if (func_ret < LHDCV5_FRET_SUCCESS)
      {
        LHDC_LOGE ("[AUTO_BITRATE][VBR_ADJ][DEMOTE] get current bitrate's index error (%d)", func_ret);
        func_ret = LHDCV5_FRET_ERROR;
        goto ABR_EXIT_FUNC;
      }

      //// configure new target bitrate
      new_abr_bitrate_inx = vbr_to_abr_promote_bitrate_idx;
      if (new_abr_bitrate_inx > LHDCV5_AUTOBITRATE_ADJTABLE_MAX_INDEX)
      {
        LHDC_LOGE ("[AUTO_BITRATE][VBR_ADJ][DEMOTE] Error! new index > max index in abr_table!");
        func_ret = LHDCV5_FRET_ERROR;
        goto ABR_EXIT_FUNC;
      }
      new_bitrate_inx = handle_abr.abr_table[new_abr_bitrate_inx];

      // get new bitrate value
      func_ret = lhdcv5_util_get_bitrate (new_bitrate_inx, &new_bitrate);
      if (func_ret < LHDCV5_FRET_SUCCESS)
      {
        LHDC_LOGE ("[AUTO_BITRATE][VBR_ADJ][DEMOTE] get new bitrate value error (%d)", func_ret);
        func_ret = LHDCV5_FRET_ERROR;
        goto ABR_EXIT_FUNC;
      }

      // set new bitrate check
      if (new_bitrate_inx <= last_bitrate_inx)
      {
        LHDC_LOGE ("[AUTO_BITRATE][VBR_ADJ][DEMOTE] qLen:%u set bitrate[%u](%u) to abr_table[%u]:bitrate[%u](%u)",
            queueLength,
            last_bitrate_inx,
            last_bitrate,
            new_abr_bitrate_inx,
            new_bitrate_inx,
            new_bitrate);

        func_ret = lhdcv5_util_set_target_bitrate_inx (handle, new_bitrate_inx, &new_bitrate_inx_set);
        if (func_ret < LHDCV5_FRET_SUCCESS)
        {
          LHDC_LOGE ("[AUTO_BITRATE][VBR_ADJ][DEMOTE] set new bitrate index:%u error (%d)",
              new_bitrate_inx, func_ret);
          func_ret = LHDCV5_FRET_ERROR;
          goto ABR_EXIT_FUNC;
        }

        func_ret = lhdcv5_util_get_bitrate (new_bitrate_inx_set, &new_bitrate);
        if (func_ret < LHDCV5_FRET_SUCCESS)
        {
          LHDC_LOGE ("[AUTO_BITRATE][VBR_ADJ][DEMOTE] get result bitrate value error (%d)", func_ret);
          func_ret = LHDCV5_FRET_ERROR;
          goto ABR_EXIT_FUNC;
        }

        LHDC_LOGE ("[AUTO_BITRATE][VBR_ADJ][DEMOTE] resulting set bitrate[%u](%u) done",
            new_bitrate_inx_set,
            new_bitrate);

        // update current index of abr_table
        handle_abr.gABR_table_index = new_abr_bitrate_inx;

        // clean up statistics parameters
        handle_abr.up_bitrate_count = 0;
        handle_abr.up_bitrate_sum = 0;

        // clean VBR's params
        func_ret = lhdcv5_util_reset_down_bitrate_vbr (handle);
        if (func_ret < LHDCV5_FRET_SUCCESS)
        {
          LHDC_LOGE ("[AUTO_BITRATE][VBR_ADJ][DEMOTE] clean VBR params error (%d)", func_ret);
          func_ret = LHDCV5_FRET_ERROR;
          goto ABR_EXIT_FUNC;
        }

        func_ret = lhdcv5_util_reset_up_bitrate_vbr (handle);
        if (func_ret < LHDCV5_FRET_SUCCESS)
        {
          LHDC_LOGE ("[AUTO_BITRATE][VBR_ADJ][DEMOTE] clean VBR params error (%d)", func_ret);
          func_ret = LHDCV5_FRET_ERROR;
          goto ABR_EXIT_FUNC;
        }
      }
      else
      {
        // not need to change bitrate
        handle_abr.gABR_table_index = new_abr_bitrate_inx;
      }
    }
    else
    {
      // condition not matched, do nothing
    }
  }
  else
  {
    //
    // keep processing in VBR-lossless layer
    //
    func_ret = lhdcv5_util_vbr_process(handle);
    if (func_ret < LHDCV5_FRET_SUCCESS)
    {
      LHDC_LOGE ("[AUTO_BITRATE][VBR_ADJ] VBR process error (%d)", func_ret);
      func_ret = LHDCV5_FRET_ERROR;
      goto ABR_EXIT_FUNC;
    }
  }

  // update statistics parameters
  if (queueLen > 0)
  {
    handle_abr.up_bitrate_sum += queueLen;
    handle_abr.down_bitrate_sum += queueLen;
  }

  handle_abr.up_bitrate_count++;
  handle_abr.down_bitrate_count++;

ABR_EXIT_FUNC:
  return func_ret;
}

//----------------------------------------------------------------
// lhdcv5_enc_vbr_plus_adjust_bitrate ()
//
// Adjust bit rate automatically for the scenario of lossless raw mode
//  Parameter
//    handle: a pointer to the resource allocated and is returned
//        by function lhdcBT_get_handle ()
//  Return
//    LHDCV5_FRET_SUCCESS: succeed to adjust bit rate automatically
//    otherwise: fail to adjust bit rate automatically
//----------------------------------------------------------------
static int lhdcv5_enc_vbr_plus_adjust_bitrate
(
    HANDLE_LHDCV5_BT handle
)
{
  int32_t func_ret = LHDCV5_FRET_SUCCESS;

  if (handle == NULL)
  {
    LHDC_LOGE ("Handle is NULL!");
    func_ret = LHDCV5_FRET_INVALID_HANDLE_CB;
    goto ABR_EXIT_FUNC;
  }

  func_ret = lhdcv5_util_vbr_plus_process(handle);
  if (func_ret < LHDCV5_FRET_SUCCESS)
  {
    LHDC_LOGE ("lhdcv5_util_vbr_plus_process error (%d)", func_ret);
    func_ret = LHDCV5_FRET_ERROR;
    goto ABR_EXIT_FUNC;
  }

ABR_EXIT_FUNC:
  return func_ret;
}


/////////////////////////////////
//  Auto Bit Rate mechanism APIs
/////////////////////////////////
int32_t lhdcv5BT_autoBR_reset_abr_index
(
    void
)
{
  handle_abr.gABR_table_index = LHDCV5_AUTOBITRATE_DEFAULT_TABLE_INDEX;
  return LHDCV5_FRET_SUCCESS;
}

int32_t lhdcv5BT_autoBR_adjust_bitrate_process
(
    HANDLE_LHDCV5_BT handle,
    uint32_t queue_len
)
{
  int32_t func_ret = LHDCV5_FRET_SUCCESS;
  uint32_t qm = 0;
  uint32_t loss_enable = 0;
  uint32_t loss_on_off = 0;
  uint32_t raw_enable = 0;

  if (handle == NULL)
  {
    LHDC_LOGE ("Handle is NULL!");
    func_ret = LHDCV5_FRET_INVALID_HANDLE_CB;
    goto ABR_EXIT_FUNC;
  }

  func_ret = lhdcv5_util_get_quality_mode(handle, &qm);
  if (func_ret < LHDCV5_FRET_SUCCESS)
  {
    LHDC_LOGE ("Failed to get quality mode (%d)!", func_ret);
    func_ret = LHDCV5_FRET_ERROR;
    goto ABR_EXIT_FUNC;
  }

  if (qm != LHDCV5_ENC_AUTO_BITRATE)
  {
    // ignore if not in auto bitrate mode
    func_ret = LHDCV5_FRET_SUCCESS;
    goto ABR_EXIT_FUNC;
  }

  func_ret = lhdcv5_util_get_lossless_enabled(handle, &loss_enable);
  if (func_ret < LHDCV5_FRET_SUCCESS)
  {
    LHDC_LOGE ("Failed to get lossless enable (%d)!", func_ret);
    func_ret = LHDCV5_FRET_ERROR;
    goto ABR_EXIT_FUNC;
  }

  if (loss_enable != LHDCV5_LLESS_ENABLED)
  {
    // lossy-only mode: ABR
    func_ret = lhdcv5_enc_abr_adjust_bitrate (handle, queue_len);
    if (func_ret < LHDCV5_FRET_SUCCESS)
    {
      LHDC_LOGE ("Failed to ABR adjust process (%d)!", func_ret);
      func_ret = LHDCV5_FRET_ERROR;
      goto ABR_EXIT_FUNC;
    }
  }
  else
  {
    // lossless/raw mode: VBR-plus
    func_ret = lhdcv5_util_get_lossless_raw_enabled(handle, &raw_enable);
    if (func_ret < LHDCV5_FRET_SUCCESS)
    {
      LHDC_LOGE ("Failed lhdcv5_util_get_lossless_raw_enabled (%d)!", func_ret);
      func_ret = LHDCV5_FRET_ERROR;
      goto ABR_EXIT_FUNC;
    }

    func_ret = lhdcv5_util_get_lossless_status(handle, &loss_on_off);
    if (func_ret < LHDCV5_FRET_SUCCESS)
    {
      LHDC_LOGE ("Failed lhdcv5_util_get_lossless_status (%d)!", func_ret);
      func_ret = LHDCV5_FRET_ERROR;
      goto ABR_EXIT_FUNC;
    }

    if (raw_enable == LHDCV5_LLESS_ENABLED)
    {
      if (loss_on_off == LHDCV5_LLESS_ON)
      {
        func_ret = lhdcv5_enc_vbr_plus_adjust_bitrate(handle);
        if (func_ret < LHDCV5_FRET_SUCCESS)
        {
          LHDC_LOGE ("Failed to VBR-Plus adjust process (%d)!", func_ret);
          func_ret = LHDCV5_FRET_ERROR;
          goto ABR_EXIT_FUNC;
        }
      }
      else
      {
        LHDC_LOGE ("VBR-Plus: (Error) lossless not ON!");
        func_ret = LHDCV5_FRET_ERROR;
        goto ABR_EXIT_FUNC;
      }
    }
    else
    {
      // standard lossless mode: VBR
      if (loss_on_off == LHDCV5_LLESS_ON)
      {
        // to VBR-lossless layer
        func_ret = lhdcv5_enc_vbr_adjust_bitrate (handle, queue_len);
        if (func_ret < LHDCV5_FRET_SUCCESS)
        {
          LHDC_LOGE ("Failed to VBR-lless adjust process (%d)!", func_ret);
          func_ret = LHDCV5_FRET_ERROR;
          goto ABR_EXIT_FUNC;
        }
      }
      else
      {
        // to VBR-lossy layer
        func_ret = lhdcv5_enc_abr_adjust_bitrate (handle, queue_len);
        if (func_ret < LHDCV5_FRET_SUCCESS)
        {
          LHDC_LOGE ("Failed to VBR-lossy adjust process (%d)!", func_ret);
          func_ret = LHDCV5_FRET_ERROR;
          goto ABR_EXIT_FUNC;
        }
      }
    }
  }

ABR_EXIT_FUNC:
  return func_ret;
}


int32_t lhdcv5BT_autoBR_adjust_bitrate_init
(
    HANDLE_LHDCV5_BT handle,
    uint32_t sample_rate,
    uint32_t bits_per_sample,
    uint32_t frame_duration
)
{
  int32_t func_ret = LHDCV5_FRET_SUCCESS;
  uint32_t lossless_enable = 0;

  if (handle == NULL)
  {
    LHDC_LOGE ("Handle is NULL!");
    func_ret = LHDCV5_FRET_INVALID_HANDLE_CB;
    goto ABR_EXIT_FUNC;
  }

  memset(&handle_abr, 0, sizeof(lhdcv5_abr_cb_t));

  func_ret = lhdcv5_util_get_lossless_enabled(handle, &lossless_enable);
  if (func_ret < LHDCV5_FRET_SUCCESS)
  {
    LHDC_LOGE ("failed to get lossless enable/disable (%u)", func_ret);
    func_ret = LHDCV5_FRET_ERROR;
    goto ABR_EXIT_FUNC;
  }

  // select bitrate table
  if (lossless_enable == 0)
  {
    // lossy-only mode:
    if (sample_rate == LHDCV5_SR_44100HZ)
    {
      if (frame_duration == LHDCV5_FRAME_2P5MS)
      {
        handle_abr.abr_table = &(auto_bitrate_adjust_table_lhdcv5_44k_25f[0]);
      }
      else if (frame_duration == LHDCV5_FRAME_5MS)
      {
        handle_abr.abr_table = &(auto_bitrate_adjust_table_lhdcv5_44k_50f[0]);
      }
      else if (frame_duration == LHDCV5_FRAME_10MS)
      {
        handle_abr.abr_table = &(auto_bitrate_adjust_table_lhdcv5_44k_100f[0]);
      }
      else
      {
        func_ret = LHDCV5_FRET_INVALID_INPUT_PARAM;
        goto ABR_EXIT_FUNC;
      }
    }
    else if (sample_rate == LHDCV5_SR_48000HZ)
    {
      if (frame_duration == LHDCV5_FRAME_2P5MS)
      {
        handle_abr.abr_table = &(auto_bitrate_adjust_table_lhdcv5_48k_25f[0]);
      }
      else if (frame_duration == LHDCV5_FRAME_5MS)
      {
        handle_abr.abr_table = &(auto_bitrate_adjust_table_lhdcv5_48k_50f[0]);
      }
      else if (frame_duration == LHDCV5_FRAME_10MS)
      {
        handle_abr.abr_table = &(auto_bitrate_adjust_table_lhdcv5_48k_100f[0]);
      }
      else
      {
        func_ret = LHDCV5_FRET_INVALID_INPUT_PARAM;
        goto ABR_EXIT_FUNC;
      }
    }
    else if (sample_rate == LHDCV5_SR_96000HZ)
    {
      if (frame_duration == LHDCV5_FRAME_2P5MS)
      {
        handle_abr.abr_table = &(auto_bitrate_adjust_table_lhdcv5_96k_25f[0]);
      }
      else if (frame_duration == LHDCV5_FRAME_5MS)
      {
        handle_abr.abr_table = &(auto_bitrate_adjust_table_lhdcv5_96k_50f[0]);
      }
      else if (frame_duration == LHDCV5_FRAME_10MS)
      {
        handle_abr.abr_table = &(auto_bitrate_adjust_table_lhdcv5_96k_100f[0]);
      }
      else
      {
        func_ret = LHDCV5_FRET_INVALID_INPUT_PARAM;
        goto ABR_EXIT_FUNC;
      }
    }
    else if (sample_rate == LHDCV5_SR_192000HZ)
    {
      if (frame_duration == LHDCV5_FRAME_2P5MS)
      {
        handle_abr.abr_table = &(auto_bitrate_adjust_table_lhdcv5_192k_25f[0]);
      }
      else if (frame_duration == LHDCV5_FRAME_5MS)
      {
        handle_abr.abr_table = &(auto_bitrate_adjust_table_lhdcv5_192k_50f[0]);
      }
      else if (frame_duration == LHDCV5_FRAME_10MS)
      {
        handle_abr.abr_table = &(auto_bitrate_adjust_table_lhdcv5_192k_100f[0]);
      }
      else
      {
        func_ret = LHDCV5_FRET_INVALID_INPUT_PARAM;
        goto ABR_EXIT_FUNC;
      }
    }
    else
    {
      LHDC_LOGE ("Sample rate is invalid (%u)!", sample_rate);
      func_ret = LHDCV5_FRET_INVALID_INPUT_PARAM;
      goto ABR_EXIT_FUNC;
    }
  }
  else
  {
    // lossless/raw mode:
    if (sample_rate == LHDCV5_SR_48000HZ && bits_per_sample == LHDCV5BT_SMPL_FMT_S16)
    {
      if (frame_duration == LHDCV5_FRAME_2P5MS)
      {
        handle_abr.abr_table = &(auto_bitrate_adjust_table_lhdcv5_lless25_48k_16b[0]);
      }
      else if (frame_duration == LHDCV5_FRAME_5MS)
      {
        handle_abr.abr_table = &(auto_bitrate_adjust_table_lhdcv5_lless50_48k_16b[0]);
      }
      else
      {
        func_ret = LHDCV5_FRET_INVALID_INPUT_PARAM;
        goto ABR_EXIT_FUNC;
      }
    }
    else if (sample_rate == LHDCV5_SR_48000HZ && bits_per_sample == LHDCV5BT_SMPL_FMT_S24)
    {
      if (frame_duration == LHDCV5_FRAME_2P5MS)
      {
        handle_abr.abr_table = &(auto_bitrate_adjust_table_lhdcv5_lless25_48k_24b[0]);
      }
      else if (frame_duration == LHDCV5_FRAME_5MS)
      {
        handle_abr.abr_table = &(auto_bitrate_adjust_table_lhdcv5_lless50_48k_24b[0]);
      }
      else
      {
        func_ret = LHDCV5_FRET_INVALID_INPUT_PARAM;
        goto ABR_EXIT_FUNC;
      }
    }
    else if (sample_rate == LHDCV5_SR_96000HZ && bits_per_sample == LHDCV5BT_SMPL_FMT_S24)
    {
      if (frame_duration == LHDCV5_FRAME_2P5MS)
      {
        handle_abr.abr_table = &(auto_bitrate_adjust_table_lhdcv5_lless25_96k_24b[0]);
      }
      else if (frame_duration == LHDCV5_FRAME_5MS)
      {
        handle_abr.abr_table = &(auto_bitrate_adjust_table_lhdcv5_lless50_96k_24b[0]);
      }
      else
      {
        func_ret = LHDCV5_FRET_INVALID_INPUT_PARAM;
        goto ABR_EXIT_FUNC;
      }
    }
    else
    {
      LHDC_LOGE ("Sample rate is invalid (%u)!", sample_rate);
      func_ret = LHDCV5_FRET_INVALID_INPUT_PARAM;
      goto ABR_EXIT_FUNC;
    }
  }

  handle_abr.gABR_table_index = LHDCV5_AUTOBITRATE_DEFAULT_TABLE_INDEX;
  handle_abr.down_bitrate_count = 0;
  handle_abr.down_bitrate_sum = 0;
  handle_abr.up_bitrate_count = 0;
  handle_abr.up_bitrate_sum = 0;

  // setup VBR condition thresholds
  func_ret = lhdcv5_util_set_vbr_up_th(handle, VBR_UP_LOSSY_RATIO_THRESHOLD);
  if (func_ret < LHDCV5_FRET_SUCCESS) goto ABR_EXIT_FUNC;

  func_ret = lhdcv5_util_set_vbr_dn_th(handle, VBR_DOWN_LOSSLESS_RATIO_THRESHOLD);
  if (func_ret < LHDCV5_FRET_SUCCESS) goto ABR_EXIT_FUNC;

  func_ret = lhdcv5_util_set_vbr_up_intv(handle, VBR_UP_RATE_TIME_CNT);
  if (func_ret < LHDCV5_FRET_SUCCESS) goto ABR_EXIT_FUNC;

  func_ret = lhdcv5_util_set_vbr_dn_intv(handle, VBR_DOWN_RATE_TIME_CNT);
  if (func_ret < LHDCV5_FRET_SUCCESS) goto ABR_EXIT_FUNC;


ABR_EXIT_FUNC:
  return func_ret;
}

