/*
 * dialing_handler.h
 *
 *  Created on: Nov 21, 2015
 *	  Author: pchero
 */

#ifndef SRC_DIALING_HANDLER_H_
#define SRC_DIALING_HANDLER_H_

#include "asterisk/json.h"

#include <stdbool.h>

typedef enum _E_DIALING_STATUS_T
{
	E_DIALING_NONE				  = 0,	///< None state
	E_DIALING_ORIGINATE_REQUEST	 = 1,
	E_DIALING_DIAL_BEGIN,
	E_DIALING_CHANNEL_CREATE,
	E_DIALING_DIAL_END,
	E_DIALING_ORIGINATE_RESPONSE	= 5,
	E_DIALING_HANGUP,

	E_DIALING_ERROR				 = 10,   ///< error
} E_DIALING_STATUS_T;

typedef struct _rb_dialing{
	char* uuid;				 ///< dialing uuid(channel's unique id)
	char* name;				 ///< dialing name(channel's name)
	E_DIALING_STATUS_T status;  ///< dialing status

	char* tm_create;
	char* tm_update;
	char* tm_delete;
	struct timespec timeptr_update; ///< timestamp for timeout

	struct ast_json* j_dialing;	///< dialing info(result).
	struct ast_json* j_event;	///< current channel status info(the latest event)
	struct ast_json* j_events;		///< event info(json array).
} rb_dialing;

int init_rb_dialing(void);
rb_dialing* rb_dialing_create(const char* dialing_uuid, struct ast_json* j_camp, struct ast_json* j_plan, struct ast_json* j_dlma, struct ast_json* j_dest, struct ast_json* j_dl_list, struct ast_json* j_dial);
void rb_dialing_destory(rb_dialing* dialing);

rb_dialing* rb_dialing_find_chan_name(const char* chan);
rb_dialing* rb_dialing_find_chan_uuid(const char* chan);
bool rb_dialing_is_exist_uuid(const char* uuid);

struct ao2_iterator rb_dialing_iter_init(void);
void rb_dialing_iter_destroy(struct ao2_iterator* iter);
rb_dialing* rb_dialing_iter_next(struct ao2_iterator *iter);

struct ast_json* rb_dialing_get_all_for_cli(void);
struct ast_json* rb_dialing_get_info_for_cli(const char* uuid);

bool rb_dialing_update_name(rb_dialing* dialing, const char* name);
bool rb_dialing_update_status(rb_dialing* dialing, E_DIALING_STATUS_T status);
bool rb_dialing_update_events_append(rb_dialing* dialing, struct ast_json* j_evt);
bool rb_dialing_update_dialing_update(rb_dialing* dialing, struct ast_json* j_dialing);
bool rb_dialing_update_current_update(rb_dialing* dialing, struct ast_json* j_evt);
bool rb_dialing_update_event_substitute(rb_dialing* dialing, struct ast_json* j_evt);

int rb_dialing_get_count(void);
int rb_dialing_get_count_by_camp_uuid(const char* camp_uuid);


#endif /* SRC_DIALING_HANDLER_H_ */
