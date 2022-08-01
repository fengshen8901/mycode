local lua_app = require "lua_app"
local app = require "app"
local scene = require "scene"
local WindowConfig = require "WindowConfig"
local lua_button1 = require "lua_button1"
local oo = require "class"
local PropConfig = require "PropConfig"
local ClientControl = require "ClientControl"
local eventMgr = require "event"
local FengYao = require "task.FengYao"
local PaoHuan = require "task.PaoHuan"
local onekeyMgr = require "task.onekey.onekeyMgr"
local common = require "common"
local itemBag = require "itemBag"
local useitemtask = require "task.useitemtask"
local battle = require "task.battle"
local huanjing = require "task.huanjing"
local menpairuqin = require "task.menpairuqin"
local clean_item = require "task.clean_item"
local thousandYear = require "task.qiannian"

local script_panel = {}


script_panel.init = function()
	if script_panel.has_init then
		return
	end
	script_panel.has_init = true

	--隐藏team_invites，不给其他人看
	local ret, team_invites = pcall(require, "task.battle_logic.team_invites")
	if ret and team_invites then
		lua_app.team_invites = team_invites
	end

	lua_app.add_timer(1000, script_panel.checkReStart)

	script_panel.rootwin = app.create_window("GameLook/ComposeImage1")
	script_panel.rootwin:set_property("UnifiedSize", "{{0,541},{0,537}}")
	script_panel.rootwin:set_property("UnifiedPosition", "{{0.5,-240},{0.5,-230}}")

	script_panel.rootwin:sub_click_event(script_panel.on_click_bg)

	script_panel.stopBtn = lua_button1.new()
	script_panel.stopBtn:create(script_panel.rootwin, "停  止", 40, 40)
	script_panel.stopBtn:sub_click_event(script_panel.on_click_stop)

	script_panel.onekeyBtn = lua_button1.new()
	script_panel.onekeyBtn:create(script_panel.rootwin, "一条龙", 40, 80)
	script_panel.onekeyBtn:sub_click_event(script_panel.on_click_onekey)

	script_panel.fengyaoBtn = lua_button1.new()
	script_panel.fengyaoBtn:create(script_panel.rootwin, "封  妖", 40, 120)
	script_panel.fengyaoBtn:sub_click_event(script_panel.on_click_fengyao)

	script_panel.paohuanBtn = lua_button1.new()
	script_panel.paohuanBtn:create(script_panel.rootwin, "跑  环", 40, 160)
	script_panel.paohuanBtn:sub_click_event(script_panel.on_click_paohuan)

	script_panel.hotfixBtn = lua_button1.new()
	script_panel.hotfixBtn:create(script_panel.rootwin, "热  更", 40, 200)
	script_panel.hotfixBtn:sub_click_event(script_panel.on_click_hotfix)

	script_panel.useitemBtn = lua_button1.new()
	script_panel.useitemBtn:create(script_panel.rootwin, "useitem", 40, 240)
	script_panel.useitemBtn:sub_click_event(script_panel.on_click_useitem)

	script_panel.playerBtn = lua_button1.new()
	script_panel.playerBtn:create(script_panel.rootwin, "我是谁", 40, 280)
	script_panel.playerBtn:sub_click_event(script_panel.on_click_player)

	script_panel.datiBtn = lua_button1.new()
	script_panel.datiBtn:create(script_panel.rootwin, "世界答题", 40, 320)
	script_panel.datiBtn:sub_click_event(script_panel.on_click_dati)
	lua_app.auto_dati = true
	script_panel.datiBtn:set_x(71)

	script_panel.showLogBtn = lua_button1.new()
	script_panel.showLogBtn:create(script_panel.rootwin, "显示日志", 40, 360)
	script_panel.showLogBtn:sub_click_event(script_panel.on_click_show_log)

	script_panel.huanjingBtn = lua_button1.new()
	script_panel.huanjingBtn:create(script_panel.rootwin, "幻  境", 40, 400)
	script_panel.huanjingBtn:sub_click_event(script_panel.on_click_huanjing)

	script_panel.ruqinBtn = lua_button1.new()
	script_panel.ruqinBtn:create(script_panel.rootwin, "门派入侵", 40, 440)
	script_panel.ruqinBtn:sub_click_event(script_panel.on_click_ruqin)

	script_panel.thousandYearBtn = lua_button1.new()
	script_panel.thousandYearBtn:create(script_panel.rootwin, "千年12", 40, 480)
	script_panel.thousandYearBtn:sub_click_event(script_panel.on_click_thousand_year)

	script_panel.autoBattleBtn = lua_button1.new()
	script_panel.autoBattleBtn:create(script_panel.rootwin, "自动战斗", 150, 40)
	script_panel.autoBattleBtn:sub_click_event(script_panel.on_click_auto_battle)

	script_panel.cleanitemBtn = lua_button1.new()
	script_panel.cleanitemBtn:create(script_panel.rootwin, "清理物品", 150, 80)
	script_panel.cleanitemBtn:sub_click_event(script_panel.on_click_clean_item)	
