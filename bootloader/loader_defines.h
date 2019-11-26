
#include <assert.h>
#include <stddef.h>
#include <stdbool.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>

#define BUILD_STUB

/* bootutil_priv.h*/
#define BOOT_MAGIC_GOOD     1
#define BOOT_MAGIC_BAD      2
#define BOOT_MAGIC_UNSET    3
#define BOOT_MAGIC_ANY      4  /* NOTE: control only, not dependent on sector */
#define BOOT_MAGIC_NOTGOOD  5  /* NOTE: control only, not dependent on sector */

/*
 * NOTE: leave BOOT_FLAG_SET equal to one, this is written to flash!
 */
#define BOOT_FLAG_SET       1
#define BOOT_FLAG_BAD       2
#define BOOT_FLAG_UNSET     3
#define BOOT_FLAG_ANY       4  /* NOTE: control only, not dependent on sector */

#define BOOT_STATUS_IDX_0   1

#define BOOT_STATUS_STATE_0 1
#define BOOT_STATUS_STATE_1 2
#define BOOT_STATUS_STATE_2 3

#ifdef MCUBOOT_IMAGE_NUMBER
#define BOOT_IMAGE_NUMBER       MCUBOOT_IMAGE_NUMBER
#else
#define BOOT_IMAGE_NUMBER       1
#endif

/*
 * Extract the swap type and image number from image trailers's swap_info
 * field.
 */
#define SWAP_INFO_SWAP_TYPE_MASK        (0x0Fu)
#define SWAP_INFO_SWAP_TYPE_POS         (0)
#define SWAP_INFO_IMAGE_NUM_MASK        (0xF0u)
#define SWAP_INFO_IMAGE_NUM_POS         (4)

#define BOOT_GET_SWAP_TYPE(swap_info)   ((swap_info) & SWAP_INFO_SWAP_TYPE_MASK)
#define BOOT_GET_IMAGE_NUM(swap_info)   ((swap_info) >> SWAP_INFO_IMAGE_NUM_POS)

/* Construct the swap_info field from swap type and image number */
#define BOOT_SET_SWAP_INFO(swap_info, image, type)  {                          \
                     assert(((image) & (SWAP_INFO_IMAGE_NUM_MASK >>            \
                                        SWAP_INFO_IMAGE_NUM_POS)) == (image)); \
                     assert(((type) & SWAP_INFO_SWAP_TYPE_MASK) == (type));    \
                     (swap_info) = (image) << SWAP_INFO_IMAGE_NUM_POS          \
                                 | (type);                                     \
                     }

/*
 * The current flashmap API does not check the amount of space allocated when
 * loading sector data from the flash device, allowing for smaller counts here
 * would most surely incur in overruns.
 *
 * TODO: make flashmap API receive the current sector array size.
 */
#if BOOT_MAX_IMG_SECTORS < 32
#error "Too few sectors, please increase BOOT_MAX_IMG_SECTORS to at least 32"
#endif

/** Number of image slots in flash; currently limited to two. */
#define BOOT_NUM_SLOTS                  2

/** Maximum number of image sectors supported by the bootloader. */
#define BOOT_STATUS_STATE_COUNT         3

#define BOOT_PRIMARY_SLOT               0
#define BOOT_SECONDARY_SLOT             1

#define BOOT_STATUS_SOURCE_NONE         0
#define BOOT_STATUS_SOURCE_SCRATCH      1
#define BOOT_STATUS_SOURCE_PRIMARY_SLOT 2

extern const uint32_t BOOT_MAGIC_SZ;

/**
 * Compatibility shim for flash sector type.
 *
 * This can be deleted when flash_area_to_sectors() is removed.
 */
#ifdef MCUBOOT_USE_FLASH_AREA_GET_SECTORS
typedef struct flash_sector boot_sector_t;
#else
typedef struct flash_area boot_sector_t;
#endif

/** Private state maintained during boot. */
struct boot_loader_state {
    struct {
        struct image_header hdr;
        const struct flash_area *area;
        boot_sector_t *sectors;
        size_t num_sectors;
        bool is_hdr_valid;
    } imgs[BOOT_IMAGE_NUMBER][BOOT_NUM_SLOTS];

    struct {
        const struct flash_area *area;
        boot_sector_t *sectors;
        size_t num_sectors;
    } scratch;

    uint8_t swap_type[BOOT_IMAGE_NUMBER];
    uint32_t write_sz;
};

/* These are macros so they can be used as lvalues. */
#define BOOT_IMG(state, slot) ((state)->imgs[current_image][(slot)])
#define BOOT_IMG_AREA(state, slot) (BOOT_IMG(state, slot).area)
#define BOOT_IMG_HDR_IS_VALID(state, slot) (BOOT_IMG(state, slot).is_hdr_valid)
#define BOOT_SCRATCH_AREA(state) ((state)->scratch.area)
#define BOOT_WRITE_SZ(state) ((state)->write_sz)
#define BOOT_SWAP_TYPE(state) ((state)->swap_type[current_image])

static inline struct image_header*
boot_img_hdr(struct boot_loader_state *state, size_t slot)
{
    return &BOOT_IMG(state, slot).hdr;
}

static inline size_t
boot_img_num_sectors(struct boot_loader_state *state, size_t slot)
{
    return BOOT_IMG(state, slot).num_sectors;
}

static inline size_t
boot_scratch_num_sectors(struct boot_loader_state *state)
{
    return state->scratch.num_sectors;
}


