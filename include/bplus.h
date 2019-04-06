#ifndef _BPLUS_H_
#define _BPLUS_H_

#include <stdint.h> /* uintx_t */

#ifdef __cplusplus
extern "C" {
#endif

#define BP_PADDING 64

#define BP_KEY_FIELDS   \
		uint64_t length;    \
		char *value;

#define BP_KEY_PRIVATE                  \
    uint64_t _prev_offset;              \
    uint64_t _prev_length;

#define BP_OK              0

#define BP_EFILE           0x101
#define BP_EFILEREAD_OOB   0x102
#define BP_EFILEREAD       0x103
#define BP_EFILEWRITE      0x104
#define BP_EFILEFLUSH      0x105
#define BP_EFILERENAME     0x106
#define BP_ECOMPACT_EXISTS 0x107
#define BP_NO_MALLOC       0x108

#define BP_ECOMP           0x201
#define BP_EDECOMP         0x202

#define BP_EALLOC          0x301
#define BP_EMUTEX          0x302
#define BP_ERWLOCK         0x303

#define BP_ENOTFOUND       0x401
#define BP_ESPLITPAGE      0x402
#define BP_EEMPTYPAGE      0x403
#define BP_EUPDATECONFLICT 0x404
#define BP_EREMOVECONFLICT 0x405

typedef struct bp_db_s bp_db_t;

typedef struct bp_key_s bp_key_t;
typedef struct bp_key_s bp_value_t;

struct bp_key_s {
	BP_KEY_FIELDS
	BP_KEY_PRIVATE
};

typedef int (*bp_compare_cb)(const bp_key_t *a, const bp_key_t *b);
typedef int (*bp_update_cb)(void *arg,
														const bp_value_t *previous,
														const bp_value_t *value);
typedef int (*bp_remove_cb)(void *arg,
														const bp_value_t *value);
typedef void (*bp_range_cb)(void *arg,
														const bp_key_t *key,
														const bp_value_t *value);
typedef int (*bp_filter_cb)(void* arg, const bp_key_t *key);

/*
 * Open and close database
 */
int bp_open(bp_db_t **tree, const char *filename);
int bp_close(bp_db_t *tree);

/*
 * Get one value by key
 */
int bp_get(bp_db_t *tree, const bp_key_t *key, bp_value_t *value);
int bp_get_s(bp_db_t *tree, const char *key, char **value);

/*
 * Get previous value
 */
int bp_get_previous(bp_db_t *tree,
										const bp_value_t *value,
										bp_value_t *previous);

/*
 * Set one value by key (without solving conflicts, overwrite)
 */
int bp_set(bp_db_t *tree,
					 const bp_key_t *key,
					 const bp_value_t *value);
int bp_set_s(bp_db_t *tree,
						const char *key,
						const char *value);

/*
 * Update or create value by key (with solving conflicts)
 */
int bp_update(bp_db_t *tree,
							const bp_key_t *key,
							const bp_value_t *value,
							bp_update_cb update_cb,
							void *arg);
int bp_update_s(bp_db_t *tree,
							 const char *key,
							 const char *value,
							 bp_update_cb update_cb,
							 void *arg);

/*
 * Set multiple values by keys
 */
int bp_bulk_set(bp_db_t *tree,
								const uint64_t count,
								const bp_key_t **keys,
								const bp_value_t **values);
int bp_bulk_set_s(bp_db_t *tree,
								 const uint64_t count,
								 const char **keys,
								 const char **values);

/*
 * Update multiple values by keys
 */
int bp_bulk_update(bp_db_t *tree,
									 const uint64_t count,
									 const bp_key_t **keys,
									 const bp_value_t **values,
									 bp_update_cb update_cb,
									 void *arg);
int bp_bulk_update_s(bp_db_t *tree,
										const uint64_t count,
										const char **keys,
										const char **values,
										bp_update_cb update_cb,
										void *arg);

/*
 * Remove one value by key
 */
int bp_remove(bp_db_t *tree, const bp_key_t *key);
int bp_remove_s(bp_db_t *tree, const char *key);

/*
 * Remove value by key only if it's equal to specified one
 */
int bp_removev(bp_db_t *tree,
							 const bp_key_t *key,
							 bp_remove_cb remove_cb,
							 void *arg);
int bp_removev_s(bp_db_t *tree,
								const char *key,
								bp_remove_cb remove_cb,
								void *arg);

/*
 * Get all values in range
 * Note: value will be automatically freed after invokation of callback
 */
int bp_get_range(bp_db_t *tree,
								 const bp_key_t *start,
								 const bp_key_t *end,
								 bp_range_cb cb,
								 void *arg);
int bp_get_range_s(bp_db_t *tree,
									const char *start,
									const char *end,
									bp_range_cb cb,
									void *arg);

/*
 * Get values in range (with custom key-filter)
 * Note: value will be automatically freed after invokation of callback
 */
int bp_get_filtered_range(bp_db_t *tree,
													const bp_key_t *start,
													const bp_key_t *end,
													bp_filter_cb filter,
													bp_range_cb cb,
													void *arg);
int bp_get_filtered_range_s(bp_db_t *tree,
													 const char *start,
													 const char *end,
													 bp_filter_cb filter,
													 bp_range_cb cb,
													 void *arg);

/*
 * Run compaction on database
 */
int bp_compact(bp_db_t *tree);

/*
 * Set compare function to define order of keys in database
 */
void bp_set_compare_cb(bp_db_t *tree, bp_compare_cb cb);

/*
 * Ensure that all data is written to disk
 */
int bp_fsync(bp_db_t *tree);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* _BPLUS_H_ */
