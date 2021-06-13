#ifndef EQEMU_TASKS_H
#define EQEMU_TASKS_H

#define MAXTASKS 10000
#define MAXTASKSETS 1000
#define MAXACTIVEQUESTS 19 // The Client has a hard cap of 19 active quests, 29 in SoD+
#define MAXCHOOSERENTRIES 40 // The Max Chooser (Task Selector entries) is capped at 40 in the Titanium Client.
#define MAXACTIVITIESPERTASK 20 // The Client has a hard cap of 20 activities per task.
#define TASKSLOTEMPTY 0 // This is used to determine if a client's active task slot is empty.

#define TASKSLOTTASK 0
#define TASKSLOTSHAREDTASK 0

// Command Codes for worldserver ServerOP_ReloadTasks
#define RELOADTASKS 0
#define RELOADTASKGOALLISTS 1
#define RELOADTASKPROXIMITIES 2
#define RELOADTASKSETS 3

typedef enum {
	METHODSINGLEID = 0,
	METHODLIST     = 1,
	METHODQUEST    = 2
} TaskMethodType;

struct ActivityInformation {
	int              step_number;
	int              activity_type;
	std::string      target_name; // name mob, location -- default empty
	std::string      item_list; // likely defaults to empty
	std::string      skill_list; // IDs ; separated -- default -1
	std::string      spell_list; // IDs ; separated -- default 0
	std::string      description_override; // overrides auto generated description -- default empty
	int              skill_id; // older clients, first id from above
	int              spell_id; // older clients, first id from above
	int              goal_id;
	TaskMethodType   goal_method;
	int              goal_count;
	int              deliver_to_npc;
	std::vector<int> zone_ids;
	std::string      zones; // IDs ; searated, ZoneID is the first in this list for older clients -- default empty string
	bool             optional;

	inline bool CheckZone(int zone_id)
	{
		if (zone_ids.empty()) {
			return true;
		}
		return std::find(zone_ids.begin(), zone_ids.end(), zone_id) != zone_ids.end();
	}
};

typedef enum {
	ActivitiesSequential = 0,
	ActivitiesStepped    = 1
} SequenceType;

enum class TaskType {
	Task   = 0,        // can have at max 1
	Shared = 1,        // can have at max 1
	Quest  = 2,        // can have at max 19 or 29 depending on client
	E      = 3         // can have at max 19 or 29 depending on client, not present in live anymore
};

static const uint8 TASK_TYPE_TASK   = 0;
static const uint8 TASK_TYPE_SHARED = 1;
static const uint8 TASK_TYPE_QUEST  = 2;

enum class DurationCode {
	None   = 0,
	Short  = 1,
	Medium = 2,
	Long   = 3
};

struct TaskInformation {
	TaskType            type;
	int                 duration{};
	DurationCode        duration_code;         // description for time investment for when duration == 0
	std::string         title{};            // max length 64
	std::string         description{};      // max length 4000, 2048 on Tit
	std::string         reward{};
	std::string         item_link{};        // max length 128 older clients, item link gets own string
	std::string         completion_emote{}; // emote after completing task, yellow. Maybe should make more generic ... but yellow for now!
	int                 reward_id{};
	int                 cash_reward{};       // Expressed in copper
	int                 experience_reward{};
	int                 faction_reward{};   // just a npc_faction_id
	TaskMethodType      reward_method;
	int                 activity_count{};
	SequenceType        sequence_mode;
	int                 last_step{};
	short               min_level{};
	short               max_level{};
	bool                repeatable{};
	ActivityInformation activity_information[MAXACTIVITIESPERTASK];
};

typedef enum {
	ActivityHidden    = 0,
	ActivityActive    = 1,
	ActivityCompleted = 2
}                  ActivityState;

typedef enum {
	ActivityDeliver    = 1,
	ActivityKill       = 2,
	ActivityLoot       = 3,
	ActivitySpeakWith  = 4,
	ActivityExplore    = 5,
	ActivityTradeSkill = 6,
	ActivityFish       = 7,
	ActivityForage     = 8,
	ActivityCastOn     = 9,
	ActivitySkillOn    = 10,
	ActivityTouch      = 11,
	ActivityCollect    = 13,
	ActivityGiveCash   = 100
}                  ActivityType;

struct ClientActivityInformation {
	int           activity_id;
	int           done_count;
	ActivityState activity_state;
	bool          updated; // Flag so we know if we need to updated the database
};

struct ClientTaskInformation {
	int                       slot; // intrusive, but makes things easier :P
	int                       task_id;
	int                       current_step;
	int                       accepted_time;
	bool                      updated;
	ClientActivityInformation activity[MAXACTIVITIESPERTASK];
};

struct CompletedTaskInformation {
	int  task_id;
	int  completed_time;
	bool activity_done[MAXACTIVITIESPERTASK];
};

