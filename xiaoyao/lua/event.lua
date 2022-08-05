local app = require "app"
local lua_app = require "lua_app"

local eventMgr = {}
eventMgr.events = {}

function eventMgr.subEvent(eventID, target, func)
	if not eventMgr.events[eventID] then
		eventMgr.events[eventID] = {}
	end
	for _, obj in pairs(eventMgr.events[eventID]) do
		if obj.target == target and obj.func == func then
			return
		end
	end
	local obj = {}
	obj.func = func
	obj.target = target
	obj.eventID = eventID
	table.insert(eventMgr.events[eventID], obj)
end



function eventMgr.unsubEvent(eventID, target, func)
	if not eventMgr.events[eventID] then
		return
	end
	local ok = false
	for i, obj in pairs(eventMgr.events[eventID]) do
		if obj.target == target and obj.func == func then
			ok = true
			eventMgr.events[eventID][i] = nil
			break
		end
	end
	--if not ok then
	--	print(debug.traceback())
	--end
end

function eventMgr.unsubAllEvent(target)
    for _, events in pairs(eventMgr.events) do
        for i, obj in pairs(events) do
            if obj.target == target then
                events[i] = nil
            end
        end
    end
end

function eventMgr.fireEvent(eventID, ...)
	if not eventMgr.events[eventID] then
		return
	end

	for _, obj in pairs(eventMgr.events[eventID]) do
		if type(obj.func) == "function" then
			obj.func(obj.target, ...)
		elseif type(obj.func) == "string" then
			local func = obj.target[obj.func] 
			if func and type(func) == "function" then
				func(obj.target, ...)
			end
		end
	end

end


eventMgr.event = 
{
    open_mutual = 1,    --打开交互
    patch_end = 2,      --寻路结束
    npcshop_open = 3,   --npc商店打开
    giveui_open = 4,    --给予界面打开
    pet_trade_open = 5, --宠物交易界面打开
    pet_list_select_open = 6, --宠物上交选择界面打开
    prop_event_start = 10,    --人物属性事件
    prop_event_end = 1000, --人物属性事件
    sale_center_open = 1001, --寄售物品界面打开
    shang_hui_open = 1002, --商会界面打开  银币购买物品
    progress_item_open = 1003, --进度条物品使用界面打开
    mission_guid_open = 1003, --右下角任务使用界面打开
    team_invite = 1004, --队伍邀请
	actor_ready_ins = 1005, --人物开始使用技能
	pet_ready_ins = 1006, --宠物开始使用技能
	fishing_bar = 1007,		--鱼竿拉起
	begin_da_ti = 1008,		--开始世界答题
}




eventMgr.makePropEvent = function (prop)
    return eventMgr.event.prop_event_start + prop
end




--for c++
__G__OPEN__MUTUAL__ = function(TargetEntityID, mutualID, selects, contexts)
	eventMgr.fireEvent(eventMgr.event.open_mutual, TargetEntityID, mutualID, selects, contexts)
end
--for c++
__G__AUTO_PATCH_END__ = function()
	eventMgr.fireEvent(eventMgr.event.patch_end)
end
--for c++
__G__NPC_SHOP_OPEN__ = function(st)
	eventMgr.fireEvent(eventMgr.event.npcshop_open, st)
end
--for c++
__G_OPEN_GIVE_UI__ = function ()
	eventMgr.fireEvent(eventMgr.event.giveui_open)
end
--for c++
__G__OPEN_PET_TRADE_CENTER__ = function (firstCatchId)
	eventMgr.fireEvent(eventMgr.event.pet_trade_open, firstCatchId)
end
--for c++
__G__OPEN_PET_LIST_SELECT__ = function (selectPetHandel)
	eventMgr.fireEvent(eventMgr.event.pet_list_select_open, selectPetHandel)
end
--for c++
__G__PROP_CHANGE__ = function (prop, old, new)
	--lua_app.print(7, "__G__PROP_CHANGE__", prop, old, new)
	local event = eventMgr.makePropEvent(prop)
	eventMgr.fireEvent(event, prop, old, new)
end
--for c++
__G_SALE_CENTER_OPEN__ = function (isTaskOpen, guids)
	lua_app.print(7, "__G_SALE_CENTER_OPEN__", isTaskOpen)
	table.print(guids, 11)
	eventMgr.fireEvent(eventMgr.event.sale_center_open, isTaskOpen, guids)
end
--for c++
__G_SHANG_HUI_OPEN__ = function (itemId, num)
	lua_app.print(7, "__G_SHANG_HUI_OPEN__", itemId, num)
	eventMgr.fireEvent(eventMgr.event.shang_hui_open, itemId, num)
end
--for c++
__G_PROGRESS_UI_OPEN__ = function (itemHandel)
	lua_app.print(7, "__G_PROGRESS_UI_OPEN__", itemHandel)
	eventMgr.fireEvent(eventMgr.event.progress_item_open, itemHandel)
end
--for c++
__G_MISSION_GUID_UI_OPEN__ = function (missionId, itemId)
	lua_app.print(7, "__G_MISSION_GUID_UI_OPEN__", missionId, itemId)
	eventMgr.fireEvent(eventMgr.event.mission_guid_open, missionId, itemId)
end
--for c++
__G_TEAM_INVITE__ = function (intvitTeamId, inviterName)
	lua_app.print(7, "__G_TEAM_INVITE__", intvitTeamId, inviterName)
	eventMgr.fireEvent(eventMgr.event.team_invite, intvitTeamId, inviterName)
end
--for c++
__G_ACTOR_READY_INS__ = function (bout)
	lua_app.print(7, "__G_ACTOR_READY_INS__", bout)
	eventMgr.fireEvent(eventMgr.event.actor_ready_ins, bout)
end
--for c++
__G_PET_READY_INS__ = function (bout, petEntityID)
	lua_app.print(7, "__G_PET_READY_INS__", bout, petEntityID)
	eventMgr.fireEvent(eventMgr.event.pet_ready_ins, bout, petEntityID)
end
--for c++
__G_FISHING_BAR__ = function ()
	lua_app.print(7, "__G_FISHING_BAR__")
	eventMgr.fireEvent(eventMgr.event.fishing_bar)
end
--for c++
__G_BEGIN_DA_TI__ = function (answer1, answer2)
	lua_app.print(7, "__G_BEGIN_DA_TI__ ", answer1, answer2)
	eventMgr.fireEvent(eventMgr.event.begin_da_ti, answer1, answer2)
end

return eventMgr