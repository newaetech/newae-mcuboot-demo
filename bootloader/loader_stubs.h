
#include <assert.h>
#include <stddef.h>
#include <stdbool.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>

#define BUILD_STUB

/*
 * \brief Verifies the image header: magic value, flags, integer overflow.
 *
 * \retval 0
 * \retval BOOT_EBADIMAGE
 */
static int
boot_verify_image_header(struct image_header *hdr);

/**
 * Checks whether on overflow can happen during a summation operation
 *
 * @param  a  First operand of summation
 *
 * @param  b  Second operand of summation
 *
 * @return    True in case of overflow, false otherwise
 */
bool
boot_add_uint32_overflow_check(uint32_t a, uint32_t b);

/*
 * This depends on the mappings defined in sysflash.h, and assumes that the
 * primary slot, the secondary slot, and the scratch area are contiguous.
 */
int flash_area_id_from_image_slot(int slot);

/**
 * `open` a flash area.  The `area` in this case is not the individual
 * sectors, but describes the particular flash area in question.
 *
 * Note: make sure return is 0 or assert test will fail
 * */
int flash_area_open(uint8_t id, const struct flash_area **area);

/**
 * Prepare image to be updated if required.
 *
 * Prepare image to be updated if required with completing an image swap
 * operation if one was aborted and/or determining the type of the
 * swap operation. In case of any error set the swap type to NONE.
 *
 * @param bs                    Pointer where the read and possibly updated
 *                              boot status can be written to.
 */
static void
boot_prepare_image_for_update(struct boot_status *bs);

int flash_area_read(const struct flash_area *area, uint32_t off, void *dst,
                    uint32_t len);

                    