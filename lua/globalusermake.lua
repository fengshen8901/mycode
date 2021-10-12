
local f = nil

function w(data)
	if f ~= nil then
		f:write(data)
	end
end

function init()
	local path = string.format("createglobaluser.sql")
	return io.open(path, "w")
end

f = init(s)
for s=0, 99 do
	local tbl = string.format("globaluser_%s", s)
	w("DROP TABLE IF EXISTS `" .. tbl .. "`;\n")
	w("CREATE TABLE `" .. tbl .. "` (\n")
	w("`userid`  int(10) UNSIGNED NOT NULL COMMENT '用户唯一id' ,\n")
	w("`account`  varchar(64) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '用户帐户的字符串' ,\n")
	w("`passwd`  varchar(32) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '玩家的密码' ,\n")
	w("`identity`  varchar(32) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '玩家的身份证号码' ,\n")
	w("`createtime`  datetime NULL DEFAULT NULL COMMENT '帐号的创建时间' ,\n")
	w("`updatetime`  datetime NULL DEFAULT NULL COMMENT '上次登录时间' ,\n")
	w("`updateip`  bigint(20) NULL DEFAULT NULL COMMENT '用户上次登录的ip地址，64位整形ip地址，支持ipv6' ,\n")
	w("`ipstr`  varchar(128) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '用户上次登录的ip地址' ,\n")	
	w("`gmlevel`  int(11) NULL DEFAULT 0 COMMENT '玩家的gm等级，普通玩家是0.gm等级越高表示权限越高。1-10级gm' ,\n")
	w("`pwtime`  bigint(20) NULL DEFAULT 0 COMMENT '密码的有效时间，使用的是unix的时间戳，这里记录的是密码创建的时间' ,\n")
	w("`closed`  int(11) NULL DEFAULT 0 COMMENT '用户是否被关闭，0否，1被关闭' ,\n")
	w("`closedtime`  datetime NULL DEFAULT NULL COMMENT '封禁结束时间' ,\n")
	w("`openkey`  varchar(64) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL ,\n")
	w("`pfkey`  varchar(64) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL ,\n")
	w("`manyouid`  varchar(64) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL ,\n")
	w("`pf`  varchar(64) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL ,\n")
	w("PRIMARY KEY (`userid`)\n")
	w(")\n")
	w("ENGINE=MyISAM\n")
	w("DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci\n")
	w("COMMENT='账号表'\n")
	w("\n")
	w(";\n")
	w("# ------------\n")
end