namespace Tasks {

	inline int GetActivityStateIdentifier(ActivityState activity_state)
	{
		switch (activity_state) {
			case ActivityHidden:
				return 0;
			case ActivityActive:
				return 1;
			case ActivityCompleted:
				return 2;
			default:
				return 0;
		}
	}
	inline std::string GetActivityStateDescription(ActivityState activity_state)
	{
		switch (activity_state) {
			case ActivityHidden:
				return "Hidden";
			case ActivityActive:
				return "Active";
			case ActivityCompleted:
				return "Completed";
			default:
				return "Hidden";
		}
	}

	inline int GetTaskTypeIdentifier(TaskType task_type)
	{
		switch (task_type) {
			case TaskType::Task:
				return 0;
			case TaskType::Shared:
				return 1;
			case TaskType::Quest:
				return 2;
			case TaskType::E:
				return 3;
			default:
				return 0;
		}
	}
	inline std::string GetTaskTypeDescription(TaskType task_type)
	{
		switch (task_type) {
			case TaskType::Task:
				return "Task";
			case TaskType::Shared:
				return "Shared";
			case TaskType::Quest:
				return "Quest";
			case TaskType::E:
				return "E";
			default:
				return "Task";
		}
	}
}

namespace SharedTaskMessage {
	static constexpr uint16 AVG_LVL_HIGH                                      = 8889; // You can not be assigned this shared task because your party's average level is too high.
	static constexpr uint16 LVL_SPREAD_HIGH                                   = 8890; // You can not be assigned this shared task because your party's level spread is too high.
	static constexpr uint16 PARTY_EXCEED_MAX_PLAYER                           = 8891; // You can not be assigned this shared task because your party exceeds the maximum allowed number of players.
	static constexpr uint16 LEADER_NOT_MEET_REQUIREMENTS                      = 8892; // You can not be assigned this shared task because the leader does not meet the shared task requirements.
	static constexpr uint16 SHARED_TASK_NOT_MEET_MIN_NUM_PLAYER               = 8895; // You can not be assigned this shared task because your party does not contain the minimum required number of players.
	static constexpr uint16 WILL_REMOVE_ZONE_TWO_MIN_RAID_NOT_MIN_NUM_PLAYER  = 8908; // %1 will be removed from their zone in two minutes because your raid does not meet the minimum requirement of qualified players.
	static constexpr uint16 WILL_REMOVE_ZONE_TWO_MIN_GROUP_NOT_MIN_NUM_PLAYER = 8909; // %1 will be removed from their zone in two minutes because your group does not meet the minimum requirement of qualified players.
	static constexpr uint16 WILL_REMOVE_AREA_TWO_MIN_RAID_NOT_MIN_NUM_PLAYER  = 8910; // %1 will be removed from their area in two minutes because your raid does not meet the minimum requirement of qualified players.
	static constexpr uint16 WILL_REMOVE_AREA_TWO_MIN_GROUP_NOT_MIN_NUM_PLAYER = 8911; // %1 will be removed from their area in two minutes because your group does not meet the minimum requirement of qualified players.
	static constexpr uint16 HAS_REMOVED_ZONE_TWO_MIN_RAID_NOT_MIN_NUM_PLAYER  = 8912; // %1 has been removed from their zone because your raid does not meet the minimum requirement of qualified players.
	static constexpr uint16 HAS_REMOVED_ZONE_TWO_MIN_GROUP_NOT_MIN_NUM_PLAYER = 8913; // %1 has been removed from their zone because your group does not meet the minimum requirement of qualified players.
	static constexpr uint16 HAS_REMOVED_AREA_TWO_MIN_RAID_NOT_MIN_NUM_PLAYER  = 8914; // %1 has been removed from their area because your raid does not meet the minimum requirement of qualified players.
	static constexpr uint16 HAS_REMOVED_AREA_TWO_MIN_GROUP_NOT_MIN_NUM_PLAYER = 8915; // %1 has been removed from their area because your group does not meet the minimum requirement of qualified players.
	static constexpr uint16 SEND_INVITE_TO                                    = 8916; // Sending a shared task invitation to %1.
	static constexpr uint16 COULD_NOT_BE_INVITED                              = 8917; // %1 could not be invited to join you.
	static constexpr uint16 YOU_ARE_NOT_LEADER_COMMAND_ISSUE                  = 8919; // You are not the shared task leader.  Only %1 can issue this command.
	static constexpr uint16 SWAP_SENDING_INVITATION_TO                        = 8920; // Sending an invitation to: %1.  They must accept in order to swap party members.
	static constexpr uint16 SWAP_ACCEPTED_OFFER                               = 8921; // %1 has accepted your offer to join your shared task.  Swapping %1 for %2.
	static constexpr uint16 IS_NOT_MEMBER                                     = 8922; // %1 is not a member of this shared task.
	static constexpr uint16 NOT_ALLOW_PLAYER_REMOVE                           = 8923; // The shared task is not allowing players to be removed from it at this time.
	static constexpr uint16 PLAYER_HAS_BEEN_REMOVED                           = 8924; // %1 has been removed from your shared task, '%2'.
	static constexpr uint16 TRANSFER_LEADERSHIP_NOT_ONLINE                    = 8925; // %1 is not currently online.  You can only transfer leadership to an online member of the shared task.
	static constexpr uint16 MADE_LEADER                                       = 8926; // %1 has been made the leader for this shared task.
	static constexpr uint16 YOU_MADE_LEADER                                   = 8927; // You have been made the leader of this shared task.
	static constexpr uint16 LEADER_PRINT                                      = 8928; // Shared Task Leader: %1
	static constexpr uint16 MEMBERS_PRINT                                     = 8929; // Shared Task Members: %1
	static constexpr uint16 PLAYER_ACCEPTED_OFFER_JOIN                        = 8930; // %1 has accepted your offer to join your shared task.
	static constexpr uint16 PLAYER_HAS_BEEN_ADDED                             = 8931; // %1 has been added to your shared task, '%2'.
	static constexpr uint16 ACCEPTED_OFFER_TO_JOIN_BUT_COULD_NOT              = 8932; // %1 accepted your offer to join your shared task but could not.
	static constexpr uint16 PLAYER_DECLINED_OFFER                             = 8933; // %1 has declined your offer to join your shared task.
	static constexpr uint16 PLAYER_HAS_ASKED_YOU_TO_JOIN                      = 8934; // %1 has asked you to join the shared task '%2'.        Would you like to join?
	static constexpr uint16 NO_REQUEST_BECAUSE_HAVE_ONE                       = 8935; // You may not request a shared task because you already have one.
	static constexpr uint16 NO_REQUEST_BECAUSE_RAID_HAS_ONE                   = 8936; // You may not request a shared task because someone in your raid, %1, already has one.
	static constexpr uint16 NO_REQUEST_BECAUSE_GROUP_HAS_ONE                  = 8937; // You may not request a shared task because someone in your group, %1, already has one.
	static constexpr uint16 YOU_DO_NOT_MEET_REQ_AVAILABLE                     = 8938; // You do not meet the requirements for any available shared tasks.
	static constexpr uint16 YOUR_RAID_DOES_NOT_MEET_REQ                       = 8939; // Your raid does not meet the requirements for any available shared tasks.
	static constexpr uint16 YOUR_GROUP_DOES_NOT_MEET_REQ                      = 8940; // Your group does not meet the requirements for any available shared tasks.
	static constexpr uint16 YOUR_GROUP__RAID_DOES_NOT_MEET_REQ                = 8941; // You can not be assigned this shared task because the raid or group does not meet the shared task requirements.
	static constexpr uint16 YOU_NO_LONGER_MEMBER                              = 8942; // You are no longer a member of the shared task.
	static constexpr uint16 YOU_MAY_NOT_REQUEST_EXPANSION                     = 8943; // You may not request this shared task because you do not have the required expansion.
	static constexpr uint16 PLAYER_MAY_NOT_REQUEST_EXPANSION                  = 8944; // You may not request this shared task because %1 does not have the required expansion.
	static constexpr uint16 TWO_MIN_REQ_TASK_TERMINATED                       = 8945; // If your party does not meet the requirements in two minutes, the shared task will be terminated.
	static constexpr uint16 YOU_MUST_WAIT_TIME_LOCKOUT_TYPE                   = 8946; // You may not request this shared task because you must wait %1d:%2h:%3m before you can do another task of this type.
	static constexpr uint16 PLAYER_MUST_WAIT_TIME_LOCKOUT_TYPE                = 8947; // You may not request this shared task because %1 must wait %2d:%3h:%4m before they can do another task of this type.
	static constexpr uint16 PLAYER_NOW_LEADER                                 = 8948; // %1 is now the leader of your shared task, '%2'.
	static constexpr uint16 HAS_ENDED                                         = 8951; // Your shared task, '%1', has ended.
	static constexpr uint16 YOU_ALREADY_LEADER                                = 8952; // You are already the leader of the shared task.
	static constexpr uint16 TASK_NO_LONGER_ACTIVE                             = 8953; // Your shared task, '%1', is no longer active.
	static constexpr uint16 YOU_HAVE_BEEN_ADDED_TO_TASK                       = 8954; // You have been added to the shared task '%1'.
	static constexpr uint16 YOU_ARE_NOW_LEADER                                = 8955; // You are now the leader of your shared task, '%1'.
	static constexpr uint16 YOU_HAVE_BEEN_REMOVED                             = 8956; // You have been removed from the shared task '%1'.
	static constexpr uint16 YOU_ARE_NO_LONGER_A_MEMBER                        = 8960; // You are no longer a member of the shared task, '%1'.
	static constexpr uint16 YOUR_TASK_NOW_LOCKED                              = 8961; // Your shared task is now locked.  You may no longer add or remove players.
	static constexpr uint16 TASK_NOT_ALLOWING_PLAYERS_AT_TIME                 = 8962; // The shared task is not allowing players to be added at this time.
	static constexpr uint16 PLAYER_NOT_ONLINE_TO_ADD                          = 8963; // %1 is not currently online.  A player needs to be online to be added to a shared task.
	static constexpr uint16 CANT_ADD_PLAYER_ALREADY_MEMBER                    = 8964; // You can not add %1 because they are already a member of this shared task.
	static constexpr uint16 CANT_ADD_PLAYER_ALREADY_ASSIGNED                  = 8965; // You can not add %1 because they are already assigned to another shared task.
	static constexpr uint16 PLAYER_ALREADY_OUTSTANDING_INVITATION_THIS        = 8966; // %1 already has an outstanding invitation to join this shared task.
	static constexpr uint16 PLAYER_ALREADY_OUTSTANDING_ANOTHER                = 8967; // %1 already has an outstanding invitation to join another shared task.  Players may only have one invitation outstanding.
	static constexpr uint16 CANT_ADD_PLAYER_MAX_PLAYERS                       = 8968; // You can not add another player since you currently have the maximum number of players allowed (%1) in this shared task.
	static constexpr uint16 CANT_ADD_PLAYER_MAX_LEVEL_SPREAD                  = 8969; // You can not add this player because you would exceed the maximum level spread (%1) for this shared task.
	static constexpr uint16 CANT_ADD_PLAYER_MAX_AVERAGE_LEVEL                 = 8970; // You can not add this player because you would exceed the maximum average level for this shared task.
	static constexpr uint16 CANT_ADD_PLAYER_FALL_MIN_AVG_LEVEL                = 8971; // You can not add this player because you would fall below the minimum average level for this shared task.
	static constexpr uint16 PLAYER_DOES_NOT_OWN_EXPANSION                     = 8972; // %1 does not own the expansion needed for this shared task.
	static constexpr uint16 CANT_ADD_PLAYER_PARTY_FILTER_REQ_FOR_TASK         = 8973; // You can not add this player because your party would no longer meet the filter requirements for this shared task.
	static constexpr uint16 CANT_ADD_PLAYER_ONE_OF_GROUP_RAID_HAS_TASK        = 8977; // You can not add %1 because they or one of their group or raid members is in another shared task.
	static constexpr uint16 CANT_JOIN_GROUP_ACTIVE_TASK                       = 8978; // You can not join that group because you have an active shared task.
	static constexpr uint16 CANT_ADD_PLAYER_CAUSE_LOCKOUT_TIME                = 8979; // You may not add %1 because they must wait %2d:%3h:%4m before they can do another task of this type.
	static constexpr uint16 CANT_LOOT_BECAUSE_TASK_LOCKED_BELONG              = 8980; // You may not loot that corpse because you are not in the shared task the corpse belongs to.
	static constexpr uint16 CANT_ADD_PLAYER_BECAUSE_GROUP_RAID_BELONG_TASK    = 8981; // The player could not be added to the raid because they or one of their group members is in a different shared task.
	static constexpr uint16 PLAYER_CANT_ADD_GROUP_BECAUSE_DIFF_TASK           = 8982; // %1 can not be added to the group because they are in a different shared task.
	static constexpr uint16 YOU_CANT_ADD_TO_GROUP_BECAUSE_DIFF_TASK           = 8983; // You can not be added to the group because you are in a different shared task.
	static constexpr uint16 PLAYER_CANT_ADD_RAID_BECAUSE_DIFF_TASK            = 8984; // %1 can not be added to the raid because they are in a different shared task.
	static constexpr uint16 YOU_CANT_ADD_RAID_BECAUSE_DIFF_TASK               = 8985; // You can not be added to the raid because you are in a different shared task.
	static constexpr uint16 REPLAY_TIMER_REMAINING                            = 8987; // '%1' replay timer:  %2d:%3h:%4m remaining.
	static constexpr uint16 YOU_NO_CURRENT_REPLAY_TIMERS                      = 8989; // You do not currently have any task replay timers.
	static constexpr uint16 SURE_QUIT_TASK                                    = 8995; // Are you sure you want to quit the task '%1'?
	static constexpr uint16 SURE_REMOVE_SELF_FROM_TASK                        = 8996; // Are you sure you want to remove yourself from the shared task '%1'
}

#endif //EQEMU_TASKS_H