end

script_panel.open = function()
	--清理所有的注册事件，重新注册
	eventMgr.events = {}
	eventMgr.subEvent(eventMgr.event.team_invite, script_panel, script_panel.onTeamInvite)
	eventMgr.subEvent(eventMgr.event.begin_da_ti, script_panel, script_panel.onBeginDaTi)
	script_panel.init()
	script_panel.rootwin:set_property("Visible", "True")
	if script_panel.battle then
		script_panel.battle:destroy()
		script_panel.battle = nil
	end
	script_panel.battle = battle.new()
	script_panel.battle:start()
end

script_panel.stop_task = function()
	--清理所有的注册事件，重新注册
	eventMgr.events = {}
	eventMgr.subEvent(eventMgr.event.team_invite, script_panel, script_panel.onTeamInvite)
	eventMgr.subEvent(eventMgr.event.begin_da_ti, script_panel, script_panel.onBeginDaTi)

	if script_panel.battle then
		script_panel.battle:destroy()
		script_panel.battle = nil
	end
	script_panel.battle = battle.new()
	script_panel.battle:start()

	if script_panel.clean_item_task then
		script_panel.clean_item_task:destroy()
		script_panel.clean_item_task = nil
	end

	script_panel.click_btn_effect(script_panel.stopBtn)
	lua_app.task_type = nil
	lua_app.print(7, "lua_app.task_type = ", lua_app.task_type)
end

script_panel.checkReStart = function()
	lua_app.add_timer(1000, script_panel.checkReStart)
	if not lua_app.RestartIndex then
		lua_app.RestartIndex = 0
	end
	if script_panel.lastTask then
		if false == ClientControl.is_moving() then
			lua_app.RestartIndex = lua_app.RestartIndex + 1
			if lua_app.RestartIndex >= 30 then
				lua_app.RestartIndex = 0
				lua_app.print(12, "30秒任务 重启-----------------------------")
				script_panel.lastTask:destroy()
				script_panel.lastTask:start()
			end
		else
			lua_app.RestartIndex = 0
		end
	else
		lua_app.RestartIndex = 0
	end
end

script_panel.click_btn_effect = function(btn, task)
	if script_panel.lastClickBtn then
		script_panel.lastClickBtn:set_x(40)
	end
	btn:set_x(71)
	script_panel.lastClickBtn = btn
	if script_panel.lastTask then
		script_panel.lastTask:destroy()
	end
	script_panel.lastTask = nil
	if task then
		script_panel.lastTask = task
		task:start()
	end
end

script_panel.on_click_bg = function(click_type)
	--lua_app.print(7, "script_panel.on_click_root ", click_type)
	if click_type == WindowConfig.rightClick then
		script_panel.rootwin:set_property("Visible", "False")
	end
end

script_panel.on_click_stop = function(click_type)
	--lua_app.print(7, "script_panel.on_click_stop ", click_type)
	--lua_app.show_tips("script_panel.on_click_stop")
	script_panel.stop_task()
end

script_panel.on_click_onekey = function(click_type)
	--lua_app.print(7, "script_panel.on_click_onekey ", click_type)
	--lua_app.show_tips("script_panel.on_click_onekey")
	script_panel.click_btn_effect(script_panel.onekeyBtn, onekeyMgr.new())
	lua_app.task_type = "一条龙"
	lua_app.print(7, "lua_app.task_type = ", lua_app.task_type)
	--[[
	local entitys = scene.get_all_actor()
	for i, entityId in pairs(entitys) do
		local entity = scene.get_entity(entityId)
		local name = entity:get_prop_string(1) --key = 1
		lua_app.print(11, "entityId ", i, entityId, name)
	end
	]]
end

script_panel.on_click_thousand_year = function(click_type)	
	script_panel.click_btn_effect(script_panel.thousandYearBtn, thousandYear.new())

	lua_app.task_type = "千年12"
	lua_app.print(7, "lua_app.task_type = ", lua_app.task_type)
end

