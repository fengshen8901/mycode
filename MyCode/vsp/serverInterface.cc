/*
** Lua binding: MyCode
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
int  tolua_MyCode_open (lua_State* tolua_S);

#include "../StdAfx.h"
#include "../MyLuaExport.h"
#include "../tclass.h"

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_Tst_C (lua_State* tolua_S)
{
 Tst_C* self = (Tst_C*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_Tst_A__Tst_BB (lua_State* tolua_S)
{
 Tst_A::Tst_BB* self = (Tst_A::Tst_BB*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_Tst_A (lua_State* tolua_S)
{
 Tst_A* self = (Tst_A*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_D (lua_State* tolua_S)
{
 D* self = (D*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_Tst_B (lua_State* tolua_S)
{
 Tst_B* self = (Tst_B*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_Tst_A__Tst_AA (lua_State* tolua_S)
{
 Tst_A::Tst_AA* self = (Tst_A::Tst_AA*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"Tst_C");
 tolua_usertype(tolua_S,"Tst_A::Tst_BB");
 tolua_usertype(tolua_S,"Tst_A");
 tolua_usertype(tolua_S,"D");
 tolua_usertype(tolua_S,"Tst_B");
 tolua_usertype(tolua_S,"Tst_A::Tst_AA");
}

/* function: System::Add */
#ifndef TOLUA_DISABLE_tolua_MyCode_System_Add00
static int tolua_MyCode_System_Add00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int a = ((int)  tolua_tonumber(tolua_S,1,0));
  int b = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   int tolua_ret = (int)  System::Add(a,b);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'Add'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: last of class  Tst_A */
#ifndef TOLUA_DISABLE_tolua_get_Tst_A_last_ptr
static int tolua_get_Tst_A_last_ptr(lua_State* tolua_S)
{
  tolua_pushusertype(tolua_S,(void*)Tst_A::last,"Tst_A");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: last of class  Tst_A */
#ifndef TOLUA_DISABLE_tolua_set_Tst_A_last_ptr
static int tolua_set_Tst_A_last_ptr(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!tolua_isusertype(tolua_S,2,"Tst_A",0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  Tst_A::last = ((Tst_A*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Tst_A */
#ifndef TOLUA_DISABLE_tolua_MyCode_A_new00
static int tolua_MyCode_A_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Tst_A",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Tst_A* tolua_ret = (Tst_A*)  new Tst_A();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"Tst_A");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Tst_A */
#ifndef TOLUA_DISABLE_tolua_MyCode_A_new00_local
static int tolua_MyCode_A_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Tst_A",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Tst_A* tolua_ret = (Tst_A*)  new Tst_A();
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"Tst_A");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: a of class  Tst_A */
#ifndef TOLUA_DISABLE_tolua_MyCode_A_a00
static int tolua_MyCode_A_a00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Tst_A",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Tst_A* self = (Tst_A*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in function 'a'",NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->a();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'a'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Tst_AA */
#ifndef TOLUA_DISABLE_tolua_MyCode_A_AA_new00
static int tolua_MyCode_A_AA_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Tst_A::Tst_AA",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Tst_A::Tst_AA* tolua_ret = (Tst_A::Tst_AA*)  new Tst_A::Tst_AA();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"Tst_A::Tst_AA");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Tst_AA */
#ifndef TOLUA_DISABLE_tolua_MyCode_A_AA_new00_local
static int tolua_MyCode_A_AA_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Tst_A::Tst_AA",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Tst_A::Tst_AA* tolua_ret = (Tst_A::Tst_AA*)  new Tst_A::Tst_AA();
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"Tst_A::Tst_AA");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  Tst_AA */
#ifndef TOLUA_DISABLE_tolua_MyCode_A_AA_delete00
static int tolua_MyCode_A_AA_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Tst_A::Tst_AA",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Tst_A::Tst_AA* self = (Tst_A::Tst_AA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in function 'delete'",NULL);
#endif
  delete self;
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: aa of class  Tst_AA */
#ifndef TOLUA_DISABLE_tolua_MyCode_A_AA_aa00
static int tolua_MyCode_A_AA_aa00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Tst_A::Tst_AA",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Tst_A::Tst_AA* self = (Tst_A::Tst_AA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in function 'aa'",NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->aa();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'aa'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Tst_BB */
#ifndef TOLUA_DISABLE_tolua_MyCode_A_BB_new00
static int tolua_MyCode_A_BB_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Tst_A::Tst_BB",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Tst_A::Tst_BB* tolua_ret = (Tst_A::Tst_BB*)  new Tst_A::Tst_BB();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"Tst_A::Tst_BB");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Tst_BB */
#ifndef TOLUA_DISABLE_tolua_MyCode_A_BB_new00_local
static int tolua_MyCode_A_BB_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Tst_A::Tst_BB",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Tst_A::Tst_BB* tolua_ret = (Tst_A::Tst_BB*)  new Tst_A::Tst_BB();
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"Tst_A::Tst_BB");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  Tst_BB */
#ifndef TOLUA_DISABLE_tolua_MyCode_A_BB_delete00
static int tolua_MyCode_A_BB_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Tst_A::Tst_BB",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Tst_A::Tst_BB* self = (Tst_A::Tst_BB*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in function 'delete'",NULL);
#endif
  delete self;
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Base of class  Tst_BB */
#ifndef TOLUA_DISABLE_tolua_MyCode_A_BB_Base00
static int tolua_MyCode_A_BB_Base00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Tst_A::Tst_BB",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Tst_A::Tst_BB* self = (Tst_A::Tst_BB*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in function 'Base'",NULL);
#endif
  {
   Tst_A::Tst_AA* tolua_ret = (Tst_A::Tst_AA*)  self->Base();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"Tst_A::Tst_AA");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'Base'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: classname of class  Tst_BB */
