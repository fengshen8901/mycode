local lua_app = require "lua_app"


lua_app.print(11, _VERSION)
lua_app.print(11, "hello world")

local a = 1
local b = 2
local c = "���"
lua_app.print(11, "lua_app.print ", a, b, c)

local t = {"a", "b", "c", "����", 1234, 5678, {"��������", "hello world", "����"}}

table.print(t, 12)

PANEL_MGR = {}--��ֹ����gc
local function delay_load()
	lua_app.print(11, "require_logic_file............... start")

	PANEL_MGR.script_panel = require "script_panel"

	lua_app.print(11, "require_logic_file...............end")
end

lua_app.add_timer(1000, delay_load)

lua_app.print(11, "main.lua end")