
local function writeFile(fileName, content)
	local f = assert(io.open(fileName, 'w'))
	f:write(content)
	f:close()
end

local content = ""

for i=0,48 do
	local x = (i%7) * 52 + 5
	local y = math.floor(i/7) * 52 + 2
	content = content .. "<Window Type=\"GameLook/StaticImage\" Name=\"GMLotteryTicketRes/MainGB/LotteryTicket_BG_" .. i .. "\" >\n"
	content = content .. "\t<Property Name=\"UnifiedSize\" Value=\"{{0,48},{0,48}}\" />\n"	
	content = content .. "\t<Property Name=\"UnifiedPosition\" Value=\"{{0," .. x .. "},{0," .. y .. "}}\" />\n"
	content = content .. "\t<Property Name=\"AlwaysOnTop\" Value=\"True\" />\n"   
	content = content .. "\t<Property Name=\"FrameEnabled\" Value=\"False\" />\n"
	content = content .. "\t<Window Type=\"GameLook/StaticImage\" Name=\"GMLotteryTicketRes/MainGB/LotteryTicket_" .. i .. "\" >\n"
	content = content .. "\t\t<Property Name=\"AlwaysOnTop\" Value=\"True\" />\n"
	content = content .. "\t\t<Property Name=\"UnifiedSize\" Value=\"{{0,48},{0,48}}\" />\n"
	content = content .. "\t\t<Property Name=\"UnifiedPosition\" Value=\"{{0,0},{0,0}}\" />\n"
	content = content .. "\t\t<Property Name=\"FrameEnabled\" Value=\"False\" />\n"
	content = content .. "\t</Window>\n"
	content = content .. "</Window>\n"
	
	--[[local x = (i%7) * 62
	local y = math.floor(i/7) * 62
	content = content .. "<Window Type=\"GameLook/StaticImage\" Name=\"SprFstLtyTik/MainGB/LotteryTicket_BG_" .. i .. "\" >\n"
	content = content .. "\t<Property Name=\"UnifiedSize\" Value=\"{{0,58},{0,58}}\" />\n"	
	content = content .. "\t<Property Name=\"UnifiedPosition\" Value=\"{{0," .. x .. "},{0," .. y .. "}}\" />\n"
	content = content .. "\t<Property Name=\"MousePassThroughEnabled\" Value=\"True\" />\n"  
	content = content .. "\t<Property Name=\"AlwaysOnTop\" Value=\"True\" />\n"   
	content = content .. "\t<Property Name=\"FrameEnabled\" Value=\"False\" />\n"
	content = content .. "\t<Window Type=\"GameLook/Button\" Name=\"SprFstLtyTik/MainGB/LotteryTicket_" .. i .. "\" >\n"
	content = content .. "\t\t<Property Name=\"AlwaysOnTop\" Value=\"True\" />\n"
	content = content .. "\t\t<Property Name=\"UnifiedSize\" Value=\"{{0,58},{0,58}}\" />\n"
	content = content .. "\t\t<Property Name=\"UnifiedPosition\" Value=\"{{0,0},{0,0}}\" />\n"
	content = content .. "\t\t<Property Name=\"ClippedByParent\" Value=\"False\" />\n"
	content = content .. "\t\t<Property Name=\"NormalImage\" Value=\"X2_jiemian_1.X2_jiemian_57_01\" />\n"        
	content = content .. "\t\t<Property Name=\"HoverImage\" Value=\"X2_jiemian_1.X2_jiemian_57_02\" />\n"
	content = content .. "\t\t<Property Name=\"PushedImage\" Value=\"X2_jiemian_1.X2_jiemian_57_03\" />\n"
	content = content .. "\t\t<Property Name=\"DisabledImage\" Value=\"X2_jiemian_1.X2_jiemian_57_03\" />\n"	
	content = content .. "\t\t<Window Type=\"GameLook/StaticImage\" Name=\"SprFstLtyTik/MainGB/LotteryTicket_" .. i .. "/Hover\" >\n"
	content = content .. "\t\t\t<Property Name=\"UnifiedSize\" Value=\"{{0,58},{0,58}}\" />\n"
	content = content .. "\t\t\t<Property Name=\"UnifiedPosition\" Value=\"{{0,0},{0,0}}\" />\n"
	content = content .. "\t\t\t<Property Name=\"MousePassThroughEnabled\" Value=\"True\" />\n"  
	content = content .. "\t\t\t<Property Name=\"AlwaysOnTop\" Value=\"True\" />\n"  
	content = content .. "\t\t\t<Property Name=\"FrameEnabled\" Value=\"False\" />\n"  	                    
	content = content .. "\t\t</Window>\n"
	content = content .. "\t\t<Window Type=\"GameLook/StaticImage\" Name=\"SprFstLtyTik/MainGB/LotteryTicket_" .. i .. "/Effect\" >\n"
	content = content .. "\t\t\t<Property Name=\"UnifiedSize\" Value=\"{{0,58},{0,58}}\" />\n"
	content = content .. "\t\t\t<Property Name=\"UnifiedPosition\" Value=\"{{0,0},{0,0}}\" />\n"
	content = content .. "\t\t\t<Property Name=\"MousePassThroughEnabled\" Value=\"True\" />\n"  
	content = content .. "\t\t\t<Property Name=\"AlwaysOnTop\" Value=\"True\" />\n"   
	content = content .. "\t\t\t<Property Name=\"FrameEnabled\" Value=\"False\" />\n"  	                    
	content = content .. "\t\t</Window>\n"
	content = content .. "\t</Window>\n"
	content = content .. "</Window>\n"--]]
end

writeFile("out.layout", content)