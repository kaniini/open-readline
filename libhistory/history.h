/*
 * Copyright (c) 2020 Ariadne Conill <ariadne@dereferenced.org>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * This software is provided 'as is' and without any warranty, express or
 * implied.  In no event shall the authors be liable for any damages arising
 * from the use of this software.
 */

#ifndef LIBHISTORY_HISTORY_H__GUARD
#define LIBHISTORY_HISTORY_H__GUARD

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <time.h>

/* Structures used by libhistory. */

/* A history entry. */
typedef struct _hist_entry {
	char *line;
	char *timestamp;
	void *data;
} HIST_ENTRY;

/* Size of libhistory's memory allocations for a HIST_ENTRY. */
#define HISTENT_BYTES(hs)       (strlen ((hs)->line) + strlen ((hs)->timestamp))

/* A structure containing the state of the history library. */
typedef struct _hist_state {
	HIST_ENTRY **entries;
	int offset;
	int length;
	int size;
	int flags;
} HISTORY_STATE;

#define HS_STIFLED		(1 << 0)

/* State-management functions implemented by libhistory. */

/* Initialize internal state of libhistory. */
extern void using_history(void);

/* Get/set current internal state of libhistory. */
extern HISTORY_STATE *history_get_history_state(void);
extern void history_set_history_state(const HISTORY_STATE *state);

/* Lifecycle of history entries (HIST_ENTRY). */
extern HIST_ENTRY *alloc_history_entry(const char *line, const char *timestamp);
extern HIST_ENTRY *copy_history_entry(const HIST_ENTRY *entry);
extern void *free_history_entry(HIST_ENTRY *entry);

#ifdef __cplusplus
}
#endif

#endif
