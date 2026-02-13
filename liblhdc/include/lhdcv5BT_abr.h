#ifndef INCLUDE_LHDCV5BT_ABR_H_
#define INCLUDE_LHDCV5BT_ABR_H_

// element counts in auto bitrate adjust table
#define LHDCV5_AUTOBITRATE_ADJTABLE_COUNT (6)
#define LHDCV5_AUTOBITRATE_ADJTABLE_MAX_INDEX (LHDCV5_AUTOBITRATE_ADJTABLE_COUNT - 1)
#define LHDCV5_AUTOBITRATE_DEFAULT_TABLE_INDEX (LHDCV5_AUTOBITRATE_ADJTABLE_COUNT - 1)

// ABR: policy parameters and bit rate adjustment tables
/*******************************************************************************/
#define ABR_UP_RATE_TIME_CNT              300  // ABR bitrate upgrade checking interval (by tick count)
#define ABR_DOWN_RATE_TIME_CNT            4    // ABR bitrate downgrade checking interval (by tick count)
#define ABR_UP_QUEUE_LENGTH_THRESHOLD     1    // The threshold of ABR bitrate upgrade condition
#define ABR_DOWN_QUEUE_LENGTH_THRESHOLD   2    // The threshold of ABR bitrate downgrade condition
#define ABR_DOWN_TARGET_STAGE             0    // The target bitrate in ABR table that go downgrade

// VBR: policy parameters and bit rate adjustment tables
/*******************************************************************************/
#define VBR_UP_RATE_TIME_CNT                  100   // (default)VBR bitrate upgrade checking interval (by tick count)
#define VBR_DOWN_RATE_TIME_CNT                100   // (default)VBR bitrate downgrade checking interval (by tick count)
#define VBR_UP_LOSSY_RATIO_THRESHOLD          0     // (default) (at most) lossy ratio threshold(percentage: integer 0~100)
#define VBR_DOWN_LOSSLESS_RATIO_THRESHOLD     100   // (default) (at least) lossless ratio threshold(percentage: integer 0~100)
#define VBR_DEMOTE_TO_LOSSY_QLENGTH_THRESHOLD 5     // The threshold that demoting step from VBR to ABR
#define VBR_DEMOTE_TO_LOSSY_INDEX             0     // The target bitrate stage in ABR table of demoting step
#define VBR_PROMOTE_TO_LOSSLESS_INDEX         (LHDCV5_QUALITY_HIGH)   // promote target bitrate index in VBR-lossless table
/*******************************************************************************/

typedef struct _lhdcv5_abr_s {
  uint32_t *abr_table;  // ptr to the actual ABR bitrate table
  uint32_t gABR_table_index;    // record current index in the ABR bitrate table
  uint32_t down_bitrate_count;
  uint32_t down_bitrate_sum;
  uint32_t up_bitrate_count;
  uint32_t up_bitrate_sum;
} lhdcv5_abr_cb_t;


//----------------------------------------------------------------
// lhdcv5BT_adjust_bitrate_init ()
//
// Initialize auto bit rate mechanism
//  Parameter
//      [in] handle: a pointer to the memory resource allocated to the encoder.
//  Return
//      LHDCV5_FRET_SUCCESS: Succeed
//      otherwise: Fail
//----------------------------------------------------------------
int32_t lhdcv5BT_autoBR_adjust_bitrate_init
(
    HANDLE_LHDCV5_BT handle,
    uint32_t sample_rate,
    uint32_t bits_per_sample,
    uint32_t frame_duration
);


//----------------------------------------------------------------
// lhdcv5BT_adjust_bitrate_process ()
//
// call auto bit rate mechanism
//  Parameter
//      [in] handle: a pointer to the memory resource allocated to the encoder.
//  Return
//      LHDCV5_FRET_SUCCESS: Succeed
//      otherwise: Fail
//----------------------------------------------------------------
int32_t lhdcv5BT_autoBR_adjust_bitrate_process
(
    HANDLE_LHDCV5_BT lhdc_handle,
    uint32_t queue_len
);

//----------------------------------------------------------------
// lhdcv5BT_autoBR_reset_abr_index ()
//
// reset auto bit rate mechanism: ABR table index
//  Parameter
//  Return
//      LHDCV5_FRET_SUCCESS: Succeed
//      otherwise: Fail
//----------------------------------------------------------------
int32_t lhdcv5BT_autoBR_reset_abr_index
(
    void
);

#endif /* INCLUDE_LHDCV5BT_ABR_H_ */