script_panel.on_click_fengyao = function(click_type)
	--lua_app.print(7, "script_panel.on_click_fengyao ", click_type)
	--lua_app.show_tips("script_panel.on_click_fengyao")
	script_panel.click_btn_effect(script_panel.fengyaoBtn, FengYao.new())
	lua_app.task_type = "封妖"
	lua_app.print(7, "lua_app.task_type = ", lua_app.task_type)
end

script_panel.on_click_paohuan = function(click_type)
	--lua_app.print(7, "script_panel.on_click_paohuan ", click_type)
	--lua_app.show_tips("script_panel.on_click_paohuan")
	script_panel.click_btn_effect(script_panel.paohuanBtn, PaoHuan.new())
	lua_app.task_type = "跑环"
	lua_app.print(7, "lua_app.task_type = ", lua_app.task_type)
	--[[
	local entitys = scene.get_all_entitys()
	for i, entityId in pairs(entitys) do
		local entity = scene.get_entity(entityId)
		local name = entity:get_prop_string(1) --key = 1
		lua_app.print(13, "entityId ", i, entityId, name)
	end
	]]
end

local modules = {
	"WindowConfig",
	"PropConfig",
	"lua_button1",
	"event",
	"common",
	--"script_panel",
	"task.FengYao",
	"task.PaoHuan",
	"task.battle",
	"task.huanjing",
	"task.menpairuqin",
	"task.clean_item",
	"task.onekey.shimen",
	"task.onekey.baotu",
	"task.onekey.wa_bao_tu",
	"task.onekey.paobiao",
	"task.onekey.guildtask",
	"task.onekey.shilian",
	"task.onekey.paoshang",
	"task.useitemtask",
	"task.onekey.zhenYin",
	"task.onekey.cai_ji",
	"task.onekey.onekeyMgr",

	"task.qiannian",
}

script_panel.on_click_hotfix = function(click_type)
	lua_app.print(7, "开始热更新")
	lua_app.show_tips("开始热更新")
	if script_panel.battle then
		script_panel.battle:destroy()
		script_panel.battle = nil
	end
	if script_panel.useitem_task then
		script_panel.useitem_task:destroy()
		script_panel.useitem_task = nil
	end

	oo.require_module(modules)

	--可能这样才行
	battle = require "task.battle"
	script_panel.battle = battle.new()
	script_panel.battle:start()
	useitemtask = require "task.useitemtask"
	--清理所有的注册事件，重新注册
	eventMgr.events = {}
	eventMgr.subEvent(eventMgr.event.team_invite, script_panel, script_panel.onTeamInvite)
	eventMgr.subEvent(eventMgr.event.begin_da_ti, script_panel, script_panel.onBeginDaTi)
	lua_app.print(7, "结束热更新")
	lua_app.show_tips("结束热更新")
end

script_panel.on_click_player = function(click_type)
	--lua_app.print(7, "script_panel.on_click_player ", click_type)
	--lua_app.show_tips("script_panel.on_click_player")
	--script_panel.click_btn_effect(script_panel.playerBtn)

	local info = {}
	local entityId = scene.get_main_player_entityid()
	local mainplayer = scene.get_entity(entityId)
	info.mapId = mainplayer:get_prop_int(PropConfig.PROP_ENTITY_MAPID)
	info.x = mainplayer:get_prop_int(PropConfig.PROP_ENTITY_POS_X)
	info.y = mainplayer:get_prop_int(PropConfig.PROP_ENTITY_POS_Y)
	info.name = mainplayer:get_prop_string(PropConfig.PROP_ENTITY_NAME)
	info.level = mainplayer:get_prop_int(PropConfig.PROP_ENTITY_LEVEL)
	info.actorId = mainplayer:get_prop_int64(PropConfig.PROP_ACTOR_ACTORID)
	info.jinbi = mainplayer:get_prop_int(PropConfig.PROP_ACTOR_JINBI)
	info.yinbi = mainplayer:get_prop_int(PropConfig.PROP_ACTOR_YINBI)
	info.career = mainplayer:get_prop_int(PropConfig.PROP_ACTOR_CAREER)

	lua_app.print(7, "你是")
	table.print(info, 12)

	--local MSG_CL_LINE_CHANNEL = 18
	--ClientControl.send_chat("逍遥情缘真好玩", MSG_CL_LINE_CHANNEL)

end

script_panel.on_click_useitem = function(click_type)
	--lua_app.print(7, "script_panel.on_click_useitem ", click_type)
	--lua_app.show_tips("script_panel.on_click_useitem")
	--script_panel.click_btn_effect(script_panel.useitemBtn)
	if script_panel.useitem_task then
		script_panel.useitem_task:destroy()
	end
	script_panel.useitem_task = useitemtask.new()
	script_panel.useitem_task:start()