#ifndef TOLUA_DISABLE_tolua_MyCode_A_BB_classname00
static int tolua_MyCode_A_BB_classname00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Tst_A::Tst_BB",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Tst_A::Tst_BB* self = (const Tst_A::Tst_BB*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in function 'classname'",NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->classname();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'classname'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: last of class  Tst_B */
#ifndef TOLUA_DISABLE_tolua_get_Tst_B_last_ptr
static int tolua_get_Tst_B_last_ptr(lua_State* tolua_S)
{
  tolua_pushusertype(tolua_S,(void*)Tst_B::last,"Tst_B");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: last of class  Tst_B */
#ifndef TOLUA_DISABLE_tolua_set_Tst_B_last_ptr
static int tolua_set_Tst_B_last_ptr(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!tolua_isusertype(tolua_S,2,"Tst_B",0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  Tst_B::last = ((Tst_B*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Tst_B */
#ifndef TOLUA_DISABLE_tolua_MyCode_B_new00
static int tolua_MyCode_B_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Tst_B",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Tst_B* tolua_ret = (Tst_B*)  new Tst_B();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"Tst_B");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Tst_B */
#ifndef TOLUA_DISABLE_tolua_MyCode_B_new00_local
static int tolua_MyCode_B_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Tst_B",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Tst_B* tolua_ret = (Tst_B*)  new Tst_B();
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"Tst_B");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: b of class  Tst_B */
#ifndef TOLUA_DISABLE_tolua_MyCode_B_b00
static int tolua_MyCode_B_b00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Tst_B",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Tst_B* self = (Tst_B*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in function 'b'",NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->b();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'b'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: last of class  Tst_C */
#ifndef TOLUA_DISABLE_tolua_get_Tst_C_last_ptr
static int tolua_get_Tst_C_last_ptr(lua_State* tolua_S)
{
  tolua_pushusertype(tolua_S,(void*)Tst_C::last,"Tst_C");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: last of class  Tst_C */
#ifndef TOLUA_DISABLE_tolua_set_Tst_C_last_ptr
static int tolua_set_Tst_C_last_ptr(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!tolua_isusertype(tolua_S,2,"Tst_C",0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  Tst_C::last = ((Tst_C*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Tst_C */
#ifndef TOLUA_DISABLE_tolua_MyCode_luaC_new00
static int tolua_MyCode_luaC_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Tst_C",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int n = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   Tst_C* tolua_ret = (Tst_C*)  new Tst_C(n);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"Tst_C");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Tst_C */
#ifndef TOLUA_DISABLE_tolua_MyCode_luaC_new00_local
static int tolua_MyCode_luaC_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Tst_C",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int n = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   Tst_C* tolua_ret = (Tst_C*)  new Tst_C(n);
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"Tst_C");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  Tst_C */
#ifndef TOLUA_DISABLE_tolua_MyCode_luaC_delete00
static int tolua_MyCode_luaC_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Tst_C",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Tst_C* self = (Tst_C*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in function 'delete'",NULL);
#endif
  delete self;
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: c of class  Tst_C */
#ifndef TOLUA_DISABLE_tolua_MyCode_luaC_c00
static int tolua_MyCode_luaC_c00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Tst_C",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Tst_C* self = (Tst_C*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in function 'c'",NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->c();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'c'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  D */
#ifndef TOLUA_DISABLE_tolua_MyCode_D_delete00
static int tolua_MyCode_D_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"D",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  D* self = (D*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in function 'delete'",NULL);
#endif
  delete self;
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  D */
#ifndef TOLUA_DISABLE_tolua_MyCode_D_new00
static int tolua_MyCode_D_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"D",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   D* tolua_ret = (D*)  new D();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"D");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  D */
#ifndef TOLUA_DISABLE_tolua_MyCode_D_new00_local
static int tolua_MyCode_D_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"D",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   D* tolua_ret = (D*)  new D();
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"D");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Tst_create_aa */
#ifndef TOLUA_DISABLE_tolua_MyCode_create_aa00
static int tolua_MyCode_create_aa00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Tst_A::Tst_AA* tolua_ret = (Tst_A::Tst_AA*)  Tst_create_aa();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"Tst_A::Tst_AA");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'create_aa'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Tst_is_aa */
#ifndef TOLUA_DISABLE_tolua_MyCode_is_aa00
static int tolua_MyCode_is_aa00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Tst_A::Tst_AA",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Tst_A::Tst_AA* obj = ((Tst_A::Tst_AA*)  tolua_tousertype(tolua_S,1,0));
  {
   bool tolua_ret = (bool)  Tst_is_aa(obj);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'is_aa'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
int tolua_MyCode_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_module(tolua_S,(char*)"System",0);
  tolua_beginmodule(tolua_S,(char*)"System");
   tolua_function(tolua_S,(char*)"Add",tolua_MyCode_System_Add00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"A","Tst_A","",tolua_collect_Tst_A);
  #else
  tolua_cclass(tolua_S,"A","Tst_A","",NULL);
  #endif
  tolua_beginmodule(tolua_S,(char*)"A");
   tolua_variable(tolua_S,"last",tolua_get_Tst_A_last_ptr,tolua_set_Tst_A_last_ptr);
   tolua_function(tolua_S,(char*)"new",tolua_MyCode_A_new00);
   tolua_function(tolua_S,(char*)"new_local",tolua_MyCode_A_new00_local);
   tolua_function(tolua_S,".call",tolua_MyCode_A_new00_local);
   tolua_function(tolua_S,(char*)"a",tolua_MyCode_A_a00);
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"AA","Tst_A::Tst_AA","",tolua_collect_Tst_A__Tst_AA);
   #else
   tolua_cclass(tolua_S,"AA","Tst_A::Tst_AA","",NULL);
   #endif
   tolua_beginmodule(tolua_S,(char*)"AA");
    tolua_function(tolua_S,(char*)"new",tolua_MyCode_A_AA_new00);
    tolua_function(tolua_S,(char*)"new_local",tolua_MyCode_A_AA_new00_local);
    tolua_function(tolua_S,".call",tolua_MyCode_A_AA_new00_local);
    tolua_function(tolua_S,(char*)"delete",tolua_MyCode_A_AA_delete00);
    tolua_function(tolua_S,(char*)"aa",tolua_MyCode_A_AA_aa00);
   tolua_endmodule(tolua_S);
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"BB","Tst_A::Tst_BB","Tst_A::Tst_AA",tolua_collect_Tst_A__Tst_BB);
   #else
   tolua_cclass(tolua_S,"BB","Tst_A::Tst_BB","Tst_A::Tst_AA",NULL);
   #endif
   tolua_beginmodule(tolua_S,(char*)"BB");
    tolua_function(tolua_S,(char*)"new",tolua_MyCode_A_BB_new00);
    tolua_function(tolua_S,(char*)"new_local",tolua_MyCode_A_BB_new00_local);
    tolua_function(tolua_S,".call",tolua_MyCode_A_BB_new00_local);
    tolua_function(tolua_S,(char*)"delete",tolua_MyCode_A_BB_delete00);
    tolua_function(tolua_S,(char*)"Base",tolua_MyCode_A_BB_Base00);
    tolua_function(tolua_S,(char*)"classname",tolua_MyCode_A_BB_classname00);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"B","Tst_B","Tst_A",tolua_collect_Tst_B);
  #else
  tolua_cclass(tolua_S,"B","Tst_B","Tst_A",NULL);
  #endif
  tolua_beginmodule(tolua_S,(char*)"B");
   tolua_variable(tolua_S,"last",tolua_get_Tst_B_last_ptr,tolua_set_Tst_B_last_ptr);
   tolua_function(tolua_S,(char*)"new",tolua_MyCode_B_new00);
   tolua_function(tolua_S,(char*)"new_local",tolua_MyCode_B_new00_local);
   tolua_function(tolua_S,".call",tolua_MyCode_B_new00_local);
   tolua_function(tolua_S,(char*)"b",tolua_MyCode_B_b00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"luaC","Tst_C","Tst_B",tolua_collect_Tst_C);
  #else
  tolua_cclass(tolua_S,"luaC","Tst_C","Tst_B",NULL);
  #endif
  tolua_beginmodule(tolua_S,(char*)"luaC");
   tolua_variable(tolua_S,"last",tolua_get_Tst_C_last_ptr,tolua_set_Tst_C_last_ptr);
   tolua_function(tolua_S,(char*)"new",tolua_MyCode_luaC_new00);
   tolua_function(tolua_S,(char*)"new_local",tolua_MyCode_luaC_new00_local);
   tolua_function(tolua_S,".call",tolua_MyCode_luaC_new00_local);
   tolua_function(tolua_S,(char*)"delete",tolua_MyCode_luaC_delete00);
   tolua_function(tolua_S,(char*)"c",tolua_MyCode_luaC_c00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"D","D","",tolua_collect_D);
  #else
  tolua_cclass(tolua_S,"D","D","",NULL);
  #endif
  tolua_beginmodule(tolua_S,(char*)"D");
   tolua_function(tolua_S,(char*)"delete",tolua_MyCode_D_delete00);
   tolua_function(tolua_S,(char*)"new",tolua_MyCode_D_new00);
   tolua_function(tolua_S,(char*)"new_local",tolua_MyCode_D_new00_local);
   tolua_function(tolua_S,".call",tolua_MyCode_D_new00_local);
  tolua_endmodule(tolua_S);
  tolua_function(tolua_S,(char*)"create_aa",tolua_MyCode_create_aa00);
  tolua_function(tolua_S,(char*)"is_aa",tolua_MyCode_is_aa00);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 int luaopen_MyCode (lua_State* tolua_S) {
 return tolua_MyCode_open(tolua_S);
};
#endif

