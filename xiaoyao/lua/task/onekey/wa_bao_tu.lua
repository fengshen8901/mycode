local oo = require "class"
local lua_app = require "lua_app"
local app = require "app"
local scene = require "scene"
local itemBag = require "itemBag"
local ClientControl = require "ClientControl"
local PropConfig = require "PropConfig"
local eventMgr = require "event"
local common = require "common"



local wa_bao_tu = oo.class()


function wa_bao_tu:ctor()
    self.itemId = 1251
end
--判断是否完成了
function wa_bao_tu:is_finish()
    local items = itemBag.get_items(self.itemId)
    --lua_app.print(11, "wa_bao_tu:is_finish 1 ")
    --table.print(items, 11)
    if #items >= 1 then
        return false
    end
    --挖宝完成了
    lua_app.print(11, "挖宝完成了")
    return true
end

function wa_bao_tu:destroy()
    --[[
    eventMgr.unsubEvent(eventMgr.event.open_mutual, self, "onOpenMutual")
    eventMgr.unsubEvent(eventMgr.event.open_mutual, self, "onOpenLingQuMutual")
    eventMgr.unsubEvent(eventMgr.event.patch_end, self, "onPatchEndLingQu")
    eventMgr.unsubEvent(eventMgr.event.patch_end, self, "onPatchEndTrace")
    eventMgr.unsubEvent(eventMgr.event.npcshop_open, self, "onNpcShopOpen")
    eventMgr.unsubEvent(eventMgr.event.giveui_open, self, "onGiveUiOpen")
    eventMgr.unsubEvent(eventMgr.event.pet_trade_open, self, "onPetTradeCenterOpen")
    eventMgr.unsubEvent(eventMgr.event.pet_list_select_open, self, "onPetListSelectOpen")
    local event = eventMgr.makePropEvent(PropConfig.PROP_ENTITY_BATTLESCENEID)
    eventMgr.unsubEvent(event, self, "onBattleSceneIdChange")
    eventMgr.unsubEvent(eventMgr.event.sale_center_open, self, "onSaleCenterOpen")
    eventMgr.unsubEvent(eventMgr.event.shang_hui_open, self, "onShangHuiOpen")
    eventMgr.unsubEvent(eventMgr.event.progress_item_open, self, "onProgressItemOpen")
    ]]
    eventMgr.unsubAllEvent(self)

    if self.work_timer then
		lua_app.del_timer(self.work_timer)
		self.work_timer = nil
	end
end

function wa_bao_tu:start()
    --lua_app.print(7, "wa_bao_tu:start 1 ")
    if self.work_timer then
		lua_app.del_timer(self.work_timer)
		self.work_timer = nil
	end
	self.work_timer = lua_app.add_timer(1000, "onTimer", self)
    itemBag.tidy_bag()
    eventMgr.subEvent(eventMgr.event.progress_item_open, self, "onProgressItemOpen")

end

function wa_bao_tu:onTimer()
	self.work_timer = lua_app.add_timer(1000, "onTimer", self)
	--lua_app.print(7, "wa_bao_tu:onTimer 1 ")

    if self.delay then
        self.delay = self.delay - 1
        if self.delay <= 0 then
            self.delay = nil
        end
        return
    end
    self:logic()

end

function wa_bao_tu:logic()
    if common.InBattle() then
        --lua_app.print(7, "wa_bao_tu:logic InBattle ")
        return
    end
    if ClientControl.is_moving() then
        --lua_app.print(7, "wa_bao_tu:logic is_moving ")
        return
    end
    if not self.itemHandel then
        --lua_app.print(7, "wa_bao_tu:logic 1 ")
        if ClientControl.is_moving() then
            --lua_app.print(7, "wa_bao_tu:is_moving 1 ")
            return
        end
        if common.InBattle() then
            --lua_app.print(7, "wa_bao_tu:InBattle 1 ")
            return
        end
        local items = itemBag.get_items(self.itemId)
        --table.print(items, 11)
        if #items >= 1 then
            self.itemHandel = items[1].handel
        end

        if self.itemHandel then
            --lua_app.print(7, "wa_bao_tu:logic self.itemHandel ", self.itemHandel)
            itemBag.use_item(self.itemHandel)
        else
            --挖宝完成了
            --lua_app.print(11, "logic挖宝完成了")
        end
    end

end

function wa_bao_tu:onProgressItemOpen(itemHandel)
    --lua_app.print(7, "wa_bao_tu:onProgressItemOpen ", itemHandel)
    --if self.itemHandel then
        itemBag.click_progress_use()
    --end
    self.itemHandel = nil
    self.delay = 5
end


return wa_bao_tu