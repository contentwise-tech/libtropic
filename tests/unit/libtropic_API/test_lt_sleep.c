/**
 * @file test_libtropic__lt_sleep.c
 * @author Tropic Square s.r.o.
 *
 * @license For the license see file LICENSE.txt file in the root directory of this source tree.
 */

#include "libtropic.h"
#include "libtropic_common.h"
#include "lt_l2_api_structs.h"
#include "mock_lt_aesgcm.h"
#include "mock_lt_asn1_der.h"
#include "mock_lt_ed25519.h"
#include "mock_lt_hkdf.h"
#include "mock_lt_l1.h"
#include "mock_lt_l1_port_wrap.h"
#include "mock_lt_l2.h"
#include "mock_lt_l3.h"
#include "mock_lt_l3_process.h"
#include "mock_lt_random.h"
#include "mock_lt_sha256.h"
#include "mock_lt_x25519.h"
#include "string.h"
#include "time.h"
#include "unity.h"

//---------------------------------------------------------------------------------------------------------//
//---------------------------------- SETUP AND TEARDOWN ---------------------------------------------------//
//---------------------------------------------------------------------------------------------------------//

void setUp(void)
{
    char buffer[100] = {0};
#ifdef RNG_SEED
    srand(RNG_SEED);
#else
    time_t seed = time(NULL);
    // Using this approach, because in our version of Unity there's no TEST_PRINTF yet.
    // Also, raw printf is worse solution (without additional debug msgs, such as line).
    snprintf(buffer, sizeof(buffer), "Using random seed: %ld\n", seed);
    TEST_MESSAGE(buffer);
    srand((unsigned int)seed);
#endif
}

void tearDown(void) {}

//---------------------------------------------------------------------------------------------------------//
//---------------------------------- INPUT PARAMETERS   ---------------------------------------------------//
//---------------------------------------------------------------------------------------------------------//

// Test if function returns LT_PARAM_ERROR when invalid handle is passed
void test__invalid_handle() { TEST_ASSERT_EQUAL(LT_PARAM_ERR, lt_sleep(NULL, LT_L2_SLEEP_KIND_DEEP_SLEEP)); }

// Test if function returns LT_PARAM_ERROR when invalid sleep_kind is passed
void test__invalid_sleep_kind()
{
    lt_handle_t h = {0};
    TEST_ASSERT_EQUAL(LT_PARAM_ERR, lt_sleep(&h, LT_L2_SLEEP_KIND_DEEP_SLEEP + 1));
    TEST_ASSERT_EQUAL(LT_PARAM_ERR, lt_sleep(&h, LT_L2_SLEEP_KIND_DEEP_SLEEP - 1));
    TEST_ASSERT_EQUAL(LT_PARAM_ERR, lt_sleep(&h, LT_L2_SLEEP_KIND_SLEEP + 1));
    TEST_ASSERT_EQUAL(LT_PARAM_ERR, lt_sleep(&h, LT_L2_SLEEP_KIND_SLEEP - 1));
    TEST_ASSERT_EQUAL(LT_PARAM_ERR, lt_sleep(&h, 0));
}

//---------------------------------------------------------------------------------------------------------//
//---------------------------------- EXECUTION ------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------------//

/*// Test if function propagates l2 error if l2 transfer fails
void test__lt_l2_transfer_fail()
{
    lt_handle_t h = {0};

    lt_ret_t rets[] = {LT_L1_SPI_ERROR, LT_L1_CHIP_BUSY, LT_L1_DATA_LEN_ERROR, LT_L1_CHIP_STARTUP_MODE,
LT_L1_CHIP_ALARM_MODE, LT_PARAM_ERR};

    for(uint32_t i=0; i<(sizeof(rets)/sizeof(rets[0])); i++) {
        lt_l2_send_ExpectAndReturn(&h, LT_OK);
        lt_l2_receive_ExpectAndReturn(&h, rets[i]);
        TEST_ASSERT_EQUAL(rets[i], lt_sleep(&h, LT_L2_SLEEP_KIND_SLEEP));
    }

    for(uint32_t i=0; i<(sizeof(rets)/sizeof(rets[0])); i++) {
        lt_l2_send_ExpectAndReturn(&h, LT_OK);
        lt_l2_receive_ExpectAndReturn(&h, rets[i]);
        TEST_ASSERT_EQUAL(rets[i], lt_sleep(&h, LT_L2_SLEEP_KIND_DEEP_SLEEP));
    }
}

//---------------------------------------------------------------------------------------------------------//

uint16_t inject_rsp_len;
lt_ret_t callback__lt_l2_transfer(lt_handle_t *h, int __attribute__((unused))cmock_num_calls)
{
    struct lt_l2_encrypted_session_abt_rsp_t* p_l2_rsp = (struct lt_l2_encrypted_session_abt_rsp_t*)&h->l2_buff;
    p_l2_rsp->rsp_len = inject_rsp_len;

    return LT_OK;
}

// Test if function fails on size mismatch in l2 response
void test__resp_size_mismatch()
{
    lt_handle_t h = {0};

    inject_rsp_len = 0+1;
    lt_l2_send_ExpectAndReturn(&h, LT_OK);
    lt_l2_receive_StubWithCallback(callback__lt_l2_transfer);
    TEST_ASSERT_EQUAL(LT_FAIL, lt_sleep(&h, LT_L2_SLEEP_KIND_SLEEP));

}

//---------------------------------------------------------------------------------------------------------//

// Test if function returns LT_OK if all went correctly
void test__correct()
{
    lt_handle_t h = {0};

    inject_rsp_len = 0;
    lt_l2_send_ExpectAndReturn(&h, LT_OK);
    lt_l2_receive_StubWithCallback(callback__lt_l2_transfer);
    TEST_ASSERT_EQUAL(LT_OK, lt_sleep(&h, LT_L2_SLEEP_KIND_SLEEP));
}
*/