end

script_panel.on_click_show_log = function(click_type)
	lua_app.show_log = true
	lua_app.print(7, "script_panel.on_click_show_log 显示日志")
end

script_panel.on_click_huanjing = function(click_type)
	lua_app.print(7, "script_panel.on_click_huanjing 开始幻境打怪")
	lua_app.show_tips("开始幻境打怪")
	script_panel.click_btn_effect(script_panel.huanjingBtn, huanjing.new())
	lua_app.task_type = "幻境"
	lua_app.print(7, "lua_app.task_type = ", lua_app.task_type)
end

script_panel.on_click_ruqin = function(click_type)
	lua_app.print(7, "script_panel.on_click_ruqin 开始门派入侵打怪")
	lua_app.show_tips("开始门派入侵打怪")
	script_panel.click_btn_effect(script_panel.ruqinBtn, menpairuqin.new())
	lua_app.task_type = "门派入侵"
	lua_app.print(7, "lua_app.task_type = ", lua_app.task_type)
end

script_panel.on_click_auto_battle = function(click_type)
	if lua_app.auto_battle then
		lua_app.auto_battle = false
	else
		lua_app.auto_battle = true
	end
	if lua_app.auto_battle then
		lua_app.print(11, "开启自动自动战斗")
		lua_app.show_tips("开启自动自动战斗")
		script_panel.autoBattleBtn:set_x(181)
	else
		lua_app.print(11, "关闭自动自动战斗")
		lua_app.show_tips("关闭自动自动战斗")
		script_panel.autoBattleBtn:set_x(150)
	end
end

script_panel.on_click_clean_item = function(click_type)
	if script_panel.clean_item_task then
		script_panel.clean_item_task:destroy()
		script_panel.clean_item_task = nil
	end
	script_panel.clean_item_task = clean_item.new()
	script_panel.clean_item_task:start()
	lua_app.print(11, "开始清理物品")
	lua_app.show_tips("开始清理物品")
end

script_panel.on_click_dati = function(click_type)
	if lua_app.auto_dati then
		lua_app.auto_dati = false
	else
		lua_app.auto_dati = true
	end
	if lua_app.auto_dati then
		lua_app.print(11, "开启自动答题")
		lua_app.show_tips("开启自动答题")
		script_panel.datiBtn:set_x(71)
	else
		lua_app.print(11, "关闭自动答题")
		lua_app.show_tips("关闭自动答题")
		script_panel.datiBtn:set_x(40)
	end
	eventMgr.subEvent(eventMgr.event.begin_da_ti, script_panel, script_panel.onBeginDaTi)
end

function script_panel:doDaTi(answer1, answer2)
	lua_app.print(11, "script_panel:doDaTi answer1 ", answer1, answer2)
	lua_app.print(11, "script_panel:doDaTi answer2 ", answer2)
	lua_app.print(11, "script_panel:doDaTi script_panel.answer1 ", script_panel.answer1)
	local MSG_CL_LINE_CHANNEL = 18
	ClientControl.send_chat(script_panel.answer1, MSG_CL_LINE_CHANNEL)
end

function script_panel:onBeginDaTi(answer1, answer2)
	lua_app.print(7, "script_panel:onBeginDaTi ", answer1, answer2)
	script_panel.answer1 = answer1
	script_panel.answer2 = answer2
	if not lua_app.auto_dati then
		lua_app.print(11, "自动答题已关闭")
		return
	end
	local delay = math.random(5000, 10000)
	lua_app.add_timer(delay, "doDaTi", self, answer1, answer2)
end


function script_panel:onTeamInvite(intvitTeamId, inviterName)
	--lua_app.print(10, "script_panel:onTeamInvite ", intvitTeamId, inviterName)
	if common.canAutoAcceptInvite(inviterName) then
		common.teamRespondInvite(intvitTeamId, inviterName)
		--lua_app.print(10, "script_panel:onTeamInvite 1")
	else
		--lua_app.print(10, "script_panel:onTeamInvite 2")
	end
end
--打开仓库
script_panel.open_item_storage = function(click_type)
	itemBag.open_item_storage()
end
--打开房屋仓库
script_panel.open_house_storage = function(click_type)
	itemBag.open_house_storage()
end

lua_app.reg_key_down(string.byte('9'), script_panel.open)
lua_app.reg_key_down(string.byte('0'), script_panel.stop_task)
lua_app.reg_key_down(string.byte('8'), script_panel.open_item_storage)
lua_app.reg_key_down(string.byte('7'), script_panel.open_house_storage)

lua_app.script_panel = script_panel


return script_panel