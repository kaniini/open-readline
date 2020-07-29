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

#include <string.h>
#include "history.h"

/* State management. */
static HISTORY_STATE *current_state = NULL;

void
using_history(void)
{
	current_state = calloc(1, sizeof *current_state);
}

static HISTORY_STATE *
__history_state_copy(const HISTORY_STATE *state)
{
	HISTORY_STATE *out_state = calloc(1, sizeof *out_state);
	if (out_state == NULL)
		abort();

	out_state->entries = state->entries;
	out_state->offset = state->offset;
	out_state->length = state->length;
	out_state->size = state->size;
	out_state->flags = state->flags;

	return out_state;	
}

HISTORY_STATE *
history_get_history_state(void)
{
	return __history_state_copy(current_state);
}

void
history_set_history_state(const HISTORY_STATE *state)
{
	free(current_state);
	current_state = __history_state_copy(state);
}

void
clear_history(void)
{
	for (size_t i = 0; current_state->entries[i] != NULL; i++)
	{
		free_history_entry(current_state->entries[i]);
		current_state->entries[i] = NULL;
	}
}

void
stifle_history(int size)
{
	current_state->flags |= HS_STIFLED;
	current_state->size = size;
}

int
unstifle_history(void)
{
	current_state->flags &= ~HS_STIFLED;
	return current_state->size;
}

int
history_is_stifled(void)
{
	return current_state->flags & HS_STIFLED;
}

/* HIST_ENTRY lifecycle. */
HIST_ENTRY *
alloc_history_entry(const char *line, const char *timestamp)
{
	HIST_ENTRY *entry = calloc(1, sizeof *entry);

	entry->line = line != NULL ? strdup(line) : NULL;
	entry->timestamp = timestamp != NULL ? strdup(timestamp) : NULL;
	entry->data = NULL;

	return entry;
}

HIST_ENTRY *
copy_history_entry(const HIST_ENTRY *entry)
{
	HIST_ENTRY *out_entry = alloc_history_entry(entry->line, entry->timestamp);
	out_entry->data = entry->data;

	return out_entry;
}

void *
free_history_entry(HIST_ENTRY *entry)
{
	void *data = entry->data;

	if (entry->timestamp != NULL)
		free(entry->timestamp);

	if (entry->line != NULL)
		free(entry->line);

	free(entry);

	return data;
}
