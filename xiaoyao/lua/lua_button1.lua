local oo = require "class"
local lua_app = require "lua_app"


local lua_btn = oo.class()

function lua_btn:ctor()
	self.x = 0
	self.y = 0
end

function lua_btn:create(rootwin, text, x, y)
	self.window = rootwin:create_child_window("GameLook/Button")
	self.window:set_property("Font", "Font3")
	--self.window:set_property("Text", "按钮") 这个不合适，编码转换麻烦
	--self.window:set_text("按钮")
	self.window:set_text(text)
	self.window:set_property("HoverImage", "X2_jiemian_5.X2_jiemian_73_02")
	self.window:set_property("NormalImage", "X2_jiemian_5.X2_jiemian_73_01")
	self.window:set_property("PushedImage", "X2_jiemian_5.X2_jiemian_73_03")
	self.window:set_property("DisabledImage", "X2_jiemian_5.X2_jiemian_73_01")
	self.window:set_property("UnifiedSize", "{{0,63},{0,32}}")
	self.window:set_property("HoverTextColour", "FFC6F2FD")
	self.window:set_property("NormalTextColour", "FFC6F2FD")
	self.window:set_property("PushedTextColour", "FFC6F2FD")
	self.window:set_property("DisabledTextColour", "FFC6F2FD")

	self.x = x
	self.y = y
	self:update_pos()
end

function lua_btn:update_pos()
	local str = string.format("{{0,%d},{0,%d}}", self.x, self.y)
	self.window:set_property("UnifiedPosition", str)
end

function lua_btn:set_x(x)
	self.x = x
	self:update_pos()
end

function lua_btn:set_y(y)
	self.y = y
	self:update_pos()
end

function lua_btn:sub_click_event(func)
	if type(func) ~= "function" then
		lua_app.print(12, debug.traceback())
		return
	end
	self.window:sub_click_event(func)
end





return lua_btn